#include "CharacterBase.h"
#include <string>

#ifndef CHR_AKI_H
#define CHR_AKI_H

class Chr_Aki : public CharacterBase
{
public:
	Chr_Aki(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, int &player_health, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::pair<std::string, int> &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			13,
			"AKI", 
			"aki_happy_neutral.bmp",
			"aki_angry_neutral.bmp",
			"aki_happy_neutral.bmp",
			"aki_nervous.bmp"
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 4) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("You STOLE IT!              ", "Where's proof?!", false));
		dialog_choice_1.push_back(std::make_tuple("You thief!               ", "NEVER", false));
		dialog_choice_1.push_back(std::make_tuple("Was it you??               ", "Never!", true));
		dialog_choice_1.push_back(std::make_tuple("Are you ready to die??      ", "Magic lives!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("LIE!                       ", "NO!", false));
		dialog_choice_2.push_back(std::make_tuple("Untrustworthy               ", "You are!", false));
		dialog_choice_2.push_back(std::make_tuple("You're a thief!             ", "I'm not!", false));
		dialog_choice_2.push_back(std::make_tuple("You're not lying?          ", "Of course not!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("Is it true                 ", "Yes! Please no more!", true));
		dialog_choice_3.push_back(std::make_tuple("Sus from the beginning         ", "You were!", false));
		dialog_choice_3.push_back(std::make_tuple("Can't take the chances         ", "You dummy!", false));
		dialog_choice_3.push_back(std::make_tuple("Anime should die               ", "NOOOOOOOOO", false));

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
			attack_pattern_3 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 3, 25);

			AttackPatternBase *attack_pattern_4;
			attack_pattern_4 = new Explode_Slow(screen_width, screen_height, matrix_display, player_health, 200);
			AttackPatternBase *attack_pattern_13;
			attack_pattern_13 = new VerticleGap_Slow(screen_width, screen_height, matrix_display, player_health);
			AttackPatternBase *attack_pattern_5;
			attack_pattern_5 = new AttackPattern_ShootHorizontal(screen_width, screen_height, matrix_display, player_health, 30);
			AttackPatternBase *attack_pattern_6;
			attack_pattern_6 = new AttackPattern_Snake(screen_width, screen_height, matrix_display, player_health, 1);
			AttackPatternBase *attack_pattern_7;
			attack_pattern_7 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 1, 35);

			AttackPatternBase *attack_pattern_8;
			attack_pattern_8 = new Explode_Slowest(screen_width, screen_height, matrix_display, player_health, 50);
			AttackPatternBase *attack_pattern_9;
			attack_pattern_9 = new AttackPattern_Snake(screen_width, screen_height, matrix_display, player_health, 4);
			AttackPatternBase *attack_pattern_10;
			attack_pattern_10 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 3, 15);
			AttackPatternBase *attack_pattern_11;
			attack_pattern_11 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, matrix_display, player_health, 30);

			AttackPatternBase *attack_pattern_12;
			attack_pattern_12 = new VerticleGap_VerySlow(screen_width, screen_height, matrix_display, player_health);

			attack_patterns_.push_back(attack_pattern_1);
			attack_patterns_.push_back(attack_pattern_2);
			attack_patterns_.push_back(attack_pattern_3);
			attack_patterns_.push_back(attack_pattern_4);
			attack_patterns_.push_back(attack_pattern_13); // <----- This was intentional
			attack_patterns_.push_back(attack_pattern_5);
			attack_patterns_.push_back(attack_pattern_6);
			attack_patterns_.push_back(attack_pattern_7);
			attack_patterns_.push_back(attack_pattern_8);
			attack_patterns_.push_back(attack_pattern_9);
			attack_patterns_.push_back(attack_pattern_10);
			attack_patterns_.push_back(attack_pattern_11);
			attack_patterns_.push_back(attack_pattern_12);
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
		DialogNode *node_1 = new DialogNode("", "Woah! A pirate?");
		DialogNode *node_1_1 = new DialogNode("Whats your name?", "Magical Aki!");
		DialogNode *node_1_2 = new DialogNode("Could you help?", "Of course! Z I'm here to save you!Z");
		DialogNode *node_1_3 = new DialogNode("Goodbye...", "See ya!"); //-
		DialogNode *node_1_1_1 = new DialogNode("Magical?", "I'm a magical girl Z can't you tell?");
		DialogNode *node_1_1_1_1 = new DialogNode("Are you able to help?", "That's my duty! Z To help!");
		DialogNode *node_1_2_1 = new DialogNode("My flahsdive was stolen.", "Stolen? What's so Z important about that?");
		DialogNode *node_1_2_2 = new DialogNode("Is this your glove?", "Mmm, maybe. Z Where did you find it?");

		DialogNode *node_1_2_1_1 = new DialogNode("It was important", "How boring!");
		DialogNode *node_1_2_1_2 = new DialogNode("It just is!", "touchy...");
		DialogNode *node_1_2_1_3 = new DialogNode("Just help me!", "Well, an old rusty thing Z is meaningless to me. Z I might help");

		DialogNode *node_1_2_1_2_1 = new DialogNode("please, it's important...", "hm, maybe.");

		DialogNode *node_1_2_2_1 = new DialogNode("At the border", "I thought I left  Z this at my old home");
		DialogNode *node_1_2_2_1_1 = new DialogNode("Did you take my drive?", "Are you accusing me?!", "FIGHT"); //-
		DialogNode *node_1_2_2_1_2 = new DialogNode("Who took my drive?", " I don't know. Z It was chaos Z at the border.");
		DialogNode *node_1_2_2_1_3 = new DialogNode("Will you help me now?", "Now I will!");

		DialogNode *node_1_2_2_1_3_1 = new DialogNode("What happened there?", "Everyone Z wanted to get in. Z It's dangerous up there");
		DialogNode *node_1_2_2_1_3_2 = new DialogNode("Why were you there?", "Moving, what else? Z We can't live above Z anymore");

		DialogNode *node_1_2_2_1_3_2_1 = new DialogNode("So you didn't see?", "I saw nothing Z happen");
		DialogNode *node_1_2_2_1_3_2_2 = new DialogNode("Was anyone suspicious?", "Ryuuko, he's dumb Z so he might've Z accidentally dont it");

		DialogNode *node_1_2_2_1_3_2_2_1 = new DialogNode("Who else?", "*mumble* Z those disgucting pirates");
		DialogNode *node_1_2_2_1_3_2_2_1_1 = new DialogNode("huh?", "oh no! Z Ignore that!");
		DialogNode *node_1_2_2_1_3_2_2_1_2 = new DialogNode("Disgusting?", "I didn't mean that! Z here's just tension Z amoung factions");
		DialogNode *node_1_2_2_1_3_2_2_1_3 = new DialogNode("..I'm a pirate.", "I'm sorry, Z I didn't mean that");

		DialogNode *node_1_2_2_1_3_2_2_1_3_1 = new DialogNode("Well, who's sus?", "...Ryuuko, Z Bonny, and Sharktooth");

		DialogNode *node_1_2_2_1_3_2_2_1_3_1_1 = new DialogNode("Thank you!", "Magical Aki Z will always help!", "SAVE");
		DialogNode *node_1_2_2_1_3_2_2_1_3_1_2 = new DialogNode("It was you!", "How could you Z accuse Magical Aki!", "FIGHT");
		DialogNode *node_1_2_2_1_3_2_2_1_3_1_3 = new DialogNode("You're suspicious...", "hmph, Z no help from me then. Z Goodbye", "SAVE");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_1->setChoice1(node_1_1_1);

		node_1_1_1->setChoice1(node_1_1_1_1);

		node_1_1_1_1->setChoice1(node_1_2_1);
		node_1_1_1_1->setChoice2(node_1_2_2);

		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);

		node_1_2_1->setChoice1(node_1_2_1_1);
		node_1_2_1->setChoice2(node_1_2_1_2);
		node_1_2_1->setChoice3(node_1_2_1_3);

		node_1_2_1_1->setChoice1(node_1_2_1_2_1);
		node_1_2_1_2->setChoice1(node_1_2_1_2_1);

		node_1_2_1_3->setChoice1(node_1_2_2);
		node_1_2_1_2_1->setChoice1(node_1_2_2);

		node_1_2_2->setChoice1(node_1_2_2_1);

		node_1_2_2_1->setChoice1(node_1_2_2_1_1);
		node_1_2_2_1->setChoice2(node_1_2_2_1_2);
		node_1_2_2_1->setChoice3(node_1_2_2_1_3);

		node_1_2_2_1_2->setChoice1(node_1_2_2_1_3_1);
		node_1_2_2_1_2->setChoice2(node_1_2_2_1_3_2);

		node_1_2_2_1_3->setChoice1(node_1_2_2_1_3_1);
		node_1_2_2_1_3->setChoice2(node_1_2_2_1_3_2);

		node_1_2_2_1_3_1->setChoice1(node_1_2_2_1_3_2_1);
		node_1_2_2_1_3_1->setChoice2(node_1_2_2_1_3_2_2);

		node_1_2_2_1_3_2->setChoice1(node_1_2_2_1_3_2_1);
		node_1_2_2_1_3_2->setChoice2(node_1_2_2_1_3_2_2);

		node_1_2_2_1_3_2_1->setChoice1(node_1_2_2_1_3_2_2);

		node_1_2_2_1_3_2_2->setChoice1(node_1_2_2_1_3_2_2_1);

		node_1_2_2_1_3_2_2_1->setChoice1(node_1_2_2_1_3_2_2_1_1);
		node_1_2_2_1_3_2_2_1->setChoice2(node_1_2_2_1_3_2_2_1_2);
		node_1_2_2_1_3_2_2_1->setChoice3(node_1_2_2_1_3_2_2_1_3);

		node_1_2_2_1_3_2_2_1_1->setChoice1(node_1_2_2_1_3_2_2_1_3_1);
		node_1_2_2_1_3_2_2_1_2->setChoice1(node_1_2_2_1_3_2_2_1_3_1);
		node_1_2_2_1_3_2_2_1_3->setChoice1(node_1_2_2_1_3_2_2_1_3_1);

		node_1_2_2_1_3_2_2_1_3_1->setChoice1(node_1_2_2_1_3_2_2_1_3_1_1);
		node_1_2_2_1_3_2_2_1_3_1->setChoice2(node_1_2_2_1_3_2_2_1_3_1_2);
		node_1_2_2_1_3_2_2_1_3_1->setChoice3(node_1_2_2_1_3_2_2_1_3_1_3);

		setHeadNode(node_1);
	}
};

#endif // !CHR_AKI_H



