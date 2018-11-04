#include "Image.h"
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
public:
	void addImageToMatrix(int center_position_x, int center_position_y, Image &image, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied);
	void addImageToMatrix(int center_position_x, int center_position_y, Image &image, std::vector<std::vector<char>> &matrix);
	void drawRectangle(int top_left_x, int top_left_y, int width, int height, char character, std::vector<std::vector<char>> &matrix);
	void waitForInput();
	void generateRandomSequence(std::vector<std::shared_ptr<int>> &random_sequence, int min, int max);
	void generateInOrderSequence(std::vector <std::shared_ptr<int>> &in_order_sequence, int min, int max);
	
	template<typename Container, typename T>
	inline bool contains(Container const & container, T const & value);

	void DEBUG_simpleDisplay(Image &image);
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