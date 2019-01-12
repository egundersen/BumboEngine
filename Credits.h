#include "MatrixBase.h"
#include "BitmapDefinition.h"

#ifndef CREDITS_H
#define CREDITS_H

class Credits : public MatrixBase
{
public:
	Credits(int width, int height, BitmapDefinition &bitmap, Matrix &screen_matrix);

	// Setters
	void setBackgroundText();
	void refreshScreen();
	void clearText();
private:
	// Setters
	void displayScreen();

	Matrix &screen_matrix_, credits_matrix_;
	BitmapDefinition &bitmap_;
	int width_, height_;
};

#endif // !CREDITS_H
