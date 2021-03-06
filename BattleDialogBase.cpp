#include "BattleDialogBase.h"

BattleDialogBase::BattleDialogBase(int width, int height, Matrix& screen_matrix, std::vector<std::vector<std::tuple<std::string, std::string, bool>>> &dialog_choices, BossFightDefinition boss_fight_definition, BitmapDefinition &bitmap)
	: width_{ width }, height_{ height }, dialog_matrix_(width, height), screen_matrix_{ screen_matrix }, dialog_choices_index_(0), should_exit_dialog_{ false }, start_time_exit_dialog_(0), bitmap_{ bitmap },
	dialog_choices_{ dialog_choices }, start_time_move_cursor_(0), cursor_index_(0), max_choices_(0), boss_{ boss_fight_definition },
	displaying_response_{ false }, enter_key_pressed_{ false }, return_to_menu_{ false }
{
	start_time_move_cursor_ = GetTickCount64();
	setBackgroundText();
}

// Calls when battle dialog is opened
void BattleDialogBase::onOpenDialog()
{
	cursor_index_ = 0;
	start_time_move_cursor_ = GetTickCount64();
	enter_key_pressed_ = false;
	should_exit_dialog_ = false;
	return_to_menu_ = false;
	displaying_response_ = false;
	setDialogOptions();
}

// updates the screen depending the player's inputs
void BattleDialogBase::refreshScreen()
{
	// Delay before closing dialog menu
	if (displaying_response_)
	{
		double current_time_exit_dialog = GetTickCount64() - start_time_exit_dialog_;
		if (current_time_exit_dialog > 5000)
		{
			// check if boss has given up
			if (dialog_choices_index_ == dialog_choices_.size())
			{
				has_boss_given_up_ = true;
			}
			hideFileSprite();
			should_exit_dialog_ = true;
			start_time_exit_dialog_ = GetTickCount64();
		}
	}
	else
	{
		showFileSprite();
		evaluatePlayerInput();
		setCursorText();
		displayScreen();
	}
}

// resets everything related to battle dialog 
void BattleDialogBase::reset()
{
	dialog_choices_index_ = 0;
	clearMatrix(width_, height_, dialog_matrix_);
	setBackgroundText();
}

// accepts the player's inputs
void BattleDialogBase::evaluatePlayerInput()
{
	double current_time_move_cursor = GetTickCount64() - start_time_move_cursor_;

	if (current_time_move_cursor > 100)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			moveCursor("UP");
			setCursorText();
			start_time_move_cursor_ = GetTickCount64();
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			moveCursor("DOWN");
			setCursorText();
			start_time_move_cursor_ = GetTickCount64();
		}
		if (GetKeyState(VK_RETURN) & 0x8000)
		{
			if (current_time_move_cursor > 500)
			{
				if (!enter_key_pressed_)
				{
					confirmSelection();
					enter_key_pressed_ = true;
				}
				start_time_move_cursor_ = GetTickCount64();
			}
		}
		else if (GetKeyState(VK_BACK) & 0x8000)
		{
			hideFileSprite();
			should_exit_dialog_ = true;
			return_to_menu_ = true;
			start_time_move_cursor_ = GetTickCount64();
		}
	}
}

// Changes the dialog to the next dialog
void BattleDialogBase::progressDialog()
{
	dialog_choices_index_++;
}

// Sets static parts of the battle dialog
void BattleDialogBase::setBackgroundText()
{
	for (int i = 1; i < height_ - 1; ++i)
	{
		dialog_matrix_[i][1] = 'X';
		dialog_matrix_[i][2] = 'X';
		dialog_matrix_[i][3] = 'X';
		dialog_matrix_[i][width_ - 2] = 'X';
		dialog_matrix_[i][width_ - 3] = 'X';
		dialog_matrix_[i][width_ - 4] = 'X';
	}

	if (!boss_.use_files)
	{
		Image main_ascii(boss_.ascii);
		Image overlay_ascii(boss_.overlay);
		addImageToMatrix(29, 14, main_ascii, dialog_matrix_);
		addImageToMatrix(boss_.overlay_x - 11, boss_.overlay_y, overlay_ascii, dialog_matrix_);
	}
}

// Updates player options as text
void BattleDialogBase::setDialogOptions()
{
	drawSolidRectangle(17, 29, 57, 5, ' ', dialog_matrix_);
	max_choices_ = -1;

	int dialog_choices_index = 0;
	std::vector<std::vector<std::tuple<std::string, std::string, bool>>>::iterator row;
	std::vector<std::tuple<std::string, std::string, bool>>::iterator col;
	for (row = dialog_choices_.begin(); row != dialog_choices_.end(); row++)
	{
		int offset = 0;
		if (dialog_choices_index_ == dialog_choices_index)
		{
			for (col = row->begin(); col != row->end(); col++)
			{
				addTextToMatrix(17, 29 + offset, 'l', std::get<0>(*col), dialog_matrix_);
				max_choices_++;
				offset++;
			}
			return;
		}
		dialog_choices_index++;
	}
}

// Updates cursor location
void BattleDialogBase::setCursorText()
{
	for (int i = 0; i < 4; ++i)
		dialog_matrix_[29 + i][15] = ' ';
	dialog_matrix_[29 + (cursor_index_)][15] = '>';
}

// Updates character responses as text
void BattleDialogBase::setReponseText(std::string response_text_string)
{
	drawSolidRectangle(51, 7, 20, 9, ' ', dialog_matrix_);
	drawRectangle(50, 6, 21, 10, 'X', dialog_matrix_);

	addTextToMatrix(60, 10, 'm', response_text_string, dialog_matrix_, 17, 7);

	start_time_exit_dialog_ = GetTickCount64();
	displaying_response_ = true;
}

// Moves the player's cursor UP, DOWN, or let's them press ENTER
void BattleDialogBase::moveCursor(std::string move_cursor_direction)
{
	if (move_cursor_direction == "UP")
	{
		if (cursor_index_ == 0)
			cursor_index_ = max_choices_;
		else
			cursor_index_--;
	}
	else if (move_cursor_direction == "DOWN")
	{
		if (cursor_index_ == max_choices_)
			cursor_index_ = 0;
		else
			cursor_index_++;
	}
}

// Calls dialogEvent depending on what the cursor is pointing at
void BattleDialogBase::confirmSelection()
{
	int dialog_choices_index = 0;
	std::vector<std::vector<std::tuple<std::string, std::string, bool>>>::iterator row;
	std::vector<std::tuple<std::string, std::string, bool>>::iterator col;
	for (row = dialog_choices_.begin(); row != dialog_choices_.end(); row++)
	{
		int offset = 0;
		if (dialog_choices_index_ == dialog_choices_index)
		{
			int dialog_index = 0;
			for (col = row->begin(); col != row->end(); col++)
			{
				if (dialog_index == cursor_index_)
				{
					if (std::get<2>(*col) == true) // Should progress dialog?
					{
						showFileSprite();
						setReponseText(std::get<1>(*col));
						progressDialog();
						return; // Prevents loop from running twice
					}
					showFileSprite();
					setReponseText(std::get<1>(*col));
				}
				dialog_index++;
			}
		}
		dialog_choices_index++;
	}
}

// Checks if player has high enough stats for a dialogue option to use
bool BattleDialogBase::checkLevel()
{
	return false;
}

// Decides which file sprite to display
void BattleDialogBase::showFileSprite()
{
	if (boss_.use_files)
	{
		// TODO Animate (Based on Option emotions)
		bitmap_.showBitmap();
		bitmap_.setXOffset(60);
	}
}

// Erases the file sprite
void BattleDialogBase::hideFileSprite()
{
	if (boss_.use_files)
		bitmap_.hideBitmap();
}

// Draws dialog menu to the screen
void BattleDialogBase::displayScreen()
{
	for (int i = 0; i < height_; i++)
	{
		for (int j = 0; j < width_; j++)
		{
			char temp = dialog_matrix_[i][j];
			screen_matrix_[i][j] = temp;
			screen_matrix_[i][j].setColor(dialog_matrix_[i][j].getRGBA());
		}
	}
}
