#pragma once
struct ptrCount
{
	int smartCount{ 0 };
	int weakCount{ 0 };

	ptrCount(int sc, int wc)
		: smartCount(sc), weakCount(wc)
	{
	}
};

template <class T>
class SmartPointer
{
public:
	SmartPointer();
	explicit SmartPointer(T *ptr);
	SmartPointer(const SmartPointer& ptr);
	SmartPointer(SmartPointer&& ptr) noexcept;
	SmartPointer& operator=(const SmartPointer& ptr);
	SmartPointer& operator=(SmartPointer&& ptr) noexcept;
	~SmartPointer();

	T& operator*() const;
	T* operator->() const;
	operator bool() const;
	T& operator[](int index) const;

	void Reset();
	void Swap(SmartPointer<T>& ptr);
	bool Peek() const;
	int UseCount() const;
	int WeakCount() const;
	//A very bad idea
	void Downcast(T** o_objPtr, ptrCount** o_countCache);

protected:
	void decrement();
	T* objPtr;
	ptrCount* countCache;
};

template<class T>
inline SmartPointer<T>::SmartPointer()
	: objPtr(nullptr), countCache()
{

}

template<class T>
inline SmartPointer<T>::SmartPointer(T* ptr)
	: objPtr(ptr), countCache(new ptrCount(1, 0))
{
}

template<class T>
inline SmartPointer<T>::SmartPointer(const SmartPointer<T>& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	(countCache->smartCount)++;
}

template<class T>
inline SmartPointer<T>::SmartPointer(SmartPointer&& ptr) noexcept
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	ptr.objPtr = nullptr;
	ptr.countCache = nullptr;
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

template<class T>
inline void SmartPointer<T>::Downcast(T** o_objPtr, ptrCount** o_countCache)
{
	(*o_objPtr) = objPtr;
	(*o_countCache) = countCache;
}

template <class T>
inline bool operator==(const SmartPointer<T>& ptr_1, const SmartPointer<T>& ptr_2)
{
	return *ptr_1 == *ptr_2;
}

template<class T>
bool operator==(const SmartPointer<T>& i_ptr1, std::nullptr_t)
{
	return !i_ptr1;
}

template<class T>
bool operator==(std::nullptr_t, const SmartPointer<T>& i_ptr1)
{
	return !i_ptr1;
}

template<class T>
bool operator!=(const SmartPointer<T>& i_ptr1, const SmartPointer<T>& i_ptr2)
{
	return *i_ptr1 != *i_ptr2;
}

template<class T>
bool operator!=(const SmartPointer<T>& i_ptr1, std::nullptr_t)
{
	return (bool)i_ptr1;
}

template<class T>
bool operator!=(std::nullptr_t, const SmartPointer<T>& i_ptr1)
{
	return (bool)i_ptr1;
}

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
