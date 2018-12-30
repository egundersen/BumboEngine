#include "Attack_HorizontalLine.h"
#include <windows.h>

Attack_HorizontalLine::Attack_HorizontalLine(int width, int height, PlayerPosition &player_position, Matrix &attack_matrix, bool **&element_is_occupied, int min_position_x, int max_position_x, int trail_length, int height_y, int speed)
	: AttackBase(width, height, player_position, attack_matrix, element_is_occupied),
	min_position_x_{ min_position_x }, max_position_x_{ max_position_x }, trail_length_{ trail_length }, height_y_{ height_y }, speed_{ speed }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;

#ifdef _DEBUG
	if (max_position_x_ > width_)
		throw "max position must not be greater than the screen width_";
	if (min_position_x_ < 0)
		throw "min position must not be less than 0";
#endif
}

Attack_HorizontalLine::~Attack_HorizontalLine()
{
	for (int i = 0; i < width_; ++i)
		element_is_occupied_[height_y_][i] = false;
}

// checks if player has collided with attack
void Attack_HorizontalLine::detectCollision()
{
	for (int i = 0; i < width_; ++i)
		if (element_is_occupied_[height_y_][i] == true)
			if (player_position_.y == height_y_ && player_position_.x == i)
				has_hit_player_ = true;
}

// Moves attack 1-frame ( -----> Move left to right)
void HorizontalLine_Right::move()
{
	if (min_position_x_ * speed_ - trail_length_ >= max_position_x_)
	{
		has_attack_finished_ = true;
	}
	else
	{
		if (min_position_x_ * speed_ < max_position_x_)
		{
			attack_matrix_[height_y_][min_position_x_ * speed_] = '>';
			element_is_occupied_[height_y_][min_position_x_ * speed_] = true;
		}
		if (min_position_x_ * speed_ - trail_length_ >= 0)
		{
			attack_matrix_[height_y_][min_position_x_ * speed_ - trail_length_] = ' ';
			element_is_occupied_[height_y_][min_position_x_ * speed_ - trail_length_] = false;
		}
		if (min_position_x_ * speed_ - trail_length_ * 3 / 4 >= 0 && min_position_x_ * speed_ - trail_length_ * 3 / 4 < max_position_x_)
		{
			if ((min_position_x_ * speed_ - trail_length_ * 3 / 4) % 2 == 0)
				attack_matrix_[height_y_][min_position_x_ * speed_ - trail_length_ * 3 / 4] = '-';
			else
				attack_matrix_[height_y_][min_position_x_ * speed_ - trail_length_ * 3 / 4] = ' ';
		}
		if (min_position_x_ * speed_ - trail_length_ / 2 >= 0 && min_position_x_ * speed_ - trail_length_ / 2 < max_position_x_)
		{
			attack_matrix_[height_y_][min_position_x_ * speed_ - trail_length_ / 2] = '-';
		}
		if (min_position_x_ * speed_ - 1 >= 0 && min_position_x_ * speed_ - 1 < max_position_x_)
		{
			attack_matrix_[height_y_][min_position_x_ * speed_ - 1] = '=';
		}
		detectCollision();
		min_position_x_++;
	}
}

// Moves attack 1-frame ( <----- Move right to left)
void HorizontalLine_Left::move()
{
	if (max_position_x_ * speed_ + trail_length_ <= 0)
	{
		has_attack_finished_ = true;
	}
	else
	{
		if (max_position_x_ * speed_ > min_position_x_ && max_position_x_ * speed_ < width_)
		{
			attack_matrix_[height_y_][max_position_x_ * speed_] = '<';
			element_is_occupied_[height_y_][max_position_x_ * speed_] = true;
		}
		if (max_position_x_ * speed_ + trail_length_ < width_)
		{
			attack_matrix_[height_y_][max_position_x_ * speed_ + trail_length_] = ' ';
			element_is_occupied_[height_y_][max_position_x_ * speed_ + trail_length_] = false;
		}
		if (max_position_x_ * speed_ + trail_length_ * 3 / 4 < width_ && max_position_x_ * speed_ + trail_length_ * 3 / 4 > min_position_x_)
		{
			if ((max_position_x_ * speed_ + trail_length_ * 3 / 4) % 2 == 0)
				attack_matrix_[height_y_][max_position_x_ * speed_ + trail_length_ * 3 / 4] = '-';
			else
				attack_matrix_[height_y_][max_position_x_ * speed_ + trail_length_ * 3 / 4] = ' ';
		}
		if (max_position_x_ * speed_ + trail_length_ / 2 < width_ && max_position_x_ * speed_ + trail_length_ / 2 > min_position_x_)
		{
			attack_matrix_[height_y_][max_position_x_ * speed_ + trail_length_ / 2] = '-';
		}
		if (max_position_x_ * speed_ + 1 < width_ && max_position_x_ * speed_ + 1 > min_position_x_)
		{
			attack_matrix_[height_y_][max_position_x_ * speed_ + 1] = '=';
		}
		detectCollision();
		max_position_x_--;
	}
}
