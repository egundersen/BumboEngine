#include "MatrixBase.h"
#include "PlayerSprite.h"
#include "Popup.h"
#include "Signpost.h"
#include <utility>

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
	// Setters
	void evaluatePlayerInput();
	void generateWorld();
	void modifyWorld();

	// Getters
	bool hasCollided(char direction, int offset);
	std::pair<int, int> getFacingEntity();

	// World Generation-related Setters
	void GENERATE_WorldBorder();
	void GENERATE_OutsideArea();
	//void GENERATE_Maze();
	//void GENERATE_Enemies();
	//void GENERATE_NonHostileNPCs();
	//void GENERATE_Cutscenes();
	void GENERATE_Signposts();
	//void GENERATE_Pickups();
	void GENERATE_AdditionalObjects();


	// Output Displays
	void displayScreen();

	int screen_width_, screen_height_, world_width_, world_height_, &player_health_, start_time_player_speed_,
		player_speed_modifier_;
	bool is_viewing_popup_;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> world_matrix_;
	std::vector<std::vector<std::pair<int, int>>> element_has_object_;
	std::vector<Image> mountain_lines_;
	std::vector<Signpost*> signposts_;
	ScreenPosition screen_position_;
	PlayerSprite player_sprite_;
};

#endif // !WORLDBASE_H
