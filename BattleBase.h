#include "MatrixBase.h"
#include "Image.h"
#include "AttackPatterns.h"
#include "AttackPatternBase.h"
#include "BattleDialogBase.h"
#include "BossFightDefinition.h"

#ifndef BATTLEBASE_H
#define BATTLEBASE_H

class BattleBase : public MatrixBase
{
public:
	explicit BattleBase(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int &player_health, BossFightDefinition boss_fight_definition, std::pair<std::string, int> &image_file_path);
	virtual ~BattleBase() {}

	// Setters
	void onBeginBattle();
	void refreshScreen();
	void setVectorSpace(std::string local_vector_space) { local_vector_space_ = local_vector_space; }

	// Getters
	bool isBattleOver() { return is_battle_finished_; }
	bool isDestroyed() { return is_destroyed_; }
	std::string getLocalVectorSpace() { return local_vector_space_; }
protected:
	// Setters
	void setBackgroundText();
	void setBossHealthText();
	void setPlayerHealthText(int x_position, int y_position);
	void setGameOverText();
	void setCursorText();
	void evaluatePlayerInput();
	void drawCursor(int offset);
	void moveCursor(std::string move_cursor_direction);
	void damageBoss();
	void bossOutOfAttacks();
	void bossDestroyed();
	void bossSpared();
	void confirmSelection();
	void setBossHealth(int boss_health) { boss_.health = boss_health; }
	void gameOver();
	void showFileSprite();
	void hideFileSprite();

	// Output Displays
	void displayScreen();

	std::vector<std::vector<std::tuple<std::string, std::string, bool>>> dialog_choices_;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> matrix_;
	std::vector<AttackPatternBase*> attack_patterns_;
	int width_, height_, &player_health_, cursor_index_, start_time_move_cursor_, start_time_battle_end_animation_;
	std::string local_vector_space_;
	std::pair<std::string, int> &image_file_path_;
	bool is_battle_finished_, is_destroyed_;
	BattleDialogBase dialog_;
	BossFightDefinition boss_;
};

#endif // !BATTLEBASE_H
