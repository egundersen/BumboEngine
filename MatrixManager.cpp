#include "MatrixManager.h"
#include "MatrixBase.h"
#include "Inventory.h"
#include "Characters.h"
#include "Image.h"
#include <windows.h>
#include <thread>
#include <iostream>

MatrixManager::MatrixManager(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), inventory_(width, height, matrix_display, player_health_),
	player_health_{ player_health }, matrix_display_{ matrix_display }, current_vector_space_("START SCREEN"), has_initialized_inventory_(false), has_initialized_battle_(false),
	DEBUG_battle_(width, height, matrix_display, player_health_), maze_(width, height, 5000, 5000, 2370, 5000 - 55, player_health_, matrix_display, inventory_)
{
	inventory_.addItem("Health Potion"); //TODO: remove from here and add this to picking up item on map
	inventory_.addItem("Secret Potion");
	inventory_.addItem("Hat          ");
	inventory_.addItem("Hat          ");
	StartScreen startScreen(width_, height_, matrix_display_);
}

// Takes input and decides whether to move player, use item, etc...
void MatrixManager::evaluatePlayerInput()
{
	if (current_vector_space_ == "START SCREEN")  // START GAME
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			current_vector_space_ = "MAP"; //TODO: Change to MAP
	}
	else if (current_vector_space_ == "MAP")
	{
		if (GetAsyncKeyState(0x49) & 0x8000) // OPEN INVENTORY?
			loadVectorSpace("INVENTORY");
		else
			maze_.refreshScreen();
	}
	else if (current_vector_space_ == "BATTLE")
	{
		if (DEBUG_battle_.isBattleOver()) {
			has_initialized_battle_ = false;
			std::cout << "BATTLE IS OVER FUCKO!";
			current_vector_space_ = "MAP";
		}
		else if (DEBUG_battle_.getLocalVectorSpace() != "INVENTORY") {
			if (!has_initialized_battle_) {
				DEBUG_battle_.onBeginBattle();
				has_initialized_battle_ = true;
			}
			DEBUG_battle_.refreshScreen();
		}
		else {
			if (!has_initialized_inventory_) {
				inventory_.onOpenInventory();
				has_initialized_inventory_ = true;
			}
			if (GetAsyncKeyState(VK_BACK) & 0x8000) {// CLOSE INVENTORY?
				has_initialized_inventory_ = false;
				DEBUG_battle_.setVectorSpace("MENU");
			}
			inventory_.evaluatePlayerInput();
		}
	}
	else if (current_vector_space_ == "INVENTORY")
	{
		if (GetAsyncKeyState(VK_BACK) & 0x8000) {// CLOSE INVENTORY?
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
		maze_.onEnterWorld();
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
