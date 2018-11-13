#include "MatrixBase.h"
#include "Sprite.h"

#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

class PlayerSprite : public Sprite
{
public:
	using Sprite::Sprite;

	// Setters
	void initializeSprites();
	void setPlayerMoving(std::string direction);

protected:
	// Output Displays
	void displaySpriteAtDirection(std::vector<std::vector<char>> &direction, int screen_height, int screen_width);
};

#endif // !PLAYERSPRITE_H