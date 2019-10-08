#include "HeapManagerProxy.h"
#include <iostream>

class HeapManager {
public:
	HeapManager* nextBlock;
	HeapManager* prevBlock;
	size_t sizeOf;
	bool isAllocated = false;
};

HeapManager* HeapManagerProxy::CreateHeapManager(void* i_pMemory, size_t i_sizeMemory)
{
	HeapManager* currMem = (HeapManager*)i_pMemory;
	size_t initMem = i_sizeMemory - sizeof(HeapManager) - sizeof(int);
	currMem->prevBlock = nullptr;
	currMem->nextBlock = nullptr;
	currMem->sizeOf = initMem;
	currMem->isAllocated = false;

	//Establishing Guard Band
	char* guardPoint = (char*)(currMem + 1);
	guardPoint += initMem;
	int* gp = (int*)guardPoint;
	*gp = 4261281277;

	int* filler = (int*)(currMem + 1);
	//Filling internals
	while (initMem > 4)
	{
		*filler = 3722304989;
		filler++;
		initMem -= sizeof(int);
	}

	return currMem;
}

void HeapManagerProxy::Destroy()
{
	return;
}

void* HeapManagerProxy::alloc(HeapManager* i_pManager, size_t i_size)
{
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

	HeapManager* nextBlock = currBlock->nextBlock;
	currBlock->isAllocated = true;
	size_t targSize = i_size + (4 - i_size % 4);
	void* userPointer = (void*)((char*)(currBlock + 1) + (4 - i_size % 4));

	//If allocating this block wouldn't leave enough size for another HeapManager, allocate the whole block.
	//In this case, we don't need to update the back and next links.

	//Otherwise we have to set the size of the currBlock to the user-block, and update the links
	if (currBlock->sizeOf - targSize > sizeof(HeapManager) + sizeof(int)) //Might need to change this later to account for padding and such
	{
		size_t prevSize = currBlock->sizeOf - targSize - sizeof(HeapManager) - sizeof(int);
		currBlock->sizeOf = targSize;

		//Need to perform pointer arithmetic to get to where the new Manager will be setup.
		int* guardPointer = (int*)((char*)(currBlock + 1) + targSize);
		*guardPointer = 4261281277; //Should convert into 0xFDFDFDFD?

		HeapManager* newManager = (HeapManager*)(guardPointer + 1);
		newManager->prevBlock = currBlock;
		newManager->nextBlock = nextBlock;
		newManager->sizeOf = prevSize;
		newManager->isAllocated = false;

		currBlock->nextBlock = newManager;
		if (nextBlock != nullptr)
		{
			nextBlock->prevBlock = newManager;
		}
	}

	int* fillPointer = (int*)(currBlock + 1);
	while (targSize > 0)
	{
		*fillPointer = 3452816845;
		fillPointer++;
		targSize -= sizeof(int);
	}

	return userPointer;
}

void* HeapManagerProxy::alloc(HeapManager* i_pManager, size_t i_size, unsigned int i_alignment)
{
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

	HeapManager* nextBlock = currBlock->nextBlock;
	currBlock->isAllocated = true;
	size_t targSize = i_size + (i_alignment - i_size % i_alignment);
	void* userPointer = (void*)((char*)(currBlock + 1) + (i_alignment - i_size % i_alignment));

	//If allocating this block wouldn't leave enough size for another HeapManager, allocate the whole block.
	//In this case, we don't need to update the back and next links.

	//Otherwise we have to set the size of the currBlock to the user-block, and update the links
	if (currBlock->sizeOf - targSize > sizeof(HeapManager) + sizeof(int)) //Might need to change this later to account for padding and such
	{
		size_t prevSize = currBlock->sizeOf - targSize - sizeof(HeapManager) - sizeof(int);
		currBlock->sizeOf = targSize;

		//Need to perform pointer arithmetic to get to where the new Manager will be setup.
		int* guardPointer = (int*)((char*)(currBlock + 1) + targSize);
		*guardPointer = 4261281277; //Should convert into 0xFDFDFDFD?

		HeapManager* newManager = (HeapManager*)(guardPointer + 1);
		newManager->prevBlock = currBlock;
		newManager->nextBlock = nextBlock;
		newManager->sizeOf = prevSize;
		newManager->isAllocated = false;

		currBlock->nextBlock = newManager;
		if (nextBlock != nullptr)
		{
			nextBlock->prevBlock = newManager;
		}
	}

	int* fillPointer = (int*)(currBlock + 1);
	while (targSize > 0)
	{
		*fillPointer = 3452816845;
		fillPointer++;
		targSize -= sizeof(int);
	}

	return userPointer;
}

bool HeapManagerProxy::free(void* i_ptr)
{
	HeapManager* thisBlock = (HeapManager*)i_ptr - 1;
	if (thisBlock->isAllocated)
	{
		thisBlock->isAllocated = false;
		int* fp = (int*)i_ptr;
		size_t totalSize = thisBlock->sizeOf;
		while (totalSize > 0)
		{
			*fp = 3722304989;
			totalSize -= sizeof(int);
		}

		CollectHelper(thisBlock);
		return true;
	}
	else
	{
		return false;
	}
}
void HeapManagerProxy::Collect(HeapManager* i_pManager)
{
	HeapManager* currManager = i_pManager;
	while (currManager->nextBlock != nullptr)
	{
		CollectHelper(currManager);
		if (currManager->nextBlock == nullptr)
		{
			return;
		}
		else
		{
			currManager = currManager->nextBlock;
		}
	}
	return;
}

void HeapManagerProxy::CollectHelper(HeapManager* i_pManager)
{
	if (i_pManager->nextBlock != nullptr)
	{
		if (!i_pManager->nextBlock->isAllocated)
		{
			i_pManager->sizeOf += sizeof(int) + sizeof(HeapManager) + i_pManager->nextBlock->sizeOf;
			i_pManager->nextBlock = i_pManager->nextBlock->nextBlock;
			
		}
	}

	if (i_pManager->prevBlock != nullptr)
	{
		if (!i_pManager->prevBlock->isAllocated)
		{
			i_pManager->prevBlock->sizeOf += sizeof(int) + sizeof(HeapManager) + i_pManager->sizeOf;
			i_pManager->prevBlock->nextBlock = i_pManager->nextBlock;
		}
	}
}

bool HeapManagerProxy::Contains(const HeapManager* i_pManager, void* i_ptr)
{
	const HeapManager* currP = i_pManager;
	while (currP != i_ptr)
	{
		if (currP->nextBlock == nullptr)
		{
			return false;
		}
		currP = currP->nextBlock;
	}

	return true;
}

bool HeapManagerProxy::IsAllocated(void* i_ptr)
{
	HeapManager* thisBlock = (HeapManager*)i_ptr;
	thisBlock--;
	return thisBlock->isAllocated;
}

size_t HeapManagerProxy::GetLargestFreeBlock(const HeapManager* i_pManager)
{
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

size_t HeapManagerProxy::GetTotalFreeMemory(const HeapManager* i_pManager)
{
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

void HeapManagerProxy::ShowFreeBlocks(const HeapManager* i_pManager)
{
	const HeapManager* currP = i_pManager;
	if (currP == nullptr)
	{
		return;
	}
	while (currP != nullptr)
	{
		if (!currP->isAllocated)
		{
			printf("Free Block: %p, Next Block: %p, Previous Block: %p, Space: %zu\n", currP, currP->nextBlock, currP->prevBlock, currP->sizeOf);
		}
		currP = currP->nextBlock;
	}
	return;
}

void HeapManagerProxy::ShowOutstandingAllocations(const HeapManager* i_pManager)
{
	const HeapManager* currP = i_pManager;
	if (currP == nullptr)
	{
		return;
	}
	while (currP != nullptr)
	{
		if (currP->isAllocated)
		{
			printf("Allocated Block: %p, Next Block: %p, Previous Block: %p, Space: %zu\n", currP, currP->nextBlock, currP->prevBlock, currP->sizeOf);
		}
		currP = currP->nextBlock;

	}
	return;
}

