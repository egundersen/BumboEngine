#include "BattleBase.h"
#include "Chr_AllMight.h"

Chr_AllMight::Chr_AllMight(int width, int height, std::vector<std::vector<std::string>>& matrix_display, int player_health, int boss_health, std::string boss_ascii_art, std::string ascii_overlay = "", int overlay_x = 40, int overlay_y = 20)
	: BattleBase(width, height, matrix_display, player_health, boss_health, boss_ascii_art, ascii_overlay, overlay_x, overlay_y)
{
	AttackPatternBase *attackPattern1;
	attackPattern1 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
	AttackPatternBase *attackPattern2;
	attackPattern2 = new AttackPattern_ShootHorizontal(width, height, matrix_display_, player_health, 10);
	attack_patterns_.push_back(attackPattern1);
	attack_patterns_.push_back(attackPattern2);
}
