#pragma once
class BitArray;
class HeapManager;
class FixedSizeAllocator
{
public:
	static FixedSizeAllocator* Create(size_t i_blockSize, size_t i_blockCount, HeapManager* i_pHeap);
	~FixedSizeAllocator();
	FixedSizeAllocator(const FixedSizeAllocator& i_other) = delete;
	FixedSizeAllocator& operator=(const FixedSizeAllocator& i_other) = delete;

	void* alloc();
	bool free(void* const i_ptr);
	size_t getBlockSize();
private:
	inline void memsetPattern(const size_t i_blockSize, const void* i_pointer, const int i_pattern);
	size_t blockSize;
	size_t blockCount;
	void* userBlock;
	BitArray* bitArray;
};

#include "FixedSizeAllocator-inl.h"