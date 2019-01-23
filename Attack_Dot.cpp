#include "Attack_Dot.h"

Attack_Dot::Attack_Dot(int width, int height, PlayerPosition & player_position, Matrix & attack_matrix, bool **& element_is_occupied, int position_2D, int speed, char direction, int slip_modifier, char slip_direction)
	: AttackBase(width, height, player_position, attack_matrix, element_is_occupied), slip_{ 0 },
	position_2D_{ position_2D }, speed_{ speed }, slip_modifier_{ slip_modifier },
	direction_{ direction }, slip_direction_{ slip_direction }
{
	ending_position_ = direction_ != 'u' && direction_ != 'l' ? direction_ == 'r' ? width : height + 1 : -2;
	position_ = direction_ != 'd' && direction_ != 'r' ? direction_ == 'l' ? width - 1 : height - 1 : 0;
}

Attack_Dot::~Attack_Dot()
{
	if (direction_ == 'r') {
		attack_matrix_[position_2D_ + slip_][position_ * speed_ - 1] = ' ';
		element_is_occupied_[position_2D_ + slip_][position_ * speed_ - 1] = false;
	}
}

void Attack_Dot::move()
{
	if (position_ * speed_ == ending_position_) { has_attack_finished_ = true; }
	else {
		switch (direction_) {
		case 'r':
			if (slip_direction_ == 'u') {
				if (position_ * speed_ - 1 >= 0 && position_ * speed_ - 1 < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_ - 1] = ' ';
					element_is_occupied_[position_2D_ + slip_][position_ * speed_ - 1] = false;
				}
				slip_ = position_2D_ + slip_ > 0 ? slip_ - slip_modifier_ : height_ - position_2D_ - 1;
				if (position_ * speed_ < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_] = 'O';
					element_is_occupied_[position_2D_ + slip_][position_ * speed_] = true;
				}
			}
			else { // d
				if (position_ * speed_ - 1 >= 0 && position_ * speed_ - 1 < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_ - 1] = ' ';
					element_is_occupied_[position_2D_ + slip_][position_ * speed_ - 1] = false;
				}
				slip_ = position_2D_ + slip_ < height_ - 1 ? slip_ + slip_modifier_ : 0 - position_2D_;
				if (position_ * speed_ < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_] = 'O';
					element_is_occupied_[position_2D_ + slip_][position_ * speed_] = true;
				}
			}
			detectCollision();
			position_++;
			break;
		case 'l':
			if (slip_direction_ == 'u') {
				if (position_ * speed_ + 1 >= 0 && position_ * speed_ + 1 < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_ + 1] = ' ';
					element_is_occupied_[position_2D_ + slip_][position_ * speed_ + 1] = false;
				}
				slip_ = position_2D_ + slip_ > 0 ? slip_ - slip_modifier_ : height_ - position_2D_ - 1;
				if (position_ * speed_ >= 0 && position_ * speed_ < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_] = 'O';
					element_is_occupied_[position_2D_ + slip_][position_* speed_] = true;
				}
			}
			else { // d
				if (position_ * speed_ + 1 >= 0 && position_ * speed_ + 1 < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_ + 1] = ' ';
					element_is_occupied_[position_2D_ + slip_][position_ * speed_ + 1] = false;
				}
				slip_ = position_2D_ + slip_ < height_ - 1 ? slip_ + slip_modifier_ : 0 - position_2D_;
				if (position_ * speed_ >= 0 && position_ * speed_ < width_)
				{
					attack_matrix_[position_2D_ + slip_][position_ * speed_] = 'O';
					element_is_occupied_[position_2D_ + slip_][position_* speed_] = true;
				}
			}
			detectCollision();
			position_--;
			break;
		case 'u':
			if (slip_direction_ == 'r') {
				if (position_ * speed_ + 1 >= 0 && position_ * speed_ + 1 < height_)
				{
					attack_matrix_[position_ * speed_ + 1][position_2D_ + slip_] = ' ';
					element_is_occupied_[position_ * speed_ + 1][position_2D_ + slip_] = false;
				}
				slip_ = position_2D_ + slip_ < width_ - 1 ? slip_ + slip_modifier_ : 0 - position_2D_;
				if (position_ * speed_ >= 0 && position_ * speed_ < height_)
				{
					attack_matrix_[position_ * speed_][position_2D_ + slip_] = 'O';
					element_is_occupied_[position_ * speed_][position_2D_ + slip_] = true;
				}
			}
			else { // l
				if (position_ * speed_ + 1 >= 0 && position_ * speed_ + 1 < height_)
				{
					attack_matrix_[position_ * speed_ + 1][position_2D_ + slip_] = ' ';
					element_is_occupied_[position_ * speed_ + 1][position_2D_ + slip_] = false;
				}
				slip_ = position_2D_ + slip_ > 0 ? slip_ - slip_modifier_ : width_ - position_2D_ - 1;
				if (position_ * speed_ >= 0 && position_ * speed_ < height_)
				{
					attack_matrix_[position_ * speed_][position_2D_ + slip_] = 'O';
					element_is_occupied_[position_ * speed_][position_2D_ + slip_] = true;
				}
			}
			detectCollision();
			position_--;
			break;
		case 'd':
			if (slip_direction_ == 'r') {
				if (position_ * speed_ - 1 >= 0 && position_ * speed_ - 1 < height_)
				{
					attack_matrix_[position_ * speed_ - 1][position_2D_ + slip_] = ' ';
					element_is_occupied_[position_ * speed_ - 1][position_2D_ + slip_] = false;
				}
				slip_ = position_2D_ + slip_ < width_ - 1 ? slip_ + slip_modifier_ : 0 - position_2D_;
				if (position_ * speed_ < height_)
				{
					attack_matrix_[position_ * speed_][position_2D_ + slip_] = 'O';
					element_is_occupied_[position_ * speed_][position_2D_ + slip_] = true;
				}
			}
			else { // l
				if (position_ * speed_ - 1 >= 0 && position_ * speed_ - 1 < height_)
				{
					attack_matrix_[position_ * speed_ - 1][position_2D_ + slip_] = ' ';
					element_is_occupied_[position_ * speed_ - 1][position_2D_ + slip_] = false;
				}
				slip_ = position_2D_ + slip_ > 0 ? slip_ - slip_modifier_ : width_ - position_2D_ - 1;
				if (position_ * speed_ < height_)
				{
					attack_matrix_[position_ * speed_][position_2D_ + slip_] = 'O';
					element_is_occupied_[position_ * speed_][position_2D_ + slip_] = true;
				}
			}
			detectCollision();
			position_++;
			break;
		}
	}
}

void Attack_Dot::detectCollision()
{
	if (attack_matrix_[player_position_.y][player_position_.x] == 'O') {
		has_hit_player_ = true;
		attack_matrix_[player_position_.y][player_position_.x] = ' ';
		element_is_occupied_[player_position_.y][player_position_.x] = false;
	}
}
