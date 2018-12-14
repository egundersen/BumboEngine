#ifndef RGBA_H
#define RGBA_H

// Stores Red GREEN BLUE and ALPHA channel using 4 bytes
struct RGBA
{
	RGBA(): r(0), g(0), b(0), a(255) {}
	RGBA(unsigned char  r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}
	RGBA(unsigned char  r, char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

	unsigned int getHex()
	{
		return ((b & 0xff) << 16) + ((g & 0xff) << 8) + (r & 0xff);
	}

	unsigned char r, g, b, a;
};

#endif // !RGBA_H