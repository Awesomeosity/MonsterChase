#include "SmartPointer.h"
struct ptrCount
{
	int smartCount{ 1 };
	int weakCount{ 0 };
};

template<class T>
SmartPointer<T>::SmartPointer(T* ptr)
	: objPtr(ptr), countCache(new ptrCount)
{
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer& ptr)
{
	if (ptr == this)
	{
		return;
	}

	if (ptr == nullptr)
	{
		return;
	}

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;
	countCache.smartCount++;
}

template<class T>
SmartPointer& SmartPointer<T>::operator=(const SmartPointer& ptr)
{
	if (ptr == this)
	{
		return;
	}

	//Exchange data
	
}

template<class T>
void SmartPointer<T>::increment()
{
}
