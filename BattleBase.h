#include "MatrixBase.h"
#include "Image.h"
#include "RGBA.h"
#include "PlayerDefinition.h"
#include "AttackPatterns.h"
#include "AttackPatternBase.h"
#include "BattleDialogBase.h"
#include "BossFightDefinition.h"
#include <tuple>

#ifndef BATTLEBASE_H
#define BATTLEBASE_H

class BattleBase : public MatrixBase
{
public:
	explicit BattleBase(int width, int height, Matrix &screen_matrix, PlayerDefinition &player, BossFightDefinition boss_fight_definition, BitmapDefinition &image_file_path);
	virtual ~BattleBase() {}

	// Setters
	void onBeginBattle();
	void refreshScreen();
	void setVectorSpace(std::string local_vector_space) { local_vector_space_ = local_vector_space; }
	void setPersistent() { do_not_despawn_ = true; }

	// Getters
	bool isBattleOver() { return is_battle_finished_; }
	bool isDestroyed() { return is_destroyed_; }
	bool shouldRestart() { return should_restart_battle_; }
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
	void showFileSprite(std::string emotion = "");
	void showBasicSprite();
	void hideFileSprite();
	void resetBattleSpace();
	void removeAllUI();

	// Output Displays
	void displayScreen();

	std::vector<std::vector<std::tuple<std::string, std::string, bool>>> dialog_choices_;
	Matrix &screen_matrix_, menu_matrix_;
	std::vector<AttackPatternBase*> attack_patterns_;
	int width_, height_, cursor_index_, start_time_move_cursor_, start_time_battle_end_animation_,
		initial_boss_health_, initial_player_health_, end_animation_index_;
	std::string local_vector_space_;
	BitmapDefinition &bitmap_;
	bool is_battle_finished_, is_destroyed_, should_restart_battle_, do_not_despawn_;
	PlayerDefinition &player_;
	BattleDialogBase dialog_;
	BossFightDefinition boss_;
};

#endif // !BATTLEBASE_H
