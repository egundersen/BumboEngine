#include "DialogManager.h"
#include <iostream>

DialogManager::DialogManager(int dialog_width, int dialog_height, int screen_height, int screen_width, Matrix &screen_matrix)
	: screen_matrix_{ screen_matrix }, max_choices_(2), action_{ "" }, should_give_item_{ false }, should_start_event_{ false },
	dialog_height_{ dialog_height }, dialog_width_{ dialog_width }, dialog_matrix_(dialog_width, dialog_height),
	screen_width_{ screen_width }, screen_height_{ screen_height }, cursor_index_(0), should_show_dialog_{ false }, should_enter_battle_{ false }
{
	setBackgroundText();
}

// Refreshes the dialog text
void DialogManager::refreshDialog()
{
	setCursorText();
	setDialogOptions();
	setResponseText();
}

// Calls once when dialog is opened
void DialogManager::onOpenDialog()
{
	moving_node_ = head_node_;
	setMaxChoices();
	refreshDialog();
}

// Draws dialog menu to the screen
void DialogManager::displayDialogMenu()
{
	for (int i = 0; i < dialog_height_; i++)
	{
		for (int j = 0; j < dialog_width_; j++)
		{
			char temp = dialog_matrix_[i][j];
			screen_matrix_[i + 24][j + 5] = temp;
			screen_matrix_[i + 24][j + 5].setColor(dialog_matrix_[i][j].getRGBA());
		}
	}
}

// Sets static parts of dialog menu
void DialogManager::setBackgroundText()
{
	drawRectangle(0, 0, dialog_width_, dialog_height_, 'X', 'I', dialog_matrix_);
	for (int i = 0; i < 7; i++)
	{
		dialog_matrix_[i + 1][56] = 'X';
		dialog_matrix_[i + 1][56].setColor(ColorPalette('I').getRGBA());
	}
	for (int i = 0; i < 5; i++)
	{
		dialog_matrix_[i + 2][30] = '|';
		dialog_matrix_[i + 2][30].setColor(ColorPalette('I').getRGBA());
	}
}

// Updates player options as text
void DialogManager::setDialogOptions()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 25; j++)
			dialog_matrix_[2 + i][4 + j] = ' ';

	if (action_ == "")
	{
		if (moving_node_->choice_1_ != nullptr)
			addTextToMatrix(4, 2, 'l', moving_node_->choice_1_->getPlayerDialog(), 'M', dialog_matrix_);
		if (moving_node_->choice_2_ != nullptr)
			addTextToMatrix(4, 4, 'l', moving_node_->choice_2_->getPlayerDialog(), 'M', dialog_matrix_);
		if (moving_node_->choice_3_ != nullptr)
			addTextToMatrix(4, 6, 'l', moving_node_->choice_3_->getPlayerDialog(), 'M', dialog_matrix_);
		// Replaces empty text block with goodbye text. For it to work, also remove the -1 condition in setDialogText
		//else if(head_node_->choice_1_ == nullptr && head_node_->choice_2_ == nullptr && head_node_->choice_3_ != nullptr)
		//	addTextToMatrix(4, 6, "Goodbye", dialog_matrix_);
	}
	else if (action_ == "FIGHT")
	{
		addTextToMatrix(4, 4, 'l', "COMBAT INITIATED !", 'M', dialog_matrix_);
	}
	else if (action_ == "ITEM")
	{
		addTextToMatrix(4, 4, 'l', "Item added to inventory", 'M', dialog_matrix_);
	}
}

// Updates character responses as text
void DialogManager::setResponseText()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 25; j++)
			dialog_matrix_[2 + i][31 + j] = ' ';

#ifdef _DEBUG
	if (moving_node_->getAction() != "")
	{
		if (moving_node_->choice_1_ == nullptr && moving_node_->getAction() == "ITEM")
			throw " If an item is given through a dialog node, that node must point to atleast one other node. ";
	}
#endif
	addTextToMatrix(32, 2, 'l', moving_node_->getResponse(), 'M', dialog_matrix_, 23, 5);
}

// Updates cursor location
void DialogManager::setCursorText()
{
	clearCursorText();
	if (action_ == "" && max_choices_ != -1)
	{
		dialog_matrix_[2 + (2 * cursor_index_)][2] = '>';
		dialog_matrix_[2 + (2 * cursor_index_)][2].setColor(ColorPalette('A').getRGBA());
	}
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
	if (moving_node_->choice_1_ != nullptr)
		max_choices_++;
	if (moving_node_->choice_2_ != nullptr)
		max_choices_++;
	if (moving_node_->choice_3_ != nullptr)
		max_choices_++;
}

// Calls dialogEvent depending on what the cursor is pointing at
void DialogManager::confirmSelection()
{
	switch (cursor_index_)
	{
	case 0:
		dialogEvent(moving_node_->choice_1_);
		break;
	case 1:
		dialogEvent(moving_node_->choice_2_);
		break;
	case 2:
		dialogEvent(moving_node_->choice_3_);
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
		moving_node_ = dialog_node;
	}
	else if (dialog_node->getAction() == "ITEM")
	{
		action_ = "ITEM";
		moving_node_ = dialog_node;
	}
	else if (dialog_node->getAction() == "EVENT")
	{
		action_ = "EVENT";
		moving_node_ = dialog_node;
	}
	else
	{
		if (dialog_node->getAction() == "SAVE")
			head_node_ = dialog_node;
		action_ = "";
		moving_node_ = dialog_node;
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
		dialogEvent(moving_node_->choice_1_);
		setMaxChoices();
	}
	else if (action_ == "ITEM")
	{
		action_ = "";
		item_ = moving_node_->getItem();
		should_give_item_ = true;
		should_show_dialog_ = false;
		dialogEvent(moving_node_->choice_1_);
		setMaxChoices();
	}
	else if (action_ == "EVENT")
	{
		action_ = "";
		should_show_dialog_ = false;
		should_start_event_ = true;
		dialogEvent(moving_node_->choice_1_);
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
	moving_node_ = dialog_node;
}

// Forces dialog to appear
void DialogManager::showDialog()
{
	onOpenDialog();
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

// Closes dialog if all conditions are met (Usually only called when player hits BACKSPACE key)
void DialogManager::closeDialog()
{
	if (moving_node_->getAction() != "FIGHT" && moving_node_->getAction() != "ITEM")
	{
		should_show_dialog_ = false;
	}
}
