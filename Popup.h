#ifndef POPUP_H
#define POPUP_H

#include "MatrixBase.h"

/* Text and dimensions for a popup */
struct PopupDefinition
{
	PopupDefinition()
		: text{ "" }, border_character{ 'Z' }, width{ 0 }, height{ 0 } { }
	PopupDefinition(std::string ascii_text, char popup_border_character, int popup_width, int popup_height)
		: text{ ascii_text }, border_character{ popup_border_character }, width{ popup_width }, height{ popup_height } { }
	
	std::string text;
	char border_character;
	int width, height;
};

class Popup: public MatrixBase
{
public:
	Popup(PopupDefinition popup_sprite, Matrix &screen_matrix);
	Popup(int popup_width, int popup_height, std::string text, Matrix &screen_matrix, char border_character);

	// Output Displays
	void displayPopup(int popup_position_x, int popup_position_y);
	void createPopupText();

protected:
	int popup_width_, popup_height_;
	char border_character_;
	Matrix &screen_matrix_, popup_matrix_;
	std::string text_;
};

#endif // !POPUP_H
