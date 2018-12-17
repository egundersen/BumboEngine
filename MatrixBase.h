#include "Image.h"
#include "Matrix.h"
#include <memory>
#include <algorithm>

#ifndef MATRIXBASE_H
#define MATRIXBASE_H

struct PlayerPosition
{
	int x;
	int y;
};

// Useful functions that come standard with the Bumbo Engine (Can be used at will)
class MatrixBase
{
protected:
	void addImageToMatrix(int center_position_x, int center_position_y, Image &image, Matrix &matrix, bool exclude_spaces = false);
	void addTextToMatrix(int position_x, int position_y, char alignment, std::string text, Matrix &matrix, int paragraph_width = 0, int paragraph_height = 0);
	void drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, Matrix &matrix);
	void drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, Matrix &matrix, bool **&element_is_occupied);
	void drawSolidRectangle(int top_left_x, int top_left_y, int width, int height, char character, Matrix &matrix);
	void clearMatrix(int width, int height, Matrix &matrix);

	int generateRandomNumber(int min, int max);
	void generateRandomSequence(std::vector<std::shared_ptr<int>> &random_sequence, int min, int max);
	void generateInOrderSequence(std::vector <std::shared_ptr<int>> &in_order_sequence, int min, int max);

	template<typename Container, typename T>
	inline bool contains(Container const & container, T const & value);

	void DEBUG_printMatrix(Matrix &matrix);
	void DEBUG_print2DVector(int width, int height, std::vector<std::vector<char>>& matrix);
	void DEBUG_printImage(Image &image);

	// Deprecated Function (Legacy Support)
	void addImageToMatrix(int center_position_x, int center_position_y, Image &image, std::vector<std::vector<char>> &matrix, bool exclude_spaces = false);
	void addTextToMatrix(int top_left_x, int top_left_y, char alignment, std::string text, std::vector<std::vector<char>> &matrix, int paragraph_width = 0, int paragraph_height = 0);
	void drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>> &matrix);
	void drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied);
	void drawSolidRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>> &matrix);
	void clearMatrix(int width, int height, std::vector<std::vector<char>>& matrix);
	void waitForInput();
private:
	bool shouldIndent(std::string text, int letter_index, int matrix_iterator, int paragraph_width);
	int addLeftAlignedTextToMatrix(int top_left_x, int top_left_y, std::string text, Matrix &matrix, int paragraph_width, int paragraph_height);
	
	// Deprecated Function (Legacy Support)
	int addLeftAlignedTextToMatrix(int top_left_x, int top_left_y, std::string text, std::vector<std::vector<char>>& matrix, int paragraph_width, int paragraph_height);
};

template<typename Container, typename T>
inline bool MatrixBase::contains(Container const & container, T const & value)
{
	using std::begin;
	auto it = std::find_if(begin(container), end(container), [&](std::shared_ptr<T> const& p) {
		return *p == value; // assumes MyType has operator==
	});

	if (it != end(container)) { return true; }
	else
		return false;
}

#endif // !MATRIXBASE_H