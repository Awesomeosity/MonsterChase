#pragma once
#include "SmartPointer.h"
#include "WeakPointer.h"

template<class T>
inline WeakPointer<T>::WeakPointer()
	: objPtr(nullptr), countCache(nullptr)
{

}

//template<class T>
//inline WeakPointer<T>* WeakPointer<T>::makePointer(SmartPointer<T> sPtr)
//{
//	WeakPointer<T>* newPtr = new WeakPointer<T>();
//
//	newPtr->objPtr = sPtr.objPtr;
//	newPtr->countCache = sPtr.countCache;
//
//	if (newPtr->objPtr != nullptr && newPtr->countCache != nullptr)
//	{
//		newPtr->countCache->weakCount++;
//	}
//	return newPtr;
//}

template<class T>
inline WeakPointer<T>::WeakPointer(SmartPointer<T>& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	if (countCache)
	{
		countCache->weakCount++;
	}
}

template<class T>
inline WeakPointer<T>::WeakPointer(const WeakPointer& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	if (countCache)
	{
		countCache->weakCount++;
	}
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
inline bool WeakPointer<T>::operator==(const WeakPointer<T>& ptr) const
{
	return objPtr == ptr.objPtr;
}

template<class T>
inline bool WeakPointer<T>::operator==(const SmartPointer<T>& ptr) const
{
	return objPtr == ptr.objPtr;
}

template<class T>
inline bool WeakPointer<T>::operator==(std::nullptr_t) const
{
	return objPtr == nullptr;
}

template<class T>
inline bool WeakPointer<T>::operator!=(const WeakPointer<T>& ptr) const
{
	return objPtr != ptr.objPtr;
}

template<class T>
inline bool WeakPointer<T>::operator!=(const SmartPointer<T>& ptr) const
{
	return objPtr != ptr.objPtr;
}

template<class T>
inline bool WeakPointer<T>::operator!=(std::nullptr_t) const
{
	return objPtr != nullptr;
}

template<class T>
inline SmartPointer<T> WeakPointer<T>::Promote() const
{
	return SmartPointer<T>(*this);
}

template<class T>
inline void WeakPointer<T>::Reset()
{
	decrement();

	objPtr = nullptr;
	countCache = nullptr;
}

template<class T>
inline void WeakPointer<T>::Swap(WeakPointer<T>& ptr)
{
	if (ptr.objPtr == this->objPtr)
	{
		return;
	}

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
	return (objPtr != nullptr);
}

template<class T>
inline void WeakPointer<T>::decrement()
{
	if (countCache == nullptr)
	{
		return;
	}

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

template<class T>
bool operator==(std::nullptr_t, WeakPointer<T>& ptr)
{
	return !ptr.Peek();
}


template<class T>
bool operator!=(std::nullptr_t, WeakPointer<T>& ptr)
{
	return ptr.Peek();
}

