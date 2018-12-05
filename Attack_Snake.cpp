#include "Attack_Snake.h"
#include <windows.h>

Attack_Snake::Attack_Snake(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>>& matrix, bool **&element_is_occupied, int head_position_x, int head_position_y, int duration_of_attack)
	: AttackBase(width, height, player_position, matrix, element_is_occupied), duration_of_attack_{ duration_of_attack },
	head_position_x_{ head_position_x }, head_position_y_{ head_position_y }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;
	start_time_update_attack_ = GetTickCount();
	start_time_end_attack_ = GetTickCount();
}

Attack_Snake::~Attack_Snake()
{
	//for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
	//	for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
	//		element_is_occupied_[center_position_y_ + i][center_position_x_ + j] = false;
	matrix_[head_position_y_][head_position_x_] = ' ';
	element_is_occupied_[head_position_y_][head_position_x_] = false;
}

// checks if player has collided with attack
void Attack_Snake::detectCollision()
{
	//for (int i = -(diameter_ / 2); i < (diameter_ / 2); ++i)
		//for (int j = -(diameter_ / 2); j < (diameter_ / 2); ++j)
			//if (element_is_occupied_[center_position_y_ + i][center_position_x_ + j] == true)
				//if (player_position_.y == center_position_y_ + i && player_position_.x == center_position_x_ + j)
					//has_hit_player_ = true;
	if (player_position_.x == head_position_x_ && player_position_.y == head_position_y_)
		has_hit_player_ = true;
}

// Creates box, fills box
void Attack_Snake::move()
{
	double current_time_end_attack = GetTickCount() - start_time_end_attack_;
	double current_time_update_attack = GetTickCount() - start_time_update_attack_;

	if (current_time_end_attack > duration_of_attack_)
		has_attack_finished_ = true;
	else if (current_time_update_attack > 500)
	{
		matrix_[head_position_y_][head_position_x_] = 'o';
		element_is_occupied_[head_position_y_][head_position_x_] = true;
		if (head_position_x_ < player_position_.x)
		{
			head_position_x_++;
		}
		if (head_position_x_ > player_position_.x)
		{
			head_position_x_--;
		}
		if (head_position_y_ < player_position_.y)
		{
			head_position_y_++;
		}
		if (head_position_y_ > player_position_.y)
		{
			head_position_y_--;
		}
		detectCollision();
		start_time_update_attack_ = GetTickCount();
	}
}


