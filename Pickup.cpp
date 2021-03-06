#include "Pickup.h"

Pickup::Pickup(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>>& element_has_object, Matrix& screen_matrix, int screen_width, int screen_height, Item item, Inventory &inventory, char border_character)
	: PopupWithCollision(center_position_x, center_position_y, popup_width, popup_height, unique_object_ID, "You found a " + item.getName() + "! Added to inventory", world_matrix, element_has_object, screen_matrix, screen_width, screen_height, border_character), item_{ item }, inventory_{ inventory }, has_picked_up_item_ {false}
{

}

Pickup::~Pickup()
{
	drawSolidRectangle(center_position_x_ - item_.getImage().getWidth() / 2, center_position_y_ - item_.getImage().getHeight() / 2, item_.getImage().getWidth(), item_.getImage().getHeight(), ' ', world_matrix_);
}

// draws the pickup image on the world matrix
void Pickup::createWorldSprite()
{
	addImageToMatrix(center_position_x_, center_position_y_, item_.getImage(), world_matrix_);
	collider_height_ = item_.getImage().getHeight();
	collider_width_ = item_.getImage().getWidth();
	setObjectID();
	updateColliderCoordinates();
}

// Calls when player picks up item
void Pickup::pickupItem()
{
	if (!has_picked_up_item_)
	{
		inventory_.addItem(item_);
		has_picked_up_item_ = true;
	}
}
