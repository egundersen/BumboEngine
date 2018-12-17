#include "Attack_Explode.h"
#include <windows.h>

Attack_Explode::Attack_Explode(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>>& matrix, bool **&element_is_occupied, int center_position_x, int center_position_y, int diameter, int delay, int duration_of_explosion)
	: AttackBase(width, height, player_position, matrix, element_is_occupied), diameter_{ diameter }, delay_{ delay }, duration_of_explosion_{ duration_of_explosion },
	center_position_x_{ center_position_x }, center_position_y_{ center_position_y }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;
	start_time_update_attack_ = GetTickCount64();
}

Attack_Explode::~Attack_Explode()
{
	for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
		for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
			element_is_occupied_[center_position_y_ + i][center_position_x_ + j] = false;
}

// checks if player has collided with attack
void Attack_Explode::detectCollision()
{
	for (int i = -(diameter_ / 2); i < (diameter_ / 2); ++i)
		for (int j = -(diameter_ / 2); j < (diameter_ / 2); ++j)
			if (element_is_occupied_[center_position_y_ + i][center_position_x_ + j] == true)
				if (player_position_.y == center_position_y_ + i && player_position_.x == center_position_x_ + j)
					has_hit_player_ = true;
}

// Creates box, fills box
void Attack_Explode::move()
{
	if (!has_attack_finished_)
	{
		double current_time_update_attack = GetTickCount64() - start_time_update_attack_;
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
			start_time_update_attack_ = GetTickCount64();
		}
	}
}

