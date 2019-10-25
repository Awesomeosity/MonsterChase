#ifndef __HEAP_MANAGER_PROXY_H
#define __HEAP_MANAGER_PROXY_H

class HeapManager;

namespace HeapManagerProxy
{

	HeapManager*	CreateHeapManager(void* const i_pMemory, const size_t i_sizeMemory);
	void			Destroy();

	void*			alloc(HeapManager* const i_pManager, const size_t i_size);
	void*			alloc(HeapManager* const i_pManager, const size_t i_size, const unsigned int i_alignment);
	bool			free(HeapManager* const i_pManager, void* const i_ptr);

	void			Collect(HeapManager* const i_pManager);
	void			CollectHelper(HeapManager* const i_pManager);

	bool			Contains(const HeapManager* const i_pManager, void* const i_ptr);
	bool			IsAllocated(const HeapManager* const i_pManager, void* const i_ptr);

	size_t			GetLargestFreeBlock(const HeapManager* const i_pManager);
	size_t			GetTotalFreeMemory(const HeapManager* const i_pManager);

	void			ShowFreeBlocks(const HeapManager* const i_pManager);
	void			ShowOutstandingAllocations(const HeapManager* const i_pManager);

} // namespace HeapManagerProxy



#endif // __HEAP_MANAGER_PROXY_H