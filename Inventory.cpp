#include "Inventory.h"
#include "MatrixBase.h"
#include <windows.h>

Inventory::Inventory(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health)
	: width_{ width }, height_{ height }, matrix_(height, std::vector<char>(width, ' ')), cursor_index_(0), player_health_{ player_health }, matrix_display_{ matrix_display }, start_time_move_cursor_(0)
{
	start_time_move_cursor_ = GetTickCount();
	setInventoryBackgroundText();
}

// Runs when inventory is opened
void Inventory::onOpenInventory(int player_health)
{
	start_time_move_cursor_ = GetTickCount();
	player_health_ = player_health;
	cursor_index_ = 0;
	refreshScreen();
}

// Refreshes screen to show updated items list
void Inventory::refreshScreen()
{
#ifdef _DEBUG
	if (items_list_.size() > 10)
		throw std::invalid_argument("Inventory may not have more than 10 items!");
#endif
	setItemsListText();
	setCursorText();
	displayScreen();
}

// Sets the static parts of the inventory menu
void Inventory::setInventoryBackgroundText()
{
	for (int i = 1; i < height_ - 1; ++i)
	{
		matrix_[i][1] = 'X';
		matrix_[i][2] = 'X';
		matrix_[i][3] = 'X';
		matrix_[i][width_ - 2] = 'X';
		matrix_[i][width_ - 3] = 'X';
		matrix_[i][width_ - 4] = 'X';
	}
	for (int i = 10; i < height_ - 1; ++i)
		matrix_[i][45] = 'X';
	for (int j = 5; j < width_ - 5; ++j)
	{
		matrix_[1][j] = '=';
		matrix_[2][j] = '=';
	}
	Image inventory_letters("Z===[]=== []   [][]      [][]==== []   [] ==[]== [][][] [][][][]    []Z   []    []]  [] []    [] []     []]  []   []   []  [] []  [] []  [] Z   []    [][] []  []  []  []==== [][] []   []   []  [] [][][]  [][]  Z   []    [] [][]   [][]   []     [] [][]   []   []  [] [][]     []   Z===[]=== []  [[]    []    []==== []  [[]   []   [][][] [] []_   []   Z");
	Image instructions("Z=====================================Z============= CONTROLS ==============Z                                     ZNavigate up and down      Arrow KeysZ                                     ZUse Selected Item         ENTERZ                                     ZExit inventory            BACKSPACEZZ");
	Image itemsMenu("Z=========================Z========= ITEMS =========ZZ");
	addImageToMatrix(60, 11, itemsMenu, matrix_);
	addImageToMatrix(24, 14, instructions, matrix_);
	addImageToMatrix(39, 6, inventory_letters, matrix_);
}

// Sets the items list
void Inventory::setItemsListText()
{
	for (int i = 0; i < items_list_.size(); ++i)
	{
		std::string item = "Z" + items_list_.at(i).getName() + "Z";
		Image items(item);
		addImageToMatrix(58, 13 + (2 * i), items, matrix_);
	}
	for (int i = items_list_.size(); i < 10; ++i)
		for (int j = 0; j < 20; ++j)
			matrix_[13 + (2 * i)][52 + j] = ' ';
}

// Sets the cursor
void Inventory::setCursorText()
{
	for (int i = 0; i < 20; ++i)
		matrix_[13 + i][48] = ' ';
	matrix_[13 + (2 * cursor_index_)][48] = '>';
}

// Takes input for inventory menu
void Inventory::evaluatePlayerInput()
{
	double current_time_move_cursor = GetTickCount() - start_time_move_cursor_;

	if (current_time_move_cursor > 100) {
		if (items_list_.size() > 0)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				moveCursor("UP");
				refreshScreen();
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				moveCursor("DOWN");
				refreshScreen();
			}
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				useItem();
				refreshScreen();
			}
		}
		start_time_move_cursor_ = GetTickCount();
	}
}

// Use an item
void Inventory::useItem()
{
	//TODO: Do something for item name: items_list_.at(cursor_index_);

	// delete selected item
	removeItem(cursor_index_);
	if (items_list_.size() <= cursor_index_ && items_list_.size() != 0)
		cursor_index_--;
}

// Add item to inventory
void Inventory::addItem(std::string item_name)
{
	Item item(item_name);
	items_list_.push_back(item);
}

// Remove item from inventory (at index)
void Inventory::removeItem(int index_of_item)
{
	items_list_.erase(items_list_.begin() + index_of_item);
}

// Move the cursor up or down
void Inventory::moveCursor(std::string move_cursor_direction)
{
	if (items_list_.size() == 0)
		return;
	if (move_cursor_direction == "UP")
	{
		if (cursor_index_ == 0)
			cursor_index_ = items_list_.size() - 1;
		else
			cursor_index_--;
	}
	else if (move_cursor_direction == "DOWN")
	{
		if (cursor_index_ == items_list_.size() - 1)
			cursor_index_ = 0;
		else
			cursor_index_++;
	}
}

// displays matrix on screen
void Inventory::displayScreen()
{
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			matrix_display_[i][j] = std::string(1, matrix_[i][j]);
		}
	}
}
