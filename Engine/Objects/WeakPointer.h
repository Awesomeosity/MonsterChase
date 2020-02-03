#pragma once
#include "SmartPointer.h"
struct ptrCount;
template <class T>
class WeakPointer
{
public:
	static WeakPointer<T> makePointer(SmartPointer<T> ptr);
	WeakPointer(const WeakPointer& ptr);
	WeakPointer(WeakPointer&& ptr) noexcept;
	WeakPointer& operator=(const WeakPointer& ptr);
	WeakPointer& operator=(WeakPointer&& ptr) noexcept;
	~WeakPointer();

	T& operator*() const;
	T* operator->() const;
	operator bool() const;
	T& operator[](int index) const;

	//Generates a SmartPointer from this WeakPointer. Will convert, even if there is no valid obj pointer.
	SmartPointer<T> Promote() const;
	void Reset();
	void Swap(const WeakPointer<T>& ptr);
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
inline WeakPointer<T> WeakPointer<T>::makePointer(SmartPointer<T> sPtr)
{
	WeakPointer<T> newPtr = WeakPointer<T>();
	T* i_objPtr = nullptr;
	ptrCount* i_countCache = nullptr;

	sPtr.Downcast(i_objPtr, i_countCache);

	newPtr.objPtr = i_objPtr;
	newPtr.countCache = i_countCache;

	newPtr.countCache->weakCount++;
	return newPtr;
}

template<class T>
inline WeakPointer<T>::WeakPointer(const WeakPointer& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	countCache->weakCount++;
}

template<class T>
inline WeakPointer<T>::WeakPointer(WeakPointer&& ptr) noexcept
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	ptr.objPtr = nullptr;
	ptr.countCache = nullptr;
}

template<class T>
inline WeakPointer<T>& WeakPointer<T>::operator=(const WeakPointer& ptr)
{
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
	return (*objPtr);
}

template<class T>
inline T* WeakPointer<T>::operator->() const
{
	if (countCache->smartCount == 0)
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
inline void WeakPointer<T>::Swap(const WeakPointer<T>& ptr)
{
	if (ptr == this)
	{
		return;
	}

	decrement();

	T* tempPtr = objPtr;
	ptrCount* tempCache = countCache;

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	ptr.objPtr = tempPtr;
	ptr.countCache = tempCache;
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
	return (objPtr == nullptr);
}

template<class T>
inline void WeakPointer<T>::decrement()
{
	if (--(countCache->weakCount) == 0)
	{
		//Just because the count cache no longer has any weak pointers doesn't mean we should automatically delete the count cache
		//Check if the smart count is 0, and if so, then we should be safe to delete the cache.
		if (countCache->smartCount == 0)
		{
			delete countCache;
		}
	}
}