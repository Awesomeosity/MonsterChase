#include <inttypes.h>
#include <malloc.h>

#include <stdio.h>
#include "MemorySystem.h"

extern HeapManager* heap;
extern FixedSizeAllocator* allFSAs[3];

FixedSizeAllocator* getFSA(size_t size)
{
	for (int i = 0; i < 3; i++)
	{
		if (size < allFSAs[i]->getBlockSize())
		{
			return allFSAs[i];
		}
	}

	return nullptr;
}

void* __cdecl malloc(size_t i_size)
{
	void* retPoint = nullptr;

	FixedSizeAllocator* targFSA = getFSA(i_size);
	if (targFSA)
	{
		retPoint = targFSA->alloc();
	}

	if (retPoint == nullptr)
	{
		retPoint = HeapManagerProxy::alloc(heap, i_size);
	}

	printf("malloc %zu\n", i_size);
	return retPoint;
}

void __cdecl free(void* i_ptr)
{
	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));

	if (i_ptr == nullptr)
	{
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		if (allFSAs[i]->free(i_ptr))
		{
			return;
		}
	}

	if (HeapManagerProxy::free(heap, i_ptr))
	{
		return;
	}
}

void* operator new(size_t i_size)
{
	void* retPoint = nullptr;

	FixedSizeAllocator* targFSA = getFSA(i_size);
	if (targFSA)
	{
		retPoint = targFSA->alloc();
	}

	if (retPoint == nullptr)
	{
		retPoint = HeapManagerProxy::alloc(heap, i_size);
	}
	printf("new %zu\n", i_size);
	return retPoint;
}

void operator delete(void* i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	return _aligned_free(i_ptr);
}

void* operator new[](size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("new [] %zu\n", i_size);
	return _aligned_malloc(i_size, 4);
}

void operator delete [](void* i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	return _aligned_free(i_ptr);
}
