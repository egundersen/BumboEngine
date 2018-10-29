#include "MatrixBase.h"
#include <thread>

#ifndef BATTLE_H
#define BATTLE_H

class EnemyAttack : public MatrixBase
{
public:
	EnemyAttack() {}
	EnemyAttack(int width, int height, int player_health, std::string attack_name, int number_of_minor_attacks);

	// Full Enemy Attacks
	void shootHorizontalAttack(int time_in_seconds_between_attacks);

	// Minor attacks (Called 10 - 15 times by the full attack)
	void shootHorizontalAttack_Minor(int minor_attack_start_time, int speed, int trail_length, int min, int max, int height, int attack_index, std::string minor_attack_name);

	// Setters
	void useAttack();
	void refreshScreen();
	void OnBeginAttack();
	void setPlayerLocation();
	void movePlayerPosition(int x_position, int y_position, bool should_round_position = false);
	void evaluatePlayerInput();
	void hurtPlayer();
	void playPlayerHurtSound();

	// Getters
	int getPlayerHealth() { return player_health_; }

	// Output Displays
	void displayScreen();
	void displayCollision(int x_position, int y_position);
	void DEBUG_displayMatrix(std::vector<std::vector<char>> matrix);
	void DEBUG_displayImage(int center_x, int center_y, std::string image_in_ASCII);
private:
	int width_ = 0;
	int height_ = 0;
	int player_health_;
	int number_of_minor_attacks_;
	int number_of_remaining_attacks;
	bool should_use_attack;
	bool is_attack_pattern_in_progress;
	bool call_once_threads;
	bool *should_use_minor_attack;
	double attack_start_time;
	std::string attack_name_;
	std::vector<std::string> remaining_attacks_;
	std::vector<char> empty_vector_;
	std::vector<std::vector<char>> matrix_;
	std::string **element_is_occupied_;
	PlayerPosition player_position_;
	std::vector<std::thread> minor_attacks;
};

#endif // !BATTLE_H
