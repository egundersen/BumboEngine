#include "WorldSprite.h"

// Area for generating sprites for npcs
// Because there are so many, with so many different sprites, this seemed easier than making a new class for every pirate with a different shaped hat
struct SpriteSheet
{
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
};