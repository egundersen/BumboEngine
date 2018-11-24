#include "MatrixBase.h"

#ifndef MAZE_H
#define MAZE_H

// Container class for the maze
class Maze : MatrixBase
{
public:
	Maze(std::vector<std::vector<char>> &world_matrix, int top_left_position_x, int top_left_position_y);

	void GENERATE_Maze();

private:
	void createSection(int offset_x, int offset_y, std::wstring *maze_segment, int number_of_lines);

	int position_x_, position_y_;
	std::vector<std::vector<char>> &world_matrix_;
};

#endif // !MAZE_H
