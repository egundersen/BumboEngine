#include "DialogManager.h"
#include <iostream>

DialogManager::DialogManager(int dialog_width, int dialog_height, int screen_height, int screen_width, std::vector<std::vector<std::string>> &matrix_display)
	: has_opened_dialog_{ false }, matrix_display_{ matrix_display }, max_choices_(2), action_{ "" }, should_give_item_{ false },
	dialog_height_{ dialog_height }, dialog_width_{ dialog_width }, dialog_matrix_(dialog_height, std::vector<char>(dialog_width, ' ')),
	screen_width_{ screen_width }, screen_height_{ screen_height }, cursor_index_(0), should_show_dialog_{ false }, should_enter_battle_{ false }
{
}

// Refreshes the dialog text
void DialogManager::refreshDialog()
{
	if (!has_opened_dialog_)
	{
		onOpenDialog();
		has_opened_dialog_ = true;
	}

	setCursorText();
	setDialogOptions();
	setResponseText();
}

// Draws dialog menu to the screen
void DialogManager::displayDialogMenu()
{
	for (int i = 0; i < dialog_height_; i++)
	{
		for (int j = 0; j < dialog_width_; j++)
		{
			matrix_display_[i + 24][j + 5] = std::string(1, dialog_matrix_[i][j]);
		}
	}
}

// Calls once when dialog is opened
void DialogManager::onOpenDialog()
{
	setBackgroundText();
}

// Sets static parts of dialog menu
void DialogManager::setBackgroundText()
{
	drawRectangle(0, 0, dialog_width_, dialog_height_, 'X', dialog_matrix_);
	for (int i = 0; i < 7; i++)
		dialog_matrix_[i + 1][56] = 'X';
	for (int i = 0; i < 5; i++)
		dialog_matrix_[i + 2][30] = '|';
}

// Updates player options as text
void DialogManager::setDialogOptions()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 25; j++)
			dialog_matrix_[2 + i][4 + j] = ' ';

	if (action_ == "")
	{
		if (head_node_->choice_1_ != nullptr)
			addTextToMatrix(4, 2, head_node_->choice_1_->getPlayerDialog(), dialog_matrix_);
		if (head_node_->choice_2_ != nullptr)
			addTextToMatrix(4, 4, head_node_->choice_2_->getPlayerDialog(), dialog_matrix_);
		if (head_node_->choice_3_ != nullptr)
			addTextToMatrix(4, 6, head_node_->choice_3_->getPlayerDialog(), dialog_matrix_);
		// Replaces empty text block with goodbye text. FOr it to work, also remove the -1 condition in setDialogText
		//else if(head_node_->choice_1_ == nullptr && head_node_->choice_2_ == nullptr && head_node_->choice_3_ != nullptr)
		//	addTextToMatrix(4, 6, "Goodbye", dialog_matrix_);
	}
	else if (action_ == "FIGHT")
	{
		addTextToMatrix(4, 4, "COMBAT INITIATED !", dialog_matrix_);
	}
	else if (action_ == "ITEM")
	{
		addTextToMatrix(4, 4, "Item added to inventory", dialog_matrix_);
	}
}

// Updates character responses as text
void DialogManager::setResponseText()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 25; j++)
			dialog_matrix_[2 + i][31 + j] = ' ';

	if (head_node_->getAction() != "")
	{
#ifdef _DEBUG
		if (head_node_->choice_1_ == nullptr && head_node_->getAction() == "ITEM")
			throw std::invalid_argument(" If an item is given through a dialog node, that node must point to atleast one other node. ");
#endif
		if (head_node_->choice_1_ != nullptr)
		{
			//Image response(head_node_->choice_1_->getResponse());
			//addImageToMatrix(43, 4, response, dialog_matrix_);
		}
		Image response(head_node_->getResponse());
		addImageToMatrix(43, 4, response, dialog_matrix_);
	}
	else
	{
		Image response(head_node_->getResponse());
		addImageToMatrix(43, 4, response, dialog_matrix_);
	}
}

// Updates cursor location
void DialogManager::setCursorText()
{
	clearCursorText();
	if (action_ == "" && max_choices_ != -1)
		dialog_matrix_[2 + (2 * cursor_index_)][2] = '>';
}

// Clears the previous cursor(s)
void DialogManager::clearCursorText()
{
	for (int i = 0; i < 3; ++i)
		dialog_matrix_[2 + 2 * i][2] = ' ';
}

// Sets the max amount of choices (Usually 1, 2 or 3)
void DialogManager::setMaxChoices()
{
	max_choices_ = -1;
	if (head_node_->choice_1_ != nullptr)
		max_choices_++;
	if (head_node_->choice_2_ != nullptr)
		max_choices_++;
	if (head_node_->choice_3_ != nullptr)
		max_choices_++;
}

// Calls dialogEvent depending on what the cursor is pointing at
void DialogManager::confirmSelection()
{
	switch (cursor_index_)
	{
	case 0:
		dialogEvent(head_node_->choice_1_);
		break;
	case 1:
		dialogEvent(head_node_->choice_2_);
		break;
	case 2:
		dialogEvent(head_node_->choice_3_);
		break;
	default:
		break;
	}
}

// Starts a battle, uses an item, progresses dialog or closes it
void DialogManager::dialogEvent(DialogNode * dialog_node)
{
	if (dialog_node == nullptr || dialog_node->getAction() == "CLOSE")
		onCloseDialog();
	else if (dialog_node->getAction() == "FIGHT")
	{
		action_ = "FIGHT";
		head_node_ = dialog_node;
	}
	else if (dialog_node->getAction() == "ITEM")
	{
		action_ = "ITEM";
		head_node_ = dialog_node;
	}
	else
	{
		action_ = "";
		head_node_ = dialog_node;
	}
}

// Moves the player's cursor UP, DOWN, or let's them press ENTER
void DialogManager::moveDialogCursor(std::string move_cursor_direction)
{
	if (action_ == "FIGHT") // Disable all input if player should receive ITEM or a FIGHT
	{
		action_ = "";
		should_enter_battle_ = true;
		should_show_dialog_ = false;
		dialogEvent(head_node_->choice_1_);
		setMaxChoices();
	}
	else if (action_ == "ITEM")
	{
		action_ = "";
		item_ = head_node_->getItem();
		should_give_item_ = true;
		should_show_dialog_ = false;
		dialogEvent(head_node_->choice_1_);
		setMaxChoices();
	}
	else
	{
		if (move_cursor_direction == "UP")
		{
			if (cursor_index_ <= 0)
				cursor_index_ = max_choices_;
			else
				cursor_index_--;
		}
		else if (move_cursor_direction == "DOWN")
		{
			if (cursor_index_ >= max_choices_)
				cursor_index_ = 0;
			else
				cursor_index_++;
		}
		else if (move_cursor_direction == "RETURN")
		{
			confirmSelection();
			cursor_index_ = 0;
			setMaxChoices();
		}
	}
	refreshDialog();
}

// Sets the head node to the provided node
void DialogManager::setHeadNode(DialogNode * dialog_node)
{
	head_node_ = dialog_node;
}

// Forces dialog to appear
void DialogManager::showDialog()
{
	refreshDialog();
	should_show_dialog_ = true;
}

// Stops giving the player an item (Useful so they don't get INFINITY amount of an item)
void DialogManager::stopGivingItem()
{
	should_give_item_ = false;
}

// Called when a battle should end, lets dialogue proceed normally
void DialogManager::stopBattle()
{
	should_enter_battle_ = false;
}
