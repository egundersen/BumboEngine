#include "Popup.h"

Popup::Popup(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID, std::string text, std::vector<std::vector<char>>& world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>>& matrix_display, int screen_width, int screen_height, char border_character, int collider_width, int collider_height)
	: center_position_x_{ center_position_x }, center_position_y_{ center_position_y }, popup_width_{ popup_width }, popup_height_{ popup_height }, world_matrix_{ world_matrix }, element_has_object_{ element_has_object }, matrix_display_{ matrix_display }, screen_width_{ screen_width }, screen_height_{ screen_height }, collider_height_{ collider_height }, collider_width_{ collider_width }, border_character_{ border_character },
	text_{ text }, popup_matrix_(popup_height, std::vector<char>(popup_width, ' ')), object_type_ID_(0), unique_object_ID_{ unique_object_ID }
{
	createPopupText();
}

// Calls every frame
void Popup::refreshPopup()
{
	displayPopup();
}

// Creates interactive "Sign" in world. Whether it's invisible or not...
void Popup::createWorldSprite()
{
	setObjectID();
	updateColliderCoordinates();
}

// Adds colliders to world so they can be seen
void Popup::DEBUG_viewCollider()
{
	drawSolidRectangle(center_position_x_ - collider_width_ / 2, center_position_y_ - collider_height_ / 2, collider_width_, collider_height_, 'C', world_matrix_);
}

// Creates text box used in the popup
void Popup::createPopupText()
{
	drawSolidRectangle(0, 0, popup_width_, popup_height_, ' ', popup_matrix_);
	drawRectangle(0, 0, popup_width_, popup_height_, border_character_, popup_matrix_);
	addImageToMatrix(popup_width_ / 2, popup_height_ / 2, text_, popup_matrix_);
}

// Sets the location of the object's colliders
void Popup::updateColliderCoordinates()
{
	for (int i = 0; i < collider_height_; ++i)
		for (int j = 0; j < collider_width_; ++j)
		{
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].first = object_type_ID_;
			element_has_object_[center_position_y_ - collider_height_ / 2 + i][center_position_x_ - collider_width_ / 2 + j].second = unique_object_ID_;
		}
}

// Displays the popup on the screen
void Popup::displayPopup()
{
	for (int i = 0; i < popup_height_; i++)
		for (int j = 0; j < popup_width_; j++)
			matrix_display_[i + popup_width_ / 2][j + popup_height_ + 1] = std::string(1, popup_matrix_[i][j]);
}
