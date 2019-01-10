#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include "DialogNode.h"
#include "MatrixBase.h"

class DialogManager : MatrixBase
{
public:
	DialogManager(int dialog_width, int dialog_height, int screen_height, int screen_width, Matrix &screen_matrix);
	~DialogManager() {}

	// Setters
	void displayDialogMenu();
	virtual void setDialogNodes() {}
	void moveDialogCursor(std::string move_cursor_direction);
	void setHeadNode(DialogNode *dialog_node);
	void enterBattle() { should_enter_battle_ = true; }
	void showDialog();
	void stopGivingItem();
	void stopBattle();
	void closeDialog();

	// Getters
	bool shouldShowDialog() { return should_show_dialog_; }
	bool shouldGiveItem() { return should_give_item_; }
	bool shouldEnterBattle() { return should_enter_battle_; }
	bool shouldStartEvent() { return should_start_event_; }
	Item givenItem() { return item_; }
private:
	// Setters
	void refreshDialog();
	void onOpenDialog();
	void onCloseDialog() { should_show_dialog_ = false; }
	void setBackgroundText();
	void setDialogOptions();
	void setResponseText();
	void setCursorText();
	void clearCursorText();
	void setMaxChoices();
	void confirmSelection();
	void dialogEvent(DialogNode *dialog_node);

	int dialog_width_, dialog_height_, screen_height_, screen_width_, cursor_index_, start_time_move_cursor_, max_choices_;
	bool should_show_dialog_, should_give_item_, should_enter_battle_, should_start_event_;
	Matrix &screen_matrix_, dialog_matrix_;
	DialogNode *head_node_;
	DialogNode *moving_node_;
	Item item_;
	std::string action_;
};

#endif // !DIALOGMANAGER_H
