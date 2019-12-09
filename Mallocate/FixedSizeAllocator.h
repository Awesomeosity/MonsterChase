#pragma once
#include "BitArray.h"
#include "HeapManagerProxy.h"
class FixedSizeAllocator
{
public:
	static FixedSizeAllocator* Create(size_t i_blockSize, size_t i_blockCount, HeapManager* i_pHeap);
	~FixedSizeAllocator();
	void* alloc();
	void free(void* const i_ptr);
	size_t getBlockSize();
private:
	inline void memsetPattern(const size_t i_blockSize, const void* i_pointer, const int i_pattern);
	size_t blockSize;
	void* userBlock;
	BitArray* bitArray;
	const int guardBandSize = 4;
};

#include "FixedSizeAllocator-inl.h"