#ifndef INVENTORY_H
#define INVENTORY_H

#include "MatrixBase.h"
#include "PlayerDefinition.h"
#include "Item.h"

class Inventory : public MatrixBase
{
public:
	Inventory(int width, int height, Matrix &screen_matrix, PlayerDefinition &player);

	// Setters
	void onOpenInventory();
	void evaluatePlayerInput();
	void addItem(std::string item_name, int modifier, std::string item_description);
	void addItem(Item item);
	void reset();
	void backup();

private:
	// Setters
	void useItem();
	void removeItem(int index_of_item);
	void moveCursor(std::string move_cursor_direction);
	void refreshScreen();
	void setInventoryBackgroundText();
	void setItemsListText();
	void setItemDescriptionText();
	void setCursorText();
	void setPlayerHealthText(int x_position, int y_position);

	// Output Displays
	void displayScreen();

	Matrix &screen_matrix_, inventory_matrix_;
	std::vector<Item> items_list_;
	std::vector<Item> temporary_items_list_;
	PlayerDefinition &player_;
	int width_, height_, cursor_index_, start_time_move_cursor_;
};

#endif // !INVENTORY_H
