#include "MemorySystem.h"
#include "../Mallocate/HeapManagerProxy.h"
#include "../Mallocate/FixedSizeAllocator.h"

HeapManager* heap = nullptr;
FixedSizeAllocator* allFSAs[3];
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory)
{

	// create your HeapManager and FixedSizeAllocators
	heap = HeapManagerProxy::CreateHeapManager(i_pHeapMemory, i_sizeHeapMemory);
	allFSAs[0] = (FixedSizeAllocator::Create(16, 100, heap));
	allFSAs[1] = (FixedSizeAllocator::Create(32, 200, heap));
	allFSAs[2] = (FixedSizeAllocator::Create(96, 400, heap));


	return true;
}

void Collect()
{
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
}

void DestroyMemorySystem()
{
	delete allFSAs[2];
	delete allFSAs[1];
	delete allFSAs[0];
	HeapManagerProxy::Destroy();
	// Destroy your HeapManager and FixedSizeAllocators
}

