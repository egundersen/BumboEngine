#include "Attack_Snake.h"
#include <windows.h>

Attack_Snake::Attack_Snake(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>>& matrix, bool **&element_is_occupied, int head_position_x, int head_position_y, int duration_of_attack)
	: AttackBase(width, height, player_position, matrix, element_is_occupied), duration_of_attack_{ duration_of_attack },
	head_position_x_{ head_position_x }, head_position_y_{ head_position_y }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;
	start_time_update_attack_ = GetTickCount();
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
	/*if (!has_attack_finished_)
	{
		double current_time_update_attack = GetTickCount() - start_time_update_attack_;
		if (current_time_update_attack < delay_)
		{
			for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
				for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
					if (matrix_[center_position_y_ + i][center_position_x_ + j] != 'X')
						matrix_[center_position_y_ + i][center_position_x_ + j] = '.';
			for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
				for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
					element_is_occupied_[center_position_y_ + i][center_position_x_ + j] = true;
		}
		else if (current_time_update_attack > delay_ && current_time_update_attack < delay_ + duration_of_explosion_)
		{
			drawSolidRectangle(center_position_x_ - (diameter_ / 2), center_position_y_ - (diameter_ / 2), diameter_, diameter_, 'X', matrix_);
			for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
				for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
					element_is_occupied_[center_position_y_ + i][center_position_x_ + j] = true;
			detectCollision();
		}
		else if (current_time_update_attack > delay_ + duration_of_explosion_)
		{
			drawSolidRectangle(center_position_x_ - 1, center_position_y_ - 1, 3, 3, ' ', matrix_);
			for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
				for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
					if (matrix_[center_position_y_ + i][center_position_x_ + j] != '.')
						matrix_[center_position_y_ + i][center_position_x_ + j] = ' ';
			has_attack_finished_ = true;
			start_time_update_attack_ = GetTickCount();
		}
	}*/
	if ((GetTickCount() - start_time_update_attack_) > duration_of_attack_)
		has_attack_finished_ = true;
	else
	{
		matrix_[head_position_y_][head_position_x_] = 'o';
		if (head_position_x_ < player_position_.x && head_position_x_ + 2 < width_)
		{
			matrix_[head_position_y_][head_position_x_ + 2] = 'o';
			element_is_occupied_[head_position_y_][head_position_x_] = true;
			head_position_x_++;
		}
		else if (head_position_x_ > player_position_.x && head_position_x_ - 2 > 0)
		{
			matrix_[head_position_y_][head_position_x_ - 2] = 'o';
			element_is_occupied_[head_position_y_][head_position_x_] = true;
			head_position_x_--;
		}
		if (head_position_y_ < player_position_.y && head_position_y_ + 2 < height_)
		{
			matrix_[head_position_y_ + 2][head_position_x_] = 'o';
			element_is_occupied_[head_position_y_ + 2][head_position_x_] = true;
			head_position_y_++;
		}
		else if (head_position_y_ < player_position_.y && head_position_y_ - 2 < 0)
		{
			matrix_[head_position_y_ - 2][head_position_x_] = 'o';
			element_is_occupied_[head_position_y_ - 2][head_position_x_] = true;
			head_position_y_--;
		}
		detectCollision();
	}
}


