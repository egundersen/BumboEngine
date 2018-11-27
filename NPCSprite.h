#include "MatrixBase.h"
#include "Sprite.h"

#ifndef NPCSPRITE_H
#define NPCSPRITE_H

class NPCSprite : public Sprite
{
public:
	NPCSprite(int sprite_width, int sprite_height, std::vector<std::vector<std::string>> &matrix_display, std::vector<std::vector<char>>& world_matrix);

	// Setters
	void initializeSprites(std::vector<Image*> sprite_states);

	// Output Displays
	void DEBUG_eraseSquareSurroundingSprite(int top_left_position_x, int top_left_position_y);
private:
	
	// Output Displays
	void displaySpriteAtDirection(std::vector<std::vector<char>> &direction, int top_left_position_x, int top_left_position_y);
	void displayGhostSpriteAtDirection(std::vector<std::vector<char>> &direction, int top_left_position_x, int top_left_position_y, int screen_width_, int screen_height_, char moving_direction);
	void eraseSpriteAtDirection(std::vector<std::vector<char>> &direction, int top_left_position_x, int top_left_position_y);

	std::vector<std::vector<char>>& world_matrix_;
};

#endif // NPCSPRITE_H