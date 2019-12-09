#include "FixedSizeAllocator.h"
#include "HeapManagerProxy.h"
#include "BitArray.h"
#include <cassert>
FixedSizeAllocator* FixedSizeAllocator::Create(size_t i_blockSize, size_t i_blockCount, HeapManager* i_pHeap)
{
	assert(i_blockSize % 2 == 0);
	size_t guardBandSize = 4;
	static const int fillValue = 0xDD;
	static const int guardBandValue = 0xFD;

	//Request allocation of size equal to that of each (block size + guard band size) * block count
	size_t totalAllocSize = sizeof(FixedSizeAllocator) + (i_blockSize + guardBandSize) * i_blockCount;
	FixedSizeAllocator* newAlloc = reinterpret_cast<FixedSizeAllocator*>(HeapManagerProxy::alloc(i_pHeap, totalAllocSize));
	newAlloc->blockSize = i_blockSize;
	newAlloc->bitArray = BitArray::Create(i_blockCount, i_pHeap);
	newAlloc->userBlock = reinterpret_cast<void*>(newAlloc + 1);

	//Set up user blocks with fill values and guardbands
	char* currPointer = reinterpret_cast<char*>(newAlloc->userBlock);
	for (size_t i = 0; i < i_blockCount; i++)
	{
		newAlloc->memsetPattern(i_blockSize, currPointer, fillValue);
		currPointer += i_blockSize;
		newAlloc->memsetPattern(guardBandSize, currPointer, guardBandValue);
		currPointer += guardBandSize;
	}

	return newAlloc;
}

FixedSizeAllocator::~FixedSizeAllocator()
{
	
}

void* FixedSizeAllocator::alloc()
{
	size_t bitNumber = 0;
	if (!bitArray->GetFirstClearBit(bitNumber))
	{
		return nullptr;
	}

	size_t totalBlockSize = blockSize + guardBandSize;
	char* resultPointer = reinterpret_cast<char*>(userBlock) + totalBlockSize * bitNumber;
	bitArray->SetBit(bitNumber);
	return reinterpret_cast<void*>(resultPointer);
}

void FixedSizeAllocator::free(void* const i_ptr)
{
	static const int fillValue = 0xDD;
	char* passedPointer = reinterpret_cast<char*>(i_ptr);
	ptrdiff_t result = passedPointer - reinterpret_cast<char*>(userBlock);
	if (result < 0)
	{
		return;
	}

	size_t totalBlockSize = blockSize + guardBandSize;
	if (result % totalBlockSize != 0)
	{
		return;
	}

	size_t bitRef = result / totalBlockSize;
	if (bitArray->IsBitSet(bitRef))
	{
		bitArray->ClearBit(bitRef);
		memsetPattern(blockSize, i_ptr, fillValue);
	}
}

size_t FixedSizeAllocator::getBlockSize()
{
	return blockSize;
}