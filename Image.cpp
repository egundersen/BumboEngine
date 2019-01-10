#include "Image.h"

Image::Image()
	: ASCII_{ "" }, ASCII_colors_{ "" }, delimiter_{ 'Z' }, width_{ 0 }, height_{ 0 }
{
}

Image::Image(std::string ASCII, char delimiter)
	: ASCII_{ ASCII }, ASCII_colors_{ "" }, delimiter_{ delimiter }, width_{ 0 }, height_{ 0 }
{
	setImageDimensions();
	populateImageWithASCII();
}

Image::Image(std::string ASCII, std::string ASCII_colors, char delimiter)
	: ASCII_{ ASCII }, ASCII_colors_{ ASCII_colors }, delimiter_{ delimiter }, width_{ 0 }, height_{ 0 }
{
	setImageDimensions();
	populateImageWithASCII();
	if (ASCII_colors_.length() == 1)
		colorImageSingleColor();
	else
		colorImageWithASCII();
}

Image::Image(std::wstring ASCII, int width, int height, char delimiter)
	: wide_ASCII_{ ASCII }, ASCII_{ "" }, ASCII_colors_{ "" }, delimiter_{ delimiter }, width_{ width }, height_{ height },
	image_matrix(width, height)
{
	populateImageWithWideASCII();
}

Image::Image(std::wstring ASCII, std::wstring ASCII_colors, int width, int height, char delimiter)
	: wide_ASCII_{ ASCII }, wide_ASCII_colors_{ ASCII_colors }, ASCII_{ "" }, ASCII_colors_{ "" }, delimiter_{ delimiter }, width_{ width }, height_{ height },
	image_matrix(width, height)
{
	populateImageWithWideASCII();
	colorWideImageWithASCII();
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
	if (temp_width > width_)
	{ // for lines that do not end in a delimeter
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

	for (std::wstring::iterator it = wide_ASCII_.begin(); it != wide_ASCII_.end() && height_iterator < height_; ++it)
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

// Colors Image Matrix with correct colors from ASCII Colors string
void Image::colorImageWithASCII()
{
	int width_iterator = 0;
	int height_iterator = 0;

	for (std::string::iterator it = ASCII_colors_.begin(); it != ASCII_colors_.end() && height_iterator < height_; ++it)
	{
		if (*it != delimiter_)
		{
			image_matrix[height_iterator][width_iterator].setColor(ColorPalette(*it).getRGBA());
			width_iterator++;
		}
		if (*it == delimiter_)
		{
			height_iterator++;
			width_iterator = 0;
		}
	}
}

// Colors Image Matrix with correct colors from ASCII Colors string saved as a wstring
void Image::colorWideImageWithASCII()
{
	int width_iterator = 0;
	int height_iterator = 0;

	for (std::wstring::iterator it = wide_ASCII_colors_.begin(); it != wide_ASCII_colors_.end() && height_iterator < height_; ++it)
	{
		char c = static_cast<char>(*it);
		if (c != delimiter_)
		{
			image_matrix[height_iterator][width_iterator].setColor(ColorPalette(*it).getRGBA());
			width_iterator++;
		}
		if (c == delimiter_)
		{
			height_iterator++;
			width_iterator = 0;
		}
	}
}

// Colors Image Matrix with a single color (uses the first and only color in the ASCII Colors string)
void Image::colorImageSingleColor()
{
	int width_iterator = 0;
	int height_iterator = 0;

	for (std::string::iterator it = ASCII_.begin(); it != ASCII_.end() && height_iterator < height_; ++it)
	{
		if (*it != delimiter_)
		{
			image_matrix[height_iterator][width_iterator].setColor(ColorPalette(ASCII_colors_[0]).getRGBA());
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
void Image::DEBUG_printImage()
{
#ifdef _DEBUG
	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			std::cout << image_matrix[i][j];
		}
		std::cout << "\n";
	}
#endif
}
