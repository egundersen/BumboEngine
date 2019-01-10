#include "AttackPattern_SnakeandExplode.h"

AttackPattern_SnakeandExplode::AttackPattern_SnakeandExplode(int width, int height, Matrix& screen_matrix, PlayerDefinition &player, int number_of_attacks)
	: AttackPatternBase(width, height, screen_matrix, player, number_of_attacks)
{
	attacks_to_create_ = number_of_attacks + 1;
}

// Calls once when the entire attack starts
void AttackPattern_SnakeandExplode::OnBeginAttack()
{
	setAttackParameters();
	for (int i = 1; i < attacks_to_create_ ; i++)
		createAttack2(generateRandomNumber(attack_diameter_ / 2, width_ - attack_diameter_ / 2), generateRandomNumber(attack_diameter_ / 2, height_ - attack_diameter_ / 2));
	start_time_new_attack_ = GetTickCount64();
	has_completed_initialization_ = true;
}

// Refreshes screen to show player/enemy positions
void AttackPattern_SnakeandExplode::refreshScreen()
{
	if (created_attacks_ == attacks_to_create_ && attacks_list_.size() == 0 && start_time_new_attack_ >= 15000)
		has_completed_all_attacks_ = true;
	else
	{
		double current_time_new_attack_ = GetTickCount64() - start_time_new_attack_;
		if (current_time_new_attack_ >= 1500 && created_attacks_ < attacks_to_create_) // Create new Attacks
		{
			createAttack1(0, generateRandomNumber(0, height_ - 1), 15000, 50);
			start_time_new_attack_ = GetTickCount64();
		}
		attacksCheckCollision();
		moveAttack();

		evaluatePlayerInput();
		refreshPlayerLocation();
		displayScreen();
	}
}

// Add attack to list of attacks
void AttackPattern_SnakeandExplode::createAttack1(int head_position_x, int head_position_y, int duration_of_attack, int speed)
{
	Attack_Snake *attack;
	attack = new Attack_Snake(width_, height_, player_position_, attack_matrix_, element_is_occupied_, head_position_x, head_position_y, duration_of_attack, speed);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
void AttackPattern_SnakeandExplode::createAttack2(int center_position_x, int center_position_y)
{
	Attack_Explode *attack;
	attack = new Attack_Explode(width_, height_, player_position_, attack_matrix_, element_is_occupied_, center_position_x, center_position_y, attack_diameter_, delay_till_explode_, duration_of_explosion_);

	attacks_list_.push_back(attack);
	created_attacks_++;
}
