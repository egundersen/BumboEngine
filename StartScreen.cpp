#include "StartScreen.h"
#include "Image.h"
#include <iostream>

StartScreen::StartScreen(int width, int height, std::vector<std::vector<std::string>> &matrix_display)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), empty_vector_(width, ' '), matrix_display_{ matrix_display }
{
	setBackgroundText();
	displayScreen();
}

void StartScreen::setBackgroundText()
{
	for (int i = 1; i < height_ - 1; ++i)
	{
		matrix_[i][1] = 'X';
		matrix_[i][2] = 'X';
		matrix_[i][3] = 'X';
		matrix_[i][width_ - 2] = 'X';
		matrix_[i][width_ - 3] = 'X';
		matrix_[i][width_ - 4] = 'X';
	}
	for (int i = 10; i < height_ - 1; ++i)
		matrix_[i][45] = 'X';
	for (int j = 5; j < width_ - 5; ++j)
	{
		matrix_[1][j] = '=';
		matrix_[2][j] = '=';
	}
	//Image inventory_letters("Z===[]=== []   [][]      [][]==== []   [] ==[]== [][][] [][][][]    []Z   []    []]  [] []    [] []     []]  []   []   []  [] []  [] []  [] Z   []    [][] []  []  []  []==== [][] []   []   []  [] [][][]  [][]  Z   []    [] [][]   [][]   []     [] [][]   []   []  [] [][]     []   Z===[]=== []  [[]    []    []==== []  [[]   []   [][][] [] []_   []   Z");
	Image instructions("Z=====================================Z======== START SCREEN temp ==========Z                                     ZNavigate up and down      Arrow KeysZ                                     ZUse Selected Item         ENTERZ                                     ZExit inventory            BACKSPACEZZ");
	addImageToMatrix(24, 14, instructions, matrix_);
	//addImageToMatrix(39, 6, inventory_letters, matrix_);
}

void StartScreen::displayScreen()
{
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			matrix_display_[i][j] = std::string(1, matrix_[i][j]);
		}
	}
}
