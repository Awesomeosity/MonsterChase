#pragma once
#include "SmartPointer.h"
struct ptrCount;
template <class T>
class WeakPointer
{
public:
	static WeakPointer<T> makePointer(SmartPointer<T> sPtr);
	WeakPointer(const WeakPointer& ptr);
	WeakPointer& operator=(const WeakPointer& ptr);
	~WeakPointer();


private:
	WeakPointer();
	void decrement();
	T* objPtr;
	ptrCount* countCache;

};

template<class T>
inline WeakPointer<T> WeakPointer<T>::makePointer(SmartPointer<T> sPtr)
{
	WeakPointer<T> newPtr = new WeakPointer<T>();
	newPtr.objPtr = sPtr.objPtr;
	newPtr.countCache = sPtr.countCache;

	newPtr.countCache->weakCount++;
}

template<class T>
inline WeakPointer<T>::WeakPointer(const WeakPointer& ptr)
{
	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	countCache->weakCount++;
}

template<class T>
inline WeakPointer<T>& WeakPointer<T>::operator=(const WeakPointer& ptr)
{
	if (ptr == this)
	{
		return this;
	}

	if (ptr == nullptr)
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
inline WeakPointer<T>::~WeakPointer()
{
	decrement();
}

template<class T>
inline void WeakPointer<T>::decrement()
{
	if (--(*countCache).weakCount == 0)
	{
		delete countCache;
	}
}
