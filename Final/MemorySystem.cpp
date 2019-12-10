#include "MemorySystem.h"
#include "../Mallocate/HeapManagerProxy.h"
#include "../Mallocate/FixedSizeAllocator.h"

HeapManager* heap;
std::vector<FixedSizeAllocator*> allFSAs;
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager and FixedSizeAllocators
	heap = HeapManagerProxy::CreateHeapManager(i_pHeapMemory, i_sizeHeapMemory);
	allFSAs.push_back(FixedSizeAllocator::Create(16, 100, heap));
	allFSAs.push_back(FixedSizeAllocator::Create(32, 200, heap));
	allFSAs.push_back(FixedSizeAllocator::Create(96, 400, heap));


	return true;
}

void Collect()
{
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	
	// Destroy your HeapManager and FixedSizeAllocators
}

