#include "MatrixBase.h"
#include "PlayerSprite.h"
#include "PopupWithCollision.h"
#include "Signpost.h"
#include "Pickup.h"
#include "Characters.h"
#include "Events.h"
#include "Maze.h"
#include "ScreenPosition.h"
#include "SpriteSheet.h"
#include <utility>

#ifndef WORLDBASE_H
#define WORLDBASE_H

class WorldBase : MatrixBase
{
public:
	WorldBase(int screen_width, int screen_height, int world_width, int world_height, int starting_position_x, int starting_position_y, int &player_health, std::vector<std::vector<std::string>> &matrix_display, Inventory &inventory, std::pair<std::string, int> &image_file_path);

	// Setters
	void onEnterWorld();
	void refreshScreen();

	// Getters
	bool shouldEnterBattle() { return should_enter_battle_; }
	CharacterBase *getSelectedCharacter();
private:
	// Setters
	void evaluatePlayerInput();
	void teleportPlayer(int position_x, int position_y);
	void generateWorld();
	void checkRemovePickup();
	void checkForItem();
	void checkForBattle();
	void shouldDespawnCharacter();
	void shouldRemoveEvent();
	void shouldStartEventByLocation();
	void shouldStartEventByID(int event_ID);
	void setNPCAttributes();

	// Getters
	bool hasCollided(char direction, int offset);
	std::pair<int, int> getFacingEntity();

	// World Generation-related Setters
	void GENERATE_WorldBorder();
	void GENERATE_OutsideArea();
	void GENERATE_Maze();
	void GENERATE_Enemies();
	void GENERATE_NonHostileNPCs();
	void GENERATE_Signposts();
	void GENERATE_Pickups();
	void GENERATE_AdditionalObjects();
	void GENERATE_Events();

	// Output Displays
	void displayScreen();

	// Debug-only Functions
	void DEBUG_refresh();
	void DEBUG_drawUI();
	void DEBUG_displayCollisions();
	void DEBUG_stopDisplayingCollisions();
	void DEBUG_displayScreen();

	int screen_width_, screen_height_, world_width_, world_height_, &player_health_, start_time_player_speed_,
		player_speed_modifier_;
	char opposite_player_direction_;
	bool is_viewing_popup_, should_enter_battle_, is_event_active_, is_picking_up_item_,
		DEBUG_mode_enabled_, DEBUG_has_initialized_, DEBUG_showing_collisions_;
	std::pair<std::string, int> &image_file_path_;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> world_matrix_;
	std::vector<std::vector<char>> DEBUG_screen_matrix_;
	std::vector<std::vector<std::pair<int, int>>> element_has_object_;
	std::vector<Image> mountain_lines_;
	std::vector<Image> fence_lines_;
	std::vector<Signpost*> signposts_;
	std::vector<Pickup*> pickups_;
	std::vector<CharacterBase*> characters_;
	std::vector<EventBase*> events_;

	Maze maze_;
	Inventory &inventory_;
	ScreenPosition screen_position_;
	PlayerSprite player_sprite_;
	SpriteSheet sprite_sheet_;

	CharacterBase *selected_character_;
	EventBase *selected_event_;
};

#endif // !WORLDBASE_H
