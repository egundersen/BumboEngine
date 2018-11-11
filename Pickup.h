#include "Popup.h"
#include "Image.h"
#include "Inventory.h"

#ifndef PICKUP_H
#define PICKUP_H

class Pickup : public Popup
{
public:
	Pickup(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID,
		std::string text, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		std::vector<std::vector<std::string>> &matrix_display, int screen_width, int screen_height, Item item, Image item_image, Inventory &inventory,
		int collider_width = 9, int collider_height = 4, char border_character = 'X');

	// Setters
	void createSign();
	void pickupItem();
private:
	// Setters
	void setObjectID() { object_type_ID_ = 2; };

	Inventory &inventory_;
	Image item_image_;
	Item item_;
};

#endif // !PICKUP_H
