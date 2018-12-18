#include "RGBA.h"

#ifndef COLORPALETTE_H
#define COLORPALETTE_H

class ColorPalette
{
public:
	ColorPalette(char color_code)
	{
		switch (color_code)
		{
		case 'R':
			rgba_ = RGBA();
			break;
		case 'C':
			rgba_ = RGBA();
			break;
		case 'O':
			rgba_ = RGBA();
			break;
		case 'Y':
			rgba_ = RGBA();
			break;
		case 'D':
			rgba_ = RGBA();
			break;
		case 'M':
			rgba_ = RGBA();
			break;
		case 'P':
			rgba_ = RGBA();
			break;
		case 'L':
			rgba_ = RGBA();
			break;
		case 'G':
			rgba_ = RGBA();
			break;
		case 'T':
			rgba_ = RGBA();
			break;
		case 'A':
			rgba_ = RGBA();
			break;
		case 'I':
			rgba_ = RGBA();
			break;
		case 'N':
			rgba_ = RGBA();
			break;
		case 'B':
			rgba_ = RGBA();
			break;
		case 'W':
			rgba_ = RGBA();
			break;
		case 'S':
			rgba_ = RGBA();
			break;
		default:
			rgba_ = RGBA();
			break;
		}
	}

	RGBA getRGBA() { return rgba_; }

private:
	RGBA rgba_;
};

#endif // !COLORPALETTE_H
