#include "PopupWithCollision.h"
#include "Image.h"
#include "Inventory.h"

#ifndef PICKUP_H
#define PICKUP_H

class Pickup : public PopupWithCollision
{
public:
	Pickup(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID,
		Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		Matrix &screen_matrix, int screen_width, int screen_height, Item item, 
		Inventory &inventory, char border_character = 'X');
	~Pickup();

	// Setters
	void createWorldSprite();
	void pickupItem();
private:
	// Setters
	void setObjectID() { object_type_ID_ = 2; };

	bool has_picked_up_item_;
	Inventory &inventory_;
	Item item_;
};

#endif // !PICKUP_H
