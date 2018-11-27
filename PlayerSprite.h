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
	void displaySpriteAtDirection(std::vector<std::vector<char>> &direction, int top_left_position_x, int top_left_position_y);
};

#endif // !PLAYERSPRITE_H