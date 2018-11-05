#include "Image.h"
#include <iostream>

// Creates an ASCII image. The Character: 'N' is used as a delimeter
Image::Image(std::string i_ASCII, char delimiter) : ASCII_{ i_ASCII }, delimiter_{ delimiter }
{
	setImageDimensions();
	populateImageWithASCII();
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
	image_matrix.resize(height_, std::vector<char>(width_));
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

// Displays the image on the screen. [FOR DEBUG ONLY!]
void Image::DEBUG_displayImage()
{
	for (auto line : image_matrix)
	{
		for (auto x : line)
			std::cout << x;
		std::cout << "\n";
	}
}
