#ifndef RGBA_H
#define RGBA_H

// Stores Red GREEN BLUE and ALPHA channel using 4 bytes
struct RGBA
{
	RGBA(): r(0), g(0), b(0), a(255) {}
	RGBA(char  r, char g, char b) : r(r), g(g), b(b), a(255) {}
	RGBA(char  r, char g, char b, char a) : r(r), g(g), b(b), a(a) {}

	char r, g, b, a;
};

#endif // !RGBA_H