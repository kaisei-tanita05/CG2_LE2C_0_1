#include "Input.h"
#include <cassert>
#include <wrl.h>
#define DIRECTINPUT_VERSION  0x0800 //DirectInputのバージン指定
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

using namespace Microsoft::WRL;

void Input::Initialize(HINSTANCE histance, HWND hwnd)
{
	HRESULT result;
	//DirectInputの初期化
	ComPtr<IDirectInput8> directInput = nullptr;
	result = DirectInput8Create(histance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	ComPtr<IDirectInputDevice8> keyboard;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::Update() {

}