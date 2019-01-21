#ifndef BOSSFIGHTDEFINITION_H
#define BOSSFIGHTDEFINITION_H

#include <string>

// Text and dimensions for boss battle scene sprite : Neutral, Angry, Happy, Defeated
struct BossFightDefinition
{
	BossFightDefinition() 
		: use_files{ false }, health{ 1 }, overlay_x{ 0 }, overlay_y{ 0 }, name{ "" }, theme_song{ "" }, ascii{ "" }, overlay{ "" },
		resource_ID_neutral{ 0 }, resource_ID_angry{ 0 }, resource_ID_happy{ 0 }, resource_ID_nervous_dead{ 0 } {}
	BossFightDefinition(int boss_health, int overlay_x_offset, int overlay_y_offset, std::string boss_name, std::string theme_song, std::string boss_ascii_art, std::string overlay_ascii)
		: use_files{ false }, health{ boss_health }, overlay_x{ overlay_x_offset }, overlay_y{ overlay_y_offset }, name{ boss_name }, theme_song{ "open \"resources\\audio\\soundtrack\\" + theme_song + "\" type mpegvideo alias soundtrack" }, ascii{ boss_ascii_art }, overlay{ overlay_ascii },
		resource_ID_neutral{ 0 }, resource_ID_angry{ 0 }, resource_ID_happy{ 0 }, resource_ID_nervous_dead{ 0 } {}
	BossFightDefinition(int boss_health, std::string boss_name, std::string theme_song, int resource_ID_neutral, int resource_ID_angry, int resource_ID_happy, int resource_ID_nervous_dead)
		: use_files{ true }, health{ boss_health }, overlay_x{ 0 }, overlay_y{ 0 }, name{ boss_name }, theme_song{ "open \"resources\\audio\\soundtrack\\" + theme_song + "\" type mpegvideo alias soundtrack" }, ascii{ "" }, overlay{ "" },
		resource_ID_neutral{ resource_ID_neutral }, resource_ID_angry{ resource_ID_angry }, resource_ID_happy{ resource_ID_happy }, resource_ID_nervous_dead{ resource_ID_nervous_dead } {}

	bool use_files;
	int health, overlay_x, overlay_y, resource_ID_neutral, resource_ID_angry, resource_ID_happy, resource_ID_nervous_dead;;
	std::string name, ascii, theme_song, overlay;
};

#endif // !BOSSFIGHTDEFINITION_H
