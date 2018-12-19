#include "MatrixBase.h"
#include "ColoredString.h"
#include "Image.h"

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture : MatrixBase
{
public:
	Texture(int center_position_x, int center_position_y, ColoredString colored_ascii, Matrix &matrix)
	{
		Image image(colored_ascii.getASCII(), colored_ascii.getColors());
		addImageToMatrix(center_position_x, center_position_y, image, matrix, true);
	}

private:

};

#endif // !TEXTURE_H