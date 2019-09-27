// Mallocate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include "HeapManagerProxy.h"
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <vector>
int main()
{
	using namespace HeapManagerProxy;
	const size_t 		sizeHeap = 64 * 64;
	const unsigned int 	numDescriptors = 0;

	// Get SYSTEM_INFO, which includes the memory page size
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	// round our size to a multiple of memory page size
	void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	assert(pHeapMemory);
	HeapManager* pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	assert(pHeapManager);

	if (pHeapManager == nullptr)
	{
		std::cout << "BAD POINTER GENERATED\n";
	}
	std::vector<void*> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

		void* pPtr = alloc(pHeapManager, sizeAlloc);
		if (pPtr == nullptr)
		{
			break;
		}
		AllocatedAddresses.push_back(pPtr);
		numAllocs++;
	} while (1);

	printf("After exhausting allocations:\n");
	ShowFreeBlocks(pHeapManager);
	ShowOutstandingAllocations(pHeapManager);
	printf("\n");

	_getch();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
