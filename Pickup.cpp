#include "Pickup.h"

Pickup::Pickup(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID, std::string text, std::vector<std::vector<char>>& world_matrix, std::vector<std::vector<std::pair<int, int>>>& element_has_object, std::vector<std::vector<std::string>>& matrix_display, int screen_width, int screen_height, Item item, Image item_image, Inventory &inventory, int collider_width, int collider_height, char border_character)
	: Popup(center_position_x, center_position_y, popup_width, popup_height, unique_object_ID, text, world_matrix, element_has_object, matrix_display, screen_width, screen_height, collider_width, collider_height, border_character), item_{ item }, item_image_{ item_image }, inventory_{ inventory }
{

}

void Pickup::createSign()
{
	addImageToMatrix(center_position_x_, center_position_y_, item_image_, world_matrix_);
	collider_height_ = item_image_.getHeight();
	collider_width_ = item_image_.getWidth();
	setObjectID();
	setObjectCoordinates();
}

void Pickup::pickupItem()
{
	inventory_.addItem(item_);
}
