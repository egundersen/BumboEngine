#ifndef CHR_SLEEPINGPIRATE_H
#define CHR_SLEEPINGPIRATE_H

#include "CharacterBase.h"

// When woken, will attack player
class Chr_SleepingPirate : public CharacterBase
{
public:
	Chr_SleepingPirate(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, BattleSprite battle_sprite, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,  Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! Hello", 'X', 23, 9),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 0) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player,
			BossFightDefinition(
				4, // boss health
				40, // his smile/eyes (overlay) offset X position
				20, // his smile/eyes (overlay) offset Y position
				"Sleeping Pirate",
				"Pink_Floyd_-_Another_Brick_in_the_Wall.mp3",
				battle_sprite.getFace(),
				battle_sprite.getOverlay()
			), attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Sorry fer wakin' ye", "I don't needs no apology!", false));
		dialog_choice_1.push_back(std::make_tuple("Visit th' border?", "I've been sleepin' here fer two days!", false));
		dialog_choice_1.push_back(std::make_tuple("I don't 'ave time fer this!", "Neither do I!", true));

		dialog_choices_.push_back(dialog_choice_1);

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
		for (int i = 0; i < 3; i++) {
			AttackPatternBase *attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 15, 40, 1000); // [EASY] SLOW
			AttackPatternBase *attack_pattern_2 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'l', 0, ' ', false, false, 0); // [Easy] L
			AttackPatternBase *attack_pattern_3 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 15, 10, 500); // [EASY] FAST
			AttackPatternBase *attack_pattern_4 = new SafeSquares_Fast_Easy(screen_width, screen_height, screen_matrix, player, 4); // [EASY]
			AttackPatternBase *attack_pattern_5 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 3, 30, 1750); // [MEDIUM] SLOW
			AttackPatternBase *attack_pattern_6 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 60, 300, 50, 'u', 0, ' ', false, false, 0); // [Easy] U

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
		/* ACTIONS (Mini-Tutorial)
		*	"FIGHT"		Will start a battle with the NPC
		*	item		Including an Item will have the NPC give the player the provided item
		*	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		*				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		*/

		// CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "Zzzzzz...");
		DialogNode *node_1_1 = new DialogNode("WAKE!", "! ! !", "FIGHT");
			DialogNode *node_1_1_1 = new DialogNode("", "Arrr... Just le' me sleep...", "SAVE");
		DialogNode *node_1_2 = new DialogNode("Do nothing", "Zzzzzz...");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1_1->setChoice1(node_1_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_SLEEPINGPIRATE_H
