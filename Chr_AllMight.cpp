#include "BattleBase.h"
#include "Chr_AllMight.h"

Chr_AllMight::Chr_AllMight(int width, int height, std::vector<std::vector<std::string>>& matrix_display, int player_health, int boss_health, std::string boss_ascii_art, std::string ascii_overlay = "", int overlay_x = 40, int overlay_y = 20)
	: BattleBase(width, height, matrix_display, player_health, boss_health, boss_ascii_art, ascii_overlay, overlay_x, overlay_y)
{

	// Attacks
	AttackPatternBase *attack_pattern_1;
	attack_pattern_1 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
	AttackPatternBase *attack_pattern_2;
	attack_pattern_2 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
	attack_patterns_.push_back(attack_pattern_1);
	attack_patterns_.push_back(attack_pattern_2);

	// (In-Battle) Dialog:		dialog choice, boss's response, should progress dialog (only 1!)
	std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
	dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1", "NO", false));
	dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 2", "NO", false));
	dialog_choice_1.push_back(std::make_tuple("HELLO WORLD C", "YES", true));
	dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 4", "NO", false));

	std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
	dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 1", "NO", false));
	dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2", "NO", false));
	dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 3", "NO", false));
	dialog_choice_2.push_back(std::make_tuple("HELLO WORLD C", "YES", true));

	dialog_choices_.push_back(dialog_choice_1);
	dialog_choices_.push_back(dialog_choice_2);

	// Remember! Vector Size cannot be greater than 4! (always 4 dialog options at once)
#ifdef _DEBUG
	for(auto dialog_choice : dialog_choices_)
		if (dialog_choice.size() > 4)
			throw std::invalid_argument("dialog_choice size must not be greater than 4! There can only be 4 dialog options at a time");

#endif
}
