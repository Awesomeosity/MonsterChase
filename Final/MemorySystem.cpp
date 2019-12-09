#include "MemorySystem.h"
#include "../Mallocate/HeapManagerProxy.h"
#include "../Mallocate/FixedSizeAllocator.h"
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager and FixedSizeAllocators
	HeapManager* currHeap = HeapManagerProxy::CreateHeapManager(i_pHeapMemory, i_sizeHeapMemory);

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

