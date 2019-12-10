#pragma once
class HeapManager
{
public:
	static HeapManager* Create(void* const i_pMemory, const size_t i_sizeMemory);
	~HeapManager();
	HeapManager(const HeapManager& i_other) = delete;
	HeapManager& operator=(const HeapManager& i_other) = delete;

	void* alloc(HeapManager* const i_pManager, const size_t i_size);
	void* alloc(HeapManager* const i_pManager, const size_t i_size, const unsigned int i_alignment);

	bool free(HeapManager* const i_pManager, void* const i_ptr);
	void Collect(HeapManager* const i_pManager);
	bool Contains(const HeapManager* const i_pManager, void* const i_ptr) const;
	bool IsAllocated(const HeapManager* const i_pManager, void* const i_ptr) const;
	size_t GetLargestFreeBlock(const HeapManager* const i_pManager) const;
	size_t GetTotalFreeMemory(const HeapManager* const i_pManager) const;
	void ShowFreeBlocks(const HeapManager* const i_pManager) const;
	void ShowOutstandingAllocations(const HeapManager* const i_pManager) const;

private:
	void CollectHelper(HeapManager* const i_pManager);
	HeapManager* nextBlock;
	HeapManager* prevBlock;
	void* userPointer;
	size_t			sizeOf;
	bool			isAllocated = false;

};

