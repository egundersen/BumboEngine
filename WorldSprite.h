#include "Image.h"

#ifndef WORLDSPRITE_H
#define WORLDSPRITE_H

// Stores the images for the world sprite of an NPC or player
struct WorldSprite
{
	WorldSprite(std::string up_1_string, std::string down_1_string, std::string right_1_string, std::string left_1_string,
		std::string up_2_string, std::string down_2_string, std::string right_2_string, std::string left_2_string, 
		std::string up_s_string, std::string down_s_string, std::string right_s_string, std::string left_s_string) 
	{ 
		up_1 = new Image(up_1_string);
		down_1 = new Image(down_1_string);
		right_1 = new Image(right_1_string);
		left_1 = new Image(left_1_string);
		up_2 = new Image(up_2_string);
		down_2 = new Image(down_2_string);
		right_2 = new Image(right_2_string);
		left_2 = new Image(left_2_string);

		// Not moving
		up_s = new Image(up_s_string);
		down_s = new Image(down_s_string);
		right_s = new Image(right_s_string);
		left_s = new Image(left_s_string);
	}

	// Moving
	Image *up_1;
	Image *down_1;
	Image *right_1;
	Image *left_1;
	Image *up_2;
	Image *down_2;
	Image *right_2;
	Image *left_2;

	// Not moving
	Image *up_s;
	Image *down_s;
	Image *right_s;
	Image *left_s;
};

#endif // WORLDSPRITE_H