#include "Matrix.h"
#include <vector>
#include <string>

#ifndef IMAGE_H
#define IMAGE_H

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
	Image(std::string ASCII, std::string color_ASCII, char delimiter = 'Z');
	Image(std::wstring ASCII, int width, int height, char delimiter = 'Z');

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

	int width_, height_;
	char delimiter_;
	std::string ASCII_;
	std::wstring Wide_ASCII_;
};

#endif // !IMAGE_H
