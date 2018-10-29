#include "StartScreen.h"
#include "Image.h"
#include <iostream>

StartScreen::StartScreen(int width, int height) : width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), empty_vector_(width, ' ')
{
	setBackgroundText();
	displayScreen();
	waitForInput();
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
	int newLineCounter = 0;
	for (auto line : matrix_)
	{
		if (line == empty_vector_)
		{
			newLineCounter++;
		}
		else
		{
			if (newLineCounter != 0)
			{
				std::cout << std::string(newLineCounter, '\n');
				newLineCounter = 0;
			}
			for (auto x : line)
				std::cout << x;
		}
	}
	std::cout << std::string(newLineCounter, '\n');
}
