#ifndef COLOREDSTRING_H
#define COLOREDSTRING_H

#include <string>

// Assigns a char (corresponding to a color code) to every char in a string or wstring 
class ColoredString
{
public:
	ColoredString() 
		: ASCII_{ "" }, ASCII_colors_{ "" }, wide_ASCII_{ nullptr }, wide_ASCII_colors_{ nullptr }, using_wide_strings_{ false }, wstring_width_{ 0 }, wstring_height_{ 0 } { }
	ColoredString(std::string ASCII, std::string ASCII_colors) 
		: ASCII_{ ASCII }, ASCII_colors_{ ASCII_colors }, wide_ASCII_{ nullptr }, wide_ASCII_colors_{ nullptr }, using_wide_strings_{ false }, wstring_width_{ 0 }, wstring_height_{ 0 } { }
	ColoredString(std::wstring wide_ASCII[], std::wstring wide_ASCII_colors[], int wstring_width, int wstring_height)
		: wide_ASCII_{ wide_ASCII }, wide_ASCII_colors_{ wide_ASCII_colors }, ASCII_{ "" }, ASCII_colors_{ "" }, using_wide_strings_{ true }, wstring_width_{ wstring_width }, wstring_height_{ wstring_height } { }

	std::string getASCII() { return ASCII_; }
	std::string getColors() { return ASCII_colors_; }
	std::wstring *getWideASCII() { return wide_ASCII_; }
	std::wstring *getWideColors() { return wide_ASCII_colors_; }
	bool usesWideStrings() { return using_wide_strings_; }
	int getWstringWidth() { return wstring_width_; }
	int getWstringHeight() { return wstring_height_; }

private:
	std::string ASCII_, ASCII_colors_;
	std::wstring *wide_ASCII_, *wide_ASCII_colors_;
	int wstring_width_, wstring_height_;
	bool using_wide_strings_;
};

#endif // !COLOREDSTRING_H
