#include "MatrixBase.h"
#include <tuple>

#ifndef DIALOGBASE_H
#define DIALOGBASE_H

class DialogBase : public MatrixBase {
public:
	DialogBase(int width, int height, std::vector<std::vector<std::string>> &matrix_display, std::vector<std::vector<std::tuple<std::string, std::string, bool>>> &dialog_choices,
		std::string boss_ascii_art, std::string ascii_overlay, int overlay_x, int overlay_y);
	//DialogBase(int width, int height, std::vector<std::vector<std::string>> &matrix_display);

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
	void setReponseText();
	void moveCursor(std::string move_cursor_direction);
	void confirmSelection();
	bool checkLevel();

	// Output Displays
	void displayScreen();

	std::vector<std::vector<std::tuple<std::string, std::string, bool>>> &dialog_choices_;
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> matrix_;
	int width_, height_, player_health_, cursor_index_, start_time_move_cursor_, dialog_choices_index_, overlay_x_, overlay_y_;
	bool has_boss_given_up_, should_exit_dialog_;
	std::string response_, ascii_overlay_, boss_ascii_art_;
};

#endif // !DIALOGBASE_H
