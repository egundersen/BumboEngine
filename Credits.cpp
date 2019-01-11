#include "Credits.h"

Credits::Credits(int width, int height, BitmapDefinition &image_file_path, Matrix &screen_matrix)
	: width_{ width }, height_{ height }, credits_matrix_(width, height), screen_matrix_{ screen_matrix }, image_file_path_{ image_file_path }
{
}

void Credits::refreshScreen() 
{
	displayScreen();
}

// Clears all text on the matrix (aside from the border)
void Credits::clearText()
{
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_ - 8; j++) {
			credits_matrix_[i][j + 4] = ' ';
			credits_matrix_[i][j + 4].setColor(255, 255, 255);
		}
	}

	addTextToMatrix(5, 1, 'l', "Upon finally opening your father's package... the contents are revealed. It appears to be some type of picture or secret code.", credits_matrix_, 69, 2);
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

	Image thank_you_letters(
		"===[]=== []   []    []    []   [] []  []       []    []  [[]]  []  []Z   []    []   []   [][]   []]  [] [] []         []  []  []  [] []  []Z   []    []===[]  []__[]  [][] [] [][]           [][]   []  [] []  []Z   []    []   [] []    [] [] [][] [] []           []    []  [] []  []Z   []    []   [] []    [] []  [[] []  []          []     [[]]  [][][]Z",
		"RRRRRRRR RR   RR    RR    RR   RR RR  RR       RR    RR  RRRR  RR  RRZ   RR    RR   RR   RRRR   RRR  RR RR RR         RR  RR  RR  RR RR  RRZ   RR    RRRRRRR  RRRRRR  RRRR RR RRRR           RRRR   RR  RR RR  RRZ   RR    RR   RR RR    RR RR RRRR RR RR           RR    RR  RR RR  RRZ   RR    RR   RR RR    RR RR  RRR RR  RR          RR     RRRR  RRRRRRZ");
	Image for_playing_letters(
		"[]====|  [[]]  [][]]     [][]] []      []  []  [] [] []   []  [[][]] Z[]    | []  [] []  []    []  [][]     [][] []  [] [] []]  [] []      Z[]==|   []  [] [][][]    [][]] []    []__[] [][]  [] [][] [] [] |==[]Z[]      []  [] [][]      []    []   []    [] []   [] [] [][] []    []Z[]       [[]]  [] []_    []    [][] []    [] []   [] []  [[]  [[][]] Z",
		"RRRRRRR  RRRR  RRRRR     RRRRR RR      RR  RR  RR RR RR   RR  RRRRRR ZRR    R RR  RR RR  RR    RR  RRRR     RRRR RR  RR RR RRR  RR RR      ZRRRRR   RR  RR RRRRRR    RRRRR RR    RRRRRR RRRR  RR RRRR RR RR RRRRRZRR      RR  RR RRRR      RR    RR   RR    RR RR   RR RR RRRR RR    RRZRR       RRRR  RR RRR    RR    RRRR RR    RR RR   RR RR  RRR  RRRRRR Z");
	Image press_enter("Press ENTER to open the package", "R");
	Image created_by("Created by TEAM OVERKILLZat College of Marin", "C");

	addImageToMatrix(39, 7, thank_you_letters, credits_matrix_);
	addImageToMatrix(39, 13, for_playing_letters, credits_matrix_);
	addImageToMatrix(39, 23, created_by, credits_matrix_);
	addImageToMatrix(39, 30, press_enter, credits_matrix_);
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
