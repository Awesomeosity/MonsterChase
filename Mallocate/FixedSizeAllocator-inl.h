#pragma once
#include "FixedSizeAllocator.h"
#include <cstring>

inline void FixedSizeAllocator::memsetPattern(const size_t i_blockSize, const void* i_pointer, const int i_pattern)
{
	for (size_t i = 0; i < i_blockSize; i++)
	{
		memset(const_cast<void*>(i_pointer), i_pattern, 1);
	}
}
