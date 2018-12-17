#include "Popup.h"

Popup::Popup(PopupDefinition popup_sprite, Matrix& screen_matrix)
	: text_{ popup_sprite.text }, popup_width_{ popup_sprite.width }, popup_height_{ popup_sprite.height }, screen_matrix_{ screen_matrix }, border_character_{ popup_sprite.border_character },
	popup_matrix_(popup_sprite.width, popup_sprite.height)
{
}

Popup::Popup(int popup_width, int popup_height, std::string text, Matrix& screen_matrix, char border_character)
	: text_{ text }, popup_width_{ popup_width }, popup_height_{ popup_height }, screen_matrix_{ screen_matrix }, border_character_{ border_character },
	popup_matrix_(popup_width, popup_height)
{
}

// Displays the popup on the screen
void Popup::displayPopup(int popup_position_x, int popup_position_y)
{
	for (int i = 0; i < popup_height_; i++)
		for (int j = 0; j < popup_width_; j++)
		{
			char temp = popup_matrix_[i][j];
			screen_matrix_[i + popup_height_ / 2 + popup_position_y][j + popup_width_ + 1 + popup_position_x] = temp;
		}
}

// Creates text box used in the popup
void Popup::createPopupText()
{
	drawSolidRectangle(0, 0, popup_width_, popup_height_, ' ', popup_matrix_);
	drawRectangle(0, 0, popup_width_, popup_height_, border_character_, popup_matrix_);
	addTextToMatrix(popup_width_ / 2, popup_height_ / 2, 'm', text_, popup_matrix_, popup_width_ - 3, popup_height_ - 2);
}
