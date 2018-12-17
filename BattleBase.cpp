#include "BattleBase.h"
#include "AttackPatterns.h"
#include "AttackPatternBase.h"
#include <windows.h>
#include <iostream>

BattleBase::BattleBase(int width, int height, Matrix& screen_matrix, int &player_health, BossFightDefinition boss_fight_definition, BitmapDefinition &image_file_path)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), player_health_{ player_health }, boss_{ boss_fight_definition }, bitmap_{ image_file_path },
	screen_matrix_{ screen_matrix }, local_vector_space_("MENU"), cursor_index_(1), is_battle_finished_{ false }, start_time_move_cursor_{ 0 }, start_time_battle_end_animation_{ 0 },
	dialog_(width, height, screen_matrix, dialog_choices_, boss_fight_definition, image_file_path), is_destroyed_{ false }, should_restart_battle_{ false }, initial_boss_health_{ boss_fight_definition.health },
	initial_player_health_{ player_health }
{
	start_time_move_cursor_ = GetTickCount64();
	setBackgroundText();
}

// Runs when battle starts
void BattleBase::onBeginBattle()
{
	start_time_move_cursor_ = GetTickCount64();
	cursor_index_ = 1;
	refreshScreen();
	showFileSprite();
}

// Refreshes screen to show updated items list
void BattleBase::refreshScreen()
{
	if (boss_.health == 0) // BOSS DESTROYED
	{
		if (start_time_battle_end_animation_ == 0)
			start_time_battle_end_animation_ = GetTickCount64();

		bossDestroyed();
	}
	else if (local_vector_space_ != "FIGHT") // MENU OPEN
	{
		if (local_vector_space_ == "DIALOG") // DIALOG OPENED
		{
			if (dialog_.hasBossGivenUp()) // BOSS SPARED THROUGH DIALOG
			{
				if (start_time_battle_end_animation_ == 0)
					start_time_battle_end_animation_ = GetTickCount64();

				bossSpared();
			}
			else
				if (!dialog_.shouldExitDialog())
					dialog_.refreshScreen();
				else
				{
					if (attack_patterns_.size() == 0 || dialog_.shouldReturnToMenu()) // BOSS OUT OF ATTACKS
						local_vector_space_ = "MENU";
					else
						local_vector_space_ = "FIGHT";
				}
		}
		else
		{
			showFileSprite();
			evaluatePlayerInput();
			setBossHealthText();
			setPlayerHealthText(65, 3);
			displayScreen();
		}
	}
	else
	{ // ATTACK IN PROGRESS
		if (attack_patterns_.size() != 0)
		{
			if (player_health_ <= 0)
			{
				gameOver();
			}
			else if (attack_patterns_.back()->areAttacksOver())
			{
				attack_patterns_.pop_back();
				local_vector_space_ = "MENU";
			}
			else if (attack_patterns_.size() != 0)
				attack_patterns_.back()->refreshScreen();
		}
	}
}

// Sets the menu background
void BattleBase::setBackgroundText()
{
	for (int i = 1; i < height_ - 1; ++i)
	{
		matrix_[i][1] = 'X';
		matrix_[i][2] = 'X';
		matrix_[i][3] = 'X';
		matrix_[i][width_ - 2] = 'X';
		matrix_[i][width_ - 3] = 'X';
		matrix_[i][width_ - 4] = 'X';
	}

	if (!boss_.use_files)
	{
		Image main_ascii(boss_.ascii);
		Image overlay_ascii(boss_.overlay);
		addImageToMatrix(40, 14, main_ascii, matrix_);
		addImageToMatrix(boss_.overlay_x, boss_.overlay_y, overlay_ascii, matrix_);
	}

	drawRectangle(8, 29, 15, 5, 'X', matrix_);
	drawRectangle(33, 29, 15, 5, 'X', matrix_);
	drawRectangle(56, 29, 15, 5, 'X', matrix_);

	Image text1("SPEAK");
	Image text2("FIGHT");
	Image text3("ITEMS");
	addImageToMatrix(15, 31, text1, matrix_);
	addImageToMatrix(40, 31, text2, matrix_);
	addImageToMatrix(63, 31, text3, matrix_);

	drawCursor(27);

	// Boss Health
	Image bossHealthText("BOSS HEALTH");
	if (boss_.health > 11)
	{
		addImageToMatrix(8 + 11 / 2, 3, bossHealthText, matrix_);
		matrix_[4][7] = '[';
		matrix_[4][9 + 11] = ']';
		matrix_[5][7] = '[';
		matrix_[5][9 + 11] = ']';

		for (int j = 0; j < 11; ++j)
			matrix_[4][j + 8] = 'O';
	}
	else
	{
		addImageToMatrix(8 + boss_.health / 2, 3, bossHealthText, matrix_);
		matrix_[4][7] = '[';
		matrix_[4][9 + boss_.health] = ']';
	}

	// Boss name
	Image boss_name(boss_.name);
	addImageToMatrix(13, 7, boss_name, matrix_);
}

// Sets the boss health bar
void BattleBase::setBossHealthText()
{
	if (boss_.health == 0)
	{
		if (initial_boss_health_ > 11)
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 11; j++)
					matrix_[i + 4][j + 8] = ' ';
		else
			for (int j = 0; j < initial_boss_health_; j++)
				matrix_[4][j + 8] = ' ';
	}
	else if (boss_.health > 11)
	{
		for (int j = boss_.health - 11; j < 11; ++j)
			matrix_[5][j + 8] = ' ';
		for (int j = 0; j < boss_.health - 11; ++j)
			matrix_[5][j + 8] = 'O';
	}
	else
	{
		if (boss_.health == 11)
			matrix_[5][8] = ' ';
		for (int j = boss_.health; j < initial_boss_health_; ++j)
			matrix_[4][j + 8] = ' ';
		for (int j = 0; j < boss_.health; ++j)
			matrix_[4][j + 8] = 'O';
	}
}

// Sets the player health text
void BattleBase::setPlayerHealthText(int x_position, int y_position)
{
	Image player_health_text("{player}'s");
	Image lives("Lives:  ");
	addImageToMatrix(x_position, y_position, player_health_text, matrix_);
	addImageToMatrix(x_position, y_position + 1, lives, matrix_);
	matrix_[y_position + 1][x_position + 4] = player_health_ + '0';
}

// Sets the game over screen
void BattleBase::setGameOverText()
{
	drawSolidRectangle(0, 0, width_, height_, ' ', matrix_);
	for (int i = 1; i < height_ - 1; ++i)
	{
		matrix_[i][1] = 'X';
		matrix_[i][2] = 'X';
		matrix_[i][3] = 'X';
		matrix_[i][width_ - 2] = 'X';
		matrix_[i][width_ - 3] = 'X';
		matrix_[i][width_ - 4] = 'X';
	}
	for (int j = 5; j < width_ - 5; ++j)
	{
		matrix_[1][j] = '=';
		matrix_[2][j] = '=';
	}
	Image game_over_letters(" [][][]     []   []      [][]=====      [][][][]      [][]==== [][][]Z[]    []   [][]  [][]  [][][]           []  [] []    [] []     []  []Z[]  ____  []__[] [] [][] [][]=====      []  []  []  []  []==== [][][]Z[]    [] []    [][] [][] [][]           []  []   [][]   []     [] [] Z [][][]  []    [][]  []  [][]=====      [][][]    []    []==== []  []Z");
	Image funnyText(std::string("    {player} was killed by ") + boss_.name + std::string(".ZZZZZWhat? Not quite dead? Press r for a rematch!Z"));
	addImageToMatrix(39, 16, funnyText, matrix_);
	addImageToMatrix(39, 6, game_over_letters, matrix_);
}

// Chooses where to display the cursor
void BattleBase::setCursorText()
{
	// erase old cursor
	drawRectangle(11, 30, 9, 3, ' ', matrix_);
	drawRectangle(36, 30, 9, 3, ' ', matrix_);
	drawRectangle(59, 30, 9, 3, ' ', matrix_);

	// draw new cursor
	switch (cursor_index_)
	{
	case 0:
		drawCursor(2);
		break;
	case 1:
		drawCursor(27);
		break;
	case 2:
		drawCursor(50);
		break;
	default:
		break;
	}
}

// Draws a cursor at the specified location
void BattleBase::drawCursor(int offset)
{
	matrix_[30][12 + offset] = 'v';
	matrix_[30][13 + offset] = 'v';
	matrix_[30][14 + offset] = 'v';
	matrix_[32][12 + offset] = '^';
	matrix_[32][13 + offset] = '^';
	matrix_[32][14 + offset] = '^';
	matrix_[31][17 + offset] = '<';
	matrix_[31][9 + offset] = '>';
}

// Takes input for battle menu
void BattleBase::evaluatePlayerInput()
{
	double current_time_move_cursor = GetTickCount64() - start_time_move_cursor_;

	if (current_time_move_cursor > 100)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			moveCursor("RIGHT");
			setCursorText();
			start_time_move_cursor_ = GetTickCount64();
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			moveCursor("LEFT");
			setCursorText();
			start_time_move_cursor_ = GetTickCount64();
		}
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			if (current_time_move_cursor > 500)
			{
				confirmSelection();
				start_time_move_cursor_ = GetTickCount64();
			}
		}
	}
}

// Move the cursor up or down
void BattleBase::moveCursor(std::string move_cursor_direction)
{
	if (move_cursor_direction == "LEFT")
	{
		if (cursor_index_ == 0)
			cursor_index_ = 2;
		else
			cursor_index_--;
	}
	else if (move_cursor_direction == "RIGHT")
	{
		if (cursor_index_ == 2)
			cursor_index_ = 0;
		else
			cursor_index_++;
	}
}

// The player's turn to attack
void BattleBase::damageBoss()
{
	if (attack_patterns_.size() != 0)
	{
		attack_patterns_.back()->OnBeginAttack();
		local_vector_space_ = "FIGHT";
		boss_.health--;
		hideFileSprite();
	}
	else // attacking boss when boss is out of attacks is an instant kill
	{
		boss_.health = 0;
	}
}

// Called when boss runs out of attacks
void BattleBase::bossOutOfAttacks()
{
	// todo something
}

// Boss is killed
void BattleBase::bossDestroyed()
{
	double current_time_battle_end_animation = GetTickCount64() - start_time_battle_end_animation_;
	if (current_time_battle_end_animation <= 5000)
		showFileSprite("ANGRY");
	else if (current_time_battle_end_animation > 5000)
	{
		for (int i = 0; i < 27; i++)
			for (int j = 0; j < 68; j++)
				matrix_[1 + i][5 + j] = ' ';

		showFileSprite("nervous_dead");
	}

	displayScreen();
	if (current_time_battle_end_animation > 10000)
	{
		is_destroyed_ = true;
		is_battle_finished_ = true;
		hideFileSprite();
	}
}

// Boss is spared
void BattleBase::bossSpared()
{
	double current_time_battle_end_animation = GetTickCount64() - start_time_battle_end_animation_;
	if (current_time_battle_end_animation <= 5000)
		showFileSprite("NEUTRAL");
	else if (current_time_battle_end_animation > 5000)
	{
		for (int i = 0; i < 27; i++)
			for (int j = 0; j < 68; j++)
				matrix_[1 + i][5 + j] = ' ';

		showFileSprite("HAPPY");
	}

	displayScreen();
	if (current_time_battle_end_animation > 10000)
	{
		is_battle_finished_ = true;
		hideFileSprite();
	}
}

// Calls a function: Fight, Speak, Spare, Open Inventory depending on cursor position
void BattleBase::confirmSelection()
{
	switch (cursor_index_)
	{
	case 0:
		dialog_.onOpenDialog();
		local_vector_space_ = "DIALOG";
		hideFileSprite();
		break;
	case 1:
		damageBoss();
		break;
	case 2:
		local_vector_space_ = "INVENTORY";
		hideFileSprite();
		break;
	default:
		break;
	}
}

// Runs if player dies
void BattleBase::gameOver()
{
	setGameOverText();
	displayScreen();

	if (GetKeyState(0x52) & 0x8000) // Press r to restart battle
	{ //&& player_health_ <= 0
		is_destroyed_ = true;
		is_battle_finished_ = true;
		hideFileSprite();
		should_restart_battle_ = true;
	}
}

// Decides which file sprite to display
void BattleBase::showFileSprite(std::string emotion)
{
	if (boss_.use_files)
	{
		if (emotion == "") // Decide whether to use emotion based on health left
		{
			if (boss_.health < initial_boss_health_ / 2) // Half Health
				bitmap_.setFilePath(boss_.file_path_angry);
			else
				bitmap_.setFilePath(boss_.file_path_neutral);
		}
		else if (emotion == "NEUTRAL")
			bitmap_.setFilePath(boss_.file_path_neutral);
		else if(emotion == "ANGRY")
			bitmap_.setFilePath(boss_.file_path_angry);
		else if (emotion == "nervous_dead")
			bitmap_.setFilePath(boss_.file_path_nervous_dead);
		else if (emotion == "HAPPY")
			bitmap_.setFilePath(boss_.file_path_happy);
		bitmap_.setXOffset(160);
		bitmap_.showBitmap();
	}
}

// Erases the file sprite
void BattleBase::hideFileSprite()
{
	if (boss_.use_files)
		bitmap_.hideBitmap();
}

// Resets the battle space
void BattleBase::resetBattleSpace()
{
	local_vector_space_ = "MENU";

	start_time_move_cursor_ = GetTickCount64();
	boss_.health = initial_boss_health_;
	player_health_ = initial_player_health_;

	clearMatrix(width_, height_, matrix_);
	setBackgroundText();

	is_destroyed_ = false;
	is_battle_finished_ = false;
	should_restart_battle_ = false;

	dialog_.reset();
}

// displays matrix on screen
void BattleBase::displayScreen()
{
	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			screen_matrix_[i][j] = matrix_[i][j];
		}
	}
}
