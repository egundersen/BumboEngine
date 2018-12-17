#ifndef RGBA_H
#define RGBA_H

// Stores RED GREEN BLUE and ALPHA channel using 4 bytes
class RGBA
{
public:
	RGBA() : r(255), g(255), b(255), a(255) {}
	RGBA(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(255) {}
	RGBA(unsigned char r, char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {}

	unsigned int getHex()
	{
		return ((b & 0xff) << 16) + ((g & 0xff) << 8) + (r & 0xff);
	}
	void setRGBA(unsigned char red, unsigned char green, unsigned char blue)
	{
		r = red;
		g = green;
		b = blue;
	}
	void setRGBA(unsigned char red, char green, unsigned char blue, unsigned char alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	unsigned char getRed() { return r; }
	unsigned char getGreen() { return g; }
	unsigned char getBlue() { return b; }
	unsigned char getAlpha() { return a; }
private:
	unsigned char r, g, b, a;
};

#endif // !RGBA_H