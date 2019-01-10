#ifndef IMAGE_H
#define IMAGE_H

#include "Matrix.h"
#include "ColorPalette.h"
#include <vector>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

struct Position_s
{
	int x_position_min = 0;
	int x_position_max = 0;
	int y_position_min = 0;
	int y_position_max = 0;
};

class Image
{
public:
	Image();
	Image(std::string ASCII, char delimiter = 'Z');
	Image(std::string ASCII, std::string ASCII_colors, char delimiter = 'Z');
	Image(std::wstring ASCII, int width, int height, char delimiter = 'Z');
	Image(std::wstring ASCII, std::wstring ASCII_colors, int width, int height, char delimiter = 'Z');

	// Setters
	Position_s position;
	Matrix image_matrix;

	//Getters
	int getWidth() { return width_; }
	int getHeight() { return height_; }

	// Output Displays
	void DEBUG_printImage();
private:
	//Setters
	void setImageDimensions();
	void populateImageWithASCII();
	void populateImageWithWideASCII();
	void colorImageWithASCII();
	void colorWideImageWithASCII();
	void colorImageSingleColor();

	int width_, height_;
	char delimiter_;
	std::string ASCII_, ASCII_colors_;
	std::wstring wide_ASCII_, wide_ASCII_colors_;
};

#endif // !IMAGE_H
