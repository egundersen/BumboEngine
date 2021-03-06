#ifndef BATTLESPRITE_H
#define BATTLESPRITE_H

#include <string>

// Container for boss's face during a battle
class BattleSprite
{
public:
	BattleSprite()
		: face_ASCII_{ "" }, overlay_ASCII_{ "" } { }
	BattleSprite(std::string face_ASCII, std::string overlay_ASCII)
		: face_ASCII_{ face_ASCII }, overlay_ASCII_{ overlay_ASCII } { }

	std::string getFace() { return face_ASCII_; }
	std::string getOverlay() { return overlay_ASCII_; }

private:
	std::string face_ASCII_, overlay_ASCII_;
};

#endif // !BATTLESPRITE_H
