#include "MatrixBase.h"

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

class StartScreen : public MatrixBase
{
public:
	StartScreen(int width, int height, Matrix &screen_matrix);
private:
	// Setters
	void setBackgroundText();

	// Output Displays
	void displayScreen();

	Matrix &screen_matrix_;
	std::vector<std::vector<char>> matrix_;
	std::vector<char> empty_vector_;
	int width_;
	int height_;
};

#endif // !STARTSCREEN_H
