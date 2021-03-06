#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "MatrixBase.h"

// Introduction Screen showed when the game finishes loading
class StartScreen : public MatrixBase
{
public:
	StartScreen(int width, int height, Matrix &screen_matrix);
private:
	// Setters
	void setBackgroundText();

	// Output Displays
	void displayScreen();

	Matrix &screen_matrix_, startscreen_matrix_;
	std::vector<char> empty_vector_;
	int width_;
	int height_;
};

#endif // !STARTSCREEN_H
