#ifndef SIGNPOST_H
#define SIGNPOST_H

#include "PopupWithCollision.h"

class Signpost : public PopupWithCollision
{
public:
	using PopupWithCollision::PopupWithCollision;

	// Setters
	void createWorldSprite()
	{
		Image sign("  ______ Z [ .... ]Z [_____ ]Z    ||   Z", "B");
		addImageToMatrix(center_position_x_, center_position_y_, sign, world_matrix_);
		collider_height_ = sign.getHeight();
		collider_width_ = sign.getWidth();
		setObjectID();
		updateColliderCoordinates();
	}

private:
	// Setters
	void setObjectID() { object_type_ID_ = 1; };
};

#endif // !SIGNPOST_H
