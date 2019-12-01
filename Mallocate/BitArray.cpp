#include "BitArray.h"
#include "HeapManagerProxy.h"
#include <cstring>
#include <intrin.h>
#include <cassert>
BitArray* BitArray::Create(size_t i_blockSize, HeapManager* i_pHeap, bool i_startClear)
{
	//Provides clarity instead of magic numbers
	//unsigned char across x64/x86 processors should always be 1 byte in size
	const unsigned int byteSize = 1;

	BitArray* bitArray = reinterpret_cast<BitArray*>(HeapManagerProxy::alloc(i_pHeap, i_blockSize + sizeof(BitArray)));
	bitArray->bits = reinterpret_cast<unsigned char*>(bitArray + 1);
	bitArray->count = i_blockSize;

	//Clear/Set array depending on the passed i_startClear
	unsigned char* currPoint = bitArray->bits;
	for (int i = 0; i < bitArray->count; i++)
	{
		memset(currPoint, i_startClear ? 0 : 1, byteSize);
		currPoint++;
	}

	return bitArray;
}

//Note: Need to free manually from FSA due to this free's implementation requiring a starting HeapManager*
BitArray::~BitArray()
{
	bits = nullptr;
	count = 0;
}

void BitArray::ClearAll()
{
	const unsigned int byteSize = 1;
	unsigned char* currPoint = bits;
	for (int i = 0; i < count; i++)
	{
		memset(currPoint, 0, byteSize);
		currPoint++;
	}
}

void BitArray::SetAll()
{
	const unsigned int byteSize = 1;
	unsigned char* currPoint = bits;
	for (int i = 0; i < count; i++)
	{
		//65535 is the max value of 8 bits
		memset(currPoint, 65535, byteSize);
		currPoint++;
	}
}

bool BitArray::AreAllClear() const
{
#if _WIN32
	unsigned long* currPoint = reinterpret_cast<unsigned long*>(bits);
	size_t reducedCount = count / 4;
	for (size_t i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned long index;

		isNonZero = _BitScanForward(&index, *currPoint);

		if (isNonZero)
		{
			return false;
		}

		currPoint++;
	}
#else
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	int reducedCount = count / 8;
	for (int i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned __int64 index;

		isNonZero = _BitScanForward64(&index, *currPoint);

		if (isNonZero)
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
#if _WIN32
	unsigned long* currPoint = reinterpret_cast<unsigned long*>(bits);
	size_t reducedCount = count / 4;
	for (size_t i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned long index;

		unsigned long mask = ~(*currPoint);
		isNonZero = _BitScanForward(&index, mask);

		if (isNonZero)
		{
			return false;
		}

		currPoint++;
	}
#else
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	int reducedCount = count / 8;
	for (int i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned __int64 index;

		unsigned __int64 mask = ~(*currPoint);
		isNonZero = _BitScanForward64(&index, mask);

		if (isNonZero)
		{
			return false;
		}

		currPoint++;
	}
#endif

	return true;
}


void BitArray::SetBit(size_t i_bitNum)
{
	//divide by number of bits
	size_t i = i_bitNum / 8;
	//get the offset by getting the remainder
	size_t offset = i_bitNum % 8;

	//To set a bit, we need to OR it with a mask containing a 1 in the offset position.
	bits[i] = bits[i] | (1 << (offset - 1));
}

void BitArray::ClearBit(size_t i_bitNum)
{
	//divide by number of bits
	size_t i = i_bitNum / 8;
	//get the offset by getting the remainder
	size_t offset = i_bitNum % 8;

	//To unset a bit, we need to XOR the result with a similar mask.
	bits[i] = bits[i] ^ (1 << (offset - 1));
}

bool BitArray::GetFirstClearBit(size_t& o_bitNumber) const
{
#if _WIN32
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
#else
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	int reducedCount = count / 8;
	size_t result = 0;

	for (int i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned __int64 index;

		unsigned long mask = ~(*currPoint);
		isNonZero = _BitScanForward(&index, mask);

		if (isNonZero)
		{
			o_bitNumber = result + index;
			return true;
		}

		result += 64;
		currPoint++;
	}
#endif
	return false;

}

bool BitArray::GetFirstSetBit(size_t& o_bitNumber) const
{
#if _WIN32
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
#else
	unsigned __int64* currPoint = reinterpret_cast<unsigned __int64*>(bits);
	int reducedCount = count / 8;
	size_t result = 0;

	for (int i = 0; i < reducedCount; i++)
	{
		unsigned char isNonZero;
		unsigned __int64 index;

		isNonZero = _BitScanForward64(&index, *currPoint);

		if (isNonZero)
		{
			o_bitNumber = result + index;
			return true;
		}

		result += 64;
		currPoint++;
	}
#endif
	return false;
}

bool BitArray::operator[](size_t i_index) const
{
	assert(i_index < count);
	//divide by number of bits
	size_t i = i_index / 8;

	//get the offset by getting the remainder
	size_t offset = i_index % 8;

	return bits[i] & (1 << (offset - 1));
}
