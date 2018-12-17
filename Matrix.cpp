#include "Matrix.h"

// Sets the color of the matrix unit
void Matrix::Proxy::Deref::setColor(char red, char green, char blue)
{
	std::get<1>(a[index_]).setRGBA(red, green, blue);
}

// Sets the color of the matrix unit
void Matrix::Proxy::Deref::setColor(RGBA rgba)
{
	std::get<1>(a[index_]) = rgba;
}

// fades the color of the matrix unit to black
bool Matrix::Proxy::Deref::fadeColor(int fade_delay, int multiplier)
{
	return std::get<1>(a[index_]).fadeToBlack(fade_delay, multiplier);
}

// Get the color in HEX for the matrix unit
unsigned int Matrix::Proxy::Deref::getColor()
{
	return std::get<1>(a[index_]).getHex();
}
