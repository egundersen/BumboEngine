#include "Image.h"

#ifndef MATRIXBASE_H
#define MATRIXBASE_H

struct PlayerPosition
{
	int x;
	int y;
};

class MatrixBase
{
public:
	void addImageToMatrix(int center_position_x, int center_position_y, Image &image, std::vector<std::vector<char>> &matrix, bool **&element_is_occupied);
	void addImageToMatrix(int center_position_x, int center_position_y, Image &image, std::vector<std::vector<char>> &matrix);
	void waitForInput();
	void DEBUG_simpleDisplay(Image &image);
};

#endif // !MATRIXBASE_H
