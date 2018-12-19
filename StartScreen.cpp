#include "StartScreen.h"
#include "Image.h"
#include <iostream>

StartScreen::StartScreen(int width, int height, Matrix &screen_matrix)
	: width_{ width }, height_{ height }, startscreen_matrix_(width, height), empty_vector_(width, ' '), screen_matrix_{ screen_matrix }
{
	setBackgroundText();
	displayScreen();
}

void StartScreen::setBackgroundText()
{
	drawSolidRectangle(1, 1, 3, height_ - 2, 'X', startscreen_matrix_);
	drawSolidRectangle(width_ - 4, 1, 3, height_ - 2, 'X', startscreen_matrix_);

	drawRectangle(5, 1, 12, 1, '=', startscreen_matrix_);
	drawRectangle(5, 2, 8, 1, '=', startscreen_matrix_);
	drawRectangle(5, 3, 4, 1, '=', startscreen_matrix_);

	drawRectangle(width_ - 17, 1, 12, 1, '=', startscreen_matrix_);
	drawRectangle(width_ - 13, 2, 8, 1, '=', startscreen_matrix_);
	drawRectangle(width_ - 9, 3, 4, 1, '=', startscreen_matrix_);

	drawRectangle(5, height_ - 4, 4, 1, '=', startscreen_matrix_);
	drawRectangle(5, height_ - 3, 4, 1, '=', startscreen_matrix_);
	drawRectangle(5, height_ - 2, 12, 1, '=', startscreen_matrix_);

	drawRectangle(width_ - 9, height_ - 4, 4, 1, '=', startscreen_matrix_);
	drawRectangle(width_ - 13, height_ - 3, 8, 1, '=', startscreen_matrix_);
	drawRectangle(width_ - 17, height_ - 2, 12, 1, '=', startscreen_matrix_);

	Image title_letters("[]        [] []====| []   []        []     [][][] []====| []====|Z[]   []   [] []      []]  []        []       []   []    | []     Z[]  [][]  [] []====  [][] []        []       []   []==|   []==== Z [][]  [][]  []      [] [][]        []       []   []      []     Z  []    []   []====| []  [[]        [][][] [][][] []      []====|Z");
	Image press_enter("Press ENTER to begin");
	Image sprite_1("   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z");
	Image sprite_2("   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z");
	Image sprite_3("   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z");
	
	addImageToMatrix(28, 18, sprite_1, startscreen_matrix_);
	addImageToMatrix(39, 18, sprite_2, startscreen_matrix_);
	addImageToMatrix(50, 18, sprite_3, startscreen_matrix_);
	addImageToMatrix(39, 7, title_letters, startscreen_matrix_);
	addImageToMatrix(39, 30, press_enter, startscreen_matrix_);
	addTextToMatrix(58, height_ - 1, 'l', "BumboEngine v0.8", startscreen_matrix_);
#ifdef _DEBUG
	addTextToMatrix(5, height_ - 1, 'l', "Running DEBUG release : Expect Poor framerates", startscreen_matrix_);
#endif
}

void StartScreen::displayScreen()
{
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			char temp = startscreen_matrix_[i][j];
			screen_matrix_[i][j] = temp;
			screen_matrix_[i][j].setColor(startscreen_matrix_[i][j].getRGBA());
		}
	}
}
