#include "MatrixBase.h"
#include "Image.h"
#include <conio.h>
#include <iostream>
#include <random>

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
void MatrixBase::addImageToMatrix(int center_position_x, int center_position_y, Image & image, std::vector<std::vector<char>>& matrix, bool exclude_spaces)
{
	if (image.position.x_position_min == 0)
	{
		// Short version of what the below code does (Without rounding errors)
		/*image.position.x_position_min = center_position_x - round(image.getWidth() / 2);
		image.position.x_position_max = center_position_x + round(image.getWidth() / 2);
		image.position.y_position_min = center_position_y - round(image.getHeight() / 2);
		image.position.y_position_max = center_position_y + round(image.getHeight() / 2);//*/

		int temp_width = image.getWidth();
		if (image.getWidth() % 2 != 0)
		{ // Odd number? Oh boy... KILL ME
			temp_width--;
			image.position.x_position_max = center_position_x + temp_width / 2 + 1;
		}
		else
			image.position.x_position_max = center_position_x + temp_width / 2;
		image.position.x_position_min = center_position_x - temp_width / 2;

		int temp_height = image.getHeight();
		if (image.getHeight() % 2 != 0)
		{ // Odd number? Oh boy... KILL ME
			temp_height--;
			image.position.y_position_max = center_position_y + temp_height / 2 + 1;
		}
		else
			image.position.y_position_max = center_position_y + temp_height / 2;
		image.position.y_position_min = center_position_y - temp_height / 2;
	}
	int x = 0;
	int y = 0;
	int x_position_temp = image.position.x_position_min;
	while (image.position.y_position_min < image.position.y_position_max)
	{
		while (x_position_temp < image.position.x_position_max)
		{
			if (exclude_spaces) { // Ixcludes spaces and new lines
				if (image.image_matrix[y][x] != ' ' && image.image_matrix[y][x] != '\0')
					matrix[image.position.y_position_min][x_position_temp] = image.image_matrix[y][x];
			}
			else
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

// Adds a simple line of text to a matrix at the specified coordinates
void MatrixBase::addTextToMatrix(int top_left_x, int top_left_y, std::string text, std::vector<std::vector<char>>& matrix)
{
	for (int j = 0; j < text.length(); j++)
	{
		matrix[top_left_y][top_left_x + j] = text[j];
	}
}

// draws a hollow rectangle to the provided matrix
void MatrixBase::drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>>& matrix)
{
	for (int j = 0; j < width - 1; j++)
	{
		matrix[top_left_y][j + top_left_x] = character;
		matrix[top_left_y + height - 1][j + top_left_x] = character;
	}
	for (int i = 0; i < height; i++)
	{
		matrix[top_left_y + i][top_left_x] = character;
		matrix[top_left_y + i][top_left_x + width - 1] = character;
	}
}

// draws a hollow rectangle to the provided matrix and flags the location
void MatrixBase::drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>>& matrix, bool **& element_is_occupied)
{
	for (int j = 0; j < width - 1; j++)
	{
		matrix[top_left_y][j + top_left_x] = character;
		matrix[top_left_y + height - 1][j + top_left_x] = character;
		element_is_occupied[top_left_y][j + top_left_x] = true;
		element_is_occupied[top_left_y + height - 1][j + top_left_x] = true;
	}
	for (int i = 0; i < height; i++)
	{
		matrix[top_left_y + i][top_left_x] = character;
		matrix[top_left_y + i][top_left_x + width - 1] = character;
		element_is_occupied[top_left_y + i][top_left_x] = true;
		element_is_occupied[top_left_y + i][top_left_x + width - 1] = true;
	}
}

// draws a solid rectangle to the provided matrix
void MatrixBase::drawSolidRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>>& matrix)
{
	for (int j = 0; j < width; j++)
		for (int i = 0; i < height; i++)
			matrix[top_left_y + i][top_left_x + j] = character;
}

// Freezes entire program and waits for input from user. -- DEPRECATED --
void MatrixBase::waitForInput()
{
	_getch();
	char c = ' ';
	while (c == ' ')
		c = _getch();
}

int MatrixBase::generateRandomNumber(int min, int max)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

	return dist(rng);
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