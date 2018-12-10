#include "CharacterBase.h"
#include <string>

#ifndef CHR_RYUUKO_H
#define CHR_RYUUKO_H

class Chr_Ryuuko : public CharacterBase
{
public:
	Chr_Ryuuko(int center_position_x, int center_position_y, int &player_health, int unique_object_ID, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::pair<std::string, int> &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			11, // Boss health
			"RYUUKO", // name
			"ryuuko_neutral.bmp", // Neutral Expression (Image Location/Name)
			"ryuuko_mad.bmp", // Angry Expression (Image Location/Name)
			"ryuuko_happy.bmp",
			"ryuuko_nervous.bmp"
		),//*/

		  /* Sets the sprite ascii for the NPC world sprite */
		WorldSprite world_sprite = WorldSprite(
			"   ^^^^   Z  XXXXXX  Z   XXXX   Z O#XXXX#O ZO ######O Z   U  U   Z", // Up Moving 1
			"   ^^^^   Z  X[][]X  Z   X--X   Z O#XXXX#O ZO ######O Z   U  U   Z", // Down Moving 1
			"   ^^^^   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z", // Right Moving 1
			"   ^^^^   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z", // Left Moving 1
			"   ^^^^   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ   U  U   Z", // Up Moving 2
			"   ^^^^   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ   U  U   Z", // Down Moving 2
			"   ^^^^   Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z", // Right Moving 2
			"   ^^^^   Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z", // Left Moving 2
			"   ^^^^   Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O######O Z   U  U   Z", // Up Not Moving
			"   ^^^^   Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z   U  U   Z", // Down Not Moving
			"   ^^^^   Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z   U  U   Z", // Right Not Moving
			"   ^^^^   Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z   U  U   Z"  // Left Not Moving
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 3) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("You are no hero                    ", "You scum!", false));
		dialog_choice_1.push_back(std::make_tuple("Ryuuko the villain!                ", "You are!", false));
		dialog_choice_1.push_back(std::make_tuple("Give it back to me!                ", "I have nothing!", false));
		dialog_choice_1.push_back(std::make_tuple("How can I trust you!               ", "Believe me!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("I am your \"senpai\"!              ", "YOU ARE UNWORTHY", false));
		dialog_choice_2.push_back(std::make_tuple("Die!                              ", "A hero never dies!", false));
		dialog_choice_2.push_back(std::make_tuple("Coward!                           ", "You're the coward.", false));
		dialog_choice_2.push_back(std::make_tuple("Prove your trust!                 ", "Search me!!!!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("I might be in the wrong here         ", "I never steal.", true));
		dialog_choice_3.push_back(std::make_tuple("OBJECTION                         ", "GYAAA", false));
		dialog_choice_3.push_back(std::make_tuple("Today is the fall of Ryuuko!       ", "NOOOOOOO", false));
		dialog_choice_3.push_back(std::make_tuple("I see why pirates hates anime now   ", "We hate pirates!", false));

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
			attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, matrix_display, player_health, 1);
			AttackPatternBase *attack_pattern_2;
			attack_pattern_2 = new Explode_Slowest(screen_width, screen_height, matrix_display, player_health, 10);
			AttackPatternBase *attack_pattern_3;
			attack_pattern_3 = new AttackPattern_Snake(screen_width, screen_height, matrix_display, player_health, 2);
			AttackPatternBase *attack_pattern_4;
			attack_pattern_4 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, matrix_display, player_health, 50);
			AttackPatternBase *attack_pattern_5;
			attack_pattern_5 = new AttackPattern_Snake(screen_width, screen_height, matrix_display, player_health, 3);
			AttackPatternBase *attack_pattern_6;
			attack_pattern_6 = new VerticleGap_Slow(screen_width, screen_height, matrix_display, player_health);

			attack_patterns_.push_back(attack_pattern_1);
			attack_patterns_.push_back(attack_pattern_2);
			attack_patterns_.push_back(attack_pattern_3);
			attack_patterns_.push_back(attack_pattern_4);
			attack_patterns_.push_back(attack_pattern_5);
			attack_patterns_.push_back(attack_pattern_6);
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
		DialogNode *node_1 = new DialogNode("", "Woah there! Z I've never seen a pirate Z here before!Z");
		DialogNode *node_1_1 = new DialogNode("Whats your name?", "The one and only Z Ryuuko!Z");
		DialogNode *node_1_2 = new DialogNode("Is this your Sword?", "Wow! Z How did you find it?!");
		DialogNode *node_1_3 = new DialogNode("Goodbye...", "Oh? leaving already?");
		DialogNode *node_1_1_1 = new DialogNode("What a weird name.", "Of course it is, Z I am THE Ryuuko!Z");
		DialogNode *node_1_2_1 = new DialogNode("There was a label", "You have to say that Z I'm pretty smart.Z");
		DialogNode *node_1_2_2 = new DialogNode("Did you pick up anything?", "Pick up something? Z...Why?");
		DialogNode *node_1_2_2_1 = new DialogNode("It was you wasn't it?!Z", "Are you challenging me?Z", "FIGHT");
		DialogNode *node_1_2_2_2 = new DialogNode("my thing was stolen.", "What did they steal?Z");
		DialogNode *node_1_2_2_2_1 = new DialogNode("...Why do you want to know?Z", "I'm just curious senpai?Z");
		DialogNode *node_1_2_2_2_2 = new DialogNode("Can I trust you?Z", "If you trust me, Z I'll trust you.Z We're in this together!Z");
		DialogNode *node_1_2_2_2_1_1 = new DialogNode("YOU TOOK IT!Z", "Hold up! Are you here Z just to fight?!", "FIGHT");
		DialogNode *node_1_2_2_2_2_1 = new DialogNode("I was an important flashdrive", "No fear! If you need me Z I'll be there!", "SAVE");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1); //amber - go back a relink
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_1->setChoice1(node_1_1_1);

		node_1_1_1->setChoice1(node_1_2);

		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);

		node_1_2_1->setChoice1(node_1_2_2);

		node_1_2_2->setChoice1(node_1_2_2_1);
		node_1_2_2->setChoice2(node_1_2_2_2);

		node_1_2_2_2->setChoice1(node_1_2_2_2_1);
		node_1_2_2_2->setChoice2(node_1_2_2_2_2);

		node_1_2_2_2_1->setChoice1(node_1_2_2_2_1_1);
		node_1_2_2_2_1->setChoice2(node_1_2_2_2_2_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_RYUUKO_H



