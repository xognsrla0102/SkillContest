#pragma once

template<typename T>
class cSingleton
{
protected:
	static T* p;
	cSingleton() {}
public:
	virtual ~cSingleton() {}

	static T* GetInst() {
		if (!p) p = new T;
		return p;
	}

	static void ReleaseInst() {
		if (p) delete p;
		p = nullptr;
	}
};

template<typename T>
T* cSingleton<T>::p = nullptr;