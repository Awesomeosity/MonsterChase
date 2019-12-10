#include "FixedSizeAllocator.h"
#include "HeapManagerProxy.h"
#include "BitArray.h"
#include <cassert>
#include <iostream>
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
	newAlloc->blockCount = i_blockCount;
	newAlloc->userBlock = reinterpret_cast<void*>(newAlloc + 1);
	newAlloc->bitArray = BitArray::Create(i_blockCount, i_pHeap);

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
#ifdef _DEBUG
	for (size_t i = 0; i < blockCount; i++)
	{
		if ((*bitArray)[i])
		{
			std::cout << "Allocation at " << i << "\n";
		}
	}
#endif
	delete bitArray;
}

void* FixedSizeAllocator::alloc()
{
	size_t bitNumber = 0;
	size_t guardBandSize = 4;
	if (!bitArray->GetFirstClearBit(bitNumber))
	{
		return nullptr;
	}

	size_t totalBlockSize = blockSize + guardBandSize;
	char* resultPointer = reinterpret_cast<char*>(userBlock) + totalBlockSize * bitNumber;
	bitArray->SetBit(bitNumber);
	return reinterpret_cast<void*>(resultPointer);
}

bool FixedSizeAllocator::free(void* const i_ptr)
{
	size_t guardBandSize = 4;
	static const int fillValue = 0xDD;
	char* passedPointer = reinterpret_cast<char*>(i_ptr);

	//Check if the pointer is within our memory
	ptrdiff_t result = passedPointer - reinterpret_cast<char*>(userBlock);
	if (result < 0 || result > static_cast<int>((blockSize + guardBandSize) * blockCount))
	{
		return false;
	}

	//Check to make sure it points to the start of a block
	size_t totalBlockSize = blockSize + guardBandSize;
	if (result % totalBlockSize != 0)
	{
		return false;
	}

	//Finally, check the bitarray, to make sure that it's an allocated block
	size_t bitRef = result / totalBlockSize;
	if (bitArray->IsBitSet(bitRef))
	{
		bitArray->ClearBit(bitRef);
		memsetPattern(blockSize, i_ptr, fillValue);
		return true;
	}

	return false;
}

size_t FixedSizeAllocator::getBlockSize()
{
	return blockSize;
}