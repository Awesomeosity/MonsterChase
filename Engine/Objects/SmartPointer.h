#pragma once
struct ptrCount
{
	int smartCount{ 1 };
	int weakCount{ 0 };
};

template <class T>
class SmartPointer
{
public:
	SmartPointer();
	explicit SmartPointer(const T *ptr);
	SmartPointer(const SmartPointer& ptr);
	SmartPointer& operator=(const SmartPointer& ptr);
	SmartPointer& operator=(SmartPointer&& ptr) noexcept;
	~SmartPointer();

	T& operator*() const;
	T* operator->() const;
	operator bool() const;
	T& operator[](int index) const;

	void Reset();
	void Swap(SmartPointer<T>& ptr);
	int UseCount();
	int WeakCount();

private:
	void decrement();
	T* objPtr;
	ptrCount* countCache;
};



template<class T>
inline SmartPointer<T>::SmartPointer()
	: objPtr(nullptr), countCache(new ptrCount)
{

}

template<class T>
inline SmartPointer<T>::SmartPointer(const T* ptr)
	: objPtr(ptr), countCache(new ptrCount)
{
}

template<class T>
inline SmartPointer<T>::SmartPointer(const SmartPointer<T>& ptr)
	: objPtr(ptr.objPtr), countCache(ptr.countCache)
{
	countCache.smartCount++;
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& ptr)
{
	//Prevent erroneous self-assignment
	if (ptr == this)
	{
		return this;
	}

	decrement();

	objPtr = ptr.objPtr;
	countCache = ptr.countCache;

	countCache->smartCount++;

	return this;
}

template<class T>
inline SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>&& ptr) noexcept
{
	if (ptr == this)
	{
		return this;
	}

	decrement();

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
inline T& SmartPointer<T>::operator*() const
{
	if (objPtr == nullptr)
	{
		return nullptr;
	}

	return (*objPtr);
}

template<class T>
inline T* SmartPointer<T>::operator->() const
{
	if (objPtr == nullptr)
	{
		return nullptr;
	}

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
inline int SmartPointer<T>::UseCount()
{
	return countCache->smartCount;
}

template<class T>
inline int SmartPointer<T>::WeakCount()
{
	return countCache->weakCount;
}

template<class T>
inline bool operator==(const SmartPointer<T>& i_ptr1, const SmartPointer<T>& i_ptr2)
{
	return &(*i_ptr1) == &(*i_ptr2);
}

template<class T>
inline bool operator==(const SmartPointer<T>& i_ptr1, std::nullptr_t)
{
	return !i_ptr1;
}

template<class T>
inline bool operator==(std::nullptr_t, const SmartPointer<T>& i_ptr1)
{
	return !i_ptr1;
}


template<class T>
inline bool operator!=(const SmartPointer<T>& i_ptr1, const SmartPointer<T>& i_ptr2)
{
	return &(*i_ptr1) != &(*i_ptr2);
}

template<class T>
inline bool operator!=(const SmartPointer<T>& i_ptr1, std::nullptr_t)
{
	return (bool)i_ptr1;
}

template<class T>
inline bool operator!=(std::nullptr_t, const SmartPointer<T>& i_ptr1)
{
	return (bool)i_ptr1;
}


template<class T>
inline void SmartPointer<T>::decrement()
{
	if (--(countCache->smartCount) == 0)
	{
		delete objPtr;

		if (countCache->weakCount == 0)
		{
			delete countCache;
		}
	}

}
