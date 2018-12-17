#include "AttackPattern_VerticleGap.h"
#include <windows.h>
#include <iostream>

AttackPattern_VerticleGap::AttackPattern_VerticleGap(int width, int height, Matrix& screen_matrix, int & player_health)
	: AttackPatternBase(width, height, screen_matrix, player_health, height), create_attack_delay_{ 50 }, gap_width_{ 4 }, screen_duration_{ 20000 }, attacks_created_(0), move_delay_(80),
	start_time_end_warning_(0), warning_length_(3000)
{
}

// Calls once when the entire attack starts
void AttackPattern_VerticleGap::OnBeginAttack()
{
	setAttackParameters();
	start_time_new_attack_ = GetTickCount64();
	start_time_end_warning_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_VerticleGap::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_end_warning_ = GetTickCount64() - start_time_end_warning_;
		if (current_time_end_warning_ >= warning_length_)
		{
			double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
			if (current_time_new_attack_ >= create_attack_delay_ && created_attacks_ < attacks_to_create_) // Create new Attacks
			{
				createAttack(width_ / 2, created_attacks_);
				start_time_new_attack_ = GetTickCount64();
			}

			attacksCheckCollision();
			moveAttack();
		}
		else // Displaying warning message before attack begins
		{
			Image warning(">>>>>>>>>>>>>Z");
			addImageToMatrix(width_ / 2, 10, warning, matrix_);
			for (int j = 0; j < width_; j++)
				element_is_occupied_[10][j] = true;

		}
		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();
	}
}

// Add attack to list of attacks
void AttackPattern_VerticleGap::createAttack(int gap_position_x, int position_y)
{
	Attack_VerticleGap *attack;
	attack = new Attack_VerticleGap(width_, height_, player_position_, matrix_, element_is_occupied_, gap_position_x, position_y, gap_width_, screen_duration_, move_delay_);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
