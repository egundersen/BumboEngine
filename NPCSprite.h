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
	void removeSprite(int center_position_x, int center_position_y);

	// Output Displays
	void displayGhostAtPosition(int center_position_x, int center_position_y);
private:
	// Output Displays
	void displaySpriteAtDirection(std::vector<std::vector<char>> &direction, int center_position_x, int center_position_y);
	
	std::vector<std::vector<char>>& world_matrix_;
};

#endif // NPCSPRITE_H