#include "AttackPatternBase.h"
#include <windows.h>
#include <iostream>
#include <algorithm>

AttackPatternBase::AttackPatternBase(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health, int number_of_attacks)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), empty_vector_(width, ' '), player_health_{ player_health }, attacks_to_create_{ number_of_attacks }, matrix_display_{ matrix_display }
{
	element_is_occupied_ = new bool*[height_];
	for (int i = 0; i < height_; ++i)
		element_is_occupied_[i] = new bool[width_];
	for (int i = 0; i < height_; ++i)
		for (int j = 0; j < width_; ++j)
			element_is_occupied_[i][j] = false;

	created_attacks_ = 0;
	slow_player_ = 0; // Lower is faster
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
	start_time_slow_player_ = GetTickCount();
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
	double current_time_move_player = GetTickCount() - start_time_slow_player_;

	// Slow player if they are pressing SHIFT key
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		slow_player_ = 60;
	else
		slow_player_ = 0;
	if (current_time_move_player >= slow_player_)
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
		start_time_slow_player_ = GetTickCount();
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
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			matrix_display_[i][j] = std::string(1, matrix_[i][j]);
		}
	}
}