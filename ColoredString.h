#include <string>

#ifndef COLOREDSTRING_H
#define COLOREDSTRING_H

class ColoredString
{
public:
	ColoredString() 
		: ASCII_{ "" }, ASCII_colors_{ "" }, wide_ASCII_{ nullptr }, wide_ASCII_colors_{ nullptr }, using_wide_strings_{ false } {}
	ColoredString(std::string ASCII, std::string ASCII_colors) 
		: ASCII_{ ASCII }, ASCII_colors_{ ASCII_colors }, wide_ASCII_{ nullptr }, wide_ASCII_colors_{ nullptr }, using_wide_strings_{ false }  {}
	ColoredString(std::wstring wide_ASCII[], std::wstring wide_ASCII_colors[]) 
		: wide_ASCII_{ wide_ASCII }, wide_ASCII_colors_{ wide_ASCII_colors }, ASCII_{ "" }, ASCII_colors_{ "" }, using_wide_strings_{ true } {}

	std::string getASCII() { return ASCII_; }
	std::string getColors() { return ASCII_colors_; }
	std::wstring *getWideASCII() { return wide_ASCII_; }
	std::wstring *getWideColors() { return wide_ASCII_colors_; }
	bool usesWideStrings() { return using_wide_strings_; }

private:
	std::string ASCII_, ASCII_colors_;
	std::wstring *wide_ASCII_, *wide_ASCII_colors_;
	bool using_wide_strings_;
};

#endif // !COLOREDSTRING_H
