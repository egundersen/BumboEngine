#include "AttackBase.h"

AttackBase::AttackBase(int width, int height, PlayerPosition & player_position, Matrix &attack_matrix, bool **& element_is_occupied)
	: width_{ width }, height_{ height }, player_position_{ player_position }, attack_matrix_{ attack_matrix }, element_is_occupied_{ element_is_occupied },
	has_hit_player_{ false }, has_attack_finished_{ false }
{
	
}
