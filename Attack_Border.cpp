#include "Attack_Border.h"

Attack_Border::Attack_Border(int width, int height, PlayerPosition & player_position, Matrix& attack_matrix, bool **& element_is_occupied)
	: AttackBase(width, height, player_position, attack_matrix, element_is_occupied), has_initialized_{ false }
{
	has_hit_player_ = false;
	has_attack_finished_ = false;
}

Attack_Border::~Attack_Border()
{
	for (int i = 0; i < height_; i++)
		for (int j = 0; j < 3; j++)
			if (element_is_occupied_[i][j] == true && attack_matrix_[i][j] != '.')
				element_is_occupied_[i][j] = false;
	for (int j = 0; j < width_; j++)
		for (int i = 0; i < 3; i++)
			if (element_is_occupied_[i][j] == true && attack_matrix_[i][j] != '.')
				element_is_occupied_[i][j] = false;
	for (int i = 0; i < height_; i++)
		for (int j = width_ - 3; j < width_; j++)
			if (element_is_occupied_[i][j] == true && attack_matrix_[i][j] != '.')
				element_is_occupied_[i][j] = false;
	for (int j = 0; j < width_; j++)
		for (int i = height_ - 3; i < height_; i++)
			if (element_is_occupied_[i][j] == true && attack_matrix_[i][j] != '.')
				element_is_occupied_[i][j] = false;
}

// Runs when the border attack first starts
void Attack_Border::onBeginAttack()
{
	if (!has_initialized_)
	{
		drawRectangle(0, 0, width_, height_, 'O', attack_matrix_, element_is_occupied_);
		drawRectangle(1, 1, width_ - 2, height_ - 2, 'O', attack_matrix_, element_is_occupied_);
		drawRectangle(2, 2, width_ - 4, height_ - 4, 'O', attack_matrix_, element_is_occupied_);
		has_initialized_ = true;
	}
}

// Checks if player hits the border
void Attack_Border::detectCollision()
{
	for (int i = 0; i < height_; i++)
		for (int j = 0; j < 3; j++)
			if (element_is_occupied_[i][j] == true)
				if (player_position_.y == i && player_position_.x == j)
					has_hit_player_ = true;
	for (int j = 0; j < width_; j++)
		for (int i = 0; i < 3; i++)
			if (element_is_occupied_[i][j] == true)
				if (player_position_.y == i && player_position_.x == j)
					has_hit_player_ = true;
	for (int i = 0; i < height_; i++)
		for (int j = width_ - 3; j < width_; j++)
			if (element_is_occupied_[i][j] == true)
				if (player_position_.y == i && player_position_.x == j)
					has_hit_player_ = true;
	for (int j = 0; j < width_; j++)
		for (int i = height_ - 3; i < height_; i++)
			if (element_is_occupied_[i][j] == true)
				if (player_position_.y == i && player_position_.x == j)
					has_hit_player_ = true;
}
