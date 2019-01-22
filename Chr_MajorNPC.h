#ifndef CHR_MAJORNPC_H
#define CHR_MAJORNPC_H

#include "CharacterBase.h"

class Chr_MajorNPC : public CharacterBase
{
public:
	Chr_MajorNPC(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! Hello", 'X', 23, 9),

		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			5,
			"Major NPC",
			"Bee_Gees_-_Stayin_Alive.mp3",
			121,
			121,
			121,
			121
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 0) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player, boss_fight_definition, attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

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
				throw "dialog_choice size must not be greater than 4! There can only be 4 dialog options at a time";
#endif
	}

	/* Creates all attacks */
	void initializeAttackPatterns(int screen_width, int screen_height, Matrix &screen_matrix, PlayerDefinition &player)
	{
		AttackPatternBase *attack_pattern_1 = new SafeSquares_Slow(screen_width, screen_height, screen_matrix, player, 6); // [Easy-Hard] Slowest

		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 400, 50, 100, 'l', 1, 'd', true, true, 200);
		//attack_pattern_1 = new AttackPattern_CoordinatedStorm(screen_width, screen_height, screen_matrix, player, 400, 50, 100, 'l', 1, 'd', false, false, 1000);
		//attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 15000, 75); // [Medium]
		//attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 25000, 50); // [Hard]
		//attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 45000, 100); // [INSANE] Long
		//attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 2, 15000, 75); // [Medium] 2
		//attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 2, 20000, 50); // [Medium] 2
		//attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 3, 15000, 75); // [Hard] 3
		//attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 5, 25000, 100); // [INSANE] 5
		//attack_pattern_1 = new AttackPattern_ShootSnake(screen_width, screen_height, screen_matrix, player, 10, 13000, 50); // [Hard]
		//attack_pattern_1 = new AttackPattern_ShootSnake(screen_width, screen_height, screen_matrix, player, 36, 30000, 100); // [INSANE] Long

		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 15, 40, 1000); // [EASY] SLOW
		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 15, 10, 500); // [EASY] FAST
		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 3, 30, 1750); // [MEDIUM] SLOW
		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 1, 28, 1750); // [Hard] SLOW
		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 7, 10, 1000); // [Medium] FAST (Wide)
		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 20, 9, 1, 500); // [Medium] FAST
		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 28, 19, 1, 350); // [Hard] FAST
		//attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 10, 7, 100, 800); // [Hard] CLUMP

		//attack_pattern_1 = new Explode_Fast(screen_width, screen_height, screen_matrix, player, 650); // [Medium] Fast
		//attack_pattern_1 = new Explode_Slow(screen_width, screen_height, screen_matrix, player, 300); // [Medium] Slow
		//attack_pattern_1 = new Explode_Slow(screen_width, screen_height, screen_matrix, player, 75); // [Easy] Slow
		//attack_pattern_1 = new Explode_Slowest(screen_width, screen_height, screen_matrix, player, 100); // [Hard] Slowest
		//attack_pattern_1 = new Explode_Slowest(screen_width, screen_height, screen_matrix, player, 25); // [Easy] Slowest
		//attack_pattern_1 = new ShootExplode_Fast(screen_width, screen_height, screen_matrix, player, 50); // [Hard]


		//attack_pattern_1 = new SafeSquares_Fast_Easy(screen_width, screen_height, screen_matrix, player, 4); // [EASY]
		//attack_pattern_1 = new SafeSquares_Fast(screen_width, screen_height, screen_matrix, player, 8); // [Easy-Hard] Fast
		//attack_pattern_1 = new SafeSquares_Slow(screen_width, screen_height, screen_matrix, player, 6); // [Easy-Hard] Slow
		//attack_pattern_1 = new SafeSquares_Slow(screen_width, screen_height, screen_matrix, player, 6); // [Easy-Hard] Slowest

		//attack_pattern_1 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
		//attack_pattern_1 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player); // [Hard] Wavy
		//attack_pattern_1 = new VerticleGap_Slow(screen_width, screen_height, screen_matrix, player); // [Medium] Slow
		//attack_pattern_1 = new VerticleGap_VerySlow(screen_width, screen_height, screen_matrix, player); // [Hard] Slowest

		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'r', 1, 'd', false, false, 0); // [EASY]
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 350, 10, 'r', 1, 'd', false, false, 0); // [EASY] --FAST
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 50, 100, 'r', 1, 'd', false, false, 0); // [EASY] --SINGLECOLUMN
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 150, 50, 'r', 1, 'd', false, false, 0); // [MEDIUM]
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 250, 10, 'r', 1, 'd', false, false, 0); // [MEDIUM] --FAST
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 50, 100, 'r', 1, 'd', false, false, 0); // [MEDIUM] --SINGLECOLUMN
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'r', 1, 'd', false, false, 0); // [HARD]
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 150, 120, 10, 'r', 1, 'd', false, false, 0); // [HARD] --FAST
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 100, 15, 100, 'r', 1, 'd', false, false, 0); // [HARD] --SINGLECOLUMN
		//attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 400, 20, 250, 'r', 1, 'd', false, false, 0); // [INSANE] --SINGLECOLUMN

		//Freeze Fast: 200, Slow: 2000
		//Coordinated: Easy + Medium (DO NOT GO TO HARD)

		//attack_pattern_1 = new AttackPattern_CoordinatedStorm(screen_width, screen_height, screen_matrix, player, 400, 50, 100, 'l', 1, 'd', false, false, 1000); // [INSANE] Rows

		//attack_pattern_1 = new AttackPattern_SnakeHailStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'r', 1, 'd', false, false, 0, 15000, 75); // [EASY]



		/*Sleeping Pirate  --------------------------------
		attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 15, 40, 1000); // [EASY] SLOW
		attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'l', 0, ' ', false, false, 0); // [Easy] L
		attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 15, 10, 500); // [EASY] FAST
		attack_pattern_1 = new SafeSquares_Fast_Easy(screen_width, screen_height, screen_matrix, player, 4); // [EASY]
		attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 3, 30, 1750); // [MEDIUM] SLOW
		attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 60, 300, 50, 'u', 0, ' ', false, false, 0); // [Easy] U
		Bonny [Snake] 	 --------------------------------
		attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 10000, 75); // [Easy]
		GuardSharktooth	 --------------------------------
		Checkpoint Guy 	 --------------------------------

		Sharktooth [EXPL]--------------------------------
		GuardRyuuko		 --------------------------------
		Ryuuko [HAIL] 	 --------------------------------
		Aki [FREEZE] 	 --------------------------------

		MB1				 --------------------------------
		MB2				 --------------------------------
		Aki FINAL		 --------------------------------
		Thot Patrol		 --------------------------------
		*/


		attack_patterns_.push_back(attack_pattern_1);
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
		DialogNode *node_1 = new DialogNode("", "Oh hello, heh he heh fancy seeing you here");
		DialogNode *node_1_1 = new DialogNode("Whats your name?", "All MIGHT! Can you guess why?");
		DialogNode *node_1_2 = new DialogNode("Want to hear a joke?", "Sure! I love me a good joke!");
		DialogNode *node_1_3 = new DialogNode("Goodbye...", "SEE YOU LATER!");
		DialogNode *node_1_1_1 = new DialogNode("No", "You irritated me! Let's fight!!!!", "FIGHT");
		DialogNode *node_1_1_2 = new DialogNode("Because you're ALL MIGHT", "You guess it! Here, have my most valuble possession!", health_potion);
		DialogNode *node_1_1_3 = new DialogNode("*sigh* and walk away", "Hey! where are you going!!!?");
		DialogNode *node_1_2_1 = new DialogNode("Whats smiling and red?", "I dont know... What?");
		DialogNode *node_1_2_2 = new DialogNode("Too bad! ha ha ha!", "YOU DARE!!! DIE!! DIE!!! DIEE!!!", "FIGHT");
		DialogNode *node_1_2_3 = new DialogNode("YOUR EXPRESSION! get it?", "I will never speak with you again");
		DialogNode *node_1_2_1_1 = new DialogNode("YOUR FACE WHEN I BREAK IT", "...", "FIGHT");
		DialogNode *node_1_1_2_1 = new DialogNode("Goodbye", "Back again I see. Sorry, I only had the one item...", "SAVE");
		DialogNode *node_1_1_1_1 = new DialogNode("Goodbye", "I lost", "SAVE");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);
		node_1_1->setChoice3(node_1_1_3);

		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);
		node_1_2->setChoice3(node_1_2_3);

		node_1_2_1->setChoice1(node_1_2_1_1);
		node_1_1_2->setChoice1(node_1_1_2_1);
		node_1_1_1->setChoice1(node_1_1_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_MAJORNPC_H
