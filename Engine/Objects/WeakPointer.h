#pragma once
#include "SmartPointer.h"
#include <assert.h>
struct ptrCount;
template <class T>
class WeakPointer : public SmartPointer<T>
{
public:
	static WeakPointer<T> makePointer(const SmartPointer<T> sPtr);
	WeakPointer(const WeakPointer& ptr);
	WeakPointer& operator=(const WeakPointer& ptr);
	WeakPointer& operator=(WeakPointer&& ptr) noexcept;
	~WeakPointer();

	T& operator*() const;
	T* operator->() const;
	operator bool() const;
	T& operator[](int index) const;

	//Promotes a weak pointer to become a strong pointer. Will convert, even if there is no valid obj pointer.
	SmartPointer<T> Promote() const;
	void Reset();
	void Swap(const WeakPointer&& ptr);
	int UseCount() const;
	int WeakCount() const;
	bool Peek() const;

private:
	WeakPointer();
	void decrement();
	T* objPtr;
	ptrCount* countCache;
};

template<class T>
static inline WeakPointer<T> WeakPointer<T>::makePointer(const SmartPointer<T> sPtr)
{
	WeakPointer<T> newPtr = new WeakPointer<T>();
	newPtr.objPtr = sPtr.objPtr;
	newPtr.countCache = sPtr.countCache;

	newPtr.countCache->weakCount++;
}

template<class T>
inline WeakPointer<T>::WeakPointer(const WeakPointer& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	assert(ptr != nullptr);

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

	decrement();

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	countCache->weakCount++;

	return this;
}

template<class T>
inline WeakPointer<T>& WeakPointer<T>::operator=(WeakPointer&& ptr) noexcept
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
inline T& WeakPointer<T>::operator*() const
{
	if (objPtr == nullptr)
	{
		return nullptr;
	}

	return (*objPtr);
}

template<class T>
inline T* WeakPointer<T>::operator->() const
{
	if (objPtr == nullptr)
	{
		return nullptr;
	}

	return objPtr;
}

template<class T>
inline WeakPointer<T>::operator bool() const
{
	return (objPtr != nullptr);
}

template<class T>
inline T& WeakPointer<T>::operator[](int index) const
{
	return objPtr[index];
}

template<class T>
inline SmartPointer<T> WeakPointer<T>::Promote() const
{
	return SmartPointer<T>(this);
}

template<class T>
inline void WeakPointer<T>::Reset()
{
	decrement();

	objPtr = nullptr;
	countCache = nullptr;
}

template<class T>
inline void WeakPointer<T>::Swap(const WeakPointer&& ptr)
{
	assert(ptr.objPtr != nullptr);

	if (ptr == this)
	{
		return;
	}

	decrement();

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	ptr.objPtr = nullptr;
	ptr.countCache = nullptr;
}

template<class T>
inline int WeakPointer<T>::UseCount() const
{
	return countCache->smartCount;
}

template<class T>
inline int WeakPointer<T>::WeakCount() const
{
	return countCache->weakCount;
}

template<class T>
inline bool WeakPointer<T>::Peek() const
{
	return (opjPtr == nullptr);
}

template<class T>
inline void WeakPointer<T>::decrement()
{
	if (--(countCache->weakCount) == 0)
	{
		delete countCache;

		//Failsafe
		if (countCache->smartCount == 0)
		{
			delete objPtr;
		}
	}
}
