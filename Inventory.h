#include "MatrixBase.h"
#include "Image.h"
#include "Item.h"

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory : public MatrixBase
{
public:
	Inventory(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int &player_health);

	// Setters
	void onOpenInventory();
	void evaluatePlayerInput();
	void addItem(std::string item_name);

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

	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> matrix_;
	std::vector<Item> items_list_;
	int width_, height_, &player_health_, cursor_index_, start_time_move_cursor_;
};

#endif // !INVENTORY_H
