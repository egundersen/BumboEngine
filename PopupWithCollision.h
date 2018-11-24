#include "MatrixBase.h"
#include "Popup.h"
#include <utility>

#ifndef POPUPWITHCOLLISION_H
#define POPUPWITHCOLLISION_H

// Creates popup with world collider to trigger popup
class PopupWithCollision : public Popup
{
public:
	explicit PopupWithCollision(int center_position_x, int center_position_y, PopupDefinition popup_sprite, int unique_object_ID,
		std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		std::vector<std::vector<std::string>> &matrix_display, int screen_width, int screen_height, int collider_width = 9, int collider_height = 4);
	explicit PopupWithCollision(int center_position_x, int center_position_y, int popup_width, int popup_height, int unique_object_ID,
		std::string text, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,
		std::vector<std::vector<std::string>> &matrix_display, int screen_width, int screen_height, char border_character = 'X', int collider_width = 9, 
		int collider_height = 4);
	virtual ~PopupWithCollision() {}

	// Setters
	virtual void refreshPopup(int center_position_x = 0, int center_position_y = 0);
	virtual void createWorldSprite();
	void DEBUG_viewCollider();

	// Getters
	int getUniqueObjectID() { return unique_object_ID_; }
protected:
	// Setters
	void updateColliderCoordinates();
	virtual void setObjectID() { object_type_ID_ = 1; };

	int center_position_x_, center_position_y_, screen_width_, screen_height_, 
		object_type_ID_, unique_object_ID_, collider_width_, collider_height_;
	std::vector<std::vector<std::pair<int, int>>> &element_has_object_;
	std::vector<std::vector<char>> &world_matrix_;
};

#endif // !POPUPWITHCOLLISION_H
