#include "PopupWithCollision.h"

PopupWithCollision::PopupWithCollision(int center_position_x, int center_position_y, PopupDefinition popup_sprite, int unique_object_ID, std::vector<std::vector<char>>& world_matrix, std::vector<std::vector<std::pair<int, int>>>& element_has_object, std::vector<std::vector<std::string>>& matrix_display, int screen_width, int screen_height, int collider_width, int collider_height)
	: center_position_x_{ center_position_x }, center_position_y_{ center_position_y }, world_matrix_{ world_matrix }, element_has_object_{ element_has_object }, screen_width_{ screen_width }, screen_height_{ screen_height }, collider_height_{ collider_height }, collider_width_{ collider_width },
	object_type_ID_(0), unique_object_ID_{ unique_object_ID }, Popup(popup_sprite, matrix_display)
{
	createPopupText();
}

PopupWithCollision::PopupWithCollision(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID, std::string text, std::vector<std::vector<char>>& world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>>& matrix_display, int screen_width, int screen_height, char border_character, int collider_width, int collider_height)
	: center_position_x_{ center_position_x }, center_position_y_{ center_position_y }, world_matrix_{ world_matrix }, element_has_object_{ element_has_object }, screen_width_{ screen_width }, screen_height_{ screen_height }, collider_height_{ collider_height }, collider_width_{ collider_width },
	object_type_ID_(0), unique_object_ID_{ unique_object_ID }, Popup(popup_width, popup_height, text, matrix_display, border_character)
{
	createPopupText();
}

// Calls every frame (If coordinates are not provided, will display popup at player's position)
void PopupWithCollision::refreshPopup(int center_position_x, int center_position_y)
{
	displayPopup(center_position_x, center_position_y);
}

// Creates interactive "Sign" in world. Whether it's invisible or not...
void PopupWithCollision::createWorldSprite()
{
	setObjectID();
	updateColliderCoordinates();
}

// Adds colliders to world so they can be seen
void PopupWithCollision::DEBUG_viewCollider()
{
	drawSolidRectangle(center_position_x_ - collider_width_ / 2, center_position_y_ - collider_height_ / 2, collider_width_, collider_height_, 'C', world_matrix_);
}

// Sets the location of the object's colliders
void PopupWithCollision::updateColliderCoordinates()
{
	for (int i = 0; i < collider_height_; ++i)
		for (int j = 0; j < collider_width_; ++j)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].first = object_type_ID_;
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].second = unique_object_ID_;
		}
}
