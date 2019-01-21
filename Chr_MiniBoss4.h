#ifndef CHR_MINIBOSS4_H
#define CHR_MINIBOSS4_H

#include "CharacterBase.h"

class Chr_MiniBoss4 : public CharacterBase
{
public:
	Chr_MiniBoss4(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,  Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
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
			"mini_boss_4",
			"",
			133, 
			131, 
			133,
			132
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 0) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player, boss_fight_definition, attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("I'm sick of this ", "Stop complainin'", false));
		dialog_choice_1.push_back(std::make_tuple("I will kick you dead ", "you are too weak", false));
		dialog_choice_1.push_back(std::make_tuple("GO HOME ", "I got business to do", true));
		dialog_choice_1.push_back(std::make_tuple("This feels pointless ", "Yar stupid", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("Why are you after me ", "For ye tresure", false));
		dialog_choice_2.push_back(std::make_tuple("Want do you want ", "Ye valuables", false));
		dialog_choice_2.push_back(std::make_tuple("You will regret fighting me ", "I will not", false));
		dialog_choice_2.push_back(std::make_tuple("just go home ", "I cannot", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("JUST GO HOME ", "BEAT ME MATEY", true));
		dialog_choice_3.push_back(std::make_tuple("Who's your boss? ", "That's confidential", false));
		dialog_choice_3.push_back(std::make_tuple("Can you stop? ", "NO", false));
		dialog_choice_3.push_back(std::make_tuple("I WILL KILL YOU ", "*gulp*", false));

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
		AttackPatternBase *attack_pattern_1;
		attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 10, 5, 1, 1);
		AttackPatternBase *attack_pattern_2;
		attack_pattern_2 = new Explode_Slow(screen_width, screen_height, screen_matrix, player, 200);
		AttackPatternBase *attack_pattern_3;
		attack_pattern_3 = new Explode_Slowest(screen_width, screen_height, screen_matrix, player, 50);
		AttackPatternBase *attack_pattern_4;
		attack_pattern_4 = new AttackPattern_ShootHorizontal(screen_width, screen_height, screen_matrix, player, 10);
		AttackPatternBase *attack_pattern_5;
		attack_pattern_5 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, screen_matrix, player, 10); //50
		AttackPatternBase *attack_pattern_6;
		attack_pattern_6 = new VerticleGap_VerySlow(screen_width, screen_height, screen_matrix, player);
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
		Item health_potion("Bottle o' syrup", 1);

		/* ACTIONS (Mini-Tutorial)
		 *	"FIGHT"		Will start a battle with the NPC
		 *	item		Including an Item will have the NPC give the player the provided item
		 *	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		 *				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		 */

		 // CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "ARRG YOU THERE");
		DialogNode *node_1_1 = new DialogNode("LET'S JUST GET THIS OVER WITH", "ARGGGHHHH", "FIGHT");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);


		setHeadNode(node_1);
	}
};

#endif // !CHR_MINIBOSS4_H
