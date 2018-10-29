#include "MatrixBase.h"
#include "Image.h"
#include <conio.h>
#include <iostream>

// Adds an image/text to a matrix at the specified coordinates and flags the location
void MatrixBase::addImageToMatrix(int center_position_x, int center_position_y, Image &image, std::vector<std::vector<char>>& matrix, bool **& element_is_occupied)
{
	if (image.position.x_position_min == 0)
	{
		image.position.x_position_min = center_position_x - round(image.getWidth() / 2);
		image.position.x_position_max = center_position_x + round(image.getWidth() / 2);
		image.position.y_position_min = center_position_y - round(image.getHeight() / 2);
		image.position.y_position_max = center_position_y + round(image.getHeight() / 2);
	}
	int x = 0;
	int y = 0;
	int x_position_temp = image.position.x_position_max;

	while (image.position.y_position_min < image.position.y_position_max - 1)
	{
		while (x_position_temp < image.position.x_position_max - 1)
		{
			element_is_occupied[image.position.y_position_min][x_position_temp] = true;
			matrix[image.position.y_position_min][x_position_temp] = image.image_matrix[y][x];
			++x_position_temp;
			++x;
		}
		x_position_temp = image.position.x_position_min;
		x = 0;
		++image.position.y_position_min;
		++y;
	}
}

// Adds an image/text to a matrix at the specified coordinates
void MatrixBase::addImageToMatrix(int center_position_x, int center_position_y, Image & image, std::vector<std::vector<char>>& matrix)
{
	if (image.position.x_position_min == 0)
	{
		image.position.x_position_min = center_position_x - round(image.getWidth() / 2);
		image.position.x_position_max = center_position_x + round(image.getWidth() / 2);
		image.position.y_position_min = center_position_y - round(image.getHeight() / 2);
		image.position.y_position_max = center_position_y + round(image.getHeight() / 2);
	}
	int x = 0;
	int y = 0;
	int x_position_temp = image.position.x_position_max;

	while (image.position.y_position_min < image.position.y_position_max)
	{
		while (x_position_temp <= image.position.x_position_max)
		{
			matrix[image.position.y_position_min][x_position_temp] = image.image_matrix[y][x];
			++x_position_temp;
			++x;
		}
		x_position_temp = image.position.x_position_min;
		x = 0;
		++image.position.y_position_min;
		++y;
	}
}

// Freezes entire program and waits for input from user. Input is then disregarded
void MatrixBase::waitForInput()
{
	_getch();
	char c = ' ';
	while (c == ' ')
		c = _getch();
}

// Displays image to screen (completely disregards existing formatting)
void MatrixBase::DEBUG_simpleDisplay(Image & image)
{
	for (int i = 0; i < image.getHeight(); ++i)
	{
		for (int j = 0; j < image.getWidth(); ++j)
		{
			std::cout << image.image_matrix[i][j];
		}
		std::cout << "\n";
	}//*/
}
