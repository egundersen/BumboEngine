#include "MatrixManager.h"
#include "MatrixBase.h"
#include "Inventory.h"
#include "Image.h"
#include <windows.h>
#include <thread>
#include <iostream>

MatrixManager::MatrixManager(int width, int height, int player_health) : width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), empty_vector_(width, ' '), inventory_(width, height, player_health_), debugAttack_(width_, height_, player_health, "Shoot Horizontal Attack", 6), player_health_{ player_health }
{
	optimizeConsoleWindow();
	current_vector_space_ = "BATTLE"; //TODO: Change to MAP
	inventory_.addItem("Health Potion"); //TODO: remove from here and add this to picking up item on map
	inventory_.addItem("Secret Potion");
	inventory_.addItem("Hat          ");
	inventory_.addItem("Hat          ");
	StartScreen startScreen(width_, height_);
}

// Takes input and decides whether to move player, use item, etc...
void MatrixManager::evaluatePlayerInput()
{
	if (current_vector_space_ == "MAP")
	{
		
	}
	else if (current_vector_space_ == "BATTLE")
	{
		debugAttack_.OnBeginAttack();
	}
	else if (current_vector_space_ == "INVENTORY")
	{
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

// Runs optimization code to make the console run faster
void MatrixManager::optimizeConsoleWindow()
{
	std::ios::sync_with_stdio(false);
	hideTypingCursor();

	std::thread indent_lines1(&MatrixManager::indentLines, this, 3300);
	std::thread indent_lines2(&MatrixManager::indentLines, this, 3300);
	std::thread indent_lines3(&MatrixManager::indentLines, this, 3300);
	std::thread indent_lines4(&MatrixManager::indentLines, this, 3300);
	indent_lines1.join();
	indent_lines2.join();
	indent_lines3.join();
	indent_lines4.join();
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
