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
	Image() : ASCII_{ 0 } {}
	Image(std::string i_ASCII, char delimiter = 'Z');

	// Setters
	Position_s position;
	std::vector<std::vector<char>> image_matrix;

	//Getters
	int getWidth() { return width_; }
	int getHeight() { return height_; }

	// Output Displays
	void DEBUG_displayImage();
private:
	//Setters
	void setImageDimensions();
	void populateImageWithASCII();

	int width_, height_;
	char delimiter_;
	std::string ASCII_;
};

#endif // !IMAGE_H
