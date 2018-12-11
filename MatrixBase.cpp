#include "MatrixBase.h"
#include "Image.h"
#include <conio.h>
#include <iostream>
#include <random>

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
			if (exclude_spaces)
			{ // Excludes spaces and new lines
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
void MatrixBase::addTextToMatrix(int position_x, int position_y, char alignment, std::string text, std::vector<std::vector<char>>& matrix, int paragraph_width, int paragraph_height)
{
	int top_left_x = 0;
	int top_left_y = 0;
	int y_offset = 0;

	// Exists for readability sake alone
	int top_right_x = 0;

	switch (alignment)
	{
	case 'l':
		top_left_x = position_x;
		top_left_y = position_y;

		addLeftAlignedTextToMatrix(top_left_x, top_left_y, text, matrix, paragraph_width, paragraph_height);

		break;
	case 'r':
		top_right_x = paragraph_width - 1;
		top_left_x = position_x - paragraph_width;
		top_left_y = position_y;

		y_offset = addLeftAlignedTextToMatrix(top_left_x, top_left_y, text, matrix, paragraph_width, paragraph_height) + 1;

		for (int i = 0; i < y_offset; i++) // For each row
		{
			int white_space_counter = 0; // Calculate number of spaces after last letter
			bool found_letter = false;
			for (int j = 0; j < paragraph_width - 1; j++)
			{
				if (matrix[top_left_y + i][top_left_x + j] == ' ')
					white_space_counter++;
				else
				{
					found_letter = true;
					white_space_counter = 0;
				}
			}

			if (!found_letter) // Entire line of white space? Ignore it!
				break;

			std::vector<char> temp = std::vector<char>(paragraph_width - 1, ' '); // Populate temporary Matrix
			for (int j = 0; j < paragraph_width - 1 - white_space_counter; j++)
			{
				temp[j] = matrix[top_left_y + i][top_left_x + j];
			}

			for (int j = 0; j < paragraph_width - 1 - white_space_counter; j++) // Clear original Matrix
			{
				matrix[top_left_y + i][top_left_x + j] = ' ';
			}
			for (int j = 0; j < paragraph_width - 1 - white_space_counter; j++) // Swap elements in original matrix
			{
				if (temp[(paragraph_width - 1 - white_space_counter) - j - 1] != ' ')
					matrix[top_left_y + i][top_right_x - j] = temp[(paragraph_width - 1 - white_space_counter) - j - 1];
			}
		}
		break;
	case 'm':
		top_left_x = position_x + 1 - (paragraph_width / 2);
		top_left_y = position_y + 1 - (paragraph_height / 2);

		y_offset = addLeftAlignedTextToMatrix(top_left_x, top_left_y, text, matrix, paragraph_width, paragraph_height) + 1;

		for (int i = 0; i < y_offset; i++) // For each row
		{
			int white_space_counter = 0; // Calculate number of spaces after last letter
			bool found_letter = false;
			for (int j = 0; j < paragraph_width - 1; j++)
			{
				if (matrix[top_left_y + i][top_left_x + j] == ' ')
					white_space_counter++;
				else
				{
					found_letter = true;
					white_space_counter = 0;
				}
			}

			if (!found_letter) // Entire line of white space? Ignore it!
				break;

			std::vector<char> temp = std::vector<char>(paragraph_width - 1, ' '); // Populate temporary Matrix
			for (int j = 0; j < paragraph_width - 1 - white_space_counter; j++)
			{
				temp[j] = matrix[top_left_y + i][top_left_x + j];
			}

			for (int j = 0; j < white_space_counter / 2; j++) // Populate original matrix with new spacing alignment
			{
				matrix[top_left_y + i][top_left_x + j] = ' ';
			}
			for (int j = 0; j < paragraph_width - 1 - white_space_counter; j++)
			{
				matrix[top_left_y + i][top_left_x + j + white_space_counter / 2] = temp[j];
			}
		}
		break;
	default:
		break;
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

// Replaces every character in given matrix with white space
void MatrixBase::clearMatrix(int width, int height, std::vector<std::vector<char>>& matrix)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			matrix[i][j] = ' ';
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

// Decides whether to indent or not (At the end of a word AND at the end of the line)
bool MatrixBase::shouldIndent(std::string text, int letter_index, int matrix_iterator, int paragraph_width)
{
	int letter_counter = 0;

	if (letter_index != 0 && text[letter_index - 1] == ' ' || letter_index == 0 && text[letter_index] != ' ')
	{
		for (int k = letter_index; k < text.length(); k++) // Iterate over word to find best place for indent
		{
			//std::cout << text[k];
			if (text[k] == ' ' || text[k] == '\0' || k >= text.length() - 1)
			{
				if (matrix_iterator + letter_counter > paragraph_width - 1)
				{
					//std::cout << "^\n";
					return true;
				}
				break;
			}
			letter_counter++;
		}
	}
	return false;
}

// Adds text to matrix (Left-aligned) Returns the number of rows in the matrix
int MatrixBase::addLeftAlignedTextToMatrix(int top_left_x, int top_left_y, std::string text, std::vector<std::vector<char>>& matrix, int paragraph_width, int paragraph_height)
{
	int y_offset = 0;

	if (paragraph_width == 0) // Single Line Mode
		for (int j = 0; j < text.length(); j++)
			matrix[top_left_y][top_left_x + j] = text[j];
	else // Multiple Line Mode
	{
		int max_line_index = (paragraph_width - 1);
		int matrix_iterator = 0;

		for (int j = 0; j < text.length(); j++)
		{
			if (shouldIndent(text, j, matrix_iterator, paragraph_width - 1))
			{
				y_offset++;
				matrix_iterator = 0;
				max_line_index += (paragraph_width - 1);
			}
			matrix[top_left_y + y_offset][top_left_x + matrix_iterator] = text[j];
			matrix_iterator++;
		}
	}
	return y_offset;
}
