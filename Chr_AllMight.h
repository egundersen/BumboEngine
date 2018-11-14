#include "CharacterBase.h"
#include <string>

#ifndef CHR_ALLMIGHT
#define CHR_ALLMIGHT

class Chr_AllMight : public CharacterBase
{
public:
	Chr_AllMight(int center_position_x, int center_position_y, int &player_health, int unique_object_ID, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display,

		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false, //TODO: W.I.P.

		/* Popup Text		(Shows 1 text screen. useful for unimportant characters. Leave BLANK for main characters) */
		std::string basic_dialog = "HELLO PLAYERZ",
		char border_character = 'X',
		int popup_width = 23,
		int popup_height = 9,

		/* Advanced Dialog	(Shows multiple text screens with dialog options. Leave BLANK for minor characters) */
		//TODO: W.I.P.

		/* Default ASCII Art for BATTLE SEQUENCE */
		int boss_health = 22,
		std::string boss_name = "ALL MIGHT",
		std::string boss_ascii_art = "            ,,#,@@@@@,@,*@@@@,*#@@@%             Z           ,,,,,,,@@(&,@@@@@@@@@@@@@%,           Z          @,#,,,,,,,,,,,@,%@@@@@&,,@@@           Z         ,,,@@,,,,,,,,,,,,%@@@@@@,,@@@@          Z         @@,#,,,,,,,,,,,,,%@@@@@@,,,@@@          Z         @@@,,,,,,,,,,,,,,@@@@@@@@,,,@@          Z        ,,@,,,,,,,,,,,,,,,@@@@@@@@,,,@@@         Z        ,@@,,&,&,@,,,.,,,@@@@@,@,@,,,,@@         Z       ,@#,,,,,@@&,@,#(%,,@,&@@@@@@,,,@@@        Z        ,@,,,,,%@@@@@,,/#*@@@@@@@@,,,,@@@        Z       ,@#,,,,,,,(@@@%,@@@@@@@@@@@@,,,*@,,       Z      ,,@,,,,,,,,,,,,,,,,@@@,,*@@@@@,,,,@,       Z      ,@,,,,,,,,,,,,,,,,,@@@,,,,@@@@,,,@,,       Z      @,*,#,,,,,,,,,,,,,,@@@@,,@@@@@@,@@,,       Z      ,@@,,@,@,,,,,,@@@@@@@@@&,@@@@@@,,@,,       Z      ,,@,,,@,,,,&,,,,,@@@@/,@@@@@@@@,@@,.       Z       ,,@,,,,,@,,,,,,,,,,,,,,(@@@@@,,@%,,       Z      ,&,,,,,,@,,,,,,,,,,,,,,,,,,@@@,,,,@@,&     Z     ,,,@@,,,,,@@%@**,,,,,,,,,,,@@@@,,@@@@  .    Z   @@,,@,@#,,/,,@&,,,,,,,,,,,,@,@@@@,,@@@@@      Z    ,(@@,,@,,@,,,&,,,,,,,,,,,,@@@@@@,,@@.@@@@,   Z   ,@@@@,,/,,@@,,,,,,,,,,,,@@@@@@@@@,.@@,@@@@@@  Z &@@@@@@,,,@,,,,,,,,,,,,,@@@@@@@@@@@,@@@&@@(     Z@@@@ @@(,,,,@@,,,,,,,,,,,@@@@@@@@@,@@@@@@*@@@@,  Z    @@@,,,,,,,@@,,,,,,,,,@@@@@@@,@@@@@@@@,       Z      @,,,,,,,,,,@@,,,,,*@@@@%,@@@@@@@@@@@%      Z       @@,,,,,,,,,,@@@@@@@@@@@@@@@@@@@@@@@       Z     @@@@@@@@/,,,,,,@@@@@@@@@@@@@@@@@@@@@@@@     ",
		std::string ascii_overlay = "X*XXXXX________XXXXXXZ,X*  --        -- *X,Z,,X*   --------  *X,,Z,,,,X**        **X,,,Z,,,,,,,XXXXXXXX,,,,,,",
		int overlay_x = 40,
		int overlay_y = 20)

		: CharacterBase(center_position_x, center_position_y, popup_width, popup_height, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, basic_dialog, border_character, player_health, boss_health, boss_name, boss_ascii_art, ascii_overlay, overlay_x, overlay_y)
	{
		// Attacks
		AttackPatternBase *attack_pattern_1;
		attack_pattern_1 = new Explode_Fast(screen_width, screen_height, matrix_display, player_health, 500);
		AttackPatternBase *attack_pattern_2;
		attack_pattern_2 = new Explode_Slow(screen_width, screen_height, matrix_display, player_health, 200);
		AttackPatternBase *attack_pattern_3;
		attack_pattern_3 = new Explode_Slowest(screen_width, screen_height, matrix_display, player_health, 50);
		AttackPatternBase *attack_pattern_4;
		attack_pattern_4 = new AttackPattern_ShootHorizontal(screen_width, screen_height, matrix_display, player_health, 10);
		AttackPatternBase *attack_pattern_5;
		attack_pattern_5 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, matrix_display, player_health, 50);
		AttackPatternBase *attack_pattern_6;
		attack_pattern_6 = new AttackPattern_ShootHorizontal(screen_width, screen_height, matrix_display, player_health, 10);
		attack_patterns_.push_back(attack_pattern_4);
		attack_patterns_.push_back(attack_pattern_3);
		attack_patterns_.push_back(attack_pattern_2);
		attack_patterns_.push_back(attack_pattern_1);
		attack_patterns_.push_back(attack_pattern_5);
		/*attack_patterns_.push_back(attack_pattern_3);
		attack_patterns_.push_back(attack_pattern_4);
		attack_patterns_.push_back(attack_pattern_5);
		attack_patterns_.push_back(attack_pattern_6);//*/

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.1", "1.1 NO", false));
		dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.2", "1.2 NO", false));
		dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.C", "1.C YES", true));
		dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.4", "1.4 NO", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.1", "2.1 NO", false));
		dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.2", "2.2 NO", false));
		dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.3", "2.3 NO", false));
		dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.C", "2.C YES", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.C", "3.C YES", true));
		dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.2", "3.2 NO", false));
		dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.3", "3.3 NO", false));
		dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.4", "3.4 NO", false));

		dialog_choices_.push_back(dialog_choice_1);
		dialog_choices_.push_back(dialog_choice_2);
		dialog_choices_.push_back(dialog_choice_3);

		/* Just a little check to make sure you typed the above code correctly.
		 * This will throw an exception if you did something wrong
		 * Remember! Vector Size cannot be greater than 4! (always 4 dialog options at once) */
#ifdef _DEBUG
		for (auto dialog_choice : dialog_choices_)
			if (dialog_choice.size() > 4)
				throw std::invalid_argument("dialog_choice size must not be greater than 4! There can only be 4 dialog options at a time");
#endif
	}
};

#endif // !CHR_ALLMIGHT
