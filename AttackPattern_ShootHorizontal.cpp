#include "MatrixBase.h"
#include "AttackPattern_ShootHorizontal.h"
#include "Attacks.h"
#include "Image.h"
#include <windows.h>
#include <algorithm>
#include <iostream>

AttackPattern_ShootHorizontal::AttackPattern_ShootHorizontal(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, int number_of_attacks)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks)
{
	generateRandomSequence(attack_starting_positions_, 0, height_ - 1);
}

// Calls once when the entire attack starts
void AttackPattern_ShootHorizontal::OnBeginAttack()
{
	createAttack(rand() % 2, 0, width_, 60, *attack_starting_positions_[created_attacks_], 1);
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_ShootHorizontal::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= 1000 && created_attacks_ < attacks_to_create_) // Create new Attacks
		{
			createAttack(rand() % 2, 0, width_, 60, *attack_starting_positions_[created_attacks_], 1);
			start_time_new_attack_ = GetTickCount64();
		}

		attacksCheckCollision();
		moveAttack();

		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();
	}
}

// Add attack to list of attacks
void AttackPattern_ShootHorizontal::createAttack(int reverse_direction, int min_position_x, int max_position_x, int trail_length, int height_y, int speed)
{
	Attack_HorizontalLine *attack;
	if (reverse_direction == 1)
		attack = new HorizontalLine_Left(width_, height_, player_position_, attack_matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);
	else
		attack = new HorizontalLine_Right(width_, height_, player_position_, attack_matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);

	attacks_list_.push_back(attack);
	created_attacks_++;
}