#include "Attack_Clock.h"

Attack_Clock::Attack_Clock(int width, int height, PlayerPosition & player_position, Matrix & attack_matrix, bool **& element_is_occupied, int center_position_x, int center_position_y, int diameter, int angle)
	: AttackBase(width, height, player_position, attack_matrix, element_is_occupied), diameter_{ diameter }, angle_{ angle }, center_position_x_{ center_position_x }, center_position_y_{ center_position_y }
{
}

Attack_Clock::~Attack_Clock()
{
}

void Attack_Clock::move()
{
}

void Attack_Clock::detectCollision()
{
}
