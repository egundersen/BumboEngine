#include "AttackPattern_HailStorm.h"

AttackPattern_HailStorm::AttackPattern_HailStorm(int width, int height, Matrix & screen_matrix, PlayerDefinition & player, int number_of_attacks, int creation_speed, int movement_speed, char direction, int slip_modifier, char slip_direction, bool dynamic_movement_speed, bool dynamic_creation_speed, int  swap_modifier_speed)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks), direction_{ direction }, slip_direction_{ slip_direction }, slip_modifier_{ slip_modifier }, creation_speed_{ creation_speed }, movement_speed_{ movement_speed }, dynamic_creation_speed_{ dynamic_creation_speed },
	initial_movement_speed_{ movement_speed }, initial_creation_speed_{ creation_speed }, dynamic_movement_speed_{ dynamic_movement_speed }, swap_modifier_speed_{ swap_modifier_speed }
{
	max_starting_position_ = direction_ == 'u' || direction_ == 'd' ? width_ : height_;
}

void AttackPattern_HailStorm::OnBeginAttack()
{
	createAttack(rand() % 2, generateRandomNumber(0, max_starting_position_), 1);
	start_time_new_attack_ = GetTickCount64();
	start_time_move_attack_ = GetTickCount64();
	start_time_modify_speed_ = GetTickCount64();
	has_completed_initialization_ = true;
}

void AttackPattern_HailStorm::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= creation_speed_ && created_attacks_ < attacks_to_create_)
		{
			createAttack(rand() % 2, generateRandomNumber(0, max_starting_position_), 1);
			start_time_new_attack_ = GetTickCount64();
		}

		attacksCheckCollision();

		double current_time_move_attack_ = GetTickCount64() - start_time_move_attack_;
		if (current_time_move_attack_ >= movement_speed_)
		{
			moveAttack();
			start_time_move_attack_ = GetTickCount64();
		}

		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();

		double current_time_modify_speed = GetTickCount64() - start_time_modify_speed_;
		if (current_time_modify_speed >= swap_modifier_speed_)
		{
			if (dynamic_creation_speed_)
				creation_speed_ = generateRandomNumber(10, initial_creation_speed_);
			if (dynamic_movement_speed_)
				movement_speed_ = generateRandomNumber(10, initial_movement_speed_);
			start_time_modify_speed_ = GetTickCount64();
		}
	}
}

void AttackPattern_HailStorm::createAttack(int reverse_direction, int position_2D_, int speed)
{
	Attack_Dot *attack = new Attack_Dot(width_, height_, player_position_, attack_matrix_, element_is_occupied_, position_2D_, speed, direction_, slip_modifier_, slip_direction_);
	attacks_list_.push_back(attack);
	created_attacks_++;
}
