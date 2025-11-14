#pragma once
#include <string>

class StringUtility
{
	//stringをwstringに変換する
	std::wstring  ConvertString(const std::string& str);

	//wstringをstringに変換する
	std::string ConvertString(const std::wstring& str);
};

