#include "MatrixManager.h"

MatrixManager::MatrixManager(int width, int height, Matrix &screen_matrix, int player_health, BitmapDefinition &bitmap, AudioDefinition &audio)
	: width_{ width }, height_{ height }, inventory_(width, height, screen_matrix, player_), player_{ player_health, 9 }, bitmap_{ bitmap },
	screen_matrix_{ screen_matrix }, current_vector_space_("START SCREEN"), has_initialized_inventory_(false), has_initialized_battle_(false),
	world_(width, height, 1200, 273, 730, 232, player_, screen_matrix, inventory_, bitmap), credits_(width_, height_, bitmap, screen_matrix_),
	audio_(audio)
{
	// Starting Items (Not pickups! Just starting items)
	inventory_.addItem("Mug o' Grog", 1, "Looks like it could burn a hole through anything it touches. Bottoms up?");
	inventory_.addItem("Fish Mush", 1, "Number 1 meal for all pirates alike.");
	StartScreen startScreen(width_, height_, screen_matrix_);
}

// Takes input and decides whether to move player, use item, etc...
void MatrixManager::evaluatePlayerInput()
{
	if (current_vector_space_ == "START SCREEN") // START GAME
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) { loadVectorSpace("MAP"); }
	}
	else if (current_vector_space_ == "MAP")
	{
		if (GetAsyncKeyState(0x49) & 0x8000) { loadVectorSpace("INVENTORY"); } // OPEN INVENTORY?
		else
		{
			world_.refreshScreen();
			if (world_.shouldEnterBattle()) { loadVectorSpace("BATTLE"); } // Is battle going on?
			else if (world_.shouldRollCredits()) { loadVectorSpace("CREDITS"); } // Should Roll Credits?
		}
	}
	else if (current_vector_space_ == "BATTLE")
	{
		if (world_.getSelectedCharacter() == nullptr || world_.getSelectedCharacter()->isBattleOver())
		{
			bitmap_.setRGBA(RGBA(255, 255, 255));
			has_initialized_battle_ = false;
			loadVectorSpace("MAP");
		}
		else if (world_.getSelectedCharacter()->getLocalVectorSpace() != "INVENTORY")
		{
			if (!has_initialized_battle_)
			{
				world_.getSelectedCharacter()->onBeginBattle();
				has_initialized_battle_ = true;
			}
			world_.getSelectedCharacter()->refreshScreen();
		}
		else
		{
			if (!has_initialized_inventory_)
			{
				inventory_.onOpenInventory(true);
				has_initialized_inventory_ = true;
			}
			if (GetAsyncKeyState(VK_BACK) & 0x8000) // CLOSE INVENTORY?
			{
				has_initialized_inventory_ = false;
				world_.getSelectedCharacter()->setVectorSpace("MENU");
			}
			inventory_.evaluatePlayerInput();
		}
	}
	else if (current_vector_space_ == "INVENTORY")
	{
		if (GetAsyncKeyState(VK_BACK) & 0x8000) { loadVectorSpace("MAP"); } // CLOSE INVENTORY?
		inventory_.evaluatePlayerInput();
	}
	else if (current_vector_space_ == "CREDITS")
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) { 
			credits_.clearText(); 
			bitmap_.showBitmap();
			bitmap_.setFilePath("resources\\sprites\\mk.bmp");
			bitmap_.setXOffset(160);
			bitmap_.setYOffset(90);
		}
		credits_.refreshScreen();
	}
}

// Changes from MAP to INVENTORY to BATTLE scenes
void MatrixManager::loadVectorSpace(std::string vector_space_name)
{
	if (vector_space_name == "INVENTORY")
	{
		inventory_.onOpenInventory();
		current_vector_space_ = "INVENTORY";
	}
	else if (vector_space_name == "MAP")
	{
		world_.onEnterWorld();
		current_vector_space_ = "MAP";
	}
	else if (vector_space_name == "BATTLE")
	{
		current_vector_space_ = "BATTLE";
	}
	else if (vector_space_name == "CREDITS")
	{
		credits_.setBackgroundText();
		current_vector_space_ = "CREDITS";
	}
}