#include "Popup.h"

#ifndef SIGNPOST_H
#define SIGNPOST_H

class Signpost : public Popup
{
public:
	using Popup::Popup;

	// Setters
	void createSign()
	{
		Image sign("  ______ Z [ .... ]Z [_____ ]Z    ||   Z");
		addImageToMatrix(center_position_x_, center_position_y_, sign, world_matrix_);
		collider_height_ = sign.getHeight();
		collider_width_ = sign.getWidth();
		setObjectID();
		setObjectCoordinates();
	}

private:
	// Setters
	void setObjectID() { object_type_ID_ = 1; };
};

#endif // !SIGNPOST_H
