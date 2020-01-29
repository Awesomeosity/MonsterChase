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
	explicit SmartPointer(T *ptr);
	SmartPointer(const SmartPointer& ptr);
	SmartPointer& operator=(const SmartPointer& ptr);
	~SmartPointer();

	T& operator*();
	T* operator->();

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
inline SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& ptr)
{
	// TODO: insert return statement here
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

	ptr.objPtr = nullptr;
	ptr.countCache = nullptr;
}
