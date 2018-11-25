#include "MatrixBase.h"

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

class SplashScreen: MatrixBase
{
public:
	SplashScreen(int width, int height, std::vector<std::vector<std::string>> &matrix_display)
	{
		std::vector<std::vector<char>> matrix = std::vector<std::vector<char>>(height, std::vector<char>(width, ' '));
		Image loading("Loading...");
		addImageToMatrix(width / 2, height / 2, loading, matrix);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				matrix_display[i][j] = std::string(1, matrix[i][j]);
			}
		}
	}
};

#endif // !SPLASHSCREEN_H
