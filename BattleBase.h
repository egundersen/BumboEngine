#include "MatrixBase.h"
#include "Image.h"
#include "AttackPatterns.h"
#include "AttackPatternBase.h"

#ifndef BATTLEBASE
#define BATTLEBASE

class BattleBase : public MatrixBase
{
public:
	explicit BattleBase(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health, int boss_health, std::string boss_ascii_art, std::string ascii_overlay, int overlay_x, int overlay_y);
	virtual ~BattleBase() {}

	// Setters
	void onBeginBattle(int player_health);
	void refreshScreen();
	void setVectorSpace(std::string local_vector_space) { local_vector_space_ = local_vector_space; }

	// Getters
	int getPlayerHealth() { return player_health_; }
	bool isBattleOver() { return is_battle_over_; }
	std::string getLocalVectorSpace() { return local_vector_space_; }
protected:
	// Setters
	void setBackgroundText();
	void setBossHealthText();
	void setCursorText();
	void evaluatePlayerInput();
	void drawCursor(int offset);
	void moveCursor(std::string move_cursor_direction);
	void damageBoss();
	void bossGivesUp();
	void bossDestroyed();
	void spare();
	void confirmSelection();
	void setBossHealth(int boss_health) { boss_health_ = boss_health; }

	// Output Displays
	void displayScreen();

	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> matrix_;
	std::vector<AttackPatternBase*> attack_patterns_;
	int width_, height_, player_health_, boss_health_, cursor_index_, 
		start_time_move_cursor_, start_time_battle_end_animation_, overlay_x_, overlay_y_;
	std::string ascii_overlay_, boss_ascii_art_, boss_name_, local_vector_space_;
	bool is_battle_over_, allow_spare_;

};

#endif // !BATTLEBASE
