#pragma once
#include "WeakPointer.h"
#include "SmartPointer.h"
template<class T>
inline SmartPointer<T>::SmartPointer()
	: objPtr(nullptr), countCache(nullptr)
{

}

template<class T>
inline SmartPointer<T>::SmartPointer(T* ptr)
	: objPtr(ptr), countCache(new ptrCount(1, 0))
{
}

template<class T>
inline SmartPointer<T>::SmartPointer(const WeakPointer<T>& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	if (objPtr && countCache->smartCount != 0)
	{
		ptr.countCache->smartCount++;

	}
}

//template<class T>
//inline SmartPointer<T>::SmartPointer(T** _objPtr, ptrCount** _countCache)
//{
//	objPtr = *_objPtr;
//	countCache = *_countCache;
//
//	if (_countCache != nullptr)
//	{
//		countCache->smartCount++;
//	}
//}

template<class T>
inline SmartPointer<T>::SmartPointer(const SmartPointer<T>& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	if (objPtr && countCache->smartCount != 0)
	{
		(countCache->smartCount)++;
	}
}

template<class T>
inline SmartPointer<T>::SmartPointer(SmartPointer&& ptr) noexcept
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	ptr.objPtr = nullptr;
	ptr.countCache = nullptr;
}

template<class T>
inline SmartPointer<T>::SmartPointer(std::nullptr_t)
	: objPtr(nullptr), countCache(nullptr)
{
	
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& ptr)
{
	//Prevent erroneous self-assignment
	if (ptr.objPtr == this->objPtr)
	{
		return *this;
	}

	decrement();

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	countCache->smartCount++;

	return *this;
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>&& ptr) noexcept
{
	if (ptr.objPtr == this->objPtr)
	{
		return *this;
	}

	decrement();

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	ptr.objPtr = nullptr;
	ptr.countCache = nullptr;

	return *this;
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(std::nullptr_t)
{
	decrement();

	objPtr = nullptr;
	countCache = nullptr;

	return *this;
}

template<class T>
inline SmartPointer<T>::~SmartPointer()
{
	decrement();
}

template<class T>
inline T& SmartPointer<T>::operator*() const
{
	return (*objPtr);
}

template<class T>
inline T* SmartPointer<T>::operator->() const
{
	return objPtr;
}

template<class T>
inline SmartPointer<T>::operator bool() const
{
	return (objPtr != nullptr);
}

template<class T>
inline T& SmartPointer<T>::operator[](int index) const
{
	return objPtr[index];
}

template<class T>
inline bool SmartPointer<T>::operator==(const SmartPointer<T>& ptr) const
{
	return objPtr == ptr.objPtr;
}

template<class T>
inline bool SmartPointer<T>::operator==(std::nullptr_t) const
{
	return objPtr == nullptr;
}

template<class T>
inline bool SmartPointer<T>::operator==(const WeakPointer<T>& ptr) const
{
	return objPtr == ptr.objPtr;
}

template<class T>
inline bool SmartPointer<T>::operator!=(const SmartPointer<T>& ptr) const
{
	return objPtr != ptr.objPtr;
}

template<class T>
inline bool SmartPointer<T>::operator!=(std::nullptr_t) const
{
	return objPtr != nullptr;
}

template<class T>
inline bool SmartPointer<T>::operator!=(const WeakPointer<T>& ptr) const
{
	return objPtr != ptr.objPtr;
}


template<class T>
inline void SmartPointer<T>::Reset()
{
	decrement();

	objPtr = nullptr;
	countCache = nullptr;
}

template<class T>
inline void SmartPointer<T>::Swap(SmartPointer<T>& ptr)
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
inline bool SmartPointer<T>::Peek() const
{
	return objPtr != nullptr;
}

template<class T>
inline int SmartPointer<T>::UseCount() const
{
	if (countCache == nullptr)
	{
		return 0;
	}
	return countCache->smartCount;
}

template<class T>
inline int SmartPointer<T>::WeakCount() const
{
	if (countCache == nullptr)
	{
		return 0;
	}

	return countCache->weakCount;
}

//template<class T>
//inline void SmartPointer<T>::Downcast(T** o_objPtr, ptrCount** o_countCache)
//{
//	(*o_objPtr) = objPtr;
//	(*o_countCache) = countCache;
//}

template<class T>
inline void SmartPointer<T>::decrement()
{
	if (countCache == nullptr)
	{
		return;
	}

	if (--(countCache->smartCount) == 0)
	{
		delete objPtr;

		if (countCache->weakCount == 0)
		{
			delete countCache;
		}
	}

}

template<class T>
bool operator==(std::nullptr_t, SmartPointer<T>& ptr)
{
	return !ptr.Peek();
}

template<class T>
bool operator!=(std::nullptr_t, SmartPointer<T>& ptr)
{
	return ptr.Peek();
}
