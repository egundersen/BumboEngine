#include "MatrixBase.h"
#include "PlayerSprite.h"

#ifndef WORLDBASE_H
#define WORLDBASE_H

struct ScreenPosition
{
	int x;
	int y;
};

class WorldBase : MatrixBase
{
public:
	WorldBase(int screen_width, int screen_height, int world_width, int world_height, int starting_position_x, int starting_position_y, int &player_health, std::vector<std::vector<std::string>> &matrix_display);
	
	// Setters
	void onEnterWorld();
	void refreshScreen();

private:
	// Output Displays
	bool hasCollided(char direction, int offset);
	void displayScreen();
	void evaluatePlayerInput();
	void generateWorld();
	void modifyWorld();

	int screen_width_, screen_height_, world_width_, world_height_, &player_health_, start_time_player_speed_;
	bool **element_is_occupied_;
	char player_direction_;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> world_matrix_;
	std::vector<Image> mountain_lines_;
	ScreenPosition screen_position_;
	PlayerSprite player_sprite_;
};

#endif // !WORLDBASE_H
