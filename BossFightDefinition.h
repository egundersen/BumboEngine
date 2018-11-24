#include <string>

#ifndef BOSSFIGHTDEFINITION_H
#define BOSSFIGHTDEFINITION_H

// Text and dimensions for boss battle scene sprite
struct BossFightDefinition
{
	BossFightDefinition(int boss_health, int overlay_x_offset, int overlay_y_offset, std::string boss_name, std::string boss_ascii_art, std::string overlay_ascii)
		: use_files{ false }, health{ boss_health }, overlay_x{ overlay_x_offset }, overlay_y{ overlay_y_offset }, name{ boss_name }, ascii{ boss_ascii_art }, overlay{ overlay_ascii },
		file_path_neutral{ "" }, file_path_angry{ "" } {}
	BossFightDefinition(int boss_health, std::string boss_name, std::string image_file_path_neutral, std::string image_file_path_angry)
		: use_files{ true }, health{ boss_health }, overlay_x{ 0 }, overlay_y{ 0 }, name{ boss_name }, ascii{ "" }, overlay{ "" },
		file_path_neutral{ image_file_path_neutral }, file_path_angry{ image_file_path_angry } {}

	bool use_files;
	int health, overlay_x, overlay_y;
	std::string name, ascii, overlay, file_path_neutral, file_path_angry;
};

#endif // !BOSSFIGHTDEFINITION_H
