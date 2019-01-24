#ifndef CHR_MINIBOSS1_H
#define CHR_MINIBOSS1_H

#include "CharacterBase.h"

// First road block on the way to the final boss
class Chr_MiniBoss1 : public CharacterBase
{
public:
	Chr_MiniBoss1(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			22,
			"Kriis",
			"Guns_n_Roses_-_Nightrain.mp3",
			124,
			122,
			122,
			123
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 10023) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player, boss_fight_definition, attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("We can talk this out", "Less chatting. More Stabbing.", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("We can talk this out", "Again, less chatting, more Stabbing.", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("We can talk this out", "Quiet!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_4;
		dialog_choice_4.push_back(std::make_tuple("We can talk this out", "...", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_5;
		dialog_choice_5.push_back(std::make_tuple("We can talk this out", "Do you mind? I'm trying TO KILL YOU!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_6;
		dialog_choice_6.push_back(std::make_tuple("We can talk this out", "...", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_7;
		dialog_choice_7.push_back(std::make_tuple("We can talk this out", "STOP SAYING THAT!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_8;
		dialog_choice_8.push_back(std::make_tuple("We can talk this out", "BE QUIET ALREADY OR I'LL...", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_9;
		dialog_choice_9.push_back(std::make_tuple("We can talk this out", "...", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_10;
		dialog_choice_10.push_back(std::make_tuple("We can talk this out", "...", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_11;
		dialog_choice_11.push_back(std::make_tuple("We can talk this out", "...", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_12;
		dialog_choice_12.push_back(std::make_tuple("We can talk this out", "FINE! It's not even worth fighting you anymore. You're just too annoying!", true));


		dialog_choices_.push_back(dialog_choice_1);
		dialog_choices_.push_back(dialog_choice_2);
		dialog_choices_.push_back(dialog_choice_3);
		dialog_choices_.push_back(dialog_choice_4);
		dialog_choices_.push_back(dialog_choice_5);
		dialog_choices_.push_back(dialog_choice_6);
		dialog_choices_.push_back(dialog_choice_7);
		dialog_choices_.push_back(dialog_choice_8);
		dialog_choices_.push_back(dialog_choice_9);
		dialog_choices_.push_back(dialog_choice_10);
		dialog_choices_.push_back(dialog_choice_11);
		dialog_choices_.push_back(dialog_choice_12);

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
		AttackPatternBase *attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 15, 40, 1000); // [EASY] SLOW
		AttackPatternBase *attack_pattern_2 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 15000, 75); // [Medium]
		AttackPatternBase *attack_pattern_3 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 3, 30, 1750); // [MEDIUM] SLOW
		AttackPatternBase *attack_pattern_4 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 2, 15000, 100); // [Medium] 2
		AttackPatternBase *attack_pattern_5 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 7, 10, 1000); // [Medium] FAST (Wide)
		AttackPatternBase *attack_pattern_6 = new AttackPattern_ShootSnake(screen_width, screen_height, screen_matrix, player, 10, 26000, 120); // [Hard]
		AttackPatternBase *attack_pattern_7 = new Explode_Fast(screen_width, screen_height, screen_matrix, player, 650); // [Medium] Fast
		AttackPatternBase *attack_pattern_8 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player); // [Hard] Wavy
		AttackPatternBase *attack_pattern_9 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 20, 9, 1, 500); // [Medium] FAST
		AttackPatternBase *attack_pattern_10 = new AttackPattern_CoordinatedStorm(screen_width, screen_height, screen_matrix, player, 75, 25, 50, 'l', 1, 'u', false, false, 0); // [Easy]
		AttackPatternBase *attack_pattern_11 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 150, 50, 'l', 1, 'u', false, false, 0); // [MEDIUM]
		AttackPatternBase *attack_pattern_12 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
		AttackPatternBase *attack_pattern_13 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 250, 20, 'd', 1, 'l', false, false, 0); // [MEDIUM] --FAST
		AttackPatternBase *attack_pattern_14 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 50, 100, 'l', 0, ' ', false, false, 0); // [MEDIUM] --SINGLECOLUMN
		AttackPatternBase *attack_pattern_15 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'd', 0, ' ', false, false, 0); // [HARD]
		AttackPatternBase *attack_pattern_16 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 150, 120, 25, 'l', 1, 'u', false, false, 0); // [HARD] --FAST
		AttackPatternBase *attack_pattern_17 = new AttackPattern_CoordinatedStorm(screen_width, screen_height, screen_matrix, player, 200, 50, 50, 'u', 1, ' ', false, false, 0); // [Medium] Symmetrical
		AttackPatternBase *attack_pattern_18 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 150, 120, 25, 'r', 1, 'd', false, false, 0); // [HARD] --FAST
		AttackPatternBase *attack_pattern_19 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 100, 30, 100, 'l', 1, 'd', false, false, 0); // [HARD] --SINGLECOLUMN
		AttackPatternBase *attack_pattern_20 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'd', 1, 'r', false, false, 0); // [HARD]
		AttackPatternBase *attack_pattern_21 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 400, 40, 250, 'r', 1, 'd', false, false, 0); // [INSANE] --SINGLECOLUMN
	
		attack_patterns_.push_back(attack_pattern_21);
		attack_patterns_.push_back(attack_pattern_20);
		attack_patterns_.push_back(attack_pattern_19);
		attack_patterns_.push_back(attack_pattern_18);
		attack_patterns_.push_back(attack_pattern_17);
		attack_patterns_.push_back(attack_pattern_16);
		attack_patterns_.push_back(attack_pattern_15);
		attack_patterns_.push_back(attack_pattern_14);
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

	/* Advanced Dialog	(Shows multiple text screens with dialog options. Leave BLANK for minor characters) */
	void setDialogNodes()
	{
		/* ACTIONS (Mini-Tutorial)
		 *	"FIGHT"		Will start a battle with the NPC
		 *	item		Including an Item will have the NPC give the player the provided item
		 *	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		 *				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		 */

		 // CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "STOP RIGHT THERE. YOU DIDN'T HONESTLY THINK IT'D BE THAT EASY, DID YOU?");
		DialogNode *node_1_1 = new DialogNode("Enough nonsense!", "I COULDN'T AGREE MORE!", "FIGHT");
		DialogNode *node_1_2 = new DialogNode("What?", "*This was written so poorly* Look, Can we just skip introductions? I'm here to kill you.");
		DialogNode *node_1_2_1 = new DialogNode("Yes", "What a relief. Let's get this over with.", "FIGHT");
		DialogNode *node_1_2_2 = new DialogNode("No", "Are you kidding me? I can't be held accountable for staying in character.");
		DialogNode *node_1_2_2_1 = new DialogNode("Ye're right", "Thank god! Now, where were we?", "FIGHT");
		DialogNode *node_1_2_2_2 = new DialogNode("No, stay in character!", "But it's soo... you know what, fine: TRAVELER, WHO ARE... ye?");
		DialogNode *node_1_2_2_2_1 = new DialogNode("Please continue", "TRAVELER, WHO ARE \"YE\" TO TRESSPASS ON THIS MOST... SACRED GROUND!");
		DialogNode *node_1_2_2_2_1_1 = new DialogNode(player_.getPlayerName(), player_.getPlayerName() + "? YOU MEAN THE LOWLY PIRATE?");
		DialogNode *node_1_2_2_2_1_1_1 = new DialogNode("Aye", "YOU HAVE TRAVELED FAR AND WIDE... BUT YOUR JOURNEY ENDS HERE.");
		DialogNode *node_1_2_2_2_1_1_1_1 = new DialogNode("Ok", "FOR IT IS I, THE ILUSTRIO... Ok. F*ck this. You win. GG.", "EVENT");
		DialogNode *node_2 = new DialogNode("", "I honestly hope \"We can talk this out.\" is written on your tombstone!", "SAVE"); // =FIGHT
		DialogNode *node_2_1 = new DialogNode("Now let me past!", "...", "EVENT");


		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);
		node_1_2_2->setChoice1(node_1_2_2_1);
		node_1_2_2->setChoice2(node_1_2_2_2);

		node_1_2_2_2->setChoice1(node_1_2_2_2_1);
		node_1_2_2_2_1->setChoice1(node_1_2_2_2_1_1);
		node_1_2_2_2_1_1->setChoice1(node_1_2_2_2_1_1_1);
		node_1_2_2_2_1_1_1->setChoice1(node_1_2_2_2_1_1_1_1);

		node_2->setChoice1(node_2_1);

		// Seperated Links:
		node_1_1->setChoice1(node_2); // FIGHT
		node_1_2_1->setChoice1(node_2);
		node_1_2_2_1->setChoice1(node_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_MINIBOSS1_H
