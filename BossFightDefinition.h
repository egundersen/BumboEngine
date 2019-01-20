#ifndef BOSSFIGHTDEFINITION_H
#define BOSSFIGHTDEFINITION_H

#include <string>

// Text and dimensions for boss battle scene sprite : Neutral, Angry, Happy, Defeated
struct BossFightDefinition
{
	BossFightDefinition() 
		: use_files{ false }, health{ 1 }, overlay_x{ 0 }, overlay_y{ 0 }, name{ "" }, theme_song{ "" }, ascii{ "" }, overlay{ "" },
		file_path_neutral{ "" }, file_path_angry{ "" }, file_path_happy{ "" }, file_path_nervous_dead{ "" } {}
	BossFightDefinition(int boss_health, int overlay_x_offset, int overlay_y_offset, std::string boss_name, std::string theme_song, std::string boss_ascii_art, std::string overlay_ascii)
		: use_files{ false }, health{ boss_health }, overlay_x{ overlay_x_offset }, overlay_y{ overlay_y_offset }, name{ boss_name }, theme_song{ "open \"resources\\audio\\soundtrack\\" + theme_song + "\" type mpegvideo alias soundtrack" }, ascii{ boss_ascii_art }, overlay{ overlay_ascii },
		file_path_neutral{ "" }, file_path_angry{ "" }, file_path_happy{ "" }, file_path_nervous_dead{ "" } {}
	BossFightDefinition(int boss_health, std::string boss_name, std::string theme_song, std::string image_file_name_neutral, std::string image_file_name_angry, std::string image_file_name_happy, std::string image_file_name_nervous_dead)
		: use_files{ true }, health{ boss_health }, overlay_x{ 0 }, overlay_y{ 0 }, name{ boss_name }, theme_song{ "open \"resources\\audio\\soundtrack\\" + theme_song + "\" type mpegvideo alias soundtrack" }, ascii{ "" }, overlay{ "" },
		file_path_neutral{ "resources\\sprites\\" + image_file_name_neutral }, file_path_angry{ "resources\\sprites\\" + image_file_name_angry }, file_path_happy{ "resources\\sprites\\" + image_file_name_happy }, file_path_nervous_dead{ "resources\\sprites\\" + image_file_name_nervous_dead } {}

	bool use_files;
	int health, overlay_x, overlay_y;
	std::string name, ascii, theme_song, overlay, file_path_neutral, file_path_angry, file_path_happy, file_path_nervous_dead;
};

#endif // !BOSSFIGHTDEFINITION_H
