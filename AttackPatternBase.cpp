#include "AttackPatternBase.h"
#include <windows.h>
#include <iostream>
#include <algorithm>

AttackPatternBase::AttackPatternBase(int width, int height, int player_health, int number_of_attacks)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), empty_vector_(width, ' '), player_health_{ player_health }, attacks_to_create_{ number_of_attacks }
{
	element_is_occupied_ = new bool*[height_];
	for (int i = 0; i < height_; ++i)
		element_is_occupied_[i] = new bool[width_];
	for (int i = 0; i < height_; ++i)
		for (int j = 0; j < width_; ++j)
			element_is_occupied_[i][j] = false;

	created_attacks_ = 0;
	movePlayerToPosition(width_ / 2, height_ / 2, true);
	has_completed_initialization_ = false;
}

AttackPatternBase::~AttackPatternBase()
{
	for (int i = 0; i < height_; ++i)
		delete[] element_is_occupied_[i];
	delete[] element_is_occupied_;
}

// Calls once when the entire attack starts
void AttackPatternBase::OnBeginAttack()
{
	start_time_new_attack_ = GetTickCount();
	start_time_update_attacks_ = GetTickCount();
	start_time_refresh_screen_ = GetTickCount();
	has_completed_initialization_ = true;
}

// Sets the players location
void AttackPatternBase::refreshPlayerLocation()
{
	for (int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			if (i == player_position_.y && j == player_position_.x) // Player Position
			{
				matrix_[i][j] = 'O';
			}
			else if (!element_is_occupied_[i][j] && matrix_[i][j] != ' ')
			{
				matrix_[i][j] = ' ';
			}
		}
	}
}

// Takes input and decides whether to move player
void AttackPatternBase::evaluatePlayerInput()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (player_position_.y > 0)
			--player_position_.y;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (player_position_.y < height_ - 1)
			++player_position_.y;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (player_position_.x < width_ - 1)
			++player_position_.x;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (player_position_.x > 0)
			--player_position_.x;
	}
}

// Hurts the player
void AttackPatternBase::hurtPlayer()
{
	player_health_--;
	playPlayerHurtSound();
}

// Plays a sound
void AttackPatternBase::playPlayerHurtSound()
{
	Beep(600, 50);
	Beep(600, 500);
}

// Sets the player's position coordinates
void AttackPatternBase::movePlayerToPosition(int x_position, int y_position, bool should_round_position)
{
	if (should_round_position)
	{
		player_position_.x = round(x_position);
		player_position_.y = round(y_position);
	}
	else
	{
		player_position_.x = x_position;
		player_position_.y = y_position;
	}
}

// displays matrix for fight on screen
void AttackPatternBase::displayScreen()
{
	int newLineCounter = 0;
	for (auto line : matrix_)
	{
		if (line == empty_vector_)
		{
			newLineCounter++;
		}
		else
		{
			if (newLineCounter != 0)
			{
				for (int i = 0; i < newLineCounter; i++)
					putchar('\n');
				newLineCounter = 0;
			}
			std::string test = "";
			for (int i = 0; i < width_; i++)
			{
				test += line[i];
				//printf("%s - %s - %s", [0].c_str(), data[1].c_str(), data[2].c_str());
			}
			std::cout << test;
			/*for (auto x : line)
				std::cout << x;
				//*/
		}
	}
	//std::string yes = std::string(newLineCounter, '\n');
	for (int i = 0; i < newLineCounter; i++)
		putchar('\n');
	//std::cout << std::string(newLineCounter, '\n');
}