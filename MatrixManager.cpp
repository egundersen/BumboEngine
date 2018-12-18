#include "MatrixManager.h"
#include "MatrixBase.h"
#include "Inventory.h"
#include "Characters.h"
#include "Image.h"
#include <windows.h>
#include <thread>
#include <iostream>

MatrixManager::MatrixManager(int width, int height, Matrix &screen_matrix, int player_health, BitmapDefinition &image_file_path)
	: width_{ width }, height_{ height }, inventory_(width, height, screen_matrix, player_health_), player_health_{ player_health }, 
	screen_matrix_{ screen_matrix }, current_vector_space_("START SCREEN"), has_initialized_inventory_(false), has_initialized_battle_(false),
	world_(width, height, 1200, 273, 730, 232, player_health_, screen_matrix, inventory_, image_file_path)
{
	inventory_.addItem("Mug o' Grog", 1); // Starting Items (Not pickups! Just starting items)
	inventory_.addItem("Fish Mush", 1);
	StartScreen startScreen(width_, height_, screen_matrix_);
}

// Takes input and decides whether to move player, use item, etc...
void MatrixManager::evaluatePlayerInput()
{
	if (current_vector_space_ == "START SCREEN") // START GAME
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			current_vector_space_ = "MAP";
	}
	else if (current_vector_space_ == "MAP")
	{
		if (GetAsyncKeyState(0x49) & 0x8000) // OPEN INVENTORY?
			loadVectorSpace("INVENTORY");
		else
		{
			world_.refreshScreen();
			if (world_.shouldEnterBattle()) // Is battle going on?
				current_vector_space_ = "BATTLE";
		}
	}
	else if (current_vector_space_ == "BATTLE")
	{
		if (world_.getSelectedCharacter() == nullptr) // Called if enemy is destroyed during dialog
		{
			has_initialized_battle_ = false;
			world_.onEnterWorld();
			current_vector_space_ = "MAP";
		}
		else if (world_.getSelectedCharacter()->isBattleOver())
		{
			has_initialized_battle_ = false;
			world_.onEnterWorld();
			current_vector_space_ = "MAP";
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
			if (GetAsyncKeyState(VK_BACK) & 0x8000)
			{// CLOSE INVENTORY?
				has_initialized_inventory_ = false;
				world_.getSelectedCharacter()->setVectorSpace("MENU");
			}
			inventory_.evaluatePlayerInput();
		}
	}
	else if (current_vector_space_ == "INVENTORY")
	{
		if (GetAsyncKeyState(VK_BACK) & 0x8000)
		{// CLOSE INVENTORY?
			loadVectorSpace("MAP");
		}

		inventory_.evaluatePlayerInput();
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
}

// runs when the game should shut down
void MatrixManager::onShutdown()
{
	// TODO: display shutdown popup
	waitForInput();
}

// Hides the typing cursor from being displayed
void MatrixManager::hideTypingCursor()
{
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.bVisible = FALSE;
	cursor_info.dwSize = 100;
	HANDLE console_handler = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(console_handler, &cursor_info);
}

// Indents an <INSERT> amount of lines
void MatrixManager::indentLines(int number_of_indents)
{
	for (int i = 1000; i < number_of_indents; i++)
		std::cout << "\n";
}
