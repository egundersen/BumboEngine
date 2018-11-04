#include "MatrixBase.h"
#include "AttackPattern_ShootHorizontal.h"
#include "Attacks.h"
#include "Image.h"
#include <windows.h>
#include <algorithm>
#include <iostream>

AttackPattern_ShootHorizontal::AttackPattern_ShootHorizontal(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health, int number_of_attacks)
	: AttackPatternBase(width, height, matrix_display, player_health, number_of_attacks)
{
	generateRandomSequence(attack_starting_positions_, 0, height_ - 1);
}

// Calls once when the entire attack starts
void AttackPattern_ShootHorizontal::OnBeginAttack(int player_health)
{
	player_health_ = player_health;
	createAttack(rand() % 2, 0, width_, 60, *attack_starting_positions_[created_attacks_], 1);
	start_time_new_attack_ = GetTickCount();
	start_time_update_attacks_ = GetTickCount();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_ShootHorizontal::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount() - start_time_new_attack_;
		if (current_time_new_attack_ >= 1000 && created_attacks_ < attacks_to_create_)
		{
			createAttack(rand() % 2, 0, width_, 60, *attack_starting_positions_[created_attacks_], 1);
			start_time_new_attack_ = GetTickCount();
		}

		double current_time_update_attacks = GetTickCount() - start_time_update_attacks_;
		
		for (auto it = attacks_list_.begin(); it != attacks_list_.end(); )
		{
			(*it)->move();
			if ((*it)->hasHitPlayer())
			{
				hurtPlayer();
				delete(*it);
				it = attacks_list_.erase(it);
			}
			else if ((*it)->hasAttackFinished())
			{
				delete(*it);
				it = attacks_list_.erase(it);
			}
			else
				++it;
		}
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
		attack = new HorizontalLine_Left(width_, height_, player_position_, matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);
	else
		attack = new HorizontalLine_Right(width_, height_, player_position_, matrix_, element_is_occupied_, min_position_x, max_position_x, trail_length, height_y, speed);

	attacks_list_.push_back(attack);
	created_attacks_++;
}