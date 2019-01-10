#ifndef TEXTURE_H
#define TEXTURE_H

#include "MatrixBase.h"
#include "ColoredString.h"
#include "Image.h"

// Takes input ASCII art and adds it to the provided matrix
class Texture : MatrixBase
{
public:
	Texture(int center_position_x, int center_position_y, ColoredString colored_ascii, Matrix &matrix)
	{
		if (!colored_ascii.usesWideStrings())
		{
			Image image(colored_ascii.getASCII(), colored_ascii.getColors());
			addImageToMatrix(center_position_x, center_position_y, image, matrix, true);
		}
		else
		{
			std::vector<Image> lines;
			int iterator = 0;
			for (int i = 0; i < colored_ascii.getWstringHeight(); i++)
			{
				lines.push_back(Image(colored_ascii.getWideASCII()[i], colored_ascii.getWideColors()[i], colored_ascii.getWstringWidth(), 1));
				addImageToMatrix(center_position_x, center_position_y + iterator, lines[iterator], matrix, true);
				iterator++;
			}
		}
	}

	Texture(int center_position_x, int center_position_y, std::string ASCII, std::string ASCII_colors, Matrix &matrix)
	{
		Image image(ASCII, ASCII_colors);
		addImageToMatrix(center_position_x, center_position_y, image, matrix, true);
	}
};

#endif // !TEXTURE_H