#include "MatrixBase.h"
#include "BossFightDefinition.h"
#include <tuple>

#ifndef BATTLEDIALOGBASE_H
#define BATTLEDIALOGBASE_H

class BattleDialogBase : public MatrixBase {
public:
	BattleDialogBase(int width, int height, std::vector<std::vector<std::string>> &matrix_display, 
		std::vector<std::vector<std::tuple<std::string, std::string, bool>>> &dialog_choices, 
		BossFightDefinition boss_fight_definition);

	// Setters
	void onOpenDialog();
	void refreshScreen();

	// Getters
	bool shouldExitDialog() { return should_exit_dialog_; }
	bool hasBossGivenUp() { return has_boss_given_up_; }
	std::string response() { return response_; }
private:
	// Setters
	void evaluatePlayerInput();
	void progressDialog();
	void setBackgroundText();
	void setDialogOptions();
	void setCursorText();
	void setReponseText(std::string response_text_string);
	void moveCursor(std::string move_cursor_direction);
	void confirmSelection();
	bool checkLevel();

	// Output Displays
	void displayScreen();

	std::vector<std::vector<std::tuple<std::string, std::string, bool>>> &dialog_choices_;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> matrix_;
	int width_, height_, cursor_index_, start_time_move_cursor_, start_time_exit_dialog_, dialog_choices_index_;
	bool has_boss_given_up_, should_exit_dialog_, displaying_response_, enter_key_pressed_;
	std::string response_;
	BossFightDefinition boss_;
};

#endif // !BATTLEDIALOGBASE_H
