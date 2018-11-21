#include "MatrixBase.h"

#ifndef POPUP_H
#define POPUP_H

class Popup: public MatrixBase
{
public:
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
