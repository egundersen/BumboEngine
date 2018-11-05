#include "MatrixManager.h"
#include "MatrixBase.h"
#include "Inventory.h"
#include "Characters.h"
#include "Image.h"
#include <windows.h>
#include <thread>
#include <iostream>

MatrixManager::MatrixManager(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), inventory_(width, height, matrix_display, player_health),
	player_health_{ player_health }, matrix_display_{ matrix_display }, current_vector_space_("START SCREEN"), has_initialized_inventory_(false), has_initialized_battle_(false),
	debugBattle_(width, height, matrix_display, player_health, 2, "            ,,#,@@@@@,@,*@@@@,*#@@@%             Z           ,,,,,,,@@(&,@@@@@@@@@@@@@%,           Z          @,#,,,,,,,,,,,@,%@@@@@&,,@@@           Z         ,,,@@,,,,,,,,,,,,%@@@@@@,,@@@@          Z         @@,#,,,,,,,,,,,,,%@@@@@@,,,@@@          Z         @@@,,,,,,,,,,,,,,@@@@@@@@,,,@@          Z        ,,@,,,,,,,,,,,,,,,@@@@@@@@,,,@@@         Z        ,@@,,&,&,@,,,.,,,@@@@@,@,@,,,,@@         Z       ,@#,,,,,@@&,@,#(%,,@,&@@@@@@,,,@@@        Z        ,@,,,,,%@@@@@,,/#*@@@@@@@@,,,,@@@        Z       ,@#,,,,,,,(@@@%,@@@@@@@@@@@@,,,*@,,       Z      ,,@,,,,,,,,,,,,,,,,@@@,,*@@@@@,,,,@,       Z      ,@,,,,,,,,,,,,,,,,,@@@,,,,@@@@,,,@,,       Z      @,*,#,,,,,,,,,,,,,,@@@@,,@@@@@@,@@,,       Z      ,@@,,@,@,,,,,,@@@@@@@@@&,@@@@@@,,@,,       Z      ,,@,,,@,,,,&,,,,,@@@@/,@@@@@@@@,@@,.       Z       ,,@,,,,,@,,,,,,,,,,,,,,(@@@@@,,@%,,       Z      ,&,,,,,,@,,,,,,,,,,,,,,,,,,@@@,,,,@@,&     Z     ,,,@@,,,,,@@%@**,,,,,,,,,,,@@@@,,@@@@  .    Z   @@,,@,@#,,/,,@&,,,,,,,,,,,,@,@@@@,,@@@@@      Z    ,(@@,,@,,@,,,&,,,,,,,,,,,,@@@@@@,,@@.@@@@,   Z   ,@@@@,,/,,@@,,,,,,,,,,,,@@@@@@@@@,.@@,@@@@@@  Z &@@@@@@,,,@,,,,,,,,,,,,,@@@@@@@@@@@,@@@&@@(     Z@@@@ @@(,,,,@@,,,,,,,,,,,@@@@@@@@@,@@@@@@*@@@@,  Z    @@@,,,,,,,@@,,,,,,,,,@@@@@@@,@@@@@@@@,       Z      @,,,,,,,,,,@@,,,,,*@@@@%,@@@@@@@@@@@%      Z       @@,,,,,,,,,,@@@@@@@@@@@@@@@@@@@@@@@       Z     @@@@@@@@/,,,,,,@@@@@@@@@@@@@@@@@@@@@@@@     ", "X*XXXXX________XXXXXXZ,X*  --        -- *X,Z,,X*   --------  *X,,Z,,,,X**        **X,,,Z,,,,,,,XXXXXXXX,,,,,,", 40, 20)
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
		if (GetAsyncKeyState(VK_MENU) & 0x8000) //TODO: Change back to VK_RETURN
			current_vector_space_ = "BATTLE";
	}
	else if (current_vector_space_ == "MAP")
	{
		if (GetAsyncKeyState(0x49) & 0x8000) // OPEN INVENTORY?
			loadVectorSpace("INVENTORY");
		// TODO: Load_Map_Space
	}
	else if (current_vector_space_ == "BATTLE")
	{
		if (debugBattle_.isBattleOver()) {
			has_initialized_battle_ = false;
			player_health_ = debugBattle_.getPlayerHealth();
			std::cout << "BATTLE IS OVER FUCKO!";
		}
		else if (debugBattle_.getLocalVectorSpace() != "INVENTORY") {
			if (!has_initialized_battle_) {
				debugBattle_.onBeginBattle(player_health_);
				has_initialized_battle_ = true;
			}
			debugBattle_.refreshScreen();
		}
		else {
			if (!has_initialized_inventory_) {
				inventory_.onOpenInventory(player_health_);
				has_initialized_inventory_ = true;
			}
			if (GetAsyncKeyState(VK_BACK) & 0x8000) {// CLOSE INVENTORY?
				player_health_ = inventory_.getPlayerHealth();
				has_initialized_inventory_ = false;
				debugBattle_.setVectorSpace("MENU");
			}
			inventory_.evaluatePlayerInput();
		}
	}
	else if (current_vector_space_ == "INVENTORY")
	{
		if (GetAsyncKeyState(VK_BACK) & 0x8000) {// CLOSE INVENTORY?
			player_health_ = inventory_.getPlayerHealth();
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
		inventory_.onOpenInventory(player_health_);
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
