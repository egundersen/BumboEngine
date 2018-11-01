#include "MatrixBase.h"
#include "Image.h"
#include "Item.h"

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory : public MatrixBase
{
public:
	Inventory(int width, int height, int player_health, std::vector<std::vector<std::string>> &matrix_display);

	// Setters
	void onOpenInventory();
	void refreshScreen();
	void setInventoryBackgroundText();
	void setItemsListText();
	void setCursorText();
	void evaluatePlayerInput();
	void useItem();
	void addItem(std::string item_name);
	void removeItem(int index_of_item);
	void moveCursor(std::string move_cursor_direction);

	// Getters
	int getPlayerHealth() { return player_health_; }

	// Output Displays
	void displayScreen();
private:
	std::vector<std::vector<std::string>> &matrix_display_;
	std::vector<std::vector<char>> matrix_;
	std::vector<char> empty_vector_;
	std::vector<Item> items_list_;
	int cursor_index_;
	int width_ = 0;
	int height_ = 0;
	int player_health_;
	int start_time_move_cursor_ = 0;
};

#endif // !INVENTORY_H
