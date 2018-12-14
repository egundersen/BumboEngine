#include "CharacterBase.h"
#include <string>

#ifndef CHR_AKIFINAL_H
#define CHR_AKIFINAL_H

class Chr_AkiFinal : public CharacterBase
{
public:
	Chr_AkiFinal(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, int &player_health, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::tuple<std::string, int, int> &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! hello ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			22,
			"AKI (INSANE)", 
			"aki_insane_neutral_happy.bmp", 
			"aki_mad.bmp", 
			"aki_angry_neutral.bmp",
			"aki_insane_nervous_dead.bmp"
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 9) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Why did you do this?! ", "HOW STUPID OF YOU", false));
		dialog_choice_1.push_back(std::make_tuple("You will pay for this! ", "WHO DO YOU THINK I AM", false));
		dialog_choice_1.push_back(std::make_tuple("Stop this! ", "AHHHHHAHAHAHHA", true));
		dialog_choice_1.push_back(std::make_tuple("You're no magical girl! ", "IT WAS ALL AND ACT", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("What's your motive?! ", "TO GET RID YOU", false));
		dialog_choice_2.push_back(std::make_tuple("Who are you really?? ", "AKI, STUUPID", false));
		dialog_choice_2.push_back(std::make_tuple("Did you plan this from the start! ", "THAT'S A SEECRET", false));
		dialog_choice_2.push_back(std::make_tuple("I will defeat you! ", "TRY ME!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("THIS IS YOUR END ", "I WILL HAUNT YOU", true));
		dialog_choice_3.push_back(std::make_tuple("You will be defeated! ", "HAHAHAHA IDIOT", false));
		dialog_choice_3.push_back(std::make_tuple("You won't get away with this! ", "I WILL", false));
		dialog_choice_3.push_back(std::make_tuple("You're a fraud!!! ", "AND YOU FELL FOR IT", false));

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
			attack_pattern_1 = new VerticleGap_Wavy(screen_width, screen_height, matrix_display, player_health);
			AttackPatternBase *attack_pattern_2;
			attack_pattern_2 = new Explode_Fast(screen_width, screen_height, matrix_display, player_health, 600);
			AttackPatternBase *attack_pattern_3;
			attack_pattern_3 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 5, 1);

			AttackPatternBase *attack_pattern_4;
			attack_pattern_4 = new Explode_Slow(screen_width, screen_height, matrix_display, player_health, 200);
			AttackPatternBase *attack_pattern_13;
			attack_pattern_13 = new VerticleGap_Slow(screen_width, screen_height, matrix_display, player_health);
			AttackPatternBase *attack_pattern_5;
			attack_pattern_5 = new AttackPattern_ShootHorizontal(screen_width, screen_height, matrix_display, player_health, 30);
			AttackPatternBase *attack_pattern_6;
			attack_pattern_6 = new AttackPattern_Snake(screen_width, screen_height, matrix_display, player_health, 1);
			AttackPatternBase *attack_pattern_7;
			attack_pattern_7 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 3, 1);

			AttackPatternBase *attack_pattern_8;
			attack_pattern_8 = new Explode_Slowest(screen_width, screen_height, matrix_display, player_health, 50);
			AttackPatternBase *attack_pattern_9;
			attack_pattern_9 = new AttackPattern_Snake(screen_width, screen_height, matrix_display, player_health, 4);
			AttackPatternBase *attack_pattern_10;
			attack_pattern_10 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 1, 1);
			AttackPatternBase *attack_pattern_11;
			attack_pattern_11 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, matrix_display, player_health, 30);

			AttackPatternBase *attack_pattern_12;
			attack_pattern_12 = new VerticleGap_VerySlow(screen_width, screen_height, matrix_display, player_health);

			attack_patterns_.push_back(attack_pattern_13);
			attack_patterns_.push_back(attack_pattern_12);
			attack_patterns_.push_back(attack_pattern_11);
			attack_patterns_.push_back(attack_pattern_10);
			attack_patterns_.push_back(attack_pattern_9);
			attack_patterns_.push_back(attack_pattern_8);
			attack_patterns_.push_back(attack_pattern_7);
			attack_patterns_.push_back(attack_pattern_6);
			attack_patterns_.push_back(attack_pattern_5);
			attack_patterns_.push_back(attack_pattern_4);
			attack_patterns_.push_back(attack_pattern_3);
			attack_patterns_.push_back(attack_pattern_2);
			attack_patterns_.push_back(attack_pattern_1);
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
		DialogNode *node_1 = new DialogNode("", "ha...ha...ha.");
		DialogNode *node_1_1 = new DialogNode("Aki??", "hee hehehe");
		DialogNode *node_1_2 = new DialogNode("It was you...", "hmm? Was it?");
		DialogNode *node_1_3 = new DialogNode("It can't be", "oh? Z Can't be what?");

		DialogNode *node_1_1_1 = new DialogNode("How could you?", "How could I not?");
		DialogNode *node_1_1_2 = new DialogNode("But you wanted to help.", "Help a pirate? Z I would never.");

		DialogNode *node_1_1_1_1 = new DialogNode("I trusted you.", "I would never trust Z a pirate.");

		DialogNode *node_1_1_2_1 = new DialogNode("Give it back...", "This dirty thing? Z Ha, too bad");

		DialogNode *node_1_1_2_1_1 = new DialogNode("tell why", "ENOUGH! You. Z Die. Here.", "FIGHT");


		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);

		node_1_2->setChoice1(node_1_1_1);
		node_1_2->setChoice2(node_1_1_2);

		node_1_3->setChoice1(node_1_1_1);
		node_1_3->setChoice2(node_1_1_2);

		node_1_1_1->setChoice1(node_1_1_1_1);
		node_1_1_1->setChoice2(node_1_1_2_1);
		node_1_1_2->setChoice1(node_1_1_1_1);
		node_1_1_2->setChoice2(node_1_1_2_1);

		node_1_1_1_1->setChoice1(node_1_1_2_1_1);
		node_1_1_2_1->setChoice1(node_1_1_2_1_1);



		setHeadNode(node_1);
	}
};

#endif // !CHR_AKIFINAL_H




