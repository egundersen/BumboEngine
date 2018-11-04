#include "BattleBase.h"
#include <string>

#ifndef CHR_ALLMIGHT
#define CHR_ALLMIGHT

class Chr_AllMight : public BattleBase {
public:
	Chr_AllMight(int width, int height, std::vector<std::vector<std::string>> &matrix_display, int player_health, int boss_health, std::string boss_ascii_art, std::string ascii_overlay, int overlay_x, int overlay_y);
};

#endif // !CHR_ALLMIGHT
