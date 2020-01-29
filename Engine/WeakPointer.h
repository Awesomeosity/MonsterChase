#pragma once
class SmartPointer;
struct ptrCount;
template <class T>
class WeakPointer
{
public:
	static makePointer(SmartPointer sPtr);
private:
	WeakPointer();
	increment();
	decrement();
	T* objPtr;
	ptrCount* countCache;

};

