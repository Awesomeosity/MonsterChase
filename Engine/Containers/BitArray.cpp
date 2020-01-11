#include "BitArray.h"
#include "../Memory/HeapManagerProxy.h"
#include <cstring>
#include <cassert>
#include <intrin.h>
BitArray* BitArray::Create(const size_t i_blockCount, HeapManager* const i_pHeap, const bool i_startClear)
{
	//Provides clarity instead of magic numbers
	//unsigned char across x64/x86 processors should always be 1 byte in size
	const unsigned int byteSize = 1;

	BitArray* bitArray = reinterpret_cast<BitArray*>(HeapManagerProxy::alloc(i_pHeap, i_blockCount + sizeof(BitArray)));
	bitArray->bits = reinterpret_cast<unsigned char*>(bitArray + 1);
	bitArray->count = i_blockCount;

	//Clear/Set array depending on the passed i_startClear
	unsigned char* currPoint = bitArray->bits;
	for (unsigned int i = 0; i < bitArray->count; i++)
	{
		memset(currPoint, i_startClear ? 0 : 1, byteSize);
		currPoint++;
	}

	return bitArray;
}

//Note: Need to free manually from HeapManager due to this free's implementation requiring a starting HeapManager*
BitArray::~BitArray()
{
	bits = nullptr;
	count = 0;
}

void BitArray::ClearAll()
{
	const unsigned int byteSize = 1;
	unsigned char* currPoint = bits;
	for (unsigned int i = 0; i < count; i++)
	{
		memset(currPoint, 0, byteSize);
		currPoint++;
	}
}

void BitArray::SetAll()
{
	const unsigned int byteSize = 1;
	unsigned char* currPoint = bits;
	for (unsigned int i = 0; i < count; i++)
	{
		//65535 is the max value of 8 bits
		memset(currPoint, 65535, byteSize);
		currPoint++;
	}
}

bool BitArray::AreAllClear() const
{
#if _WIN64
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	size_t reducedCount = count / 8;
	for (int i = 0; i < reducedCount; i++)
	{
		if (*currPoint != 0x0000000000000000)
		{
			return false;
		}
		currPoint++;
	}

#else
	unsigned long* currPoint = reinterpret_cast<unsigned long*>(bits);
	size_t reducedCount = count / 4;
	for (size_t i = 0; i < reducedCount; i++)
	{
		if (*currPoint != 0x00000000)
		{
			return false;
		}
		currPoint++;
	}
#endif
	return true;
}

bool BitArray::AreAllSet() const
{
#if _WIN64
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	size_t reducedCount = count / 8;
	for (int i = 0; i < reducedCount; i++)
	{
		if (*currPoint != 0xFFFFFFFFFFFFFFFF)
		{
			return false;
		}
		currPoint++;
	}
#else
	unsigned long* currPoint = reinterpret_cast<unsigned long*>(bits);
	size_t reducedCount = count / 4;
	for (size_t i = 0; i < reducedCount; i++)
	{
		if (*currPoint != 0xFFFFFFFF)
		{
			return false;
		}
		currPoint++;
	}
#endif

	return true;
}


void BitArray::SetBit(const size_t i_bitNum)
{
	if (i_bitNum > count)
	{
		return;
	}

	//divide by number of bits
	size_t i = i_bitNum / 8;
	//get the offset by getting the remainder
	size_t offset = i_bitNum % 8;

	//To set a bit, we need to OR it with a mask containing a 1 in the offset position.
	bits[i] = bits[i] | (1 << (offset));
}

void BitArray::ClearBit(const size_t i_bitNum)
{
	if (i_bitNum > count)
	{
		return;
	}

	//divide by number of bits
	size_t i = i_bitNum / 8;
	//get the offset by getting the remainder
	size_t offset = i_bitNum % 8;

	//To unset a bit, we need to XOR the result with a similar mask.
	bits[i] = bits[i] ^ (1 << (offset));
}

bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const
{
#if _WIN64
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	size_t reducedCount = count / 8;
	size_t result = 0;

	for (int i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned long index;

		unsigned __int64 mask = ~(*currPoint);
		isNonZero = _BitScanForward64(&index, mask);

		if (isNonZero)
		{
			o_bitNumber = result + index;
			return true;
		}

		result += 64;
		currPoint++;
	}
#else

	unsigned long* currPoint = reinterpret_cast<unsigned long*>(bits);
	size_t reducedCount = count / 4;
	size_t result = 0;

	for (size_t i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned long index;

		unsigned long mask = ~(*currPoint);
		isNonZero = _BitScanForward(&index, mask);

		if (isNonZero)
		{
			o_bitNumber = result + index;
			return true;
		}

		result += 32;
		currPoint++;
	}
#endif
	return false;

}

bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const
{
#if _WIN64
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	size_t reducedCount = count / 8;
	size_t result = 0;

	for (int i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned long index;

		isNonZero = _BitScanForward64(&index, *currPoint);

		if (isNonZero)
		{
			o_bitNumber = result + index;
			return true;
		}

		result += 64;
		currPoint++;
	}

#else
	unsigned long* currPoint = reinterpret_cast<unsigned long*>(bits);
	size_t reducedCount = count / 4;
	size_t result = 0;

	for (size_t i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned long index;

		isNonZero = _BitScanForward(&index, *currPoint);

		if (isNonZero)
		{
			o_bitNumber = result + index;
			return true;
		}

		result += 32;
		currPoint++;
	}
#endif
	return false;
}

bool BitArray::operator[](const size_t i_index) const
{
	assert(i_index < count);
	//divide by number of bits
	size_t i = i_index / 8;

	//get the offset by getting the remainder
	size_t offset = i_index % 8;

	return bits[i] & (1 << (offset));
}
