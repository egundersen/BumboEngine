#include "RGBA.h"

RGBA::RGBA()
	: r(255), g(255), b(255), a(255), start_time_fade_animation_(0), has_started_fade_{ false }
{
}

RGBA::RGBA(unsigned char r, unsigned char g, unsigned char b)
	: r(r), g(g), b(b), a(255), start_time_fade_animation_(0), has_started_fade_{ false }
{
}

RGBA::RGBA(unsigned char r, char g, unsigned char b, unsigned char a)
	: r(r), g(g), b(b), a(a), start_time_fade_animation_(0), has_started_fade_{ false }
{
}

// Returns the RGB as a HEX value as an integer
unsigned int RGBA::getHex()
{
	return ((b & 0xff) << 16) + ((g & 0xff) << 8) + (r & 0xff);
}

// Set RED GREEN & BLUE colors
void RGBA::setRGBA(unsigned char red, unsigned char green, unsigned char blue)
{
	r = red;
	g = green;
	b = blue;
}

// Set RED GREEN & BLUE colors as well as the ALPHA channel
void RGBA::setRGBA(unsigned char red, char green, unsigned char blue, unsigned char alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

// Fades the RGBA's color to black at the specified delay per second
bool RGBA::fadeToBlack(int fade_delay, int multiplier)
{
	if (r < multiplier && g < multiplier && b < multiplier)
	{
		has_started_fade_ = false;
		return true;
	}
	else if (!has_started_fade_)
	{
		start_time_fade_animation_ = GetTickCount64();
		has_started_fade_ = true;
	}
	else if (has_started_fade_)
	{
		double current_time_fade_animation = GetTickCount64() - start_time_fade_animation_;
		if (current_time_fade_animation > fade_delay)
		{
			if (r >= multiplier) { r -= multiplier; }
			if (g >= multiplier) { g -= multiplier; }
			if (b >= multiplier) { b -= multiplier; }
			start_time_fade_animation_ = GetTickCount64();
		}
	}
	return false;
}
