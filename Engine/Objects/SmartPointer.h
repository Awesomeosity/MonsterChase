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

template<class T>
class WeakPointer;

template <class T>
class SmartPointer
{
public:

	SmartPointer();
	explicit SmartPointer(T *ptr);
	SmartPointer(const WeakPointer<T>& ptr);
	SmartPointer(const SmartPointer& ptr);
	SmartPointer(SmartPointer&& ptr) noexcept;
	SmartPointer(std::nullptr_t);
	SmartPointer& operator=(const SmartPointer& ptr);
	SmartPointer& operator=(SmartPointer&& ptr) noexcept;
	SmartPointer& operator=(std::nullptr_t);
	~SmartPointer();

	T& operator*() const;
	T* operator->() const;
	operator bool() const;
	T& operator[](int index) const;
	bool operator==(const SmartPointer<T>& ptr) const;
	bool operator==(std::nullptr_t) const;
	bool operator==(const WeakPointer<T>& ptr) const;
	bool operator!=(const SmartPointer<T>& ptr) const;
	bool operator!=(std::nullptr_t) const;
	bool operator!=(const WeakPointer<T>& ptr) const;


	void Reset();
	void Swap(SmartPointer<T>& ptr);
	bool Peek() const;
	int UseCount() const;
	int WeakCount() const;

private:
	void decrement();
	T* objPtr;
	ptrCount* countCache;

	template<class T>
	friend class WeakPointer;
};

#include "SmartPointer-inl.h"