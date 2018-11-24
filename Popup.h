#include "MatrixBase.h"

#ifndef POPUP_H
#define POPUP_H

/* Text and dimensions for a popup */
struct PopupDefinition
{
	PopupDefinition(std::string ascii_text, char popup_border_character, int popup_width, int popup_height)
		: text{ ascii_text }, border_character{ popup_border_character }, width{ popup_width }, height{ popup_height } { }
	
	std::string text;
	char border_character;
	int width, height;
};

class Popup: public MatrixBase
{
public:
	Popup(PopupDefinition popup_sprite, std::vector<std::vector<std::string>> &matrix_display);
	Popup(int popup_width, int popup_height, std::string text, std::vector<std::vector<std::string>> &matrix_display, char border_character);

	// Output Displays
	void displayPopup(int popup_position_x, int popup_position_y);
	void createPopupText();

protected:
	int popup_width_, popup_height_;
	char border_character_;
	std::vector<std::vector<char>> popup_matrix_;
	std::vector<std::vector<std::string>> &matrix_display_;
	Image text_;
};

#endif // !POPUP_H
