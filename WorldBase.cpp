#include "WorldBase.h"
#include <Windows.h>
#include <iostream>

WorldBase::WorldBase(int screen_width, int screen_height, int world_width, int world_height, int starting_position_x, int starting_position_y, int &player_health, std::vector<std::vector<std::string>> &matrix_display, Inventory &inventory)
	: screen_width_{ screen_width }, screen_height_{ screen_height }, world_width_{ world_width }, world_height_{ world_height }, start_time_player_speed_(0), element_has_object_(world_height, std::vector<std::pair<int, int>>(world_width, std::make_pair<int, int>(0, 0))),
	world_matrix_(world_height, std::vector<char>(world_width, ' ')), matrix_display_{ matrix_display }, player_health_{ player_health }, player_sprite_{ 12, 10, matrix_display }, player_speed_modifier_(30), inventory_{ inventory }, DEBUG_has_initialized_{ false },
	DEBUG_showing_collisions_{ false }, opposite_player_direction_('d'), should_enter_battle_{ false }
{
	screen_position_.x = starting_position_x - screen_width / 2;
	screen_position_.y = starting_position_y - screen_height / 2;

	generateWorld();
	player_sprite_.initializeSprites();
}

// Runs once whenever the player enters the world (Like when exiting a battle or the inventory)
void WorldBase::onEnterWorld()
{
	start_time_player_speed_ = GetTickCount();
	should_enter_battle_ = false;
}

// Calls every frame
void WorldBase::refreshScreen()
{
	if (is_viewing_popup_ && getFacingEntity() != std::make_pair<int, int>(0, 0))
	{
		switch (getFacingEntity().first)
		{
		case 1: // Signpost
			for (Signpost *signpost : signposts_)
				if (signpost->getUniqueObjectID() == getFacingEntity().second)
					signpost->refreshPopup();
			break;
		case 2: // Pickup
			for (Pickup *pickup : pickups_)
				if (pickup->getUniqueObjectID() == getFacingEntity().second)
				{
					pickup->refreshPopup();
					pickup->pickupItem();
					delete(pickup);
				}
			break;
		case 3: // Character
			for (CharacterBase *character : characters_)
				if (character->getUniqueObjectID() == getFacingEntity().second)
				{
					displayScreen();
					character->refreshPopup(opposite_player_direction_);
					selected_character_ = character; // TODO: Not have this
					should_enter_battle_ = true;
				}
			break;
		default:
			break;
		}
	}
	// else if:
	// Checks if player standing in event.trigger_zone
		// Exits if events_.isComplete()
			// Checks event.trigger_zone ID
				// --> Runs event code
	else
	{
		// teleport [example]
			//characters_[0]->teleportNPC(2382, characters_[0]->getCenterPositionY());

		// move [example]
			//if (!characters_[0]->hasReachDestination())
			//	characters_[0]->move(2382, 'x', 250);
		displayScreen();
	}
	evaluatePlayerInput();
}

CharacterBase * WorldBase::getSelectedCharacter()
{
	return selected_character_;
}

// Returns true if player collides with something
bool WorldBase::hasCollided(char direction, int offset)
{
#ifdef _DEBUG
	if (DEBUG_mode_enabled_)
		return false;
#endif

	switch (direction)
	{
	case 'u':
		for (int j = 0; j < player_sprite_.getWidth() / 2 + 2; j++)
			if (matrix_display_[screen_height_ / 2 - player_sprite_.getHeight() / 2 + offset][screen_width_ / 2 - player_sprite_.getWidth() / 2 + 2 + j] != std::string(1, ' '))
				return true;
		return false;
		break;
	case'd':
		for (int j = 0; j < player_sprite_.getWidth() / 2 + 2; j++)
			if (matrix_display_[screen_height_ / 2 + player_sprite_.getHeight() / 2 - offset][screen_width_ / 2 - player_sprite_.getWidth() / 2 + 2 + j] != std::string(1, ' '))
				return true;
		return false;
		break;
	case 'l':
		for (int i = 0; i < player_sprite_.getHeight() / 2 + 1; i++)
			if (matrix_display_[screen_height_ / 2 - player_sprite_.getHeight() / 2 + 3 + i][screen_width_ / 2 - player_sprite_.getWidth() / 2 + offset] != std::string(1, ' '))
				return true;
		return false;
		break;
	case'r':
		for (int i = 0; i < player_sprite_.getHeight() / 2 + 1; i++)
			if (matrix_display_[screen_height_ / 2 - player_sprite_.getHeight() / 2 + 3 + i][screen_width_ / 2 + player_sprite_.getWidth() / 2 - offset] != std::string(1, ' '))
				return true;
		return false;
		break;
	default:
		return false;
	}
}

// Returns entity data for the object in front of player, whether it be a signpost, item, enemy, etc...
std::pair<int, int> WorldBase::getFacingEntity()
{
	switch (player_sprite_.getDirection())
	{
	case 'u':
		for (int j = -2; j < 2; j++)
			if (element_has_object_[screen_position_.y + screen_height_ / 2 - 3][screen_position_.x + screen_width_ / 2 + j].first != 0)
				return element_has_object_[screen_position_.y + screen_height_ / 2 - 3][screen_position_.x + screen_width_ / 2 + j];
		break;
	case 'd':
		for (int j = -2; j < 2; j++)
			if (element_has_object_[screen_position_.y + screen_height_ / 2 + 4][screen_position_.x + screen_width_ / 2 + j].first != 0)
				return element_has_object_[screen_position_.y + screen_height_ / 2 + 4][screen_position_.x + screen_width_ / 2 + j];
		break;
	case 'r':
		for (int i = -1; i < 3; i++)
			if (element_has_object_[screen_position_.y + screen_height_ / 2 + i][screen_position_.x + screen_width_ / 2 + 5].first != 0)
				return element_has_object_[screen_position_.y + screen_height_ / 2 + i][screen_position_.x + screen_width_ / 2 + 5];
		break;
	case 'l':
		for (int i = -1; i < 3; i++)
			if (element_has_object_[screen_position_.y + screen_height_ / 2 + i][screen_position_.x + screen_width_ / 2 - 6].first != 0)
				return element_has_object_[screen_position_.y + screen_height_ / 2 + i][screen_position_.x + screen_width_ / 2 - 6];
		break;
	default:
		break;
	}
	return std::pair<int, int>();
}

// Displays World and Player to screen
void WorldBase::displayScreen()
{
	for (int i = 0; i < screen_height_; i++)
	{
		for (int j = 0; j < screen_width_; j++)
		{
			matrix_display_[i][j] = std::string(1, world_matrix_[screen_position_.y + i][screen_position_.x + j]);
		}
	}

	player_sprite_.displaySprite(screen_width_, screen_height_);

#ifdef _DEBUG
	if (DEBUG_mode_enabled_)
		DEBUG_refresh();
#endif // !_DEBUG
}

// Takes input and decides whether to move player
void WorldBase::evaluatePlayerInput()
{
	double current_time_move_player = GetTickCount() - start_time_player_speed_;

	if (GetAsyncKeyState(0x45) & 0x8000) // Press E
	{
		is_viewing_popup_ = true;
	}
	else
	{
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000) // Running
		{
			player_speed_modifier_ = 5;
			player_sprite_.setPlayerAnimationSpeed(180);
		}
		else
		{
			player_speed_modifier_ = 30;
			player_sprite_.setPlayerAnimationSpeed(240);
		}
		if (current_time_move_player >= player_speed_modifier_) // Movement UP, DOWN, LEFT, RIGHT
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				if (screen_position_.y > 0 && !hasCollided('u', 2)) // 2
				{
					--screen_position_.y;
					player_sprite_.setPlayerMoving("verticle");
				}
				player_sprite_.setDirection('u');
				opposite_player_direction_ = 'd';
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				if (screen_position_.y + screen_height_ < world_height_ - 1 && !hasCollided('d', 1))
				{
					++screen_position_.y;
					player_sprite_.setPlayerMoving("verticle");
				}
				player_sprite_.setDirection('d');
				opposite_player_direction_ = 'u';
			}
			else
				player_sprite_.setPlayerMoving("not verticle");
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				if (screen_position_.x + screen_width_ < world_width_ - 1 && !hasCollided('r', 1))
				{
					++screen_position_.x;
					player_sprite_.setPlayerMoving("horizontal");
				}
				player_sprite_.setDirection('r');
				opposite_player_direction_ = 'l';
			}
			else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				if (screen_position_.x > 0 && !hasCollided('l', 0))
				{
					--screen_position_.x;
					player_sprite_.setPlayerMoving("horizontal");
				}
				player_sprite_.setDirection('l');
				opposite_player_direction_ = 'r';
			}
			else
				player_sprite_.setPlayerMoving("not horizontal");
			start_time_player_speed_ = GetTickCount();
		}
		is_viewing_popup_ = false;
	}

#ifdef _DEBUG
	if (GetAsyncKeyState(0x47) & 0x8000) // Open DEBUG Mode!		Press G
		DEBUG_mode_enabled_ = true;
	if (GetAsyncKeyState(0x48) & 0x8000) // Close DEBUG Mode!		Press G
	{
		if (DEBUG_showing_collisions_)
			DEBUG_stopDisplayingCollisions();
		DEBUG_showing_collisions_ = false;
		DEBUG_mode_enabled_ = false;
	}
	if (GetAsyncKeyState(0x43) & 0x8000) // Collisions!				HOLD C
		DEBUG_showing_collisions_ = true;
	else
	{
		if (DEBUG_showing_collisions_)
			DEBUG_stopDisplayingCollisions();
		DEBUG_showing_collisions_ = false;
	}
#endif
}

// creates the world
void WorldBase::generateWorld()
{
	GENERATE_WorldBorder();
	GENERATE_OutsideArea();
	GENERATE_AdditionalObjects();
	GENERATE_NonHostileNPCs();
	GENERATE_Pickups();
	GENERATE_Signposts();
	GENERATE_Events();

	// Displays all Characters
	for (auto character : characters_)
		character->createWorldSprite();
}

// adds something to the world that doesn't exist on startup (Like doors that close behind you)
void WorldBase::modifyWorld()
{

}

// creates a nice border around the world. Useful for debugging, helps tell if you are building near edge of world
void WorldBase::GENERATE_WorldBorder()
{
	for (int i = 0; i < world_height_; i++)
		world_matrix_[i][0] = 'X';
	for (int i = 0; i < world_height_ - 15; i++)
		world_matrix_[i][world_width_ - 1] = 'X';
	for (int j = 0; j < world_width_; j++)
		world_matrix_[0][j] = 'X';
	for (int j = 0; j < world_width_; j++)
		world_matrix_[world_height_ - 15][j] = 'X';
}

// creates a cliff area outside the maze. This is the player's spawn / start of the game
void WorldBase::GENERATE_OutsideArea()
{
	// Mountainside
	std::wstring mountain[] = {
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,',,,,,,,,,,,,;;:::codxxkOKNWWWMMMMMWNXK0Oxoc:Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccccodxxxkO0KKKXNNNNXK00Okxdolc:;,'...    Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;:cllloxkkkO0KXXXXNNNXKK0kxdolc:;;'...                   Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;::::clodddxk0000KXNNNXXKK0Okxdolc:;,'...                                 Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:ccccldxkkkO0KXXXXNNNXKK0kkxolcc:;'....                                               Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;::clooodxOOOO0XNNNNXXXK0Okxdolc:;,'...                                                              Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,',;:ccccodxxxkO0KKKXNWWNXK0OOkxdolc:;'....                                                                            Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;;:clloodkkOOOKXNNXXNNXK0Okxdolc:;,'...                                                                                           Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:::clodddxkO00KKXNWNNXK00Okxdolc:;,'...                                                                                                         Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccllldxkkkO0KXXXXNNNXK0Okxdolc:;,'...                                                                                                                        Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;:::clodddxk0000XNNNNXXKK0Okxdolc:;,'...                                                                                                                                      Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccclodxxkkO0KXXXNNWNXK0Okxdolcc:;'....                                                                                                                                                    Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;::clooodkOOOOKXNNNXXXXK0Okxdolc:;,'...                                                                                                                                                                   Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccclodxxxk0KKKKXNWWNXK0OOkdollc:;'....                                                                                                                                             .,;:::::::::::::::::::::::::::::::::Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;;clllodxkkkO0KXNXXNNNXK0Okxdolc:;,'...                                                                                                                                                         'cxKWWWWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;::::clodddxO000KXNNWNXXK00Okdoolc:;,'...                                                                                                                                                                   .:dONWNNWMKxdxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccclodxkkkO0KXXXXNNNXK0Okxdolc:;,'...                                                 .................................................,'.                                                        ..................;oOXWWX0kdxXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;:::coooodxOO00KXNNNNXXKK0Okxdolc:;,'...                                                             .lOXKKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKXWNKkl;.                                               .;cdOKXKKKKXXXXXXXXXXXNWWX0kdollldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccclodxxkkOKKKXXNWWNXK0Okxdolc::,'....                                                                         .c0WMN0OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO0WMXOKXWWXOdc'.                                    ..;lx0XWWNWMN0OOOOOOOOOOOOOXMW0ollllllcdXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;:cllllooxkOOO0KXNNNXXXXK0Okxdolc:;,'...                                                                                       ;OWMMM0ollllllllllllllllllllllllllllllllllllllllllcdXMOlloxk0KNWNKkl:,'..........................',:lx0NWWXK0kxxKMKocllllllllllllOWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;::cccloddxxk0KKKXXNWWNXXK0OOkdollc:,'....                                                                                                   'xNWX0NM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllldxOKNWMWNNNNNNNNNNNNNNNNNNNNNNNNNNNNWMWXKOkdollllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:clllldxkkkO0KXXNNNNNXK0Okxdolc::;,'...                                                                                                                .oXWNOooKM0ollllllllllllllllllllllllllllllllllllllllllldXM0lllllllllllo0WWKkkkkkkkkkkkkkkkkkkkkkkkkkOXMNkollllllllloKMKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;::::codddxkO000KXNNNNXXK00Okddolc:,,'...                                                                                                                             .cKWN0dlloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxclllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccclodxkkkOKXXXXNNNNXK0Okxdolc:;,'...                                                                                                                                           ;OWWKxlllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;::looodxkOOO0KXNNNNXXKK0Okxdolc:;,'...                                                                                                                                                       ,kNWXkollllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNkllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,::ccclodxxxk0KKKKXNWNXXK0Okxdolcc:,'....                                                                                                                                                                   .dXMNOollllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;:clllodxkkOO0KXNNNNNXXK0Okxdolc:;,'...                                                                                                                                                                                .lKWN0dllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,',;:::ccldddxkO0KKKXNNWNXXK0OOxdollc:,'....                                                                                                                                                                                             :0WW0xllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:ccllodxkkkO0XXXXNNNNXK0Okxdolc:;,'...                                                                                                                                                                                 .'.......................;kWWXkolllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;::::looddxkO000KXNNNXXXK00Oxdoolc;,''...                                                                                                                                                                                             'dKNXXXXXXXXXXXXXXXXXXXXXXXWMNOolllllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,',,,,,,;:cccloxxxkkOKXXXXNWNNXK0Okxdolc:;,'....                                                                                                                                                                                                         'dXMMMWKkkOkkkkOOOOOOOkkOOkk0NMKdllllllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;;:clooodxkOOO0KXNNNXXXKK0Oxxdolc:;,'...                                                                                                                                                                                                                      .dXWN0KMNxcllllllllllllllllllll0MKollllllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxlllllllldXMOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;::cccldxxxxO0KKKXNNWNXXK0Okxdolc:;,'....                                                                                                                                                                                                                                  'oXMNOdlkWNxlllllllllllllllllllll0MKollllllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxllllllllkNMKxdddddddddddddddddddddddddddddddZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,',,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;:clllodxkkOO0XXNNNNNXXK0Okxdolc:;,....                                                                                                                                                                                                                                               'dXWN0dlllOWNxlllllllllllllllllllll0MKollllllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxllllldkKWMWWWNNNNNNNNWWWWWWWWWWWWWWWWWWWWWWWZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,',,,,,,,,,,,;:::ccodddxkO000KXNNNNXXK0Okxdollc;,''...                                                                                                                                                                                                                                                           'oXMN0dlllllOWNxlllllllllllllllllllll0MKollllllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllkWNxclok0NWNkl::::::::::::::::::::::::::::::::::Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:cccloxkkkkOKXXXXNNNXXK0Okxdolc:;,'...                                                                                                                                                                                                         .,.............................................................,dXMN0dlllllllOWNxlllllllllllllllllllll0MKollllllllllllllloKM0ollllllllllllllllllllllllllllllllllllllllllldXM0llllllllllllkWNxllllllllllllllllllllllllll0MXdllllllllllo0MKolllllllllllllOWNkxOXWW0l'                                    Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;dO0KXNNNXXXK00kxdool:;,'...                                                                                                                                                                                                                     .:xXWXKKKKKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXKKKKKKKXNMN0dlllllllllOWNxlllllllllllllllllllll0MKollllllllllllllloKMKollllllllllllllllllllllllllllllllllllllllllcdXM0llllllllllllkWNkllllllllllllllllllllllllll0MXdllllllllllo0MXxooooooooooood0WWWWWKd;.            .                         Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OWMMWOc;,'....                                                                                                                                                                                                                              .cokXWMMMNOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOXWWOlllllllllllOWNxlllllllllllllllllllll0MKollllllllllllllldXMNK0000000000000000000000000000000000000000000KWMKdlllllllllllkWNkllllllllllllllllllllllllll0MXdclllllllldONMMWNNNNNNNNNNNNNWMWXx:.             ,x0OkkkkkkkkkkkkkkkkkkkkkkkkZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,':OWWNWXx'                                                                                                                                                                                                                                 'ckXWWNKkONM0lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MKolllllllllllllokXWWK000000000000000000000000000000000000000000000XNWNK0kdollllllkWNxllllllllllllllllllllllllll0MXdllllloxOKNWXOdllllllllllllllclc'              ;kNMMWX0KK00KKKKKKKKKKKKKKKKKKZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OWKxkXWXd.                                                                                                                                                                                                                            'lkXWNKkxdlldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MKollllllllllllxKWWO:..                                           ..,cdOXWWX0kxolckWNxllllllllllllllllllllllllll0MXdloxk0NWN0dc'                               .:ONWNWMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OW0oldONWKo.                                                                                                                                        .'.............................................................................,lONWNKkdlllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MKolllllllllld0NWKc.                                                    .:okXWWNKOKWWOooooooooooooooooooolooolloKMN00XWWXkl,.                                .c0WWKkxKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OW0ollld0NWKl;,,,,'''''''''''.....................................................                ...                                            .:xXNXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXWMNKkdllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MKolllllllloONMXo.                                                          .,lx0NWMMNXXXXXXXXXXXXXXXXXXXXXXXXXXWMMWNOo;.                                  'oKWN0xoloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OW0olllllxKWMWWNNNNNNNNNNNNNNNNNNNNXXXXXXXXXXXXXXXXXXXXXXXXKKKKKKKKKKKKKK00K00K00000000000OOOOOOOO0X0o,.                                      .;dKWWKXMWKOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkONMXxlllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MKollllllokXWNx'                                                                .':oOkdooooooooooooooooooooooooodOxc'                                    ,dXWN0xlllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;lddKM0olllllllOWWKkxxkkkkkkkkkkkkkkkkkkkkkOOOOOOOOOO000000000000000000000000000000000000000000000000NMMWWW0d;.                                 ,o0WWXOxlkWNxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MKolllllxKWWk;                                                                                                                                        .;kNWXOdlllllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:kNNXNM0ollllllcxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOWNOxOXWWXxc.                           'lONWX0xolllkWNxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxllllllllllllllllllllo0MKollld0WW0:.       .;:;;;;;,,,,,,''''''''''..................'.                                                                     .,ll::::::::::::lONWXkdlllllllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;dKWXlcKM0ollllllcxNWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWNklloxOKNWXkl::cllllllllllllllllllllokNWN0kollllllkWNklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MKold0NWKl.        ,OWWWWNNNNNNNNNNNNNNNNNNNNNNNXXXXXXKKKKK00XNXko:'.                                                            .'cxKWMMWWWNNWNNWWWWMWXkolllllllllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,cONNk, ,KM0olllllllxNWOolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllldk0NWMMMWNXXXXXNNNNNNNNNNNWMMWKkdlllllllllkWWklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxlllllllllllllllllllll0MXxONWXd.        .dNMMWKxxxxxxxxkkkkkkOOOOOOOOOOOOOOOOOOOOOO0NMWNNWN0xl;.                                                     'cd0NWNKXWW0xxdddddddx0WWklllllllllllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;dNWk.  ,KM0olllllllxNW0olllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWOlllllllllokXMNkoooooooooooooooookNW0olllllllllllkWWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOWNxcllllllllllllllllllll0MWWWNk,        .cKWWNWWklllllllllllllllllllllllllllllllllllcoKMKddkOKNWWXOdc,.                                            .:d0NWNKOxdlkWNxllllllllllkWWklllllllllllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0olllllllxNMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWOollllllllll0MXdllllllllllllllllcdXWOllllllllllllkWW0ollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllllllllOMWKOOOOkkOOOOOOOOOOOOOO0NMMWO;         ;OWWKxkNWklllllllllllllllllllllllllllllllllllloKMKolllloxk0XNWWKko:;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;:oOXWWX0kdlllllkWNxllllllllllkWWklllllllllllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0olllllllxNMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWW0ollllllllll0MXdllllllllllllllllcdXWOllllllllllllkWW0ollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWkllllllllldONMNXXXXXXXXXXXXXXXXXXXXXXXX0c.        .dNWXkolxNWklllllllllllllllllllllllllllllllllllloKMKollllllllodxOKNMMWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWMMN0kdollllllllkWNxllllllllllkWWklllllllllllloKMKolllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0olllllllxNMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWW0ollllllllll0MXdllllllllllllllllldXM0olllllllllllkWMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWkllllllldOXWXd,.........................        .lKWNOdlllxNWklllllllllllllllllllllllllllllllllllloKMKolllllllllllllOWW0xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxkXMXxllllllllllllkWNxllllllllllkWWklllllllllllloKMKocllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0olllllllxNMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWMKollllllllll0MXdllllllllllllllllldXM0olllllllllllkWMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllllokXWNx,                                  ;OWW0dlllllxNWklllllllllllllllllllllllllllllllllllloKMKolllllllllllllOWNxcllllllllllllodxkOOkxdollllllllllllo0MKollllllllllllkWNxllllllllllkWWklllllllllllloKMN0OOOOOOOOOOOOkkkxxxxxxddZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0olllllllxNMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWMKollllllllll0MXdllllllllllllllllldXMKolllllllllllkWMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWklllokXWNk,                                  'xNWXkollllllxNWklllllllllllllllllllllllllllllllllllloKMKolllllllllllllOWNxllllllllloxOKNNNNNNNNNNKOxollllllllo0MXdllllllllllllkWNxllllllllllkWWkllllllllllloONMWNKKXXXXNNNNNNNNNNNNNNNNNZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0ollllllldXMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNMKollllllllll0MXdllllllllllllllllldXMXdlllllllllllxNMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXMOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWkloxKWNk;                                  .lKWNOollllllllxNWklllllllllllllllllllllllllllllllllllloKMKolllllllllllllOWNxlllllllokKWWKxc;,''';cd0WWXOollllllo0MXxllllllllllllkWNxllllllllllkWWkllllllllox0NWNkc.........''''''',,,;;;;:Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0ollllllldKMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxXMKollllllllll0MXdllllllllllllllllldXMXdlllllllllllxXMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXM0lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWOxKWWO;            .......................:OWW0dllllllllllxNWklllllllllllllllllllllllllllllllllllloKMKolllllllllllllOWNxllllllxXWNk;.          .;xNWXkollllo0MNxllllllllllllkWNxllllllllllkWWklllllldOXWW0o'                          Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KM0ollllllloKMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllldXMKollllllllll0MXdllllllllllllllllldXMNxllllllllllldXMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKolllllllllllldXM0lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWMWWWO:.           ;kXXKKKKKKKKKKKKKKKKKKKKXWMXkolllllllllllxNWklllllllllllllllllllllllllllllllllllloKMKolllllllllllllOWNxlllloOWWO;                ,kWW0olllo0MWkllllllllllllkWNxllllllllllkWWklllokKNWXx;.                            Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,KMKolllllllo0MXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllldKMKollllllllll0MXdllllllllllllllllldXMNxllllllllllldKMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MKollllllllllloONMN00000000000000000000000000000000000000000000000000000000000XWMW0c.           'dNMMN0OOOOOOOOOOOOOOOOOOOXMNxlllllllllllllxNWklllllllllllllllllllllllllllllllllllloKMKolllllllllllllOWNxlllo0WWx.                  .oNWKollo0MWOllllllllllllkWNxllllllllllkWWklxOXWNOc.                               Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.  ,0MWKOdollllo0MXdclllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMKollllllllll0MXdllllllllllllllllldXMNxllllllllllldKMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MKolllllllodx0XWNK00000000000000000000000000000000000000000000000000000000000000kc.           .dXWWWMKocllllllllllllllllllOMXdlllllllllllllxNWklllllllllllllllllooooooooooooooooooodKMKolllllllllllllOWNxlllOWWx.                    .oWW0oloOWWOllllllllllllkWWkoooooollllkWWXKWWKd,                                  Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.   'ckXWWKOxollOWXdcllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MKollllllllll0MXdllllllllllllllllloKMNxllllllllllloKMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MKolllloxOXNWN0o,.                                                                          .oKWNO0NMKolllllllllllllllllllOMXdlllllllllllllxNMXOOO000000000KKKKXXXXXXXXXXXXXXXXXXXXNWMN0xolllllllllllOWNxclxNMO.                      .kMNkllOWWOlllllllllldkXWMNXXXXXXKK00XMMMNk:.                                    Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.      .:dKWWN0OKMNdcllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MKoclllllllll0MXdllllllllllllllllloKMNxlllllllllllo0MKocllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MKolodOXWWKkd;.                                                                           .lKWN0dlkWMKolllllllllllllllllllOMXdlllllllllllldKWMNKK00000OOOOOOkkkkkxxxxxxxxdddddooooodxkKWWX0kdllllllllOWNxcl0MNc                        ;XMKolkNWOllllllldkKNWNOdodddxxkkOO00KOo'                                       Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oXWd.         .,oONWMMNOdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddxKMXdllllllllll0MXdlllllllllllllllllo0WNxlllllllllllo0MXdclllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMXkkKWWKx;.                                                                             .c0WWKxlllkWWOllllllllllllllllllllOMXdlllllllllld0NWKo'...                                    .;oONWN0kdollllOWNxcdXM0'                        .kMXxlxNWOlllldOKNWXkl'             ..                                          Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'oNWd.             'oKMMWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWWMXxllllllllll0MXdlllllllllllllllllo0WNxllllllllllokNMWX00000000000000000000000000000000000000000000000000000000000000000000000KNMWWWXx:.         .cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccoOWWKxollllkWNkllllllllllllllllllllOMXdlllllllldONWXo.                                            .'lkXWWXOxolOWNxckNMk.                        .xMWOldXMOoxOKWWXxc.                                                            Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;xNWXd;.             .:ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccclkNWXOdllllllll0MXdllllllllllllllllllOWNxlllllllox0NWNXX0OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKkc.          ,xXMWWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWMMWXkollllllOWNxllllllllllllllllllllOMXdlllllloOXWXd'                                                  .:xKWWX0XMWKkKWMk.                        .xMMXk0WMNXWWKx:.                                                               Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;xNMWWWXkl,.                                                                                               .:xXWWKOdollll0MXdllllllllllllllllllkWNxclllox0XWNOl,...                                                                         ..          .cONMMW0dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddkXMKdllllllllOMXdclllllllllllllllllllOMXdllllokXWNx,                                                       .;oOKXXNNXNNNk.                        .dXNNXNWWWKd:.                                                                  Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;xNWKkkKNWN0d:.                                                                                               .:xXWWXOxol0MXdllllllllllllllllllkWNxcodOXWW0o,                                                                                        ,dOKWWKKWWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0olllllllo0MXdllllllllllllllllllllOMXdllokXWNk,                                                             ...''..''.                          ..'...';;.                                                                     Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;xNW0olloxOKNWXko;.                                                                                              .:xXWWKOXMXdclllllllllllllllllkWW0OKWWKd;.                                                                                       .ckNWNXOxlxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0ollllllldXMXdllllllllllllllllllllOMXdlkKWNk,                                                                                                                                                                                  Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;o0WWOllllllldk0XWWKxc'                                                                                              .:xXWMMN0kkkkkOOO0000000000XMMMWXx;.                ''......................................................................,dKWNKkdolllxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0olllllllxNMXdllllllllllllllllllllOMN0KWNO;                                                                                                                                                                                    Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;lxKNWMWklllllllllloxOKNWNOdoddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddlc:.              .:kXWNNNNXXXXXKKKKKK000OOkxo:.                ,lONWXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXNMMKdlllllllxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0olllllllxNMXxodddddddddddddddddodKMMMWO:.                                                                                                                                                                                     Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;lx0NN0dOWWklllllllllllllldk0XWWMMWXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXNMMWXkl,.             .,'''..............                     ,lONWNWMWKOOOkOOkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkONMNkllllllllxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0olllllllOWMWNNNNNNNNNNNNNNNNNNNNWWMW0:.                                                                                                                                                                                       Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;cx0NN0o;..oWWklllllllllllllllllodONM0olllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWMXKNWN0d:.                                               'lONWNKkd0MXdclllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MXdlllllllcxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0ollllld0WMNOocccccccccccccccccccccc:.                                                                                                                                                                                         Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,';cd0NNKd;.   .oWWkllllllllllllllllllcdNWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWkldxOXWWXkl,.                                        'lONWNKkdlllOMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MNxllllllllxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0ollldONWXo,.                                                                                                                                                                                                                  Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:d0NNKd;.      .oWWkllllllllllllllllllldXM0olllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWkllllodk0XWNKxc'                                  'lONWN0kdllllllOMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MNkllllllllxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0oloOXWXd'                                                                                                                                                                                                                     Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,':kNMWk'          oWWkllllllllllllllllllldXMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllllloxOKNWNOo;.                          .,lONWN0kdlllllllllOMXdcllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MWOllllllllxNWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMKdkXWNx'                                                                                                                                                                                     .                                 Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OWMMN0l'       .dWWOolllllllllllllllllldXMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllllllllldk0XWWKklcllllooooodddddddxxxxkkk0NWN0kdllllllllllllOMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0WM0llllllllxNWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllldXMWNWNx,                                                                                                                                                                                     'x00OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;OWXO0NWXx:.     lKWWKOxollllllllllllllldXMXxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWkllllllllllllllloxXMMWNNNNNNNNNNNNNNXXXXKKKKKNWW0dlllllllllllllllOMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWM0llllllokXWMWXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXNWMMNk;                                                                                                                                                                                     .oXMMNK0000000000000000000000000000000Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OW0oldkKNWKd;.   .:dKWWXOxolllllllllllldXMNxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllllllllllllllOMNOdodooooooooooooooolllllkWWkllllllllllllllllOMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkNMOllllokXWN0xdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddooddo;                                                                                                                                                                                      :0WMMM0llllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OW0olllldOXWWOl'    .;o0NWN0kdllllllllldKMNxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllllllllllllllOWNklllllllllllllllllllllllkNWOllllllllllllllllOMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxXMOldOKXWNk;.                                                                                                                                                                                                                                                            ,kNWK0NWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,':0W0ollllllox0NWXk:.    .,oONWNKkdllllllo0MNxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllllllllllllllOWNklllllllllllllllllllllllxNW0olllllllllllllllOMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllldXMX0NWWXx,                                                                                                                                                                                                                                                             .oXMXkoxXWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'c0W0ollllllllldkKWWKd,.     'lkXWNKOdollo0WNxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllllllllllllllOWWOlllllllllllllllllllllllkNW0ollllllllllllllo0MN0kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxONMMMKo:'                                                                                                                                                                                                                                                             .:0WN0dllxNWkllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,cKW0olllllllllllldOXWNOl'      .cxKWWXOxdOWNxcllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllllllllllllllOWM0ollllllllllllllllllllllkNMKdllllllllllllokKWMWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNx.                                                                                                                                                                                                                                                               ,kNWKxllllkNWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,cKW0ollllllllllllllox0NWXk:.      .;dKWWNNMW0xxxxxxxxkkkxxxxkkkkkkkkkkOOOOOOOOO0000000000000000000000000000000000000XMWKdllllllllllllllllOWMKollllllllllllllllllllllxNMXdlllllllllldOXWNOl,''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''','.                                                                                                                                                                                                                                                              .oXWXkolllllkNWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,lKM0olllllllllllllllllokKNWKd,.      .;o0WMMWWNWNNNNNNNNNNNNNNNNNNNNNXXXXXXXXXXXXXXXXXXXXKKKKKKKKKKKKKKKKK000000000OO0XWNKOxollllllllllllkNMKolllllllllllllllllllllldXMXdlllllllokKNWKd,                                                                                                                                                                                                                                                                                                                                         .:0WN0dlllllllkWWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,oXM0olllllllllllllllllllodOXWN0d,       .;cc:;,,,,,,,'''''''''''..''...............................................  ..:d0WWX0kdlllllllllxNMKolllllllllllllllllllllldKMXdlllloxOXWNOc.                                                                                                                                                                                                                                                 .cool:;;;;;;;;;;;,,,,,,,,,,'''''''''''''''''''''.........................................;kWWKxlllllllllOWWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,oXM0ollllllllllllllllllllox0WMMNd.                                                                                       .,lONWNKOxollllldXMKolllllllllllllllllllllloKMXdllokKWWKd,                                                                                                                                                                                                                                                 .;dKWMMWWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNXXXXXXXXXXXXKKKKKKKKKKK00000000KNMNkollllllllllOWWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,oNM0ollllllllllllllllodk0XWWKxl,.                                                                                            'cxKWWX0kdlldXMKollllllllllllllllllllllo0MXxd0NWNkc.                                                                                                                                                                                                                                                .;d0WWKKWMKxxxxxxxxxxxxxxxxxxxxxxkkkkkkkkkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO0NMNxlllllllllllo0MWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNM0ollllllllllllodk0XNWXkl,.                                                                                                   .;oONWNKOOXMKocllllllllllllllllllllll0MWNWWKd,                                                                                                                                                                                                                                                .,o0WWXOxlxXWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MXdllllllllllloKMWOllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNM0ollllllllodk0XNWXOo;.                                                                                                           'cxKWMMMN0kkOOOOOOOOOOOOOOOOOOOkOXMMNkc.                                                                                                                                                                                                                                                ,lONWX0xolllxXWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMWkllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNWOollllloxOKNWNOo:.                                                                                                                  .;dKXXXXXXXXXXXXXXXXXXXXXXXXXXXKd'                                                                                                                                                                                                                                                'lONWX0xollllllxXW0ollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMNxllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNWOllllldKWMXx:'                                                                                                                         .............................                                                                                                                                                                                                                                               .ckNWX0kolllllllllxXW0ollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMXxllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNWOllllloKMMXc.                                                                                                                                                                                                                                                                                                  .;:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:lkXWN0kollllllllllllxXMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMXdllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNNkllllll0WMMWx'                                                                                                                                                                                                                                                                                               .,xNWWNNNWWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWNNNNWWMWKkdlllllllllllllllxXMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMXdllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNNxllllll0WWXNWKc                                                                                                                                                                                                                                                                                            'o0NMMWKxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxdkXMXdlllllllllllllllllxXMKdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMKdllllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNNxllllllOWXxdKWNx.                                                                                                                                                                                                                                                                                       .ckNWN00NWklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdlllllllllllllllllxXMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMKollllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNXxllllllOWXxloONWK:                                                                                                                                                                                                                                                                                   .:xXWNKkolxXWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdlllllllllllllllllxXMXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllloKMKollllllllllllllllllllllllllllllllZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNXdllllllOWNkllldKWNx.                                                                                                                                                                                                                                                                              .;dKWWKOdllllxNWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllldXMXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllldXMXkxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNXdllllll0WNklllloONWK:                                                                                                                                                                  .'...........................................                                                            'l0WWXOxollllllxNWOollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllloKMXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllllllxXWWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,xWXdllllll0WWOllllllxKWNx.                                                                                                                                                              .lKNXXNNNNXXXXXXXXXXXXXKKKKKKKKKKKKKKKKKKKKK000000000000000OOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkxxxxxxxxxxxxONWN0xolllllllllxNW0ollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllloKMXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdlllllllld0NNOoccccccccccccccccccccccccccccccccccZ",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,dNW0dlllll0WM0llllllloONW0:                                                                                                                                                           .oKWMMNOkkkkkkkkkkkkkkkkOOOOOOOOOOOOO000000000000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKNWOolllllllllllxNW0ollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdlllllllllllllllllo0MXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllllllokXW0o;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;oKNXOolll0WM0lllllllllxKWNx.                                                                                                                                                       'dXWNKNMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKM0olllllllllllxNMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdlllllllllllllllllo0WXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdlllllxKWXx:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:xKWXkolOWM0lllllllllloONW0:                                                                                                                                                    ,xXWNOdoKMKolllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMKolllllllllllxNMKollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllll0WXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdllld0NNOl,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,ckXWKxOWM0llllllllllllxKWNd.                                                                                                                                                ,xNWXOdlloKMXdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMKolllllllllllxNMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllllOWXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXdcokXWKo;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,lONWNMM0llllllllllllloONW0;                                                                                                                                             ;kNWXkolllloKMXxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMKolllllllllllxNMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllllOWXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMXxdKWXx:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;l0NMM0lllllllllllllllxXWNd.                                                                                                                                        .;kNWKkolllllloKMNklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMKdllllllllllldXMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllllOWNxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOMWXNNOl,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,';xNW0lllllllllllllllloONW0:.             ...................................................................................''''''''''''''''',,,,,,,,,,,,,,,,;;;;cOWWKxollllllllo0MWklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMXdllllllllllldKMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllllkWWOdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddxKMMWKo;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,cKW0llllllllllllllllllxKWN0OOOOOOOOOOOOO00000000000000000KKKKKKKKKKKKKKKKKXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXNNXXXNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWWMMKolllllllllloOWWklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMXxllllllllllldKMXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllllllllllldKWMWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNWWXkc,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'c0W0llllllllllllllllllloKMWK0000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxx0WW0dllllllllllllkNWklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMXxlllllllllllo0MXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdlllllllllllllldkKNN0xollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllc,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'c0W0lllllllllllllllllllo0MKocllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkNWOlllllllllllllxNWklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMNxlllllllllllo0WXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdlllllllllllok0NNKkl;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,':0W0ollllllllllllllllllo0MKdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkNW0ollllllllllllxNWklllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMWklllllllllllo0WXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllllllllox0XNKko;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:0W0olllllllllllllllllll0MKdlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNMKdlllllllllllldXWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMWkllllllllllllOWXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKollllloxOXWXOo:,',,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:OWNkllllllllllllllllllo0MXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllldXMKdlllllllllllldXMOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MWkllllllllllllOWXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKdllldOKNX0dc,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,cOWNkollllllllllllllllo0MXdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMXdlllllllllllldXM0lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloOWWkllllllllllllOWNxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MKddkKNN0xc;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:xXN0dlllllllllllllllo0MXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll0MXdlllllllllllldXM0ollllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloOWWkllllllllllllkWNkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMWXNNKkl;,,,,,,,,,,',,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;oKWXxllllllllllllllo0MNkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOWXdlllllllllllldXMKdllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkWWkllllllllllllOWWNKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXWWWXko:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,cONNOollllllllllllo0MNkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOWNxlllllllllllldXMXxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkNWklllllllllox0NWKkxxxdxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxddo:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:xXW0dlllllllllllo0MWkllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOWNklllllllllllldXMNxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkNWkllllllloxKNNOo;,,,,'',,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;oKWXxllllllllllo0MWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOWW0ollllllllllloKMNxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWklllllokKWXkl;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,ckNNOollllllllo0MWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllkNM0olllllllllllo0WNxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNWkllldOXNKxc,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;dXWKdllllllllOWWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxXM0ollllllllllllOWNxllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxXWkldONNKx:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,l0NXklllllllkNWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllldKM0ollllllllllllkWNxlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllcdXWXKNN0d:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:kNNOolllllkNWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllloKMKollllllllllllkWWKkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk0WMWNOo;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;dXWKdllllxNWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MKolllllllllloOXWNKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0kc,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,l0WXkollxXWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MXdlllllllldOXNKxc;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:kNN0olxXWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MNklllllldOXNKd:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;dXWKddXWOllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllo0MWOlllld0NN0o:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,l0WNXNWOlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllOWWOllx0NNOo;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:kNMMM0lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllxNW0k0NNOl;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;dXWMXOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk0WMWWXOl;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,lOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXKkc,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;::,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z",
		L",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Z"
	};
	int mountain_iterator = 0;
	for (const std::wstring &text : mountain)
	{
		mountain_lines_.push_back(Image(text, 600, 1));
		addImageToMatrix(world_width_ / 2 + 40, world_height_ - 150 + mountain_iterator, mountain_lines_[mountain_iterator], world_matrix_);
		mountain_iterator++;
	}

	// Fence
	std::wstring fence[] = {
		L" ,.   (* ,%*                                               Z",
		L" .@( .%,  #&%/#.                                           Z",
		L"  @( %. .% *# /&%%*                                        Z",
		L"  @( #  %. %,%##  */,                                      Z",
		L"  @# %. #.%.(.%, (&* /%,                                   Z",
		L"  @%..#%@( .%%, %#/. %%(#(                                 Z",
		L"  @@@@%,.##%&  ,#/#/(.%/ #&%#.                             Z",
		L"  @@@(,%@&. *(.(%..( ##,#%*  #,.                           Z",
		L"  @#.@&. /@@( .,( **/#.%*% .#&.,#                          Z",
		L"  @%  %@,   *@@#*%&%, (#( .(.%  (/                         Z",
		L"  @%   ,@%     *@@%/%%&* .#.#,.&&*  *%*,(#                 Z",
		L"  @%    .&&.      ,@@(,%,*@*   %# .(   .#@&,               Z",
		L"  @%      &@*        %@@*,%   ,%(,%  .%,,% %,              Z",
		L"  @%       *@(          #@@&%#.&%%. #/ .( .&.              Z",
		L"  @&         @@,           #@@/&%#*#*,%,#/(,  %,           Z",
		L"  @&          /@/          .,(@@@%.%. ,%/%, *%&%%.         Z",
		L"  @&           ,@%    ,/&@@@%(.&@@@*%#&%. .&%%. .&,        Z",
		L"  @&           ,#@@@@#*.       %@(/@( %  #&(#.*%%%*#       Z",
		L"  &&.   ,(&@@&%/. *@#          %@@#,@@,(%&/ ,%./%, #/      Z",
		L"  @@@@@%*.         .&%         %%(@, /@(#%./#*&%,#%#  %    Z",
		L"  ##.                @@,       #% (@. (@(/%&%%.,%,%   %*   Z",
		L"                      (@/      #%  &@,  @@*#/ (%%, (#// ** Z",
		L"                        @&.    #&   &@   /@( .#  ,% (#  ./ Z",
		L"                        .&@.   #&   .   .@&.%, &/%@&  #    Z",
		L"                          *@#  (&     @%    %@, *(##&&%%#. Z",
		L"                           ,@@ (&     *@/    .&&/#*,&%.  /(Z",
		L"                             /@&&.     ,@(    (%%#&//#.    Z",
		L"                              (@@@@(,.%@/   #((&%#&/(,     Z",
		L"                                     .,/%@@@@&&(&%%& ,#.   Z",
		L"                                          (@,,%%%#%&%%(%*  Z",
		L"                                           &@/./(%%%#%.((  Z",
		L"                                           .#%#,. ,@&&%#.  Z",
		L"                                           /%%%(%%&%&@(%.  Z",
		L"                                           (%%//%%&%%,     Z",
		L"                                           #, /@&%&@&&(    Z",
		L"                                           #%#&&&&&%       Z",
		L"                                          #     /@@((&.    Z",
		L"                                          #&&%..%@@@&&     Z",
		L"                                         #..@@.*&@@&&@.    Z",
		L"                                         #/,@@ #@&%%@@.    Z",
		L"                                            @@/&%@#&@&.    Z",
		L"                                            @@%@%@@.       Z",
		L"                                            @@@@@%         Z",
		L"                                            @@@(@/         Z",
		L"                                            @@%(@.         Z",
		L"                                            @@*&@          Z",
		L"                                            @@,@%          Z",
		L"                                            @@#@*          Z",
		L"                                            @@&&.          Z",
		L"                                            @@@#           Z",
		L"                                            @@@,           Z",
		L"                                            @@&            Z",
		L"                                            @@/            Z",
		L"                                            @@,            Z",
		L"                                            @@             Z",
		L"                                            &&             Z"
	};
	int fence_iterator = 0;
	for (const std::wstring &text : fence)
	{
		fence_lines_.push_back(Image(text, 59, 1));
		addImageToMatrix(world_width_ / 2 + 304, world_height_ - 110 + fence_iterator, fence_lines_[fence_iterator], world_matrix_, true);
		fence_iterator++;
	}

	// Trees (If you have a better way to organize these, go RIGHT AHEAD)
	Image tree_1("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2305, world_height_ - 84, tree_1, world_matrix_, true);
	Image tree_2("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2340, world_height_ - 77, tree_2, world_matrix_, true);
	Image tree_3("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2380, world_height_ - 76, tree_3, world_matrix_, true);
	Image tree_4("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2430, world_height_ - 70, tree_4, world_matrix_, true);
	Image tree_5("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2470, world_height_ - 78, tree_5, world_matrix_, true);
	Image tree_6("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2510, world_height_ - 79, tree_6, world_matrix_, true);
	Image tree_7("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2552, world_height_ - 81, tree_7, world_matrix_, true);
	Image tree_8("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2590, world_height_ - 84, tree_8, world_matrix_, true);
	Image tree_9("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	addImageToMatrix(2736, world_height_ - 114, tree_9, world_matrix_, true);
	//Image tree_10("                %%          =Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%#%%%    %%       Z              %   %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z");
	//addImageToMatrix(2776, world_height_ - 94, tree_10, world_matrix_, true);

	// Rocks
	Image rock_1("   @@&@   Z #@@* #@( Z #*%  (*&%Z @(%#*,#@ Z");
	addImageToMatrix(2325, world_height_ - 47, rock_1, world_matrix_, true);
	Image rock_2("   @@&@   Z #@@* #@( Z #*%  (*&%Z @(%#*,#@ Z");
	addImageToMatrix(2355, world_height_ - 65, rock_2, world_matrix_, true);
}

// creates NPCs that shouldn't attack (They are capable of it, but shouldn't)
void WorldBase::GENERATE_NonHostileNPCs()
{
	CharacterBase *standing_in_line_1;
	standing_in_line_1 = new Chr_AllMight(2372, 4936, player_health_, 1, screen_width_, screen_height_, world_matrix_, element_has_object_, matrix_display_);
	
	characters_.push_back(standing_in_line_1);
}

// creates all the sign posts (These show popups)
void WorldBase::GENERATE_Signposts()
{
	Signpost *checkpoint_sign_1 = new Signpost(2390, world_height_ - 63, 23, 9, 1, "    Nakinom      ZBorder CheckpointZ   -------->     Z                 Z    0.2 km       Z", world_matrix_, element_has_object_, matrix_display_, screen_width_, screen_height_);
	Signpost *checkpoint_sign_2 = new Signpost(2640, 4923, 23, 9, 2, "    Nakinom      ZBorder CheckpointZ                 Z", world_matrix_, element_has_object_, matrix_display_, screen_width_, screen_height_);

	signposts_.push_back(checkpoint_sign_1);
	signposts_.push_back(checkpoint_sign_2);

	// Displays all sign posts
	for (auto signpost : signposts_)
		signpost->createWorldSprite();
}

// creates all the items
void WorldBase::GENERATE_Pickups()
{
	Item cliff_item("Health Potion", 2);
	Pickup *cliff_pickup = new Pickup(2305, world_height_ - 60, 23, 9, 1, world_matrix_, element_has_object_, matrix_display_, screen_width_, screen_height_, cliff_item, inventory_);

	pickups_.push_back(cliff_pickup);

	// Displays all pickups
	for (auto pickup : pickups_)
		pickup->createWorldSprite();
}

// creates things that don't fit into any other category
void WorldBase::GENERATE_AdditionalObjects()
{

}

// creates events that trigger cutscenes, battles, enemy_movement, etc...
void WorldBase::GENERATE_Events()
{
	// TODO: creates event (), pass function to event
}

// Refreshes DEBUG tools
void WorldBase::DEBUG_refresh()
{
	// Initialize Debug Mode
	if (!DEBUG_has_initialized_)
	{
		DEBUG_screen_matrix_ = std::vector<std::vector<char>>(screen_height_, std::vector<char>(screen_width_, '/'));
		DEBUG_has_initialized_ = true;
	}
	DEBUG_drawUI();
	if (DEBUG_showing_collisions_)
	{
		DEBUG_displayCollisions();
	}
	DEBUG_displayScreen();
}

// Creates DEBUG_UI
void WorldBase::DEBUG_drawUI()
{
	drawSolidRectangle(51, 2, 27, 11, ' ', DEBUG_screen_matrix_);
	drawRectangle(51, 2, 27, 11, 'X', DEBUG_screen_matrix_);
	Image player_position("Player Pos: (" + std::to_string(screen_position_.x + screen_width_ / 2) + std::string(",") + std::to_string(screen_position_.y + screen_height_ / 2) + std::string(")Z"));
	addImageToMatrix(64, 4, player_position, DEBUG_screen_matrix_);

	Image show_collision_info("Show Collisions: ZPress c          Z");
	addImageToMatrix(64, 7, show_collision_info, DEBUG_screen_matrix_);

	Image close_debugger("Close Debugger:  ZPress h          Z");
	addImageToMatrix(64, 10, close_debugger, DEBUG_screen_matrix_);
}

// Display Collisions
void WorldBase::DEBUG_displayCollisions()
{
	for (auto pickup : pickups_)
		pickup->DEBUG_viewCollider();
	for (auto character : characters_)
		character->DEBUG_viewCollider();
	for (auto signpost : signposts_)
		signpost->DEBUG_viewCollider();
}

// Displays what was there before the collision markers replaced them
void WorldBase::DEBUG_stopDisplayingCollisions()
{
	for (auto pickup : pickups_)
		pickup->createWorldSprite();
	for (auto character : characters_)
		character->createWorldSprite();
	for (auto signpost : signposts_)
		signpost->createWorldSprite();
}

// Display DEBUG UI
void WorldBase::DEBUG_displayScreen()
{
	for (int i = 0; i < screen_height_; i++)
	{
		for (int j = 0; j < screen_width_; j++)
		{
			if (DEBUG_screen_matrix_[i][j] != '/')
				matrix_display_[i][j] = std::string(1, DEBUG_screen_matrix_[i][j]);
		}
	}
}