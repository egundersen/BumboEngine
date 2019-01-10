#ifndef WORLDSPRITE_H
#define WORLDSPRITE_H

#include "Image.h"

// Stores the images for the world sprite of an NPC or player
struct WorldSpriteContainer
{
	WorldSpriteContainer(
		std::string up_1_ASCII, std::string down_1_ASCII, std::string right_1_ASCII, std::string left_1_ASCII,
		std::string up_2_ASCII, std::string down_2_ASCII, std::string right_2_ASCII, std::string left_2_ASCII, 
		std::string up_s_ASCII, std::string down_s_ASCII, std::string right_s_ASCII, std::string left_s_ASCII,
	
		std::string up_1_colors, std::string down_1_colors, std::string right_1_colors, std::string left_1_colors,
		std::string up_2_colors, std::string down_2_colors, std::string right_2_colors, std::string left_2_colors,
		std::string up_s_colors, std::string down_s_colors, std::string right_s_colors, std::string left_s_colors)
	{ 
		up_1 = new Image(up_1_ASCII, up_1_colors);
		down_1 = new Image(down_1_ASCII, down_1_colors);
		right_1 = new Image(right_1_ASCII, right_1_colors);
		left_1 = new Image(left_1_ASCII, left_1_colors);
		up_2 = new Image(up_2_ASCII, up_2_colors);
		down_2 = new Image(down_2_ASCII, down_2_colors);
		right_2 = new Image(right_2_ASCII, right_2_colors);
		left_2 = new Image(left_2_ASCII, left_2_colors);

		// Not moving
		up_s = new Image(up_s_ASCII, up_s_colors);
		down_s = new Image(down_s_ASCII, down_s_colors);
		right_s = new Image(right_s_ASCII, right_s_colors);
		left_s = new Image(left_s_ASCII, left_s_colors);
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