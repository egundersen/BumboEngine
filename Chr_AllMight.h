#include "BattleBase.h"
#include <string>

#ifndef CHR_ALLMIGHT
#define CHR_ALLMIGHT

class Chr_AllMight : public BattleBase
{
public:
	Chr_AllMight(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int &player_health,

		/* Default ASCII Art for All Might */
		int boss_health = 22,
		std::string boss_name = "ALL MIGHT",
		std::string boss_ascii_art = "            ,,#,@@@@@,@,*@@@@,*#@@@%             Z           ,,,,,,,@@(&,@@@@@@@@@@@@@%,           Z          @,#,,,,,,,,,,,@,%@@@@@&,,@@@           Z         ,,,@@,,,,,,,,,,,,%@@@@@@,,@@@@          Z         @@,#,,,,,,,,,,,,,%@@@@@@,,,@@@          Z         @@@,,,,,,,,,,,,,,@@@@@@@@,,,@@          Z        ,,@,,,,,,,,,,,,,,,@@@@@@@@,,,@@@         Z        ,@@,,&,&,@,,,.,,,@@@@@,@,@,,,,@@         Z       ,@#,,,,,@@&,@,#(%,,@,&@@@@@@,,,@@@        Z        ,@,,,,,%@@@@@,,/#*@@@@@@@@,,,,@@@        Z       ,@#,,,,,,,(@@@%,@@@@@@@@@@@@,,,*@,,       Z      ,,@,,,,,,,,,,,,,,,,@@@,,*@@@@@,,,,@,       Z      ,@,,,,,,,,,,,,,,,,,@@@,,,,@@@@,,,@,,       Z      @,*,#,,,,,,,,,,,,,,@@@@,,@@@@@@,@@,,       Z      ,@@,,@,@,,,,,,@@@@@@@@@&,@@@@@@,,@,,       Z      ,,@,,,@,,,,&,,,,,@@@@/,@@@@@@@@,@@,.       Z       ,,@,,,,,@,,,,,,,,,,,,,,(@@@@@,,@%,,       Z      ,&,,,,,,@,,,,,,,,,,,,,,,,,,@@@,,,,@@,&     Z     ,,,@@,,,,,@@%@**,,,,,,,,,,,@@@@,,@@@@  .    Z   @@,,@,@#,,/,,@&,,,,,,,,,,,,@,@@@@,,@@@@@      Z    ,(@@,,@,,@,,,&,,,,,,,,,,,,@@@@@@,,@@.@@@@,   Z   ,@@@@,,/,,@@,,,,,,,,,,,,@@@@@@@@@,.@@,@@@@@@  Z &@@@@@@,,,@,,,,,,,,,,,,,@@@@@@@@@@@,@@@&@@(     Z@@@@ @@(,,,,@@,,,,,,,,,,,@@@@@@@@@,@@@@@@*@@@@,  Z    @@@,,,,,,,@@,,,,,,,,,@@@@@@@,@@@@@@@@,       Z      @,,,,,,,,,,@@,,,,,*@@@@%,@@@@@@@@@@@%      Z       @@,,,,,,,,,,@@@@@@@@@@@@@@@@@@@@@@@       Z     @@@@@@@@/,,,,,,@@@@@@@@@@@@@@@@@@@@@@@@     ",
		std::string ascii_overlay = "X*XXXXX________XXXXXXZ,X*  --        -- *X,Z,,X*   --------  *X,,Z,,,,X**        **X,,,Z,,,,,,,XXXXXXXX,,,,,,",
		int overlay_x = 40,
		int overlay_y = 20)

		: BattleBase(width, height, matrix_display, player_health, boss_health, boss_name, boss_ascii_art, ascii_overlay, overlay_x, overlay_y)
	{
		// Attacks
		AttackPatternBase *attack_pattern_1;
		attack_pattern_1 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
		AttackPatternBase *attack_pattern_2;
		attack_pattern_2 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
		AttackPatternBase *attack_pattern_3;
		attack_pattern_3 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
		AttackPatternBase *attack_pattern_4;
		attack_pattern_4 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
		AttackPatternBase *attack_pattern_5;
		attack_pattern_5 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
		AttackPatternBase *attack_pattern_6;
		attack_pattern_6 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
		attack_patterns_.push_back(attack_pattern_1);
		/*attack_patterns_.push_back(attack_pattern_2);
		attack_patterns_.push_back(attack_pattern_3);
		attack_patterns_.push_back(attack_pattern_4);
		attack_patterns_.push_back(attack_pattern_5);
		attack_patterns_.push_back(attack_pattern_6);//*/

		// (In-Battle) Dialog:		dialog choice, boss's response, should progress dialog (only 1!)
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

		// Just a little check to make sure you typed the above code correctly.
		// This will throw an exception if you did something wrong
		// Remember! Vector Size cannot be greater than 4! (always 4 dialog options at once)
#ifdef _DEBUG
		for (auto dialog_choice : dialog_choices_)
			if (dialog_choice.size() > 4)
				throw std::invalid_argument("dialog_choice size must not be greater than 4! There can only be 4 dialog options at a time");
#endif
	}
};

#endif // !CHR_ALLMIGHT
