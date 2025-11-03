#pragma once
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION  0x0800 //DirectInputのバージン指定
#include <dinput.h>



class Input
{
public:

	void Initialize(HINSTANCE histance,HWND hwnd);

	void Update();

	//namespace省略
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
private://メンバ変数
	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
};

