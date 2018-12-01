#include "CharacterBase.h"
#include <string>

#ifndef CHR_BONNY_H
#define CHR_BONNY_H

class Chr_Bonny : public CharacterBase
{
public:
	Chr_Bonny(int center_position_x, int center_position_y, int &player_health, int unique_object_ID, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::pair<std::string, int> &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			22, // Boss health
			"BONNY", // name
			"resources\\bonny_neutral.png", // Neutral Expression (Image Location/Name)
			"resources\\bonny_angry.png", // Angry Expression (Image Location/Name)
			"resources\\bonny_happy.png",
			"resources\\bonny_nervous_dead.png"
		),//*/

		  /* Sets the sprite ascii for the NPC world sprite */
		WorldSprite world_sprite = WorldSprite(
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
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 1) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

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
		AttackPatternBase *attack_pattern_1;
		attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 5, 1);
		AttackPatternBase *attack_pattern_2;
		attack_pattern_2 = new Explode_Slow(screen_width, screen_height, matrix_display, player_health, 200);
		AttackPatternBase *attack_pattern_3;
		attack_pattern_3 = new Explode_Slowest(screen_width, screen_height, matrix_display, player_health, 50);
		AttackPatternBase *attack_pattern_4;
		attack_pattern_4 = new AttackPattern_ShootHorizontal(screen_width, screen_height, matrix_display, player_health, 10);
		AttackPatternBase *attack_pattern_5;
		attack_pattern_5 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, matrix_display, player_health, 10); //50
		AttackPatternBase *attack_pattern_6;
		attack_pattern_6 = new VerticleGap_VerySlow(screen_width, screen_height, matrix_display, player_health);
		attack_patterns_.push_back(attack_pattern_2);
		attack_patterns_.push_back(attack_pattern_3);
		attack_patterns_.push_back(attack_pattern_2);
		attack_patterns_.push_back(attack_pattern_1);
		attack_patterns_.push_back(attack_pattern_5);
		attack_patterns_.push_back(attack_pattern_3);
		attack_patterns_.push_back(attack_pattern_4);
		attack_patterns_.push_back(attack_pattern_5);
		attack_patterns_.push_back(attack_pattern_6);//*/
	}

	/* Advanced Dialog	(Shows multiple text screens with dialog options. Leave BLANK for minor characters) */
	void setDialogNodes()
	{
		Item sword("an ok sword", 1);

		/* ACTIONS (Mini-Tutorial)
		*	"FIGHT"		Will start a battle with the NPC
		*	item		Including an Item will have the NPC give the player the provided item
		*	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		*				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		*/

		// CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "AHOOOYY THERE ZNever seen you 'round the sea before?Z");
		DialogNode *node_1_1 = new DialogNode("Whats your name?", "Bonny good ol'mate");
		DialogNode *node_1_2 = new DialogNode("Where am I?Z", "Tis the pirate faction,Z ya with ya kindZ");
		DialogNode *node_1_3 = new DialogNode("Goodbye", "Sea ya around matey!");
		DialogNode *node_1_1_1 = new DialogNode("Bonny. You mean theZ cowardly pirate Bonny?", "COWARDLY?! I'll show yaZ who is cowardly!", "FIGHT");
		DialogNode *node_1_1_2 = new DialogNode("Were you just at border control?", "I was jus' thar!Z");
		DialogNode *node_1_1_3 = new DialogNode("Is this you feather?", "Maybe, looks likeZ me dead birdie's.Z");
		DialogNode *node_1_1_2_1 = new DialogNode("What were you doing at there?Z", "Are ye stupid?Z Tryin' 't get me new home.Z"); //add add add ad  ad d
		DialogNode *node_1_1_3_1 = new DialogNode("I found this near the entrance.Z", "'Twas hectic thar, dropped few thin'sZ loot few thin'sZ");
		DialogNode *node_1_1_3_1_1 = new DialogNode("\"Loot?\" It was you wasn't it?", "YARR! I'm nah lookin' fer a fight!", "FIGHT");
		DialogNode *node_1_1_3_1_2 = new DialogNode("Did you take anythingZ that wasn't yours?Z", "Nah matey, only me things.Z What's troublin' ya?Z");
		DialogNode *node_1_1_3_1_2_1 = new DialogNode("Something important was stolenZ at the border.Z", "yarr..how sad. Do yaZ know who done it?Z");
		DialogNode *node_1_1_3_1_2_1_1 = new DialogNode("....it was YOU!Z", "YAAAAAARRGGG Z");
		DialogNode *node_1_1_3_1_2_1_2 = new DialogNode("No I don't, but Z I have to find them.Z", "Here, let me help ye.Z", sword);

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);
		node_1_1->setChoice3(node_1_1_3);

		node_1_2->setChoice1(node_1_1_2);
		node_1_2->setChoice2(node_1_1_3);

		node_1_1_2->setChoice1(node_1_1_2_1);

		node_1_1_3->setChoice1(node_1_1_3_1);
		
		node_1_1_3_1->setChoice1(node_1_1_3_1_1);
		node_1_1_3_1->setChoice1(node_1_1_3_1_2);

		node_1_1_3_1_2->setChoice1(node_1_1_3_1_2_1);
	
		node_1_1_3_1_2_1->setChoice1(node_1_1_3_1_2_1_1);
		node_1_1_3_1_2_1->setChoice1(node_1_1_3_1_2_1_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_BONNY_H

