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

	//Setters
	void setImageDimensions();
	void populateImageWithASCII();

	//Getters
	int getWidth() { return width_; }
	int getHeight() { return height_; }
	std::vector<std::vector<char>> image_matrix;
	Position_s position;

	// Output Displays
	void DEBUG_displayImage();
private:
	int width_;
	int height_;
	char delimiter_;
	std::string ASCII_;
};

#endif // !IMAGE_H
