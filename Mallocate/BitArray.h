#pragma once
class HeapManager;
class BitArray
{
public:
	static BitArray* Create(const size_t i_blockCount, HeapManager* const i_pHeap, const bool i_startClear = true);
	~BitArray();
	//As-is, each BitArray is unique to its holding Fixed Size Allocator. Assigning to them is dangerous.
	BitArray (const BitArray& i_other) = delete;
	BitArray& operator=(const BitArray& i_other) = delete;

	void ClearAll();
	void SetAll();

	bool AreAllClear() const;
	bool AreAllSet() const;

	inline bool IsBitClear(const size_t i_bitNum) const
	{
		if (i_bitNum > count)
		{
			return false;
		}

		//divide by number of bits
		size_t i = i_bitNum / 8;
		//get the offset by getting the remainder
		size_t offset = i_bitNum % 8;

		unsigned char targChar = bits[i];
		return (targChar & (1 << (offset))) == 0;
	};

	inline bool IsBitSet(const size_t i_bitNum) const
	{
		if (i_bitNum > count)
		{
			return false;
		}

		//divide by number of bits
		size_t i = i_bitNum / 8;

		//get the offset by getting the remainder
		size_t offset = i_bitNum % 8;

		unsigned char targChar = bits[i];
		return (targChar & (1 << (offset))) != 0;
	};

	void SetBit(const size_t i_bitNum);
	void ClearBit(const size_t i_bitNum);

	bool GetFirstClearBit(size_t& o_bitNumber) const;
	bool GetFirstSetBit(size_t& o_bitNumber) const;

	bool operator[](const size_t i_index) const;
private:
	//Pointer to the bitarray proper
	unsigned char* bits;
	//The amount of blocks this particular BitArray has access to.
	size_t count;
};

