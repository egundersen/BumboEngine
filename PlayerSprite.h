#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include "Sprite.h"
#include "WorldSpriteContainer.h"

class PlayerSprite : public Sprite
{
public:
	using Sprite::Sprite;

	// Setters
	void initializeSprites(WorldSpriteContainer player_sprite);
	void setPlayerMoving(std::string direction);

protected:
	// Output Displays
	void displaySpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y);
};

#endif // !PLAYERSPRITE_H