#include "MatrixManager.h"
#include "MatrixBase.h"
#include "Inventory.h"
#include "Image.h"
#include <windows.h>
#include <thread>
#include <iostream>

MatrixManager::MatrixManager(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), empty_vector_(width, ' '), inventory_(width, height, player_health_, matrix_display),
	debugAttack_(width_, height_, matrix_display, player_health, 15), player_health_{ player_health }, matrix_display_{ matrix_display }
{
	current_vector_space_ = "START SCREEN"; //TODO: Change to MAP
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
			current_vector_space_ = "BATTLE";
	}
	else if (current_vector_space_ == "MAP")
	{
		if (GetAsyncKeyState(0x49) & 0x8000) // OPEN INVENTORY?
			loadVectorSpace("INVENTORY");
	}
	else if (current_vector_space_ == "BATTLE")
	{
		debugAttack_.refreshScreen();
		if (GetAsyncKeyState(0x49) & 0x8000) // TODO: Remove this line of code
			loadVectorSpace("INVENTORY");
	}
	else if (current_vector_space_ == "INVENTORY")
	{
		if (GetAsyncKeyState(VK_BACK) & 0x8000) // CLOSE INVENTORY?
			loadVectorSpace("MAP");

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
		player_health_ = inventory_.getPlayerHealth();
		current_vector_space_ = "MAP";
	}
	else if (vector_space_name == "BATTLE")
	{
		player_health_ = inventory_.getPlayerHealth();
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
