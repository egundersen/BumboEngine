#include "Credits.h"
#include "Image.h"
#include <iostream>

Credits::Credits(int width, int height, BitmapDefinition &image_file_path, Matrix &screen_matrix)
	: width_{ width }, height_{ height }, credits_matrix_(width, height), empty_vector_(width, ' '), screen_matrix_{ screen_matrix }, image_file_path_{ image_file_path }
{
}

void Credits::refreshScreen() 
{
	displayScreen();
}

void Credits::setBackgroundText()
{
	drawSolidRectangle(1, 1, 3, height_ - 2, 'X', 'I', credits_matrix_);
	drawSolidRectangle(width_ - 4, 1, 3, height_ - 2, 'X', 'I', credits_matrix_);

	drawRectangle(5, 1, 12, 1, '=', 'P', credits_matrix_);
	drawRectangle(5, 2, 8, 1, '=', 'P', credits_matrix_);
	drawRectangle(5, 3, 4, 1, '=', 'P', credits_matrix_);

	drawRectangle(width_ - 17, 1, 12, 1, '=', 'P', credits_matrix_);
	drawRectangle(width_ - 13, 2, 8, 1, '=', 'P', credits_matrix_);
	drawRectangle(width_ - 9, 3, 4, 1, '=', 'P', credits_matrix_);

	drawRectangle(5, height_ - 4, 4, 1, '=', 'P', credits_matrix_);
	drawRectangle(5, height_ - 3, 8, 1, '=', 'P', credits_matrix_);
	drawRectangle(5, height_ - 2, 12, 1, '=', 'P', credits_matrix_);

	drawRectangle(width_ - 9, height_ - 4, 4, 1, '=', 'P', credits_matrix_);
	drawRectangle(width_ - 13, height_ - 3, 8, 1, '=', 'P', credits_matrix_);
	drawRectangle(width_ - 17, height_ - 2, 12, 1, '=', 'P', credits_matrix_);

	Image title_letters(
		"[]        [] []====| []   []        []     [][][] []====| []====|Z[]   []   [] []      []]  []        []       []   []    | []     Z[]  [][]  [] []====  [][] []        []       []   []==|   []==== Z [][]  [][]  []      [] [][]        []       []   []      []     Z  []    []   []====| []  [[]        [][][] [][][] []      []====|Z",
		"PM        PM PPPPPPM PM   PM        PM     PPPPPM PPPPPPM PPPPPPMZPM   PM   PM PM      PPM  PM        PM       PM   PM    M PM     ZPM  PPPM  PM PMMMMMM PPPM PM        PM       PM   PMMMM   PMMMMM Z PMPM  PMPM  PM      PM PMPM        PM       PM   PM      PM     Z  PM    PM   PPPPPPM PM  PPM        PPPPPM PPPPPM PM      PPPPPPMZ");
	Image press_enter("Press ENTER to begin", "P");
	Image sprite_1(
		"   mmmm   Z  <[]MMm  Z   >MM/   Z  O3><EO  Z OY3E3EY  Z  %U  U%  Z",
		"   YYYY   Z  WAAYYY  Z   WYYJ   Z  JRWWRJ  Z JYRRRRY  Z  NY  YN  Z");
	Image sprite_2(
		"  #@@@@#  Z @@^\\/^@@ Z @ \\vv/ @ Z oxHxxHxo Z 0/####\\0 Z  %U  U%  Z",
		"  DDDDDD Z DDRJJRDD Z D JWWJ D Z JSSJJSSJ Z JTTTTTTJ Z  MD  DM  Z");
	Image sprite_3(
		"  /####\\  Z /##\\\"\\>  Z ## \\*<   Z goX><go  Z  #0XXH#0 Z  %U  U%  Z",
		"  JOOOOJO Z JOOJLJJ  Z OO JRJ   Z OJFJJOJ  Z  OJFFHOJ Z  HB  BH  Z");

	addImageToMatrix(28, 18, sprite_1, credits_matrix_);
	addImageToMatrix(39, 18, sprite_2, credits_matrix_);
	addImageToMatrix(50, 18, sprite_3, credits_matrix_);
	addImageToMatrix(39, 7, title_letters, credits_matrix_);
	addImageToMatrix(39, 30, press_enter, credits_matrix_);
	addTextToMatrix(58, height_ - 1, 'l', "BumboEngine v0.8", 'I', credits_matrix_);
#ifdef _DEBUG
	addTextToMatrix(5, height_ - 1, 'l', "Running DEBUG release : Expect Poor framerates", credits_matrix_);
#endif
}

void Credits::displayScreen()
{
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			char temp = credits_matrix_[i][j];
			screen_matrix_[i][j] = temp;
			screen_matrix_[i][j].setColor(credits_matrix_[i][j].getRGBA());
		}
	}
}
