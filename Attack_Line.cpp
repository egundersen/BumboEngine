#include "Attack_Line.h"

Attack_Line::Attack_Line(int width, int height, PlayerPosition & player_position, Matrix & attack_matrix, bool **& element_is_occupied, int min_position, int max_position, int position_2D, int trail_length, int speed, char approach_angle, char direction, int slip_2D, char slip_direction, int percentage_solid)
	: AttackBase(width, height, player_position, attack_matrix, element_is_occupied),
	min_position_{ min_position }, max_position_{ max_position }, position_2D_{ position_2D }, trail_length_{ trail_length }, speed_{ speed }, slip_2D_{ slip_2D },
	percentage_solid_{ percentage_solid }, approach_angle_{ approach_angle }, direction_{ direction }, slip_direction_{ slip_direction }
{
}

Attack_Line::~Attack_Line()
{
}

void Attack_Line::move()
{
}

void Attack_Line::detectCollision()
{
}
