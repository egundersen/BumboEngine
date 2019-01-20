#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "MatrixBase.h"
#include "Matrix.h"

class SplashScreen: MatrixBase
{
public:
	SplashScreen(int width, int height, Matrix &screen_matrix)
	{
		std::vector<std::vector<char>> matrix = std::vector<std::vector<char>>(height, std::vector<char>(width, ' '));
		Image loading("Loading...");
		addImageToMatrix(width / 2, height / 2, loading, matrix);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				screen_matrix[i][j] = matrix[i][j];
			}
		}
	}
};

#endif // !SPLASHSCREEN_H
