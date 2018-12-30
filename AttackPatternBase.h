#include "MatrixBase.h"
#include "Attacks.h"

#ifndef ATTACKPATTERNBASE_H
#define ATTACKPATTERNBASE_H

class AttackPatternBase : public MatrixBase
{
public:
	explicit AttackPatternBase(int width, int height, Matrix &screen_matrix, int &player_health, int number_of_attacks);
	virtual ~AttackPatternBase();

	// Setters
	virtual void OnBeginAttack();
	virtual void refreshScreen() { throw "Tried to create attack using superclass alone"; };

	// Getters
	bool areAttacksOver() { return has_completed_all_attacks_; }
protected:
	// Setters
	virtual void createAttack() {};
	void createBorder();
	void refreshPlayerLocation();
	void evaluatePlayerInput();
	void hurtPlayer();
	void playPlayerHurtSound();
	void movePlayerToPosition(int x_position, int y_position, bool should_round_position = false);
	void moveAttack();
	void checkBorderCollision();
	void attacksCheckCollision();

	int width_, height_, &player_health_, attacks_to_create_, created_attacks_;
	double start_time_new_attack_;
	bool has_completed_initialization_, has_completed_all_attacks_, **element_is_occupied_, border_was_destroyed_;
	PlayerPosition player_position_;
	Matrix attack_matrix_;
	std::vector<AttackBase*> attacks_list_;
	std::vector<std::shared_ptr<int>> attack_starting_positions_;

	// Output Displays
	virtual void displayScreen();
private:
	Matrix &screen_matrix_;
	Attack_Border *border_;
	double start_time_slow_player_;
	int slow_player_;
};

#endif // !ATTACKPATTERNBASE_H
