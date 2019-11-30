#pragma once
class HeapManager;
class BitArray
{
public:
	static BitArray* Create(size_t i_blockSize, HeapManager* i_pHeap, bool i_startClear = true);
	~BitArray();
	
	void ClearAll();
	void SetAll();

	bool AreAllClear() const;
	bool AreAllSet() const;

	inline bool IsBitClear(size_t i_bitNum) const;
	inline bool IsBitSet(size_t i_bitNum) const;

	void SetBit(size_t i_bitNum);
	void ClearBit(size_t i_bitNum);

	bool GetFirstClearBit(size_t& o_bitNumber) const;
	bool GetFirstSetBit(size_t& o_bitNumber) const;

	bool operator[](size_t i_index) const;
private:
	//Prevent users from copying this, that would be bad --
	BitArray(const BitArray& arr);
	BitArray& operator=(const BitArray& arr) {};
	//Pointer to the bitarray proper
	unsigned char* bits;
	//The amount of blocks this particular BitArray has access to.
	size_t count;
};

