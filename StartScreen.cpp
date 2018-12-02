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
	drawSolidRectangle(1, 1, 3, height_ - 2, 'X', matrix_);
	drawSolidRectangle(width_ - 4, 1, 3, height_ - 2, 'X', matrix_);

	drawRectangle(5, 1, 12, 1, '=', matrix_);
	drawRectangle(5, 2, 8, 1, '=', matrix_);
	drawRectangle(5, 3, 4, 1, '=', matrix_);

	drawRectangle(width_ - 17, 1, 12, 1, '=', matrix_);
	drawRectangle(width_ - 13, 2, 8, 1, '=', matrix_);
	drawRectangle(width_ - 9, 3, 4, 1, '=', matrix_);

	drawRectangle(5, height_ - 4, 4, 1, '=', matrix_);
	drawRectangle(5, height_ - 3, 4, 1, '=', matrix_);
	drawRectangle(5, height_ - 2, 12, 1, '=', matrix_);

	drawRectangle(width_ - 9, height_ - 4, 4, 1, '=', matrix_);
	drawRectangle(width_ - 13, height_ - 3, 8, 1, '=', matrix_);
	drawRectangle(width_ - 17, height_ - 2, 12, 1, '=', matrix_);

	Image title_letters("[]        [] []====| []   []        []     [][][] []====| []====|Z[]   []   [] []      []]  []        []       []   []    | []     Z[]  [][]  [] []====  [][] []        []       []   []==|   []==== Z [][]  [][]  []      [] [][]        []       []   []      []     Z  []    []   []====| []  [[]        [][][] [][][] []      []====|Z");
	Image press_enter("Press ENTER to begin");
	Image symbol("     X     Z     X     Z     X     ZXXXX=O=XXXXZ     X     Z     X     Z     X     Z");
	
	addImageToMatrix(39, 18, symbol, matrix_);
	addImageToMatrix(39, 7, title_letters, matrix_);
	addImageToMatrix(39, 30, press_enter, matrix_);
	addTextToMatrix(58, height_ - 1, "BumboEngine v0.8", matrix_);
}

void StartScreen::displayScreen()
{
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			matrix_display_[i][j] = std::string(1, matrix_[i][j]);
		}
	}
}
