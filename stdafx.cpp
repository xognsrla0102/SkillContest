#include "DXUT.h"
#include "stdafx.h"

#ifdef _DEBUG
	void DEBUG_LOG(LPCSTR fmt, ...)
	{
		char buf[256];
		va_list list;
		va_start(list, fmt);
		vsprintf(buf, fmt, list);
		va_end(list);
		OutputDebugStringA(buf);
	}
#else
	void DEBUG_LOG(LPCSTR fmt, ...) {}
#endif