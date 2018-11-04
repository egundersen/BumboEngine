#include "MatrixBase.h"

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

class StartScreen : public MatrixBase
{
public:
	StartScreen(int width, int height, std::vector<std::vector<std::string>> &matrix_display);
private:
	// Setters
	void setBackgroundText();

	// Output Displays
	void displayScreen();

	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> matrix_;
	std::vector<char> empty_vector_;
	int width_;
	int height_;
};

#endif // !STARTSCREEN_H
