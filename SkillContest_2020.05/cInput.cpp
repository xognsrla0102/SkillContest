#include "DXUT.h"
#include "cInput.h"

cInput::cInput(HWND hWnd) : m_hWnd(hWnd)
{
	CreateDevice(m_hWnd);
}

cInput::~cInput()
{
	ReleaseInput();
}

HRESULT cInput::CreateDevice(HWND hWnd)
{
	HRESULT hr;

	if (FAILED(hr = DirectInput8Create(
		GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&m_Input, NULL)))
		return hr;

	//키보드 객체 생성
	if (FAILED(hr = m_Input->CreateDevice(
		GUID_SysKeyboard, &m_device, NULL)))
		return hr;

	//사용하고자 하는 객체의 포맷 지정 (dinput.h에 정의되어 있음)
	if (FAILED(hr = m_device->SetDataFormat(&c_dfDIKeyboard)))
		return hr;

	//응용 프로그램과 시스템간 상호작용 설정
	if (FAILED(hr = m_device->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND |
		DISCL_NONEXCLUSIVE |
		DISCL_NOWINKEY
	)))
		return hr;

	//키보드 제어권 획득
	m_device->Acquire();

	return S_OK;
}

VOID cInput::ReleaseInput()
{
	if (m_device) m_device->Unacquire();

	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_Input);
}

VOID cInput::OnActivate(WPARAM wParam)
{
	//창모드일 때 다른 창 눌렀다가 다시 이 창 누를 경우
	//키보드 제어권을 다시 확보해야함

	//현재 메세지의 상태가 창 활성화 상태이며 키보드 디바이스가 존재할 경우
	if (WA_INACTIVE != wParam && m_device)
		m_device->Acquire();

	//WM_ACTIVATE 는 활성화 비활성화 될 때 마다 뜨고
	//WA_INACTIVE가 wParam에 들어갔을 땐 비활성화
	//WA_ACTIVE 가 들어갔을떈 활성화라는 뜻

}

HRESULT cInput::GetData()
{
	HRESULT hr;

	if (m_device == nullptr)
		return S_OK;

	ZeroMemory(m_Keys, sizeof(m_Keys));

	//m_Keys 배열에 값이 들어오도록 설정
	hr = m_device->GetDeviceState(sizeof(m_Keys), m_Keys);

	//디바이스에 대한 제어권을 확보하지 못한 경우
	if (FAILED(hr)) {
		do {
			//제어권을 확보할 때 까지 반복
			hr = m_device->Acquire();
		} while (hr == DIERR_INPUTLOST);
		return S_OK;
	}
	return S_OK;
}

BOOL cInput::KeyDown(BYTE key)
{
	if (m_Keys[key] & 0x80) {
		m_Keys[key] = true;
		return true;
	}
	m_Keys[key] = false;
	return false;
}
