#include "RGBA.h"

#ifndef COLORPALETTE_H
#define COLORPALETTE_H

/*
R Red
C Crimson/Red
O Orange
Y Yellow
D Khaki/Yellow
M Magenta/Pink
P Purple
L Lime
G Green
T Teal
A Aqua/Blue
I Indigo/Blue
N Navy/Blue
B Brown
W White
S Steel/Grey
*/
class ColorPalette
{
public:
	ColorPalette(char color_code)
	{
		switch (color_code)
		{
		case 'R':
			rgba_ = RGBA(255, 0, 0);
			break;
		case 'C':
			rgba_ = RGBA(153, 0, 0);
			break;
		case 'O':
			rgba_ = RGBA(255, 69, 0);
			break;
		case 'Y':
			rgba_ = RGBA(255, 255, 0);
			break;
		case 'D':
			rgba_ = RGBA(240, 230, 140);
			break;
		case 'M':
			rgba_ = RGBA(255, 0, 255);
			break;
		case 'P':
			rgba_ = RGBA(128, 0, 128);
			break;
		case 'L':
			rgba_ = RGBA(0, 255, 0);
			break;
		case 'G':
			rgba_ = RGBA(0, 128, 0);
			break;
		case 'T':
			rgba_ = RGBA(54, 117, 136);
			break;
		case 'A':
			rgba_ = RGBA(0, 255, 255);
			break;
		case 'I':
			rgba_ = RGBA(75, 0, 130);
			break;
		case 'N':
			rgba_ = RGBA(0, 0, 128);
			break;
		case 'B':
			rgba_ = RGBA(139, 69, 19);
			break;
		case 'W':
			rgba_ = RGBA(255, 255, 255);
			break;
		case 'S':
			rgba_ = RGBA(105, 105, 105);
			break;
		default:
			rgba_ = RGBA(255, 255, 255);
			break;
		}
	}

	RGBA getRGBA() { return rgba_; }

private:
	RGBA rgba_;
};

#endif // !COLORPALETTE_H
