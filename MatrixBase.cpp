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

// draws a rectangle to the provided matrix
void MatrixBase::drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>>& matrix)
{
	for (int j = 0; j < width - 1; j++) {
		matrix[top_left_y][j + top_left_x] = character;
		matrix[top_left_y + height - 1][j + top_left_x] = character;
	}
	for (int i = 0; i < height; i++) {
		matrix[top_left_y + i][top_left_x] = character;
		matrix[top_left_y + i][top_left_x + width - 1] = character;
	}
}

// Freezes entire program and waits for input from user. -- DEPRECATED --
void MatrixBase::waitForInput()
{
	_getch();
	char c = ' ';
	while (c == ' ')
		c = _getch();
}

// Generates random sequence.
void MatrixBase::generateRandomSequence(std::vector<std::shared_ptr<int>> & random_sequence, int min, int max)
{
	for (int i = min; i < max + min; ++i)
	{
		int r;
		do
		{
			r = rand() % max + 1;
		} while (contains(random_sequence, r));
		std::shared_ptr<int> number = std::make_shared<int>();
		*number = r;
		random_sequence.push_back(number);
	}
}

// Generates in-order sequence.
void MatrixBase::generateInOrderSequence(std::vector<std::shared_ptr<int>> &in_order_sequence, int min, int max)
{
	for (int i = min; i < max; i++)
	{
		std::shared_ptr<int> number = std::make_shared<int>();
		*number = i;
		in_order_sequence.push_back(number);
	}
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