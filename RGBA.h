#ifndef RGBA_H
#define RGBA_H

#include <Windows.h>

// Stores RED GREEN BLUE and ALPHA channel using 4 bytes
class RGBA
{
public:
	RGBA();
	RGBA(unsigned char r, unsigned char g, unsigned char b);
	RGBA(unsigned char r, char g, unsigned char b, unsigned char a);

	unsigned int getHex();
	void setRGBA(unsigned char red, unsigned char green, unsigned char blue);
	void setRGBA(unsigned char red, char green, unsigned char blue, unsigned char alpha);
	bool fadeToBlack(int fade_delay, int multiplier);

	unsigned char getRed() { return r; }
	unsigned char getGreen() { return g; }
	unsigned char getBlue() { return b; }
	unsigned char getAlpha() { return a; }
private:
	unsigned char r, g, b, a;
	int start_time_fade_animation_;
	bool has_started_fade_;
};

#endif // !RGBA_H