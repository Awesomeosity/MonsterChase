#include "HeapManagerProxy.h"
#include <heapapi.h>
#include <iostream>

class HeapManager {
public:
	HeapManager* nextBlock;
	HeapManager* prevBlock;
	size_t sizeOf;
	bool isAllocated = false;
};

HeapManager* HeapManagerProxy::CreateHeapManager(void* i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	HeapManager* currMem = (HeapManager*)i_pMemory;
	size_t initMem = i_sizeMemory - sizeof(HeapManager);
	currMem->prevBlock = nullptr;
	currMem->nextBlock = nullptr;
	currMem->sizeOf = initMem;
	currMem->isAllocated = false;
	return currMem;
}

void HeapManagerProxy::Destroy(HeapManager* i_pManager)
{

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

	HeapManager* lastBlock = currBlock->prevBlock;
	HeapManager* nextBlock = currBlock->nextBlock;
	currBlock->isAllocated = true;
	size_t targSize = i_size + i_size % 4;
	
	//If allocating this block wouldn't leave enough size for another HeapManager, allocate the whole block.
	//In this case, we don't need to update the back and next links.

	//Otherwise we have to set the size of the currBlock to the user-block, and update the links
	if (currBlock->sizeOf - targSize > sizeof(HeapManager) + 4) //Might need to change this later to account for padding and such
	{
		size_t prevSize = currBlock->sizeOf;
		currBlock->sizeOf = targSize;
		prevSize -= targSize;

		//Need to perform pointer arithmetic to get to where the new Manager will be setup.
		char* newManagerLocation = (char*)currBlock + targSize;
		HeapManager* newManager = (HeapManager*)newManagerLocation;
		newManager->prevBlock = currBlock;
		newManager->nextBlock = nextBlock;
		newManager->sizeOf = prevSize - sizeof(HeapManager);
		newManager->isAllocated = false;

		currBlock->nextBlock = newManager;
		nextBlock->prevBlock = newManager;
	}
	
	void* userPointer = (void*)(currBlock + 1);
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

	HeapManager* lastBlock = currBlock->prevBlock;
	HeapManager* nextBlock = currBlock->nextBlock;
	currBlock->isAllocated = true;
	size_t targSize = i_size + i_size % i_alignment;

	//If allocating this block wouldn't leave enough size for another HeapManager, allocate the whole block.
	//In this case, we don't need to update the back and next links.

	//Otherwise we have to set the size of the currBlock to the user-block, and update the links
	if (currBlock->sizeOf - targSize > sizeof(HeapManager) + i_alignment) //Might need to change this later to account for padding and such
	{
		size_t prevSize = currBlock->sizeOf;
		currBlock->sizeOf = targSize;
		prevSize -= targSize;

		//Need to perform pointer arithmetic to get to where the new Manager will be setup.
		char* newManagerLocation = (char*)currBlock + targSize;
		HeapManager* newManager = (HeapManager*)newManagerLocation;
		newManager->prevBlock = currBlock;
		newManager->nextBlock = nextBlock;
		newManager->sizeOf = prevSize - sizeof(HeapManager);
		newManager->isAllocated = false;

		currBlock->nextBlock = newManager;
		nextBlock->prevBlock = newManager;
	}

	void* userPointer = (void*)(currBlock + 1);
	return userPointer;
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

bool HeapManagerProxy::IsAllocated(const HeapManager* i_pManager, void* i_ptr)
{
	HeapManager* thisBlock = (HeapManager*)i_ptr;
	thisBlock--;
	return thisBlock->isAllocated;
}

size_t HeapManagerProxy::GetLargestFreeBlock(const HeapManager* i_pManager)
{
	const HeapManager* currP = i_pManager;
	size_t largest = 0;
	if (currP = nullptr)
	{
		return size_t(0);
	}
	while (currP->nextBlock != nullptr)
	{
		if (currP->sizeOf > largest && !currP->isAllocated)
		{
			largest = currP->sizeOf;
		}
	}
	return largest;
}

size_t HeapManagerProxy::GetTotalFreeMemory(const HeapManager* i_pManager)
{
	const HeapManager* currP = i_pManager;
	size_t total = 0;
	if (currP = nullptr)
	{
		return size_t(0);
	}
	while (currP->nextBlock != nullptr)
	{
		if (!currP->isAllocated)
		{
			total += currP->sizeOf;
		}
	}
	return total;
}

void HeapManagerProxy::ShowFreeBlocks(const HeapManager* i_pManager)
{
	const HeapManager* currP = i_pManager;
	if (currP = nullptr)
	{
		return;
	}
	while (currP->nextBlock != nullptr)
	{
		if (!currP->isAllocated)
		{
			printf("Free Block: %p, Next Block: %p, Previous Block: %p, Space: %zu", currP, currP->nextBlock, currP->prevBlock, currP->sizeOf);
		}
	}
	return;
}

void HeapManagerProxy::ShowOutstandingAllocations(const HeapManager* i_pManager)
{
	const HeapManager* currP = i_pManager;
	if (currP = nullptr)
	{
		return;
	}
	while (currP->nextBlock != nullptr)
	{
		if (currP->isAllocated)
		{
			printf("Allocated Block: %p, Next Block: %p, Previous Block: %p, Space: %zu", currP, currP->nextBlock, currP->prevBlock, currP->sizeOf);
		}
	}
	return;
}

