#include "CharacterBase.h"
#include <string>

#ifndef CHR_TUTORIALNPC
#define CHR_TUTORIALNPC

class Chr_TutorialNPC : public CharacterBase
{
public:
	Chr_TutorialNPC(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, int &player_health, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("", 'X', 23, 9),

		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			4,
			"TUTORIAL NPC", 
			"tutorial.bmp", 
			"tutorial.bmp", 
			"tutorial.bmp",
			"tutorial.bmp"
		),//*/

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 0) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Help! I move too fast!", "Just Hold SHIFT, It's very simple", false));
		dialog_choice_1.push_back(std::make_tuple("Where's my health?", "You move as a number. That is your health", false));
		dialog_choice_1.push_back(std::make_tuple("Hello, Yes?", "Look upon", false));
		dialog_choice_1.push_back(std::make_tuple("I'm finished with the combat tutorial", "Very good", true));

		dialog_choices_.push_back(dialog_choice_1);

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
	void initializeAttackPatterns(int screen_width, int screen_height, Matrix &screen_matrix, int &player_health)
	{
		for (int i = 0; i < 6; i++)
		{
			AttackPatternBase *attack_pattern_1;
			attack_pattern_1 = new AttackPattern_ShootHorizontal(screen_width, screen_height, screen_matrix, player_health, 10);
			AttackPatternBase *attack_pattern_2;
			attack_pattern_2 = new Explode_Slow(screen_width, screen_height, screen_matrix, player_health, 15);
			AttackPatternBase *attack_pattern_3;
			attack_pattern_3 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, screen_matrix, player_health, 3);

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
		DialogNode *node_1 = new DialogNode("", "Your back You need more help, yes?");
		DialogNode *node_1_1 = new DialogNode("Yes, I need more help", "This very good What you need my help with?");
		DialogNode *node_1_2 = new DialogNode("What about my father?", "Sorry, I'm not allowed to talk about that. It would upset the my lemon");
		DialogNode *node_1_3 = new DialogNode("No thanks", "Well, I will See You later then");
		DialogNode *node_1_2_1 = new DialogNode("Slowing down in combat", "Just hold SHIFT Then you will move slower");
		DialogNode *node_1_2_2 = new DialogNode("Opening my inventory", "Oh, it very easy Just press I");
		DialogNode *node_1_2_3 = new DialogNode("Other hotkeys?", "Let's see... BACKSPACE is usually exit what you're doing something");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);
		node_1_1->setChoice1(node_1_2_1);
		node_1_1->setChoice2(node_1_2_2);
		node_1_1->setChoice3(node_1_2_3);

		setHeadNode(node_1);
	}
};

#endif // !CHR_TUTORIALNPC
