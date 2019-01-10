#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include "RGBA.h"

/*
R Red
C Crimson/Red
O Orange
Y Yellow
K Khaki/Yellow
D Deep Pink
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
F Fog/Light Grey
S Steel/Dark Grey
H Heather/Greenish-Grey

0 EXTREMELY Dark Grey
J Skin Color
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
		case 'K':
			rgba_ = RGBA(240, 230, 140);
			break;
		case 'D':
			rgba_ = RGBA(255, 140, 255);
			break;
		case 'M':
			rgba_ = RGBA(200, 0, 200);
			break;
		case 'P':
			rgba_ = RGBA(140, 0, 140);
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
		case 'F':
			rgba_ = RGBA(169, 169, 169);
			break;
		case 'S':
			rgba_ = RGBA(105, 105, 105);
			break;
		case 'H':
			rgba_ = RGBA(47, 79, 79);
			break;
		case '0':
			rgba_ = RGBA(30, 30, 30);
			break;
		case 'J':
			rgba_ = RGBA(255, 224, 189);
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
