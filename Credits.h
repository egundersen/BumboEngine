#include "MatrixBase.h"
#include "BitmapDefinition.h"

#ifndef CREDITS_H
#define CREDITS_H

class Credits : public MatrixBase
{
public:
	Credits(int width, int height, BitmapDefinition &image_file_path, Matrix &screen_matrix);

	// Setters
	void setBackgroundText();
	void refreshScreen();
private:
	// Setters
	void displayScreen();

	Matrix &screen_matrix_, credits_matrix_;
	std::vector<char> empty_vector_;
	BitmapDefinition &image_file_path_;
	int width_;
	int height_;
};

#endif // !CREDITS_H
