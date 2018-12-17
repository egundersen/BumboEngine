#include "Matrix.h"

void Matrix::Proxy::Deref::setColor(char red, char green, char blue)
{
	std::get<1>(a[index_]).setRGBA(red, green, blue);
}

void Matrix::Proxy::Deref::setColor(RGBA rgba)
{
	std::get<1>(a[index_]) = rgba;
}

unsigned int Matrix::Proxy::Deref::getColor()
{
	return std::get<1>(a[index_]).getHex();
}
