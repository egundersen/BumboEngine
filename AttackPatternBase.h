#include "MatrixBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERNBASE_H
#define ATTACKPATTERNBASE_H

class AttackPatternBase : public MatrixBase
{
public:
	explicit AttackPatternBase(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health, int number_of_attacks);
	virtual ~AttackPatternBase();

	// Setters
	virtual void refreshScreen() {};
	virtual void createAttack() {};

	virtual void OnBeginAttack();
	virtual void refreshPlayerLocation();
	virtual void evaluatePlayerInput();
	virtual void hurtPlayer();
	virtual void playPlayerHurtSound();
	virtual void movePlayerToPosition(int x_position, int y_position, bool should_round_position = false);

	// Getters
	virtual int getPlayerHealth() { return player_health_; }
	virtual bool areAttacksOver() { return has_completed_all_attacks; }

	// Output Displays
	virtual void displayScreen();
protected:
	int width_ = 0;
	int height_ = 0;
	int player_health_;
	int attacks_to_create_;
	int created_attacks_;
	double start_time_update_attacks_;
	double start_time_new_attack_;
	bool has_completed_initialization_;
	bool has_completed_all_attacks;
	bool **element_is_occupied_;
	PlayerPosition player_position_;
	std::vector<char> empty_vector_;
	std::vector<std::vector<char>> matrix_;
	std::vector<Attack_HorizontalLine*> attacks_list_;
	std::vector<std::shared_ptr<int>> attack_starting_positions_;
private:
	std::vector<std::vector<std::string>> &matrix_display_;
	double start_time_slow_player_;
	int slow_player_;
};

#endif // !ATTACKPATTERNBASE_H
