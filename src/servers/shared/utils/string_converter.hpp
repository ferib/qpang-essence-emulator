#ifndef STRING_CONVERTER_HPP
#define STRING_CONVERTER_HPP

#include <iostream>
#include <string>
#include <algorithm>

class StringConverter {
public:
	static std::wstring StringToWString(std::string string);
	static std::string WStringToString(std::wstring string);
	static const wchar_t* StringToWChar(std::string string, const size_t size = 0);
	static std::string WcharToString(wchar_t* wideString, const size_t size);
	static std::string ToLowerCase(std::string string);
};

#endif // !STRING_CONVERTER_HPP
