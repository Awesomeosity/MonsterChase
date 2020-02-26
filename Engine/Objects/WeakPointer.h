#pragma once
struct ptrCount;

template <class T>
class SmartPointer;

template <class T>
class WeakPointer
{
public:
	WeakPointer(SmartPointer<T>& ptr);
	WeakPointer(const WeakPointer& ptr);
	WeakPointer(WeakPointer&& ptr) noexcept;
	WeakPointer& operator=(const WeakPointer& ptr);
	WeakPointer& operator=(WeakPointer&& ptr) noexcept;
	~WeakPointer();

	T& operator*() const;
	T* operator->() const;
	operator bool() const;
	T& operator[](int index) const;

	bool operator==(const WeakPointer<T>& ptr) const;
	bool operator==(const SmartPointer<T>& ptr) const;
	bool operator==(std::nullptr_t) const;
	bool operator!=(const WeakPointer<T>& ptr) const;
	bool operator!=(const SmartPointer<T>& ptr) const;
	bool operator!=(std::nullptr_t) const;

	//Generates a SmartPointer from this WeakPointer. Will convert, even if there is no valid obj pointer.
	SmartPointer<T> Promote() const;
	void Reset();
	void Swap(WeakPointer<T>& ptr);
	int UseCount() const;
	int WeakCount() const;
	bool Peek() const;

private:
	WeakPointer();
	void decrement();
	T* objPtr;
	ptrCount* countCache;

	template<class T>
	friend class SmartPointer;

};

#include "WeakPointer-inl.h"