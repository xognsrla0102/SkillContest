#pragma once
class cInput
{
private:
	LPDIRECTINPUT8 m_Input;
	LPDIRECTINPUTDEVICE8 m_device;
	HWND m_hWnd;
	BYTE m_Keys[256];
public:
	cInput(HWND hWnd);
	~cInput();

	HRESULT CreateDevice(HWND hWnd);
	VOID ReleaseInput();
	VOID OnActivate(WPARAM wParam);
	HRESULT GetData();
	BOOL KeyDown(BYTE key);
};

