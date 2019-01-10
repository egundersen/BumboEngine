#ifndef NPCSPRITE_H
#define NPCSPRITE_H

#include "Sprite.h"

class NPCSprite : public Sprite
{
public:
	NPCSprite(int sprite_width, int sprite_height, Matrix &screen_matrix, Matrix &world_matrix);

	// Setters
	void initializeSprites(std::vector<Image*> sprite_states);

	// Output Displays
	void DEBUG_eraseSquareSurroundingSprite(int top_left_position_x, int top_left_position_y);
private:
	
	// Output Displays
	void displaySpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y);
	void displayGhostSpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y, int screen_width_, int screen_height_, char moving_direction);
	void eraseSpriteAtDirection(Matrix &direction, int top_left_position_x, int top_left_position_y);

	Matrix &world_matrix_;
};

#endif // NPCSPRITE_H