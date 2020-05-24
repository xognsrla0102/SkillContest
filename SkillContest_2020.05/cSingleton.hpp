#pragma once
#include "DXUT.h"

template <typename T>
class cSingleton
{
private:
	static T* p;
public:
	cSingleton(){}
	virtual ~cSingleton(){}

	static T* GetInst() {
		if (!p) p = new T;
		return p;
	}

	static void ReleaseInst() {
		if (p) delete p;
		p = nullptr;
	}
};

template <typename T>
T* cSingleton<T>::p = nullptr;