#pragma once
#include "BitArray.h"
#include "HeapManagerProxy.h"
class FixedSizeAllocator
{
public:
	static FixedSizeAllocator* Create(size_t i_blockSize, size_t i_blockCount, HeapManager* i_pHeap);
	~FixedSizeAllocator();
	void* alloc(size_t i_size);
	void free(void* const i_ptr);
	size_t getBlockSize();
private:
	size_t blockSize;
	BitArray* bitArray;
};

