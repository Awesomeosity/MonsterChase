#include "HeapManager.h"
#include <cstdint>
#include <stdio.h>

HeapManager* HeapManager::Create(void* const i_pMemory, const size_t i_sizeMemory)
{
	if (i_sizeMemory < sizeof(HeapManager) + sizeof(int) + 4)
	{
		return nullptr;
	}

	HeapManager* currMem = reinterpret_cast<HeapManager*>(i_pMemory);
	size_t initMem = i_sizeMemory - sizeof(HeapManager) - sizeof(int);
	currMem->prevBlock = nullptr;
	currMem->nextBlock = nullptr;
	currMem->userPointer = nullptr;
	currMem->sizeOf = initMem;
	currMem->isAllocated = false;

	//Establishing Guard Band
	char* guardPoint = reinterpret_cast<char*>(currMem + 1);
	guardPoint += initMem;
	int* gp = reinterpret_cast<int*>(guardPoint);
	*gp = 0xFDFDFDFD;

	int* filler = reinterpret_cast<int*>(currMem + 1);
	//Filling internals
	while (initMem > 4)
	{
		*filler = 0xDDDDDDDD;
		filler++;
		initMem -= sizeof(int);
	}

	return currMem;
}

HeapManager::~HeapManager()
{
	return;
}

void* HeapManager::alloc(HeapManager* const i_pManager, const size_t i_size)
{
	const size_t alignment = 4;
	return alloc(i_pManager, i_size, alignment);
}

void* HeapManager::alloc(HeapManager* const i_pManager, const size_t i_size, const unsigned int i_alignment)
{
	if (i_pManager == nullptr)
	{
		return nullptr;
	}

	HeapManager* currBlock = i_pManager;
	while (currBlock->isAllocated || currBlock->sizeOf < i_size)
	{
		//If we get to the end of the chain and fail to allocate, return a nullptr.
		if (currBlock->nextBlock == nullptr)
		{
			return nullptr;
		}
		currBlock = currBlock->nextBlock;
	}

	HeapManager* nextMake = currBlock->nextBlock;
	currBlock->isAllocated = true;
	size_t targSize = i_size + (i_alignment - i_size % i_alignment) % i_alignment;

	char* up = reinterpret_cast<char*>(currBlock + 1);
	up += (i_alignment - reinterpret_cast<uintptr_t>(up) % i_alignment) % i_alignment;
	currBlock->userPointer = reinterpret_cast<void*>(up);

	//If allocating this block wouldn't leave enough size for another HeapManager, allocate the whole block.
	//In this case, we don't need to update the back and next links.

	//Otherwise we have to set the size of the currBlock to the user-block, and update the links
	if (currBlock->sizeOf - targSize > sizeof(HeapManager) + sizeof(int)) //Might need to change this later to account for padding and such
	{
		size_t prevSize = currBlock->sizeOf - targSize - sizeof(HeapManager) - sizeof(int);
		currBlock->sizeOf = targSize;

		//Need to perform pointer arithmetic to get to where the new Manager will be setup.
		char* gp = reinterpret_cast<char*>(currBlock + 1) + targSize;
		int* guardPointer = reinterpret_cast<int*>(gp);
		*guardPointer = 0xFDFDFDFD;

		HeapManager* newManager = reinterpret_cast<HeapManager*>(guardPointer + 1);
		newManager->prevBlock = currBlock;
		newManager->nextBlock = nextMake;
		newManager->userPointer = nullptr;
		newManager->sizeOf = prevSize;
		newManager->isAllocated = false;

		currBlock->nextBlock = newManager;
		if (nextMake != nullptr)
		{
			nextBlock->prevBlock = newManager;
		}
	}

	int* fillPointer = reinterpret_cast<int*>(currBlock + 1);
	while (targSize > 0)
	{
		*fillPointer = 0xCDCDCDCD;
		fillPointer++;
		targSize -= sizeof(int);
	}

	return currBlock->userPointer;

}

bool HeapManager::free(HeapManager* const i_pManager, void* const i_ptr)
{
	if (i_pManager == nullptr)
	{
		return false;
	}

	HeapManager* currManager = i_pManager;
	while (currManager->userPointer != i_ptr)
	{
		if (currManager->nextBlock == nullptr)
		{
			return false;
		}
		currManager = currManager->nextBlock;
	}

	if (currManager->isAllocated)
	{
		currManager->isAllocated = false;
		int* fp = reinterpret_cast<int*>(currManager + 1);
		size_t totalSize = currManager->sizeOf;
		while (totalSize > 0)
		{
			*fp = 0xDDDDDDDD;
			totalSize -= sizeof(int);
		}

		CollectHelper(currManager);
		return true;
	}
	else
	{
		return false;
	}

}

void HeapManager::Collect(HeapManager* const i_pManager)
{
	if (i_pManager == nullptr)
	{
		return;
	}

	HeapManager* currManager = i_pManager;
	while (currManager->nextBlock != nullptr)
	{
		CollectHelper(currManager);
		if (currManager->nextBlock == nullptr)
		{
			return;
		}
		currManager = currManager->nextBlock;
	}
	return;

}

bool HeapManager::Contains(const HeapManager* const i_pManager, void* const i_ptr) const
{
	if (i_pManager == nullptr)
	{
		return false;
	}

	const HeapManager* currP = i_pManager;
	while (currP->userPointer != i_ptr)
	{
		if (currP->nextBlock == nullptr)
		{
			return false;
		}
		currP = currP->nextBlock;
	}

	return true;
}

bool HeapManager::IsAllocated(const HeapManager* const i_pManager, void* const i_ptr) const
{
	if (i_pManager == nullptr)
	{
		return false;
	}

	const HeapManager* curr = i_pManager;
	while (curr->userPointer != i_ptr)
	{
		if (curr->nextBlock == nullptr)
		{
			return false;
		}
		curr = curr->nextBlock;
	}
	return curr->isAllocated;
}

size_t HeapManager::GetLargestFreeBlock(const HeapManager* const i_pManager) const
{
	if (i_pManager == nullptr)
	{
		return size_t(0);
	}

	const HeapManager* currP = i_pManager;
	size_t largest = 0;
	if (currP == nullptr)
	{
		return size_t(0);
	}
	while (currP != nullptr)
	{
		if (currP->sizeOf > largest && !currP->isAllocated)
		{
			largest = currP->sizeOf;
		}
		currP = currP->nextBlock;

	}
	return largest;
}

size_t HeapManager::GetTotalFreeMemory(const HeapManager* const i_pManager) const
{
	if (i_pManager == nullptr)
	{
		return size_t(0);
	}

	const HeapManager* currP = i_pManager;
	size_t total = 0;
	if (currP == nullptr)
	{
		return size_t(0);
	}
	while (currP != nullptr)
	{
		if (!currP->isAllocated)
		{
			total += currP->sizeOf;
		}
		currP = currP->nextBlock;
	}
	return total;
}

void HeapManager::ShowFreeBlocks(const HeapManager* const i_pManager) const
{
	if (i_pManager == nullptr)
	{
		return;
	}

	const HeapManager* currP = i_pManager;
	if (currP == nullptr)
	{
		return;
	}
	while (currP != nullptr)
	{
		if (!currP->isAllocated)
		{
			printf("Free Block: %p, Next Block: %p, Previous Block: %p, Space: %zu, User Pointer: %p\n", currP, currP->nextBlock, currP->prevBlock, currP->sizeOf, currP->userPointer);
		}
		currP = currP->nextBlock;
	}
	return;
}

void HeapManager::ShowOutstandingAllocations(const HeapManager* const i_pManager) const
{
	if (i_pManager == nullptr)
	{
		return;
	}

	const HeapManager* currP = i_pManager;
	if (currP == nullptr)
	{
		return;
	}
	while (currP != nullptr)
	{
		if (currP->isAllocated)
		{
			printf("Allocated Block: %p, Next Block: %p, Previous Block: %p, Space: %zu, User Pointer: %p\n", currP, currP->nextBlock, currP->prevBlock, currP->sizeOf, currP->userPointer);
		}
		currP = currP->nextBlock;

	}
	return;
}

void HeapManager::CollectHelper(HeapManager* const i_pManager)
{
	if (i_pManager == nullptr || i_pManager->isAllocated == true)
	{
		return;
	}

	if (i_pManager->nextBlock != nullptr)
	{
		if (!i_pManager->nextBlock->isAllocated)
		{
			i_pManager->sizeOf += sizeof(int) + sizeof(HeapManager) + i_pManager->nextBlock->sizeOf;
			i_pManager->nextBlock = i_pManager->nextBlock->nextBlock;
			if (i_pManager->nextBlock != nullptr)
			{
				i_pManager->nextBlock->prevBlock = i_pManager;
			}
		}
	}

	if (i_pManager->prevBlock != nullptr)
	{
		if (!i_pManager->prevBlock->isAllocated)
		{
			i_pManager->prevBlock->sizeOf += sizeof(int) + sizeof(HeapManager) + i_pManager->sizeOf;
			i_pManager->prevBlock->nextBlock = i_pManager->nextBlock;
			if (i_pManager->nextBlock != nullptr)
			{
				i_pManager->nextBlock->prevBlock = i_pManager->prevBlock;
			}
		}
	}

}
