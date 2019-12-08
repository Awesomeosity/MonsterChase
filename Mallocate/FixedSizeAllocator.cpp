#include "FixedSizeAllocator.h"
#include "HeapManagerProxy.h"
#include "BitArray.h"
FixedSizeAllocator* FixedSizeAllocator::Create(size_t i_blockSize, size_t i_blockCount, HeapManager* i_pHeap)
{
	//Request allocation of size equal to that of each (block size + guard band size) * block count
	size_t totalAllocSize = sizeof(FixedSizeAllocator) + (i_blockSize + sizeof(int)) * i_blockCount;
	FixedSizeAllocator* newAlloc = reinterpret_cast<FixedSizeAllocator*>(HeapManagerProxy::alloc(i_pHeap, totalAllocSize));
	newAlloc->blockSize = i_blockSize;
	newAlloc->bitArray = BitArray::Create()
	//Must create BitArray outside of this function
	return newAlloc;
}
