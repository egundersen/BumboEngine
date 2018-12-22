#include "WorldBase.h"
#include <Windows.h>
#include <iostream>

WorldBase::WorldBase(int screen_width, int screen_height, int world_width, int world_height, int starting_position_x, int starting_position_y, int &player_health, Matrix &screen_matrix, Inventory &inventory, BitmapDefinition &image_file_path)
	: screen_width_{ screen_width }, screen_height_{ screen_height }, world_width_{ world_width }, world_height_{ world_height }, start_time_player_speed_(0), element_has_object_(world_height, std::vector<std::pair<int, int>>(world_width, std::make_pair<int, int>(0, 0))),
	world_matrix_(world_width, world_height), screen_matrix_{ screen_matrix }, player_health_{ player_health }, player_sprite_{ 12, 10, screen_matrix }, player_speed_modifier_(30), inventory_{ inventory }, DEBUG_has_initialized_{ false },
	DEBUG_showing_collisions_{ false }, opposite_player_direction_('d'), should_enter_battle_{ false }, is_event_active_{ false }, image_file_path_{ image_file_path }, enter_key_pressed_{ false }
{
	screen_position_.x = starting_position_x - screen_width / 2;
	screen_position_.y = starting_position_y - screen_height / 2;

	generateWorld();
	player_sprite_.initializeSprites(sprite_sheet_.player);
}

// Runs once whenever the player enters the world (Like when exiting a battle or the inventory)
void WorldBase::onEnterWorld()
{
	start_time_player_speed_ = GetTickCount64();
	should_enter_battle_ = false;
	shouldDespawnCharacter();
}

// Calls every frame
void WorldBase::refreshScreen()
{
	if (is_viewing_popup_ && getFacingEntity() != std::make_pair<int, int>(0, 0)) // Called onInteract (Press E)
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
				}
			break;
		case 3: // Character
			for (CharacterBase *character : characters_)
				if (character->getUniqueObjectID() == getFacingEntity().second)
				{
					if (character->useBasicDialog()) // Character uses basic dialog popup
					{
						displayScreen();
						character->refreshPopup();
					}
					else // Character uses advanced dialog system
					{
						selected_character_ = character;
						selected_character_->showDialog();
					}
					character->faceDirection(opposite_player_direction_);
					player_sprite_.setPlayerMoving("not verticle");
					player_sprite_.setPlayerMoving("not horizontal");
				}
			is_viewing_popup_ = false;
			break;
		default:
			is_viewing_popup_ = false;
			break;
		}
	}
	else
	{
		checkForItem();
		checkForBattle();
		displayScreen();

		if (is_event_active_) // EVENTS
		{
			selected_event_->refreshEvent();
			if (selected_event_->shouldEnterBattle())
			{
				// Commented code has the same function as the below code, just a different approach
				/*for (auto character : characters_)
					if (character->getUniqueObjectID() == selected_event_->getUniqueObjectID())
						selected_character_ = character; //*/
				selected_character_ = selected_event_->getAttachedCharacter();
				should_enter_battle_ = true;
				selected_character_->stopBattle();
			}
			shouldDespawnCharacter();
			shouldRemoveEvent();
		}
	}
	evaluatePlayerInput();
}

// Returns address to selected character (Either the one fighting player, talking, etc...)
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
			if (world_matrix_[screen_position_.y + screen_height_ / 2 - player_sprite_.getHeight() / 2 + offset][screen_position_.x + screen_width_ / 2 - player_sprite_.getWidth() / 2 + 2 + j] != ' ')
				return true;
		return false;
		break;
	case'd':
		for (int j = 0; j < player_sprite_.getWidth() / 2 + 2; j++)
			if (world_matrix_[screen_position_.y + screen_height_ / 2 + player_sprite_.getHeight() / 2 - offset][screen_position_.x + screen_width_ / 2 - player_sprite_.getWidth() / 2 + 2 + j] != ' ')
				return true;
		return false;
		break;
	case 'l':
		for (int i = 3; i < player_sprite_.getHeight() / 2 + 1; i++) // 3: only bottom half of player should collide
			if (world_matrix_[screen_position_.y + screen_height_ / 2 - player_sprite_.getHeight() / 2 + 3 + i][screen_position_.x + screen_width_ / 2 - player_sprite_.getWidth() / 2 + offset] != ' ')
				return true;
		return false;
		break;
	case'r':
		for (int i = 3; i < player_sprite_.getHeight() / 2 + 1; i++) // 3: only bottom half of player should collide
			if (world_matrix_[screen_position_.y + screen_height_ / 2 - player_sprite_.getHeight() / 2 + 3 + i][screen_position_.x + screen_width_ / 2 + player_sprite_.getWidth() / 2 - offset] != ' ')
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
			for (int i = 0; i < 2; i++) // Collision on Two Lines
				if (element_has_object_[screen_position_.y + screen_height_ / 2 - 3 + i][screen_position_.x + screen_width_ / 2 + j].first != 0)
					return element_has_object_[screen_position_.y + screen_height_ / 2 - 3 + i][screen_position_.x + screen_width_ / 2 + j];
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
			char temp = world_matrix_[screen_position_.y + i][screen_position_.x + j];
			screen_matrix_[i][j] = temp;
			screen_matrix_[i][j].setColor(world_matrix_[screen_position_.y + i][screen_position_.x + j].getRGBA());
		}
	}

	player_sprite_.displaySprite(screen_width_, screen_height_);
	if (selected_character_ != nullptr && selected_character_->shouldShowDialog())
		selected_character_->displayDialogMenu();

#ifdef _DEBUG
	if (DEBUG_mode_enabled_)
		DEBUG_refresh();
#endif // !_DEBUG
}

// Takes input and decides whether to move player
void WorldBase::evaluatePlayerInput()
{
	double current_time_move_player = GetTickCount64() - start_time_player_speed_;

	if (selected_character_ != nullptr && selected_character_->shouldShowDialog()) // Navigating dialog
	{
		if (current_time_move_player >= 300) // Movement UP, DOWN, LEFT, RIGHT
		{
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				selected_character_->moveDialogCursor("RETURN");
				start_time_player_speed_ = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				selected_character_->moveDialogCursor("UP");
				start_time_player_speed_ = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				selected_character_->moveDialogCursor("DOWN");
				start_time_player_speed_ = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_BACK) & 0x8000)
			{
				selected_character_->closeDialog();
			}
		}
	}
	else if (selected_event_ != nullptr && is_event_active_) // Traversing Event Dialog
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (!enter_key_pressed_)
			{
				selected_event_->progressPopup();
				enter_key_pressed_ = true;
			}
		}
		else
		{
			enter_key_pressed_ = false;
		}
	}
	else // Walking in world
	{
		if (GetAsyncKeyState(0x45) & 0x8000) // Press E
		{
			is_viewing_popup_ = true;
		}
		else
		{
			checkRemovePickup();
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000) // Running
			{
				player_speed_modifier_ = 1;
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
					if (screen_position_.y > 0 && !hasCollided('u', 5)) // 2
					{
						--screen_position_.y;
						player_sprite_.setPlayerMoving("verticle");
					}
					player_sprite_.setDirection('u');
					opposite_player_direction_ = 'd';
					shouldStartEventByLocation();
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
					shouldStartEventByLocation();
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
					shouldStartEventByLocation();
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
					shouldStartEventByLocation();
				}
				else
					player_sprite_.setPlayerMoving("not horizontal");
				start_time_player_speed_ = GetTickCount64();
			}
			is_viewing_popup_ = false;
		}
	}

#ifdef _DEBUG
	if (GetAsyncKeyState(0x47) & 0x8000) // Open DEBUG Mode!		Press G
		DEBUG_mode_enabled_ = true;
	if (GetAsyncKeyState(0x48) & 0x8000) // Close DEBUG Mode!		Press H
	{
		if (DEBUG_showing_collisions_)
			DEBUG_stopDisplayingCollisions();
		DEBUG_showing_collisions_ = false;
		DEBUG_mode_enabled_ = false;
	}
	if (DEBUG_mode_enabled_)
	{
		if (GetAsyncKeyState(0x43) & 0x8000) // Collisions!				HOLD C
			DEBUG_showing_collisions_ = true;
		else
		{
			if (DEBUG_showing_collisions_)
				DEBUG_stopDisplayingCollisions();
			DEBUG_showing_collisions_ = false;
		}
		if (GetAsyncKeyState(0x54) & 0x8000) // Teleport Player			Press T
			teleportPlayer(1048, 210);
		else if (GetAsyncKeyState(0x4D) & 0x8000) // Teleport Player    Press M (Teleport to Maze)
			teleportPlayer(296, 231);
	}
#endif
}

// Teleports player to specified coordinates
void WorldBase::teleportPlayer(int position_x, int position_y)
{
	screen_position_.x = position_x - screen_width_ + 40; // An offset
	screen_position_.y = position_y - screen_height_ + 18;
}

// creates the world
void WorldBase::generateWorld()
{
	GENERATE_Maze();
	GENERATE_OutsideArea();
	GENERATE_WorldBorder();
	GENERATE_AdditionalObjects();
	GENERATE_Enemies();
	GENERATE_NonHostileNPCs();
	GENERATE_Pickups();
	GENERATE_Signposts();
	GENERATE_Events();

	setNPCAttributes();
}

// Checks for a pickup to remove from map (That was already picked up)
void WorldBase::checkRemovePickup()
{
	if (is_viewing_popup_ && getFacingEntity().first == 2)
		for (Pickup *pickup : pickups_)
			if (pickup->getUniqueObjectID() == getFacingEntity().second)
				delete(pickup);
}

// Checks whether or not to give the player an item from dialog
void WorldBase::checkForItem()
{
	if (selected_character_ != nullptr && selected_character_->shouldGiveItem())
	{
		inventory_.addItem(selected_character_->givenItem());
		selected_character_->stopGivingItem();
	}
}

// Checks whether or not to enter battle from dialog or an event
void WorldBase::checkForBattle()
{
	if (selected_character_ != nullptr && selected_character_->shouldEnterBattle())
	{
		should_enter_battle_ = true;
		selected_character_->stopBattle();
	}
}

// Decides whether or not to removes character from array (They are dead). Called after battle has ended in player's favor
void WorldBase::shouldDespawnCharacter()
{
	if (selected_character_ != nullptr)
	{
		if (selected_character_->isDestroyed())
		{
			if (selected_character_->shouldRestart()) // Player died (so they can restart)
			{
				should_enter_battle_ = true;
				inventory_.reset();
				selected_character_->reset();
			}
			else
			{
				shouldStartEventByID(selected_character_->eventID());
				selected_character_->onDespawn();
				{
					auto it = std::find(characters_.begin(), characters_.end(), selected_character_);
					if (it != characters_.end()) { characters_.erase(it); }
				}
				selected_character_ = nullptr;
			}
		}
	}
}

// Decides whether or not to remove event from array (Event has ended).
void WorldBase::shouldRemoveEvent()
{
	if (selected_event_ != nullptr)
	{
		if (selected_event_->isComplete())
		{
			if (selected_event_->isRepeatable())
				selected_event_->reset();
			else
			{
				auto it = std::find(events_.begin(), events_.end(), selected_event_);
				if (it != events_.end()) { events_.erase(it); }
			}
			is_event_active_ = false;
			selected_event_ = nullptr;
		}
	}
}

// Decides whether or not to start an event (based on the player's location)
void WorldBase::shouldStartEventByLocation()
{
	if (getFacingEntity().first == 4)
		for (EventBase *event : events_)
			if (event->getUniqueObjectID() == getFacingEntity().second)
			{
				player_sprite_.setPlayerMoving("not verticle");
				player_sprite_.setPlayerMoving("not horizontal");

				event->onStartEvent();
				selected_event_ = event;
				is_event_active_ = true;
			}
}

// Decides whether or not to start an event (based on a given ID number)
void WorldBase::shouldStartEventByID(int event_ID)
{
	if (event_ID == 0)
		return;
	else
		for (EventBase *event : events_)
			if (event_ID == event->getUniqueObjectID())
			{
				player_sprite_.setPlayerMoving("not verticle");
				player_sprite_.setPlayerMoving("not horizontal");

				event->onStartEvent();
				selected_event_ = event;
				is_event_active_ = true;
			}
}

// Displays all Characters & Gives them an attack_on_sight event (if necessary)
void WorldBase::setNPCAttributes()
{
	for (auto character : characters_)
	{
		character->createWorldSprite();
		if (character->shouldAttackOnSight())
		{
			Event_AttackOnSight *attack_on_sight = new Event_AttackOnSight(character->getUniqueObjectID(), character->getCenterPositionX(), character->getCenterPositionY(), 10, 10, character->getUniqueObjectID(), false, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
			attack_on_sight->createEvent();

			events_.push_back(attack_on_sight);
		}
	}
}

// creates a nice border around the world. Useful for debugging, helps tell if you are building near edge of world
void WorldBase::GENERATE_WorldBorder()
{
	for (int i = 0; i < world_height_; i++)
		world_matrix_[i][0] = 'X';
	for (int i = 0; i < world_height_ - 15; i++)
		world_matrix_[i][world_width_ - 2] = 'X';
	for (int j = 0; j < world_width_; j++)
		world_matrix_[0][j] = 'X';
	for (int j = 0; j < world_width_; j++)
		world_matrix_[world_height_ - 2][j] = 'X';
}

// creates objects for the cliff area outside the maze. This is the player's spawn / start of the game
void WorldBase::GENERATE_OutsideArea()
{
	// Outside area / map
	Texture mountain(900, 137, sprite_sheet_.mountain, world_matrix_);

	// Fence
	Texture fence(1161, 181, sprite_sheet_.fence, world_matrix_);

	// Trees
	Texture tree_1(665, 205, sprite_sheet_.tree, world_matrix_);
	Texture tree_2(700, 210, sprite_sheet_.tree, world_matrix_);
	Texture tree_3(740, 210, sprite_sheet_.tree, world_matrix_);
	Texture tree_4(790, 217, sprite_sheet_.tree, world_matrix_);
	Texture tree_5(830, 192, sprite_sheet_.tree, world_matrix_);
	Texture tree_6(870, 192, sprite_sheet_.tree, world_matrix_);
	Texture tree_7(912, 206, sprite_sheet_.tree, world_matrix_);
	Texture tree_8(950, 203, sprite_sheet_.tree, world_matrix_);
	Texture tree_9(1096, 173, sprite_sheet_.tree, world_matrix_);

	// Rocks
	Texture rock_1(685, 240, sprite_sheet_.rock, world_matrix_);
	Texture rock_2(715, 222, sprite_sheet_.rock, world_matrix_);
	Texture rock_3(780, 239, sprite_sheet_.rock, world_matrix_);
}

// Creates the walls of the maze as well as objects that should be placed INSIDE the maze
void WorldBase::GENERATE_Maze()
{
	// Maze
	Texture maze_1(300, 137, sprite_sheet_.maze_1, world_matrix_);
	Texture maze_2(300, 1, sprite_sheet_.maze_2, world_matrix_);
	Texture maze_3(900, 1, sprite_sheet_.maze_3, world_matrix_);
}

// creates NPCs that SHOULD attack (They don't have to at first, but if they attack at any time, but them here)
void WorldBase::GENERATE_Enemies()
{
	CharacterBase *tutorial_npc = new Chr_TutorialNPC(838, 225, 1, sprite_sheet_.tutorial_NPC, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_);
	CharacterBase *aki_final = new Chr_AkiFinal(1063, 259, 10, sprite_sheet_.aki, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_);

	CharacterBase *ryuuko = new Chr_Ryuuko(1023, 259, 11, sprite_sheet_.ryuuko, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_);
	CharacterBase *aki = new Chr_Aki(1033, 259, 12, sprite_sheet_.aki, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_);
	CharacterBase *bonny = new Chr_Bonny(1043, 259, 13, sprite_sheet_.bonny, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_);
	CharacterBase *sharktooth = new Chr_Sharktooth(1053, 259, 14, sprite_sheet_.sharktooth, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_);

	tutorial_npc->initializeCharacter();
	aki_final->initializeCharacter();
	aki->initializeCharacter();
	ryuuko->initializeCharacter();
	bonny->initializeCharacter();
	sharktooth->initializeCharacter();

	characters_.push_back(tutorial_npc);
	characters_.push_back(aki_final);
	characters_.push_back(aki);
	characters_.push_back(ryuuko);
	characters_.push_back(bonny);
	characters_.push_back(sharktooth);

#ifdef _DEBUG
	CharacterBase *test;
	test = new Chr_AllMight(732, 223, 0, sprite_sheet_.player, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_);
	test->initializeCharacter();
	characters_.push_back(test);
#endif
}

// creates NPCs that SHOULD NOT attack (They are capable of it, but this section is for NPCs that shouldn't)
void WorldBase::GENERATE_NonHostileNPCs()
{
	CharacterBase *standing_in_line_1 = new Chr_BackgroundNPC(1027, 205, 2, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("Been waitin' in line for five days...", 'X', 23, 9), sprite_sheet_.player, 'u');
	CharacterBase *standing_in_line_2 = new Chr_BackgroundNPC(1034, 202, 3, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("Yar har har 'n a bottle o' rum!", 'X', 23, 9), sprite_sheet_.pirate_1, ' u');
	CharacterBase *standing_in_line_3 = new Chr_BackgroundNPC(1041, 200, 4, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("I be starvin'... But I don't wants t' leave th' line", 'X', 23, 9), sprite_sheet_.pirate_1, 'r');
	CharacterBase *standing_in_line_4 = new Chr_BackgroundNPC(1048, 202, 5, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("STOP SHOVING! Oh... um, ahoy matey!", 'X', 23, 9), sprite_sheet_.pirate_1, 'r');
	CharacterBase *standing_in_line_5 = new Chr_BackgroundNPC(1056, 201, 6, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("Back o' th' line! Can't ye tell I was here first?", 'X', 23, 9), sprite_sheet_.player, 'r');
	CharacterBase *standing_in_line_6 = new Chr_BackgroundNPC(1016, 210, 7, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("Ye're a pirate too? Better get in line!", 'X', 23, 9), sprite_sheet_.player, 'r');

	CharacterBase *boarder_guard_1 = new Chr_BackgroundNPC(1079, 203, 8, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("Another pirate... Get in line with the rest!", 'X', 23, 9), sprite_sheet_.player, 'l');
	CharacterBase *boarder_guard_2 = new Chr_BackgroundNPC(1071, 214, 9, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("Another pirate... Get in line with the rest!", 'X', 23, 9), sprite_sheet_.player, 'l');

	CharacterBase *boarder_incident_random = new Chr_BackgroundNPC(1013, 259, 15, player_health_, screen_width_, screen_height_, world_matrix_, element_has_object_, screen_matrix_, image_file_path_,
		PopupDefinition("", 'X', 23, 9), sprite_sheet_.player, 'r');

	standing_in_line_1->initializeCharacter();
	standing_in_line_2->initializeCharacter();
	standing_in_line_3->initializeCharacter();
	standing_in_line_4->initializeCharacter();
	standing_in_line_5->initializeCharacter();
	standing_in_line_6->initializeCharacter();
	boarder_guard_1->initializeCharacter();
	boarder_guard_1->initializeCharacter();
	boarder_incident_random->initializeCharacter();

	characters_.push_back(standing_in_line_1);
	characters_.push_back(standing_in_line_2);
	characters_.push_back(standing_in_line_3);
	characters_.push_back(standing_in_line_4);
	characters_.push_back(standing_in_line_5);
	characters_.push_back(standing_in_line_6);
	characters_.push_back(boarder_guard_1);
	characters_.push_back(boarder_guard_2);
	characters_.push_back(boarder_incident_random);
}

// creates all the sign posts (These show popups)
void WorldBase::GENERATE_Signposts()
{
	Signpost *checkpoint_sign_1 = new Signpost(750, 224, 23, 9, 1, "Nakinom Border Checkpoint --------> 0.2 km", world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_);
	Signpost *checkpoint_sign_2 = new Signpost(1000, 210, 23, 9, 2, "Nakinom Border Checkpoint", world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_);

	signposts_.push_back(checkpoint_sign_1);
	signposts_.push_back(checkpoint_sign_2);

	// Displays all sign posts
	for (auto signpost : signposts_)
		signpost->createWorldSprite();
}

// creates all the items
void WorldBase::GENERATE_Pickups()
{
	Item cliff_item("Health Potion", 2, "Restores 2 HP");
	Pickup *cliff_pickup = new Pickup(665, 227, 23, 9, 1, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, cliff_item, inventory_);

	/*Item item_1("Pirate ALE", 1, "It looks completely black. There is a 50/50 chance this will kill you if you drink it");
	Pickup *pickup_1 = new Pickup(859, 27, 23, 9, 2, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_1, inventory_);
	Item item_2("Pile of Pigeon", 1, "A local delicacy, wrapped in newspaper: try not to think of whats inside");
	Pickup *pickup_2 = new Pickup(607, 266, 23, 9, 3, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_2, inventory_);
	Item item_3("Ground meat paste", 2, "From the cafeteria, but at least it's still warm");
	Pickup *pickup_3 = new Pickup(589, 266, 23, 9, 4, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_3, inventory_);
	Item item_4("Whiskey", 1, "This is the non-alcoholic version");
	Pickup *pickup_4 = new Pickup(463, 381, 23, 9, 5, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_4, inventory_);
	Item item_5("Bottle o' Rum", 1, "This is the non-alcoholic version");
	Pickup *pickup_5 = new Pickup(450, 369, 23, 9, 6, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_5, inventory_);
	Item item_6("Health Potion", 2, "Restores 2 HP");
	Pickup *pickup_6 = new Pickup(151, 534, 23, 9, 7, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_6, inventory_);
	Item item_7("Pizza", 2, "Dominos Pizzia: Great if you're short on cash and don't mind the delivery guy missing your house entirely");
	Pickup *pickup_7 = new Pickup(177, 530, 23, 9, 8, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_7, inventory_);
	Item item_8("Lemon", 1, "An ordinary lemon. It's too sour to eat");
	Pickup *pickup_8 = new Pickup(192, 496, 23, 9, 9, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_8, inventory_);//*/

	Item item_clue_1("Cigar Box", 1, "Assembled in Cuba : Made in China");
	Pickup *pickup_clue_1 = new Pickup(1130, 212, 23, 9, 10, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_clue_1, inventory_);
	Item item_clue_2("Long Sword", 1, "There's a tag on the side: If lost return to Ryuuko");
	Pickup *pickup_clue_2 = new Pickup(1127, 204, 23, 9, 11, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_clue_2, inventory_);
	Item item_clue_3("Feather", 1, "It's a turkey feather cut to mimic a hawk feather: someone was short-changed");
	Pickup *pickup_clue_3 = new Pickup(841, 46, 23, 9, 12, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_clue_3, inventory_);
	Item item_clue_4("Glove", 1, "A single black glove, missing from a pair");
	Pickup *pickup_clue_4 = new Pickup(1146, 205, 23, 9, 13, world_matrix_, element_has_object_, screen_matrix_, screen_width_, screen_height_, item_clue_4, inventory_);

	pickups_.push_back(cliff_pickup);
	/*pickups_.push_back(pickup_1);
	pickups_.push_back(pickup_2);
	pickups_.push_back(pickup_3);
	pickups_.push_back(pickup_4);
	pickups_.push_back(pickup_5);
	pickups_.push_back(pickup_6);
	pickups_.push_back(pickup_7);
	pickups_.push_back(pickup_8);//*/
	pickups_.push_back(pickup_clue_1);
	pickups_.push_back(pickup_clue_2);
	pickups_.push_back(pickup_clue_3);
	pickups_.push_back(pickup_clue_4);

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
	/* Event_Test *test = new Event_Test(9999, 150, 649, 10, 10, element_has_object_, screen_matrix_, characters_, nullptr);
	 * Excluding the test event, Event Unique Object ID's should BEGIN at 10000
	 * Events with ID's 1 - 9998 are reserved for characters that start battles */
	Event_Tutorial *tutorial = new Event_Tutorial(10000, 790, 232, 10, 11, 1, false, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_BorderIncident *border_incident = new Event_BorderIncident(10002, 1071, 206, 4, 4, 1, false, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_LostDevice *lost_device = new Event_LostDevice(10003, 1033, 34, 4, 4, 1, false, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	
	Event_TeleportPlayer *teleport_to_maze = new Event_TeleportPlayer(10001, 1107, 195, 10, 8, 296, 231, 1, true, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_TeleportPlayer *teleport_to_mountain = new Event_TeleportPlayer(10004, 296, 250, 10, 8, 1107, 202, 1, true, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_TeleportPlayer *teleport_to_sharktooth = new Event_TeleportPlayer(10005, 297, 174, 10, 4, 104, 241, 1, true, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_TeleportPlayer *teleport_from_sharktooth = new Event_TeleportPlayer(10006, 104, 253, 10, 8, 297, 179, 1, true, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_TeleportPlayer *teleport_to_aki = new Event_TeleportPlayer(10007, 393, 21, 10, 8, 679, 87, 1, true, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_TeleportPlayer *teleport_from_aki = new Event_TeleportPlayer(10008, 679, 103, 10, 8, 393, 33, 1, true, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);
	Event_TeleportPlayer *teleport_to_mini_bosses = new Event_TeleportPlayer(10009, 731, 59, 10, 8, 857, 65, 1, true, element_has_object_, screen_matrix_, characters_, screen_position_, screen_width_, screen_height_);

	// events_.push_back(test);
	events_.push_back(tutorial);
	events_.push_back(teleport_to_maze);
	events_.push_back(border_incident);
	events_.push_back(lost_device);
	events_.push_back(teleport_to_mountain);
	events_.push_back(teleport_to_sharktooth);
	events_.push_back(teleport_from_sharktooth);
	events_.push_back(teleport_to_aki);
	events_.push_back(teleport_from_aki);
	events_.push_back(teleport_to_mini_bosses);

	// Set all event colliders / tiggers
	for (auto event : events_)
		event->createEvent();
}

// Refreshes DEBUG tools
void WorldBase::DEBUG_refresh()
{
	// Initialize Debug Mode
	if (!DEBUG_has_initialized_)
	{
		DEBUG_screen_matrix_ = Matrix(screen_width_, screen_height_, '/');
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
	drawSolidRectangle(51, 2, 27, 14, ' ', DEBUG_screen_matrix_);
	drawRectangle(51, 2, 27, 14, 'X', DEBUG_screen_matrix_);
	Image player_position("Player Pos: (" + std::to_string(screen_position_.x + screen_width_ / 2) + std::string(",") + std::to_string(screen_position_.y + screen_height_ / 2) + std::string(")Z"));
	addImageToMatrix(64, 4, player_position, DEBUG_screen_matrix_);

	Image show_collision_info("Show Collisions: ZPress c          Z");
	addImageToMatrix(64, 7, show_collision_info, DEBUG_screen_matrix_);

	Image close_debugger("Close Debugger:  ZPress h          Z");
	addImageToMatrix(64, 10, close_debugger, DEBUG_screen_matrix_);

	Image teleport("Teleport to maze:ZPress t          Z");
	addImageToMatrix(64, 13, teleport, DEBUG_screen_matrix_);
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
	for (auto event : events_)
		event->DEBUG_viewCollider(world_matrix_);
}

// Displays what was there before the collision markers replaced them
void WorldBase::DEBUG_stopDisplayingCollisions()
{
	for (auto pickup : pickups_)
		pickup->createWorldSprite();
	for (auto event : events_)
		event->DEBUG_hideCollider(world_matrix_);
	for (auto character : characters_)
		character->DEBUG_eraseSpriteColliders();
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
			{
				char temp = DEBUG_screen_matrix_[i][j];
				screen_matrix_[i][j] = temp;
				screen_matrix_[i][j].setColor(DEBUG_screen_matrix_[i][j].getRGBA());
			}
		}
	}
}