#include "Image.h"
#include <iostream>

Image::Image() 
	: ASCII_{ "" }, delimiter_{ 'Z' }, width_{ 0 }, height_{ 0 }
{
}

Image::Image(std::string ASCII, char delimiter) 
	: ASCII_{ ASCII }, delimiter_{ delimiter }, width_{ 0 }, height_{ 0 }
{
	setImageDimensions();
	populateImageWithASCII();
}

Image::Image(std::string ASCII, std::string color_ASCII, char delimiter)
	: ASCII_{ ASCII }, delimiter_{ delimiter }, width_{ 0 }, height_{ 0 }
{
	setImageDimensions();
	populateImageWithASCII();
}

Image::Image(std::wstring ASCII, int width, int height, char delimiter) 
	: Wide_ASCII_{ ASCII }, delimiter_{ delimiter }, width_{ width }, height_{ height },
	image_matrix(width, height)
{
	populateImageWithWideASCII();
}

// Sets width and height of image matrix
void Image::setImageDimensions()
{
	int temp_width = 0;
	for (char& c : ASCII_)
	{
		if (c != delimiter_)
		{
			temp_width++;
		}
		if (c == delimiter_)
		{
			if (temp_width > width_)// Find largest width (b/c ASCII can Generate varied widths :/
				width_ = temp_width;
			temp_width = 0;
			++height_;
		}
	}
	if (temp_width > width_) { // for lines that do not end in a delimeter
		width_ = temp_width;
		++height_;
	}
	image_matrix = Matrix(width_, height_);
}

// Fills image matrix with correct ASCII symbols
void Image::populateImageWithASCII()
{
	int width_iterator = 0;
	int height_iterator = 0;

	for (std::string::iterator it = ASCII_.begin(); it != ASCII_.end() && height_iterator < height_; ++it)
	{
		if (*it != delimiter_)
		{
			image_matrix[height_iterator][width_iterator] = *it;
			width_iterator++;
		}
		if (*it == delimiter_)
		{
			height_iterator++;
			width_iterator = 0;
		}
	}
}
// Fills image matrix with correct ASCII symbols saved as a wstring
void Image::populateImageWithWideASCII()
{
	int width_iterator = 0;
	int height_iterator = 0;

	for (std::wstring::iterator it = Wide_ASCII_.begin(); it != Wide_ASCII_.end() && height_iterator < height_; ++it)
	{
		char c = static_cast<char>(*it);
		if (c != delimiter_)
		{
			image_matrix[height_iterator][width_iterator] = c;
			width_iterator++;
		}
		if (c == delimiter_)
		{
			height_iterator++;
			width_iterator = 0;
		}
	}
}

// Displays the image on the screen. [FOR DEBUG ONLY!]
void Image::DEBUG_printImage()
{
	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			std::cout << image_matrix[i][j];
		}
		std::cout << "\n";
	}
}
