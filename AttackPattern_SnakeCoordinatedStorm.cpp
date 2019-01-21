#include "AttackPattern_SnakeCoordinatedStorm.h"

AttackPattern_SnakeCoordinatedStorm::AttackPattern_SnakeCoordinatedStorm(int width, int height, Matrix & screen_matrix, PlayerDefinition & player, int number_of_attacks, int creation_speed, int movement_speed, char direction, int slip_modifier, char slip_direction, bool dynamic_movement_speed, bool dynamic_creation_speed, int swap_modifier_speed, int duration_of_attack, int snake_speed)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks), direction_{ direction }, slip_direction_{ slip_direction }, slip_modifier_{ slip_modifier }, creation_speed_{ creation_speed }, movement_speed_{ movement_speed }, dynamic_creation_speed_{ dynamic_creation_speed }, duration_of_attack_{ duration_of_attack }, snake_speed_{ snake_speed },
	initial_movement_speed_{ movement_speed }, initial_creation_speed_{ creation_speed }, dynamic_movement_speed_{ dynamic_movement_speed }, swap_modifier_speed_{ swap_modifier_speed }
{
	max_starting_position_ = direction_ == 'u' || direction_ == 'd' ? width_ - 1 : height_ - 1;
	generateInOrderSequence(attack_starting_positions_, 0, max_starting_position_, 1, number_of_attacks);
}

void AttackPattern_SnakeCoordinatedStorm::OnBeginAttack()
{
	createSnake(0, generateRandomNumber(0, height_ - 1), duration_of_attack_, 50);
	createAttack(rand() % 2, *attack_starting_positions_[created_attacks_], 1);
	start_time_new_attack_ = GetTickCount64();
	start_time_move_attack_ = GetTickCount64();
	start_time_modify_speed_ = GetTickCount64();
	has_completed_initialization_ = true;
}

void AttackPattern_SnakeCoordinatedStorm::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= creation_speed_ && created_attacks_ < attacks_to_create_)
		{
			createAttack(rand() % 2, *attack_starting_positions_[created_attacks_], 1);
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

void AttackPattern_SnakeCoordinatedStorm::createAttack(int reverse_direction, int position_2D_, int speed)
{
	Attack_Dot *attack = new Attack_Dot(width_, height_, player_position_, attack_matrix_, element_is_occupied_, position_2D_, speed, direction_, slip_modifier_, slip_direction_);
	attacks_list_.push_back(attack);
	created_attacks_++;
}

void AttackPattern_SnakeCoordinatedStorm::createSnake(int head_position_x, int head_position_y, int duration_of_attack, int speed)
{
	Attack_Snake *attack;
	attack = new Attack_Snake(width_, height_, player_position_, attack_matrix_, element_is_occupied_, head_position_x, head_position_y, duration_of_attack, speed);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
