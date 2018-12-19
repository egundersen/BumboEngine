#include "WorldSprite.h"
#include "ColoredString.h"

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

	ColoredString tree = ColoredString
	(
		"                %%           Z               %             Z              %       %%%    Z     %       %       %       Z      %%      % %   %        Z        %%  % #  % %         Z %      #%%  %  % %         % Z  % %%  % # %%   % %  %% %%  Z        % %%# %%    %%       Z             %    %%         Z          %%  %  %#          Z            %%# #            Z             #%%             Z             %%#             Z             #%              Z             %%,             Z             %%#             Z             %%%             Z             %#%             Z             %#%             Z             %%%             Z             %%#             Z",
		"                LL           Z               L             Z              L       LLL    Z     L       G       L       Z      LL      G L   G        Z        GL  L G  L G         Z L      LGG  G  L G         L Z  L LL  L L GG   G L  GL LL  Z        G GBG GG    BG       Z             B    BG         Z          BB  B  BG          Z            BBB B            Z             BBB             Z             BBB             Z             BB              Z             BBB             Z             BBB             Z             BBB             Z             BBB             Z             BBB             Z             BBB             Z             BBB             Z"
	);

	ColoredString rock = ColoredString
	(
		"   @@&@   Z #@@* #@( Z #*%  (*& Z @(%#*,#@ Z",
		"   SSSS   Z SSSS SSS Z SSS  SSS Z SSSSSSSS Z"
	);

	ColoredString fence = ColoredString
	(
		fence_ASCII_,
		fence_ASCII_colors_,
		59,
		56
	);

private:
	std::wstring fence_ASCII_[56] = {
		L" ,.   (* ,%*                                               Z",
		L" .@( .%,  #&%/#.                                           Z",
		L"  @( %. .% *# /&%%*                                        Z",
		L"  @( #  %. %,%##  */,                                      Z",
		L"  @# %. #.%.(.%, (&* /%,                                   Z",
		L"  @%..#%@( .%%, %#/. %%(#(                                 Z",
		L"  @@@@%,.##%&  ,#/#/(.%/ #&%#.                             Z",
		L"  @@@(,%@&. *(.(%..( ##,#%*  #,.                           Z",
		L"  @#.@&. /@@( .,( **/#.%*% .#&.,#                          Z",
		L"  @%  %@,   *@@#*%&%, (#( .(.%  (/                         Z",
		L"  @%   ,@%     *@@%/%%&* .#.#,.&&*  *%*,(#                 Z",
		L"  @%    .&&.      ,@@(,%,*@*   %# .(   .#@&,               Z",
		L"  @%      &@*        %@@*,%   ,%(,%  .%,,% %,              Z",
		L"  @%       *@(          #@@&%#.&%%. #/ .( .&.              Z",
		L"  @&         @@,           #@@/&%#*#*,%,#/(,  %,           Z",
		L"  @&          /@/          .,(@@@%.%. ,%/%, *%&%%.         Z",
		L"  @&           ,@%    ,/&@@@%(.&@@@*%#&%. .&%%. .&,        Z",
		L"  @&           ,#@@@@#*.       %@(/@( %  #&(#.*%%%*#       Z",
		L"  &&.   ,(&@@&%/. *@#          %@@#,@@,(%&/ ,%./%, #/      Z",
		L"  @@@@@%*.         .&%         %%(@, /@(#%./#*&%,#%#  %    Z",
		L"  ##.                @@,       #% (@. (@(/%&%%.,%,%   %*   Z",
		L"                      (@/      #%  &@,  @@*#/ (%%, (#// ** Z",
		L"                        @&.    #&   &@   /@( .#  ,% (#  ./ Z",
		L"                        .&@.   #&   .   .@&.%, &/%@&  #    Z",
		L"                          *@#  (&     @%    %@, *(##&&%%#. Z",
		L"                           ,@@ (&     *@/    .&&/#*,&%.  /(Z",
		L"                             /@&&.     ,@(    (%%#&//#.    Z",
		L"                              (@@@@(,.%@/   #((&%#&/(,     Z",
		L"                                     .,/%@@@@&&(&%%& ,#.   Z",
		L"                                          (@,,%%%#%&%%(%*  Z",
		L"                                           &@/./(%%%#%.((  Z",
		L"                                           .#%#,. ,@&&%#.  Z",
		L"                                           /%%%(%%&%&@(%.  Z",
		L"                                           (%%//%%&%%,     Z",
		L"                                           #, /@&%&@&&(    Z",
		L"                                           #%#&&&&&%       Z",
		L"                                          #     /@@((&.    Z",
		L"                                          #&&%..%@@@&&     Z",
		L"                                         #..@@.*&@@&&@.    Z",
		L"                                         #/,@@ #@&%%@@.    Z",
		L"                                            @@/&%@#&@&.    Z",
		L"                                            @@%@%@@.       Z",
		L"                                            @@@@@%         Z",
		L"                                            @@@(@/         Z",
		L"                                            @@%(@.         Z",
		L"                                            @@*&@          Z",
		L"                                            @@,@%          Z",
		L"                                            @@#@*          Z",
		L"                                            @@&&.          Z",
		L"                                            @@@#           Z",
		L"                                            @@@,           Z",
		L"                                            @@&            Z",
		L"                                            @@/            Z",
		L"                                            @@,            Z",
		L"                                            @@             Z",
		L"                                            &&             Z"
	};
	std::wstring fence_ASCII_colors_[56] = {
		L" BB   BB BBB                                               Z",
		L" BBB BBB  BBBBBB                                           Z",
		L"  BB BB BB BB BBBBB                                        Z",
		L"  BB B  BB BBBBB  BBB                                      Z",
		L"  BB BB BBBBBBBB BBB BBB                                   Z",
		L"  BBBBBBBB BBBB BBBB BBBBB                                 Z",
		L"  BBBBBBBBBBB  BBBBBBBBB BBBBB                             Z",
		L"  BBBBBBBBB BBBBBBBB BBBBBB  BBB                           Z",
		L"  BBBBBB BBBB BBB BBBBBBBB BBBBBB                          Z",
		L"  BB  BBB   BBBBBBBBB BBB BBBB  BB                         Z",
		L"  BB   BBB     BBBBBBBBB BBBBBBBBB  BBBBBB                 Z",
		L"  BB    BBBB      BBBBBBBBBB   BB BB   BBBBB               Z",
		L"  BB      BBB        BBBBBB   BBBBB  BBBBB BB              Z",
		L"  BB       BBB          BBBBBBBBBBB BB BB BBB              Z",
		L"  BB         BBB           BBBBBBBBBBBBBBBBB  BB           Z",
		L"  BB          BBB          BBBBBBBBBB BBBBB BBBBBB         Z",
		L"  BB           BBB    BBBBBBBBBBBBBBBBBBB BBBBB BBB        Z",
		L"  BB           BBBBBBBBB       BBBBBB B  BBBBBBBBBBB       Z",
		L"  BBB   BBBBBBBBB BBB          BBBBBBBBBBBB BBBBBB BB      Z",
		L"  BBBBBBBB         BBB         BBBBB BBBBBBBBBBBBBBB  B    Z",
		L"  BBB                BBB       BB BBB BBBBBBBBBBBBB   BB   Z",
		L"                      BBB      BB  BBB  BBBBB BBBB BBBB BB Z",
		L"                        BBB    BB   BB   BBB BB  BB BB  BB Z",
		L"                        BBBB   BB   B   BBBBBB BBBBB  B    Z",
		L"                          BBB  BB     BB    BBB BBBBBBBBBB Z",
		L"                           BBB BB     BBB    BBBBBBBBBB  BBZ",
		L"                             BBBBB     BBB    BBBBBBBBB    Z",
		L"                              BBBBBBBBBBB   BBBBBBBBBB     Z",
		L"                                     BBBBBBBBBBBBBBB BBB   Z",
		L"                                          BBBBBBBBBBBBBBB  Z",
		L"                                           BBBBBBBBBBBBBB  Z",
		L"                                           BBBBBB BBBBBBB  Z",
		L"                                           BBBBBBBBBBBBBB  Z",
		L"                                           BBBBBBBBBBB     Z",
		L"                                           BB BBBBBBBBB    Z",
		L"                                           BBBBBBBBB       Z",
		L"                                          B     BBBBBBB    Z",
		L"                                          BBBBBBBBBBBB     Z",
		L"                                         BBBBBBBBBBBBBB    Z",
		L"                                         BBBBB BBBBBBBB    Z",
		L"                                            BBBBBBBBBBB    Z",
		L"                                            BBBBBBBB       Z",
		L"                                            BBBBBB         Z",
		L"                                            BBBBBB         Z",
		L"                                            BBBBBB         Z",
		L"                                            BBBBB          Z",
		L"                                            BBBBB          Z",
		L"                                            BBBBB          Z",
		L"                                            BBBBB          Z",
		L"                                            BBBB           Z",
		L"                                            BBBB           Z",
		L"                                            BBB            Z",
		L"                                            BBB            Z",
		L"                                            BBB            Z",
		L"                                            BB             Z",
		L"                                            BB             Z"
	};
};