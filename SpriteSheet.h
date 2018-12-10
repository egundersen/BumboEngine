#include "WorldSprite.h"

// Area for generating sprites for npcs
// Because there are so many, with so many different sprites, this seemed easier than making a new class for every pirate with a different shaped hat
struct SpriteSheet
{
	WorldSprite player = WorldSprite(
		"   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   @@@@   Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   @@@@   Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"   @@@@   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   @@@@   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite pirate_1 = WorldSprite(
		"   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"   -/\\-   Z \\=/--\\=/ Z  X@@@XX  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite pirate_2 = WorldSprite(
		"   _==_   Z \\==()==/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   _==_   Z \\==()==/ Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   _==_   Z \\==()==/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   _==_   Z \\==()==/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"   _==_   Z \\==()==/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   _==_   Z \\==()==/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   _==_   Z \\==()==/ Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   _==_   Z \\==()==/ Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"   _==_   Z \\==()==/ Z  X@@@XX  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   _==_   Z \\==()==/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   _==_   Z \\==()==/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   _==_   Z \\==()==/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite pirate_3 = WorldSprite(
		"   ___    Z \\==()==/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   ___    Z \\==()==/ Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   ___    Z \\==()==/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   ___    Z \\==()==/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"   ___    Z \\==()==/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   ___    Z \\==()==/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   ___    Z \\==()==/ Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   ___    Z \\==()==/ Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"   ___    Z \\==()==/ Z  X@@@XX  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   ___    Z \\==()==/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   ___    Z \\==()==/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   ___    Z \\==()==/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite tutorial_NPC = WorldSprite(
		"   &%%&   Z  /&&&&\\  Z   \\%%/   Z OHH  HHO ZO HHHHHHO Z  %U  U%  Z",
		"   &%%&   Z  /[][]\\  Z   \\<>/   Z OHH  HHO ZO HHHHHHO Z  %U  U%  Z",
		"   &%%&   Z  /&&[]\\  Z   \\%</   Z  O#HH#O  Z  O%HHH%O Z   %%  %  Z",
		"   &%%&   Z  /[]X&\\  Z   \\>%/   Z  O#HH#O  Z O%HHH%O  Z  %  %%   Z",
		"   &%%&   Z  /&&&&\\  Z   \\%%/   Z O#HHHH#O Z OHHHHHH OZ  %U  U%  Z",
		"   &%%&   Z  /[][]\\  Z   \\<>/   Z O#HHHH#O Z OHHHHHH OZ  %U  U%  Z",
		"   &%%&   Z  /&&[]\\  Z   \\%</ O Z  O#HH#O  Z %%O#%#   Z %=  %%   Z",
		"   &%%&   Z  /[]&&\\  Z O \\>%/   Z  O#HH#O  Z   #%#O%% Z   %%  =% Z",
		"   &%%&   Z  /&&&&\\  Z   \\%%/   Z O#XXXX#O Z OHHHHHHO Z  %U  U%  Z",
		"   &%%&   Z  /[][]\\  Z   \\<>/   Z OHH\\/HHO Z OHHHHHHO Z  %U  U%  Z",
		"   &%%&   Z  /&&[]\\  Z   \\%</   Z  O#HH#O  Z  HHHHHHO Z  %U  U%  Z",
		"   &%%&   Z  /[]&&\\  Z   \\>%/   Z  O#HH#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite bonny = WorldSprite(
		"    /\\$   Z\\=//--\\\\=/Z  XbXXdX  Z   wwww   ZO#XXXXXX#OZO ###### OZ  %U  U%  Z",
		"    /\\$   Z\\=//--\\\\=/Z  X[][]X  Z   WWWW   ZO#XXXXXX#OZO ###### OZ  %U  U%  Z",
		"    /\\$   Z\\=//--\\\\=/Z  @@X[]X  Z   WWWW   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"    /\\$   Z\\=//--\\\\=/Z  X[]X@@  Z   WWWW   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"    /\\$   Z\\=//--\\\\=/Z  XXX@@X  Z   WWWW   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"    /\\$   Z\\=//--\\\\=/Z  X[][]X  Z   WWWW   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"    /\\$   Z\\=//--\\\\=/Z  @@X[]X  Z   WWWW O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"    /\\$   Z\\=//--\\\\=/Z  X[]X@@  Z O WWWW   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"    /\\$   Z\\=//--\\\\=/Z  XXX@@X  Z   WWWW   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"    /\\$   Z\\=//--\\\\=/Z  X[][]X  Z   WWWW   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"    /\\$   Z\\=//--\\\\=/Z  @@X[]X  Z   WWWW   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"    /\\$   Z\\=//--\\\\=/Z  X[]X@@  Z   WWWW   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite sharktooth = WorldSprite(
		"    /\\   Z\\=//--\\\\=/Z  XbXXdX  Z   XmmX   ZO#XXXXXX#OZO ###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[][]X  Z   XmmX   ZO#XXXXXX#OZO ###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"    /\\   Z\\=//--\\\\=/Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"    /\\   Z\\=//--\\\\=/Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"    /\\   Z\\=//--\\\\=/Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite ryuuko = WorldSprite(
		"    /\\   Z\\=//--\\\\=/Z  XbXXdX  Z   XmmX   ZO#XXXXXX#OZO ###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[][]X  Z   XmmX   ZO#XXXXXX#OZO ###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"    /\\   Z\\=//--\\\\=/Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"    /\\   Z\\=//--\\\\=/Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"    /\\   Z\\=//--\\\\=/Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"    /\\   Z\\=//--\\\\=/Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite aki = WorldSprite(
		"  @@@@@@  Z  @XXXX@  Z @ XXXX @ Z O#XXXX#O ZO ######O Z   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XUUX @ Z O#XXXX#O ZO ######O Z   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"  @@@@@@  Z @XXXXXX@ Z @ XXXX @ Z O#XXXX#O Z O###### OZ   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XXXX @ Z O#XXXX#O Z O###### OZ   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   @@@@   Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"  @@@@@@  Z @XXX@@X@ Z @ XXXX @ Z O#XXXX#O Z O######O Z   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XXXX @ Z O#XXXX#O Z O######O Z   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite mini_boss_1 = WorldSprite(
		"  @@@@@@  Z  @XXXX@  Z @ XXXX @ Z O#XXXX#O ZO ######O Z   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XUUX @ Z O#XXXX#O ZO ######O Z   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"  @@@@@@  Z @XXXXXX@ Z @ XXXX @ Z O#XXXX#O Z O###### OZ   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XXXX @ Z O#XXXX#O Z O###### OZ   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   @@@@   Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"  @@@@@@  Z @XXX@@X@ Z @ XXXX @ Z O#XXXX#O Z O######O Z   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XXXX @ Z O#XXXX#O Z O######O Z   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite mini_boss_2 = WorldSprite(
		"   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"   -/\\-   Z \\=/--\\=/ Z  X@@@XX  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite mini_boss_3 = WorldSprite(
		"  @@@@@@  Z  @XXXX@  Z @ XXXX @ Z O#XXXX#O ZO ######O Z   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XUUX @ Z O#XXXX#O ZO ######O Z   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"  @@@@@@  Z @XXXXXX@ Z @ XXXX @ Z O#XXXX#O Z O###### OZ   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XXXX @ Z O#XXXX#O Z O###### OZ   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   @@@@   Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"  @@@@@@  Z @XXX@@X@ Z @ XXXX @ Z O#XXXX#O Z O######O Z   U  U   Z",
		"  @@@@@@  Z @X[][]X@ Z @ XXXX @ Z O#XXXX#O Z O######O Z   U  U   Z",
		"   @@@@   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   @@@@   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);

	WorldSprite mini_boss_4 = WorldSprite(
		"   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
		"   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
		"   -/\\-   Z \\=/--\\=/ Z  X@@@XX  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
		"   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
	);
};