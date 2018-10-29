#include "MatrixBase.h"

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

class StartScreen : public MatrixBase
{
public:
	StartScreen() : width_{ 0 }, height_{ 0 } {}
	StartScreen(int width, int height);

	// Setters
	void setBackgroundText();

	// Output Displays
	void displayScreen();
private:
	std::vector<std::vector<char>> matrix_;
	std::vector<char> empty_vector_;
	int width_;
	int height_;
};

#endif // !STARTSCREEN_H
