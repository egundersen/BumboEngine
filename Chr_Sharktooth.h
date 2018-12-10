#include "CharacterBase.h"
#include <string>

#ifndef CHR_SHARKTOOTH_H
#define CHR_SHARKTOOTH_H

class Chr_Sharktooth : public CharacterBase
{
public:
	Chr_Sharktooth(int center_position_x, int center_position_y, int &player_health, int unique_object_ID, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::pair<std::string, int> &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			8, // Boss health
			"SHARKTOOTH", // name
			"sharktooth_neutral.bmp", // Neutral Expression (Image Location/Name)
			"sharktooth_angry.bmp",
			"sharktooth_happy.bmp",
			"sharktooth_nervous_dead.bmp"
		),//*/

		  /* Sets the sprite ascii for the NPC world sprite */
		WorldSprite world_sprite = WorldSprite(
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
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 2) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Are you prepared to fight?!                ", "I'LL BREAK YE", false));
		dialog_choice_1.push_back(std::make_tuple("I'm gonna beat you up                      ", "YOU ARE A FRY", false));
		dialog_choice_1.push_back(std::make_tuple("IS IT YOU??                               ", " DON'T DOUBT ME", true));
		dialog_choice_1.push_back(std::make_tuple("I will prove that you are weak!            ", "YOU ARE WEAK", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("This will be your first lost!              ", "I WILL NOT BE BEATEN", false));
		dialog_choice_2.push_back(std::make_tuple("You will break!                               ", "YAR A TWIG", false));
		dialog_choice_2.push_back(std::make_tuple("AHAHHAHAHA                                ", "NOTHIN BUT A PIP", false));
		dialog_choice_2.push_back(std::make_tuple("Are you great like how I imagined you?     ", "SONNY, YAR AN IDIOT", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("It might not be you                        ", "I'M NOT WEAK", true));
		dialog_choice_3.push_back(std::make_tuple("This is your end!                       ", "I WILL FIGHT TIL YE DIE", false));
		dialog_choice_3.push_back(std::make_tuple("I will kill!                           ", "DIE DIE DIE", false));
		dialog_choice_3.push_back(std::make_tuple("I might not win....                    ", "DON'T RUN AWAY", false));

		dialog_choices_.push_back(dialog_choice_1);
		dialog_choices_.push_back(dialog_choice_2);
		dialog_choices_.push_back(dialog_choice_3);

		/* Just a little check to make sure you typed the above code correctly.
		* This will throw an exception if you added more than more dialog choices
		* Remember! Vector Size cannot be greater than 4! (always 4 dialog options at once) */
#ifdef _DEBUG
		for (auto dialog_choice : dialog_choices_)
			if (dialog_choice.size() > 4)
				throw std::invalid_argument("dialog_choice size must not be greater than 4! There can only be 4 dialog options at a time");
#endif
	}

	/* Creates all attacks */
	void initializeAttackPatterns(int screen_width, int screen_height, std::vector<std::vector<std::string>> &matrix_display, int &player_health)
	{
		for (int i = 0; i < 6; i++)
		{
			AttackPatternBase *attack_pattern_1;
			attack_pattern_1 = new Explode_Fast(screen_width, screen_height, matrix_display, player_health, 200);
			AttackPatternBase *attack_pattern_2;
			attack_pattern_2 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 3, 35);
			AttackPatternBase *attack_pattern_3;
			attack_pattern_3 = new VerticleGap_Slow(screen_width, screen_height, matrix_display, player_health);
			AttackPatternBase *attack_pattern_4;
			attack_pattern_4 = new AttackPattern_ShootHorizontal(screen_width, screen_height, matrix_display, player_health, 20);
			AttackPatternBase *attack_pattern_5;
			attack_pattern_5 = new VerticleGap_Wavy(screen_width, screen_height, matrix_display, player_health);
			attack_patterns_.push_back(attack_pattern_1);
			attack_patterns_.push_back(attack_pattern_2);
			attack_patterns_.push_back(attack_pattern_3);
			attack_patterns_.push_back(attack_pattern_4);
			attack_patterns_.push_back(attack_pattern_5);
		}
	}

	/* Advanced Dialog	(Shows multiple text screens with dialog options. Leave BLANK for minor characters) */
	void setDialogNodes()
	{
		Item health_potion("Bottle o' syrup", 1);

		/* ACTIONS (Mini-Tutorial)
		*	"FIGHT"		Will start a battle with the NPC
		*	item		Including an Item will have the NPC give the player the provided item
		*	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		*				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		*/

		// CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "AAAARRRGGGHGH!ZZWHOOOO STEPSZON ME TERRITORY?Z");
		DialogNode *node_1_1 = new DialogNode("Whats your name?", "MEEEEE NAME BEZS-H-A-R-K T-O-O-T-HZ");
		DialogNode *node_1_2 = new DialogNode("You cant take territories", "DOOOOOOOOON'T TELL MEZWHAT TO DO !!!!!Z", "FIGHT");
		DialogNode *node_1_3 = new DialogNode("Goodbye...", "LEAVE ME TERRITORY!Z");
		DialogNode *node_1_1_1 = new DialogNode("Of the Blood Sea??", "ARRRGGGG!ZIT IS I, SHARKTOOTH!ZTHE NAME WHICHZCASTS FEAR INZTHE MANY A MANZ");
		DialogNode *node_1_1_2 = new DialogNode("Were you at the border?", "AND SO WHAT IFZI WAS THAR??Z");
		DialogNode *node_1_1_3 = new DialogNode("Never heard of you...", "ARRRGGHH YOU DOZNOT KNOWZWHO I ARE?? Z"); //TODO amber - add "smelling " cigar which leads to box of cigar
		DialogNode *node_1_1_2_1 = new DialogNode("Did you lose anything?", "I BE MISSIN'ZME PRECIOUSZCIGAR BOX Z");
		DialogNode *node_1_1_2_2 = new DialogNode("Is THIS your cigar box?", "DIS MINE ITS TRUEZZ...ZAND HOW... PRAYTELL...ZDID. YOU. GET. THIS.?Z");
		DialogNode *node_1_1_2_2_1 = new DialogNode("I found it", "THATS ME BOX!ZTHANK YE. Z");
		DialogNode *node_1_1_2_2_2 = new DialogNode("I stole it", "THEN BY BALGRUF'S BEARDZI WILL END YOU!Z", "FIGHT");
		DialogNode *node_1_1_2_2_1_1 = new DialogNode("Regarding the border...", "WHAT ABOUT IT?ZSPIT IT OUT LAD!ZI HAVEN'T ALL DAY!Z");
		DialogNode *node_1_1_2_2_1_2 = new DialogNode("Take anything recently?", "ARE YE ACCUSINGZME OF SOMETHING?!ZIF THAT BE THE CASEZI'LL SEE YOU IN HELLZ", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_1 = new DialogNode("See anyone suspicious?", "E'RYONE IS SUSPICIOUSZIN MY EYES Z ...EVEN YAZ", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2 = new DialogNode("Theres this hard drive", "CUT YE OFF RIGHT 'EREZYE THINK IT WAS MEZWHO STOLE ITZDON'T KNOW NOTHINGZABOUT THAT ... HEHZ");
		DialogNode *node_1_1_2_2_1_1_2_1 = new DialogNode("You did steal it!", "ARRRGGG YE IS WRONGZ", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2_2 = new DialogNode("I have a suspicion...", "JUST A SUSPICION?!ZYE HAVEN'T THE COURAGEZNOR THE BRAVERYZTO FACE ME!ZTIME TO DIE, COWARDZ");
		DialogNode *node_1_1_2_2_1_1_2_3 = new DialogNode("No, not at all!", "YA CALLING MEZA SEA BARNACLE?Z", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2_2_1 = new DialogNode("I'm no coward!", "FINALLY SOME APTITUDEZDIE WIT' A SWORDZIN YE HAND!Z", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2_2_2 = new DialogNode("No, I dont want to fight", "WHEN WILL YE LEARN!?ZNO MATTER THE CHOICEZYOU MAKE, THISZWILL ALWAYSZEND THE SAME WAY!Z", "FIGHT");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);
		node_1_1->setChoice3(node_1_1_3);

		node_1_1_1->setChoice1(node_1_1_2);

		node_1_1_2->setChoice1(node_1_1_2_1);
		node_1_1_2->setChoice2(node_1_1_2_2);

		node_1_1_2_1->setChoice1(node_1_1_2_2);

		node_1_1_2_2->setChoice1(node_1_1_2_2_1);
		node_1_1_2_2->setChoice2(node_1_1_2_2_2);

		node_1_1_2_2_1->setChoice1(node_1_1_2_2_1_1);
		node_1_1_2_2_1->setChoice2(node_1_1_2_2_1_2);

		node_1_1_2_2_1_1->setChoice1(node_1_1_2_2_1_1_1);
		node_1_1_2_2_1_1->setChoice2(node_1_1_2_2_1_1_2);

		node_1_1_2_2_1_1_2->setChoice1(node_1_1_2_2_1_1_2_1);
		node_1_1_2_2_1_1_2->setChoice2(node_1_1_2_2_1_1_2_2);
		node_1_1_2_2_1_1_2->setChoice3(node_1_1_2_2_1_1_2_3);

		node_1_1_2_2_1_1_2_2->setChoice1(node_1_1_2_2_1_1_2_2_1);
		node_1_1_2_2_1_1_2_2->setChoice2(node_1_1_2_2_1_1_2_2_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_SHARKTOOTH_H


