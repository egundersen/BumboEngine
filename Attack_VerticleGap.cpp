#include "Attack_VerticleGap.h"
#include <Windows.h>

Attack_VerticleGap::Attack_VerticleGap(int width, int height, PlayerPosition & player_position, std::vector<std::vector<char>>& matrix, bool **& element_is_occupied, int gap_position_x, int position_y, int gap_width, int screen_duration, int move_delay)
	: AttackBase(width, height, player_position, matrix, element_is_occupied), gap_width_{ gap_width }, screen_duration_{ screen_duration },
	gap_position_x_{ gap_position_x }, position_y_{ position_y }, start_time_finish_attack_(0), move_delay_{ move_delay }, reverse_{ false }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;
	start_time_update_attack_ = GetTickCount();
	start_time_finish_attack_ = GetTickCount();
}

Attack_VerticleGap::~Attack_VerticleGap()
{
	for (int j = 0; j < width_; j++)
	{
		if (j < gap_position_x_ - gap_width_ || j > gap_position_x_ + gap_width_)
		{
			matrix_[position_y_][j] = ' ';
			element_is_occupied_[position_y_][j] = false;
		}
	}
}

void Attack_VerticleGap::move()
{
	if (!has_attack_finished_)
	{
		double current_time_update_attack = GetTickCount() - start_time_update_attack_;
		if (current_time_update_attack > move_delay_)
		{
			if (!reverse_)
			{
				gap_position_x_++;
				if (gap_position_x_ >= width_ - gap_width_)
					reverse_ = true;
			}
			else
			{
				gap_position_x_--;
				if (gap_position_x_ <= gap_width_)
					reverse_ = false;
			}

			for (int j = 0; j < width_; j++)
			{
				if (j < gap_position_x_ - gap_width_ || j > gap_position_x_ + gap_width_)
				{
					matrix_[position_y_][j] = 'X';
					element_is_occupied_[position_y_][j] = true;
				}
				else
				{
					matrix_[position_y_][j] = ' ';
					element_is_occupied_[position_y_][j] = false;
				}
				start_time_update_attack_ = GetTickCount();
			}
		}
		detectCollision();

		double current_time_finish_attack = GetTickCount() - start_time_finish_attack_;
		if (current_time_finish_attack > screen_duration_)
		{
			has_attack_finished_ = true;
			start_time_finish_attack_ = GetTickCount();
		}
	}
}

void Attack_VerticleGap::detectCollision()
{
	if (player_position_.y == position_y_)
	{
		for (int j = 0; j < width_; j++)
		{
			if (j < gap_position_x_ - gap_width_ || j > gap_position_x_ + gap_width_)
			{
				if (player_position_.x == j && element_is_occupied_[position_y_][j])
					has_hit_player_ = true;
			}
		}
	}
}
