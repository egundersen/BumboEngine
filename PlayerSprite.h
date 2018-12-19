#include "MatrixBase.h"
#include "Sprite.h"
#include "WorldSprite.h"

#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

class PlayerSprite : public Sprite
{
public:
	using Sprite::Sprite;

	// Setters
	void initializeSprites(WorldSprite player_sprite);
	void setPlayerMoving(std::string direction);

protected:
	// Output Displays
	void displaySpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y);
};

#endif // !PLAYERSPRITE_H