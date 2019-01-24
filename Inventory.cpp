#include "Inventory.h"

Inventory::Inventory(int width, int height, Matrix &screen_matrix, PlayerDefinition &player)
	: width_{ width }, height_{ height }, inventory_matrix_(width, height), cursor_index_(0), player_{ player }, screen_matrix_{ screen_matrix }, start_time_move_cursor_(0)
{
	start_time_move_cursor_ = GetTickCount64();
	setInventoryBackgroundText();
}

// Runs when inventory is opened
void Inventory::onOpenInventory()
{
	start_time_move_cursor_ = GetTickCount64();
	cursor_index_ = 0;
	refreshScreen();
}

// Refreshes screen to show updated items list
void Inventory::refreshScreen()
{
#ifdef _DEBUG
	if (items_list_.size() > 10)
		throw "Inventory may not have more than 10 items!";
#endif
	setItemsListText();
	setItemDescriptionText();
	setPlayerHealthText(6, 30);
	setCursorText();
	displayScreen();
}

// Sets the static parts of the inventory menu
void Inventory::setInventoryBackgroundText()
{
	drawSolidRectangle(1, 1, 3, height_ - 2, 'X', 'I', inventory_matrix_);
	drawSolidRectangle(width_ - 4, 1, 3, height_ - 2, 'X', 'I', inventory_matrix_);
	drawSolidRectangle(45, 10, 1, height_ - 11, 'X', 'I', inventory_matrix_);
	drawSolidRectangle(5, 1, width_ - 10, 2, '=', 'I', inventory_matrix_);
	drawRectangle(6, 19, 37, 10, 'X', 'I', inventory_matrix_);
	
	Image inventory_letters(
		"===[]=== []   [][]      [][]==== []   [] ==[]==  [[]]  [][]] []    []Z   []    []]  [] []    [] []     []]  []   []   []  [] []  [] []  [] Z   []    [][] []  []  []  []==== [][] []   []   []  [] [][][]  [][]  Z   []    [] [][]   [][]   []     [] [][]   []   []  [] [][]     []   Z===[]=== []  [[]    []    []==== []  [[]   []    [[]]  [] []_   []   Z",
		"PPPPPPPM PM   PPPM      PPPPPPPM PM   PM PPPPPM PPPPPM PPPPPMPM    PMZ   PM    PPM  PM PM    PM PM     PPM  PM   PM   PM  PM PM  PM PM  PM Z   PM    PPPM PM  PM  PM  PMMMMM PPPM PM   PM   PM  PM PPPPPM  PMPM  Z   PM    PM PMPM   PMPM   PM     PM PMPM   PM   PM  PM PMPPM    PM   ZPPPPPPPM PM  PPM    PM    PPPPPM PM  PPM   PM   PPPPPM PM PPM   PM   Z"
	);
	Image instructions(
		"=====================================Z============= CONTROLS ==============Z                                     ZNavigate up and down      Arrow Keys Z                                     ZUse Selected Item         ENTER      Z                                     ZExit Inventory            BACKSPACE  Z", 
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPZPPPPPPPPPPPPP MMMMMMMM PPPPPPPPPPPPPPZ                                     ZMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMZ                                     ZMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMZ                                     ZMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMZ"
	);
	Image itemsMenu(
		"=========================Z========= ITEMS =========Z", 
		"PPPPPPPPPPPPPPPPPPPPPPPPPZPPPPPPPPP MMMMM PPPPPPPPPZ"
	);
	addImageToMatrix(60, 11, itemsMenu, inventory_matrix_);
	addImageToMatrix(24, 14, instructions, inventory_matrix_);
	addImageToMatrix(39, 6, inventory_letters, inventory_matrix_);
}

// Sets the items list
void Inventory::setItemsListText()
{
	for (int i = 0; i < items_list_.size(); ++i)
		for (int j = 0; j < 20; ++j)
			inventory_matrix_[13 + (2 * i)][50 + j] = ' ';
	for (int i = 0; i < items_list_.size(); ++i)
		addTextToMatrix(50, 13 + (2 * i), 'l', items_list_.at(i).getName(), 'M', inventory_matrix_);
	for (int i = items_list_.size(); i < 10; ++i)
		for (int j = 0; j < 20; ++j)
			inventory_matrix_[13 + (2 * i)][50 + j] = ' ';
}

// Sets text for the Item description
void Inventory::setItemDescriptionText()
{
	std::string description = items_list_.size() == 0 ? "" : items_list_.at(cursor_index_).getDescription();
	drawSolidRectangle(8, 22, 33, 6, ' ', inventory_matrix_);
	addTextToMatrix(8, 22, 'l', description, 'A', inventory_matrix_, 33, 6);
}

// Sets the cursor
void Inventory::setCursorText()
{
	for (int i = 0; i < 20; ++i)
		inventory_matrix_[13 + i][48] = ' ';
	inventory_matrix_[13 + (2 * cursor_index_)][48] = '>';
	inventory_matrix_[13 + (2 * cursor_index_)][48].setColor(ColorPalette('A').getRGBA());
}

// Sets the player health text
void Inventory::setPlayerHealthText(int x_position, int y_position)
{

	addTextToMatrix(x_position, y_position, 'l', player_.getPlayerName() + "'s Lives:", 'M', inventory_matrix_, 1);
	inventory_matrix_[y_position + 2][x_position + 6] = player_.getHealthText();
	inventory_matrix_[y_position + 2][x_position + 6].setColor(ColorPalette('A').getRGBA());
}

// Takes input for inventory menu
void Inventory::evaluatePlayerInput()
{
	double current_time_move_cursor = GetTickCount64() - start_time_move_cursor_;

	if (current_time_move_cursor > 100) {
		if (items_list_.size() > 0)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				moveCursor("UP");
				refreshScreen();
				start_time_move_cursor_ = GetTickCount64();
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				moveCursor("DOWN");
				refreshScreen();
				start_time_move_cursor_ = GetTickCount64();
			}
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				if (current_time_move_cursor > 500)
				{
					useItem();
					refreshScreen();
					start_time_move_cursor_ = GetTickCount64();
				}
			}
		}
	}
}

// Use an item
void Inventory::useItem()
{
	if (items_list_.at(cursor_index_).getType() == "HEAL")
		player_.addHealth(items_list_.at(cursor_index_).getModifier());
	else if (items_list_.at(cursor_index_).getType() == "SHIELD")
		player_.enableShield();
	else if (items_list_.at(cursor_index_).getType() == "ATTACKUP")
		player_.increaseDamage(items_list_.at(cursor_index_).getModifier());

	// delete selected item
	removeItem(cursor_index_);
	if (items_list_.size() <= cursor_index_ && items_list_.size() != 0)
		cursor_index_--;
}

// Add item to inventory (from a string)
void Inventory::addItem(std::string item_name, int modifier, std::string item_description)
{
	Item item(item_name, modifier, item_description);
	items_list_.push_back(item);
}

// Add item to inventory
void Inventory::addItem(Item item)
{
	items_list_.push_back(item);
}

// Resets the inventory to the state it was in at the beginning of battle
void Inventory::reset()
{
	// Erase Inventory
	items_list_.clear();
	
	// Add all items (saved at the beginning of battle in temporary_inventory) to the inventory
	for (std::vector< Item >::iterator it = temporary_items_list_.begin(); it != temporary_items_list_.end(); ++it)
	{
		items_list_.push_back(*it);
	}
}

// Copies items to temporary inventory
void Inventory::backup()
{
	// Erase temporary inventory
	temporary_items_list_.clear();

	// Add all items to temporary inventory
	for (std::vector< Item >::iterator it = items_list_.begin(); it != items_list_.end(); ++it)
	{
		temporary_items_list_.push_back(*it);
	}
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
			char temp = inventory_matrix_[i][j];
			screen_matrix_[i][j] = temp;
			screen_matrix_[i][j].setColor(inventory_matrix_[i][j].getRGBA());
		}
	}
}
