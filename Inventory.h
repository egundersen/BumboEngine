#include "MatrixBase.h"
#include "Image.h"
#include "Item.h"

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory : public MatrixBase
{
public:
	Inventory(int width, int height, Matrix &screen_matrix, int &player_health);

	// Setters
	void onOpenInventory(bool in_battle = false);
	void evaluatePlayerInput();
	void addItem(std::string item_name, int modifier);
	void addItem(Item item);
	void reset();

private:
	// Setters
	void useItem();
	void removeItem(int index_of_item);
	void moveCursor(std::string move_cursor_direction);
	void refreshScreen();
	void setInventoryBackgroundText();
	void setItemsListText();
	void setCursorText();
	void setPlayerHealthText(int x_position, int y_position);

	// Output Displays
	void displayScreen();

	Matrix &screen_matrix_;
	std::vector<std::vector<char>> matrix_;
	std::vector<Item> items_list_;
	std::vector<Item> temporary_items_list_;
	int width_, height_, &player_health_, cursor_index_, start_time_move_cursor_;
	bool in_battle_;
};

#endif // !INVENTORY_H
