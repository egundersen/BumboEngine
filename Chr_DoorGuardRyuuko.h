#ifndef CHR_DOORGUARDRYUUKO_H
#define CHR_DOORGUARDRYUUKO_H

#include "CharacterBase.h"

class Chr_DoorGuardRyuuko : public CharacterBase
{
public:
	Chr_DoorGuardRyuuko(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, BattleSprite battle_sprite, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
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
				9, // boss health
				40, // his smile/eyes (overlay) offset X position
				20, // his smile/eyes (overlay) offset Y position
				"Door Guard",
				"Pink_Floyd_-_Another_Brick_in_the_Wall.mp3",
				battle_sprite.getFace(),
				battle_sprite.getOverlay()
			), attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("I loot it back!", "Th' damage be done!", false));
		dialog_choice_1.push_back(std::make_tuple("That was a compliment", "What kind of compliment is \"Wha' are ye, 7?\"", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("You know what they say about 7", "What?", true));
		dialog_choice_2.push_back(std::make_tuple("7 is a lucky number", "Where I come from it's not!", false));
		dialog_choice_2.push_back(std::make_tuple("A very clever one!", "Well, I think it's stupid!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("Let me through", "No!", true));
		dialog_choice_3.push_back(std::make_tuple("'tis greater than 6", "I guess ye do make an excellent point", true)); // 1=
		dialog_choice_3.push_back(std::make_tuple("So stop blockin' th' door", "No!", false));

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
		for (int i = 0; i < 6; i++) {
			AttackPatternBase *attack_pattern_8 = new SafeSquares_Fast(screen_width, screen_height, screen_matrix, player, 8); // [Easy-Hard] Fast
			AttackPatternBase *attack_pattern_9 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player); // [Hard] Wavy
		
			attack_patterns_.push_back(attack_pattern_9);
			attack_patterns_.push_back(attack_pattern_8);
		}

		AttackPatternBase *attack_pattern_1 = new VerticleGap_Slow(screen_width, screen_height, screen_matrix, player); // [Medium] Slow
		AttackPatternBase *attack_pattern_2 = new SafeSquares_Slow(screen_width, screen_height, screen_matrix, player, 6); // [Easy-Hard] Slow
		AttackPatternBase *attack_pattern_3 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
		AttackPatternBase *attack_pattern_4 = new SafeSquares_Slow(screen_width, screen_height, screen_matrix, player, 6); // [Easy-Hard] Slow
		AttackPatternBase *attack_pattern_5 = new VerticleGap_VerySlow(screen_width, screen_height, screen_matrix, player); // [Hard] Slowest
		AttackPatternBase *attack_pattern_6 = new SafeSquares_Fast(screen_width, screen_height, screen_matrix, player, 8); // [Easy-Hard] Fast
		AttackPatternBase *attack_pattern_7 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player); // [Hard] Wavy

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
		DialogNode *node_1 = new DialogNode("", "RUP! UP! PUP! Gonna 'ave ta stop ya right thar!");
		DialogNode *node_1_1 = new DialogNode("Let me through!", "Can nah! Checkpoint guards are conductin' an investigation! Ye'll 'ave t' wait till they be finished.", "SAVE");
		DialogNode *node_1_2 = new DialogNode("Wha' are ye, 7?", "Normally I'd thrug that off, but I've had a bad day, 'n breakin' yer bones sounds thereputic!", "FIGHT");
		DialogNode *node_1_2_1 = new DialogNode("", "Thanks fer th' compliment but ye'll 'ave t' wait till they be finished.", "SAVE");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1_2->setChoice1(node_1_2_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_DOORGUARDRYUUKO_H
