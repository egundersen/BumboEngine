#include "Attack_SafeBox.h"

Attack_SafeBox::Attack_SafeBox(int width, int height, PlayerPosition & player_position, Matrix & attack_matrix, bool **& element_is_occupied, int center_position_x, int center_position_y, int diameter, int delay, int duration_of_explosion)
	: AttackBase(width, height, player_position, attack_matrix, element_is_occupied), diameter_{ diameter }, delay_{ delay }, duration_of_explosion_{ duration_of_explosion }, center_position_x_{ center_position_x }, center_position_y_{ center_position_y },
	complete_1_{ false }, complete_2_{ false }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;
	start_time_update_attack_ = GetTickCount64();
}

Attack_SafeBox::~Attack_SafeBox()
{
	for (int i = 0; i < height_; i++)
		for (int j = 0; j < width_; j++)
			element_is_occupied_[i][j] = false;
}

void Attack_SafeBox::move()
{
	if (!has_attack_finished_)
	{
		double current_time_update_attack = GetTickCount64() - start_time_update_attack_;
		if (current_time_update_attack < delay_)
		{
			if (!complete_1_) {
				screenWarning();
				safeZone();
				complete_1_ = true;
			}
			erasePlayerPosition();
		}
		else if (current_time_update_attack >= delay_ && current_time_update_attack < delay_ + duration_of_explosion_)
		{
			if (!complete_2_) {
				screenKill();
				safeZone();
				complete_2_ = true;
			}
			detectCollision();
		}
		else if (current_time_update_attack > delay_ + duration_of_explosion_)
		{
			drawSolidRectangle(0, 0, width_ - 1, height_ - 1, ' ', attack_matrix_);
			for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
				for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
					element_is_occupied_[center_position_y_ + i][center_position_x_ + j] = false;
			has_attack_finished_ = true;
			start_time_update_attack_ = GetTickCount64();
		}
	}
}

void Attack_SafeBox::detectCollision()
{
	if(element_is_occupied_[player_position_.y][player_position_.x])
		has_hit_player_ = true;
}

void Attack_SafeBox::screenWarning()
{
	for (int i = 0; i < height_; i++)
		for (int j = 0; j < width_; j++)
			attack_matrix_[i][j] = '.';
	for (int i = 0; i < height_; i++)
		for (int j = 0; j < width_; j++)
			element_is_occupied_[i][j] = true;
}

void Attack_SafeBox::screenKill()
{
	for (int i = 0; i < height_; i++)
		for (int j = 0; j < width_; j++)
			attack_matrix_[i][j] = 'X';
	for (int i = 0; i < height_; i++)
		for (int j = 0; j < width_; j++)
			element_is_occupied_[i][j] = true;
}

void Attack_SafeBox::safeZone()
{
	for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
		for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
			attack_matrix_[center_position_y_ + i][center_position_x_ + j] = ' ';
	for (int i = -(diameter_ / 2); i < (diameter_ / 2); i++)
		for (int j = -(diameter_ / 2); j < (diameter_ / 2); j++)
			element_is_occupied_[center_position_y_ + i][center_position_x_ + j] = false;
}

void Attack_SafeBox::erasePlayerPosition()
{
	attack_matrix_[player_position_.y][player_position_.x] = '.';
}
