#include "MatrixBase.h"
#include <utility>

#ifndef POPUP_H
#define POPUP_H

class Popup : public MatrixBase
{
public:
	explicit Popup(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID,
		std::string text, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		std::vector<std::vector<std::string>> &matrix_display, int screen_width, int screen_height, char border_character = 'X', int collider_width = 9, 
		int collider_height = 4);
	virtual ~Popup() {}

	// Setters
	virtual void refreshPopup(int center_position_x = 0, int center_position_y = 0);
	virtual void createWorldSprite();
	void DEBUG_viewCollider();

	// Getters
	int getUniqueObjectID() { return unique_object_ID_; }
protected:
	// Setters
	void createPopupText();
	void updateColliderCoordinates();
	virtual void setObjectID() { object_type_ID_ = 1; };

	// Output Displays
	void displayPopup(int popup_position_x, int popup_position_y);

	int center_position_x_, center_position_y_, popup_width_, popup_height_, screen_width_, screen_height_, 
		object_type_ID_, unique_object_ID_, collider_width_, collider_height_;
	char border_character_;
	std::vector<std::vector<std::pair<int, int>>> &element_has_object_;
	std::vector<std::vector<char>> &world_matrix_, popup_matrix_;
	std::vector<std::vector<std::string>> &matrix_display_;
	Image text_;
};

#endif // !POPUP_H
