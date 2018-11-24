#include "Popup.h"

Popup::Popup(PopupDefinition popup_sprite, std::vector<std::vector<std::string>>& matrix_display)
	: text_{ popup_sprite.text }, popup_width_{ popup_sprite.width }, popup_height_{ popup_sprite.height }, matrix_display_{ matrix_display }, border_character_{ popup_sprite.border_character },
	popup_matrix_(popup_sprite.height, std::vector<char>(popup_sprite.width, ' '))
{
}

Popup::Popup(int popup_width, int popup_height, std::string text, std::vector<std::vector<std::string>>& matrix_display, char border_character)
	: text_{ text }, popup_width_{ popup_width }, popup_height_{ popup_height }, matrix_display_{ matrix_display }, border_character_{ border_character },
	popup_matrix_(popup_height, std::vector<char>(popup_width, ' '))
{
}

// Displays the popup on the screen
void Popup::displayPopup(int popup_position_x, int popup_position_y)
{
	for (int i = 0; i < popup_height_; i++)
		for (int j = 0; j < popup_width_; j++)
			matrix_display_[i + popup_height_ / 2 + popup_position_y][j + popup_width_ + 1 + popup_position_x] = std::string(1, popup_matrix_[i][j]);
}

// Creates text box used in the popup
void Popup::createPopupText()
{
	drawSolidRectangle(0, 0, popup_width_, popup_height_, ' ', popup_matrix_);
	drawRectangle(0, 0, popup_width_, popup_height_, border_character_, popup_matrix_);
	addImageToMatrix(popup_width_ / 2, popup_height_ / 2, text_, popup_matrix_);
}
