#pragma once
#include <windows.h>
#include <wrl.h>
#include <cstdint>

//WindowsAPI
class WinApp
{
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://メンバ関数
	//初期化
	void Initialize();

	//更新
	void Update();
};