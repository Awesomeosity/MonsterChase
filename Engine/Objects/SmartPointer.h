#pragma once
#include <assert.h>

struct ptrCount
{
	int smartCount{ 1 };
	int weakCount{ 0 };
};

template <class T>
class SmartPointer
{
public:
	explicit SmartPointer(T *ptr);
	SmartPointer(const SmartPointer& ptr);
	SmartPointer& operator=(const SmartPointer& ptr);
	~SmartPointer();

	T& operator*();
	T* operator->();
	operator bool();
private:
	void decrement();
	T* objPtr;
	ptrCount* countCache;
};


template<class T>
SmartPointer<T>::SmartPointer(T* ptr)
	: objPtr(ptr), countCache(new ptrCount)
{
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer& ptr)
{
	assert(ptr != nullptr);

	if (ptr == this)
	{
		return;
	}

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;
	countCache.smartCount++;
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& ptr)
{
	assert(ptr != nullptr);

	if (ptr == this)
	{
		return this;
	}

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	ptr.objPtr = nullptr;
	ptr.countCache = nullptr;

	return this;
}

template<class T>
inline SmartPointer<T>::~SmartPointer()
{
	decrement();
}

template<class T>
inline T& SmartPointer<T>::operator*()
{
	if (objPtr == nullptr)
	{
		return nullptr;
	}
	return &objPtr;
}

template<class T>
inline T* SmartPointer<T>::operator->()
{
	if (objPtr == nullptr)
	{
		return nullptr;
	}

	return *objPtr;
}

template<class T>
inline SmartPointer<T>::operator bool()
{
	return (objPtr == nullptr);
}

template<class T>
inline void SmartPointer<T>::decrement()
{
	if (--(*countCache).smartCount == 0)
	{
		delete objPtr;
	}
}
