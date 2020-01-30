#pragma once
#include "SmartPointer.h"
#include <assert.h>
struct ptrCount;
template <class T>
class WeakPointer
{
public:
	template<class t>
	static WeakPointer<T> makePointer(SmartPointer<t> sPtr);
	WeakPointer(const WeakPointer& ptr);
	WeakPointer& operator=(const WeakPointer& ptr);
	~WeakPointer();

	operator bool();
	//Promotes a weak pointer to become a strong pointer. Will convert, even if there is no valid obj pointer.
	template<class t>
	SmartPointer<t> Promote();

private:
	WeakPointer();
	void decrement();
	T* objPtr;
	ptrCount* countCache;

};

template<class T>
template<class t>
static inline WeakPointer<T> WeakPointer<T>::makePointer(SmartPointer<t> sPtr)
{
	WeakPointer<T> newPtr = new WeakPointer<T>();
	newPtr.objPtr = sPtr.objPtr;
	newPtr.countCache = sPtr.countCache;

	newPtr.countCache->weakCount++;
}

template<class T>
inline WeakPointer<T>::WeakPointer(const WeakPointer& ptr)
{
	assert(ptr != nullptr);

	if (ptr == this)
	{
		return;
	}

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	countCache->weakCount++;
}

template<class T>
inline WeakPointer<T>& WeakPointer<T>::operator=(const WeakPointer& ptr)
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
inline WeakPointer<T>::~WeakPointer()
{
	decrement();
}

template<class T>
inline WeakPointer<T>::operator bool()
{
	return (objPtr != nullptr);
}

template<class T>
template<class t>
inline SmartPointer<t> WeakPointer<T>::Promote()
{

	return new SmartPointer<T>();
}

template<class T>
inline void WeakPointer<T>::decrement()
{
	if (--(*countCache).weakCount == 0)
	{
		delete countCache;
	}
}
