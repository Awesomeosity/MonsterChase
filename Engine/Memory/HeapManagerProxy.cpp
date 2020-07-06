#include "HeapManager.h"
#include "HeapManagerProxy.h"
#include <iostream>

HeapManager* HeapManagerProxy::CreateHeapManager(void* const i_pMemory, const size_t i_sizeMemory)
{
	return HeapManager::Create(i_pMemory, i_sizeMemory);
}

void HeapManagerProxy::Destroy()
{
	return;
}

void* HeapManagerProxy::alloc(HeapManager* const i_pManager, const size_t i_size)
{
	return i_pManager->alloc(i_pManager, i_size);
}

void* HeapManagerProxy::alloc(HeapManager* const i_pManager, const size_t i_size, const unsigned int i_alignment)
{
	return i_pManager->alloc(i_pManager, i_size, i_alignment);
}

bool HeapManagerProxy::free(HeapManager* const i_pManager, void* const i_ptr)
{
	return i_pManager->free(i_pManager, i_ptr);
}
void HeapManagerProxy::Collect(HeapManager* const i_pManager)
{
	i_pManager->Collect(i_pManager);
}

bool HeapManagerProxy::Contains(const HeapManager* const i_pManager, void* const i_ptr)
{
	return i_pManager->Contains(i_pManager, i_ptr);
}

bool HeapManagerProxy::IsAllocated(const HeapManager* const i_pManager, void* const i_ptr)
{
	return i_pManager->IsAllocated(i_pManager, i_ptr);
}

size_t HeapManagerProxy::GetLargestFreeBlock(const HeapManager* const i_pManager)
{
	return i_pManager->GetLargestFreeBlock(i_pManager);
}

size_t HeapManagerProxy::GetTotalFreeMemory(const HeapManager* const i_pManager)
{
	return i_pManager->GetTotalFreeMemory(i_pManager);
}

void HeapManagerProxy::ShowFreeBlocks(const HeapManager* const i_pManager)
{
	i_pManager->ShowFreeBlocks(i_pManager);
}

void HeapManagerProxy::ShowOutstandingAllocations(const HeapManager* const i_pManager)
{
	i_pManager->ShowOutstandingAllocations(i_pManager);
}

