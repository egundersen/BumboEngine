#include "Attack_SafeBox.h"

Attack_SafeBox::Attack_SafeBox(int width, int height, PlayerPosition & player_position, Matrix & attack_matrix, bool **& element_is_occupied, int center_position_x, int center_position_y, int diameter, int delay, int duration_of_explosion)
	: AttackBase(width, height, player_position, attack_matrix, element_is_occupied), diameter_{ diameter }, delay_{ delay }, duration_of_explosion_{ duration_of_explosion }, center_position_x_{ center_position_x }, center_position_y_{ center_position_y }
{
}

Attack_SafeBox::~Attack_SafeBox()
{
}

void Attack_SafeBox::move()
{
}

void Attack_SafeBox::detectCollision()
{
}
