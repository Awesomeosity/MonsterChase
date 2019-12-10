#pragma once
class HeapManager;
class BitArray
{
public:
	static BitArray* Create(size_t i_blockCount, HeapManager* i_pHeap, bool i_startClear = true);
	~BitArray();
	
	void ClearAll();
	void SetAll();

	bool AreAllClear() const;
	bool AreAllSet() const;

	inline bool IsBitClear(size_t i_bitNum) const
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

	inline bool IsBitSet(size_t i_bitNum) const
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

	void SetBit(size_t i_bitNum);
	void ClearBit(size_t i_bitNum);

	bool GetFirstClearBit(size_t& o_bitNumber) const;
	bool GetFirstSetBit(size_t& o_bitNumber) const;

	bool operator[](size_t i_index) const;
private:
	//Pointer to the bitarray proper
	unsigned char* bits;
	//The amount of blocks this particular BitArray has access to.
	size_t count;
};

