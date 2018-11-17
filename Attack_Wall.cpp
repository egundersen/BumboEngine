#include "Attack_Wall.h"
#include <windows.h>

Attack_Wall::Attack_Wall(int width, int height, PlayerPosition &player_position, std::vector<std::vector<char>>& matrix, bool **&element_is_occupied, int min_position_x, int max_position_x, int gap_height, int speed)
	: AttackBase(width, height, player_position, matrix, element_is_occupied),
	min_position_x_{ min_position_x }, max_position_x_{ max_position_x }, speed_{ speed }, gap_height_{ gap_height }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;
#ifdef _DEBUG
	if (max_position_x_ > width_)
		throw std::invalid_argument("max position must not be greater than the screen width_");
	if (min_position_x_ < 0)
		throw std::invalid_argument("min position must not be less than 0");
#endif
}

Attack_Wall::~Attack_Wall()
{
	for (int i = 0; i < width_; ++i)
		element_is_occupied_[height_ - 1][i] = false;
}

// checks if player has collided with attack
void Attack_Wall::detectCollision()
{
	for (int i = 0; i < width_; ++i)
	{
		for (int j = 0; j < height_; ++j)
			if (element_is_occupied_[j][i] == true)
				if (player_position_.y == j && player_position_.x == i)
				{
					has_hit_player_ = true;
					for (int k = 0; k < height_; k++) //Loop through all of the x values at they wall's y to erase it
					{
						matrix_[k][i] = ' ';
						element_is_occupied_[k][i] = false;
					}
				}
	}
}

// Moves attack 1-frame ( -----> Move left to right)
void  Attack_Wall::move()
{
	if (min_position_x_ * speed_ >= max_position_x_)
	{
		has_attack_finished_ = true;
		for (int i = 0; i < height_; i++)
		{
			matrix_[i][min_position_x_ * speed_ - 1] = ' ';
			element_is_occupied_[i][min_position_x_ * speed_ - 1] = false;
		}
	}
	else
	{
		if (min_position_x_ * speed_ < max_position_x_)
		{
			for (int i = 0; i < gap_height_; i++)
			{
				matrix_[i][min_position_x_ * speed_] = 'X';
				element_is_occupied_[i][min_position_x_ * speed_] = true;
			}
			for (int i = gap_height_ + 1; i < height_; i++) //Form a second wall, creating a gap
			{
				matrix_[i][min_position_x_ * speed_] = 'X';
				element_is_occupied_[i][min_position_x_ * speed_] = true;
			}
		}
		if (min_position_x_ * speed_ - 1 >= 0)
		{
			for (int i = 0; i < gap_height_; i++)
			{
				matrix_[i][min_position_x_ * speed_ - 1] = ' ';
				element_is_occupied_[i][min_position_x_ * speed_ - 1] = false;
			}
			for (int i = gap_height_ + 1; i < height_; i++)
			{
				matrix_[i][min_position_x_ * speed_ - 1] = ' ';
				element_is_occupied_[i][min_position_x_ * speed_ - 1] = false;
			}
		}

		detectCollision();
		min_position_x_++;
	}
}