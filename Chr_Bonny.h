#include "CharacterBase.h"
#include <string>

#ifndef CHR_BONNY_H
#define CHR_BONNY_H

class Chr_Bonny : public CharacterBase
{
public:
	Chr_Bonny(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, int &player_health, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::pair<std::string, int> &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			6,
			"BONNY", 
			"bonny_neutral.bmp", 
			"bonny_angry.bmp", 
			"bonny_happy.bmp",
			"bonny_nervous_dead.bmp"
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 1) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Are you ready to fight?                ", "Never matey!", false));
		dialog_choice_1.push_back(std::make_tuple("Prepared to die?                         ", "Rather live!", false));
		dialog_choice_1.push_back(std::make_tuple("Now were you the one who took it?       ", "'Course not!", true));
		dialog_choice_1.push_back(std::make_tuple("This is your end                       ", "Matey, no!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("There are holes in your testimony!        ", "YAAARRRRR", false));
		dialog_choice_2.push_back(std::make_tuple("Why would you steal?                      ", "I didn' do it!", false));
		dialog_choice_2.push_back(std::make_tuple("Let's fight fair and square!              ", "No fighin'!", false));
		dialog_choice_2.push_back(std::make_tuple("Would you like to fight?                  ", "Noo matey!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("I guess it's not you...                 ", "No more!", true));
		dialog_choice_3.push_back(std::make_tuple("Final words!                           ", "Wasn' mee!!!", false));
		dialog_choice_3.push_back(std::make_tuple("You are so bad at lying.                ", "I' a not lyin'!", false));
		dialog_choice_3.push_back(std::make_tuple("Coward!                                   ", "Yes I know!", false));

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
		//for (int i = 0; i < 6; i++)
		//{
			AttackPatternBase *attack_pattern_1;
			attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 5, 35);
			AttackPatternBase *attack_pattern_2;
			attack_pattern_2 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, matrix_display, player_health, 50);
			AttackPatternBase *attack_pattern_3;
			attack_pattern_3 = new VerticleGap_VerySlow(screen_width, screen_height, matrix_display, player_health);
			AttackPatternBase *attack_pattern_4;
			attack_pattern_4 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 4, 1);
			attack_patterns_.push_back(attack_pattern_1);
			attack_patterns_.push_back(attack_pattern_2);
			attack_patterns_.push_back(attack_pattern_3);
			attack_patterns_.push_back(attack_pattern_4);
		//}
	}

	/* Advanced Dialog	(Shows multiple text screens with dialog options. Leave BLANK for minor characters) */
	void setDialogNodes()
	{
		Item sword("An 'ok' sword", "WEAPON", 7, "Looks like something you'd get for 5 bucks on a street corner. Do x7 damage for one attack");

		/* ACTIONS (Mini-Tutorial)
		*	"FIGHT"		Will start a battle with the NPC
		*	item		Including an Item will have the NPC give the player the provided item
		*	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		*				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		*/

		// CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "AHOOOYY THERE ZNever seen you Z'round the sea before?Z");
		DialogNode *node_1_1 = new DialogNode("Whats your name?", "Bonny good ol'mate");
		DialogNode *node_1_2 = new DialogNode("Where am I?", "Tis the pirate faction,Z ya with ya kindZ");
		DialogNode *node_1_3 = new DialogNode("Goodbye", "Sea ya around matey!");
		DialogNode *node_1_1_1 = new DialogNode("You mean cowardly Bonny?", "COWARDLY?!Z I'll show ya whoZ is cowardly!", "FIGHT");
		DialogNode *node_1_1_2 = new DialogNode("Were you at the border?", "I was jus' thar!");
		DialogNode *node_1_1_3 = new DialogNode("Is this your feather?", "Maybe, looks likeZ me dead birdie's.");
		DialogNode *node_1_1_2_1 = new DialogNode("What were you doing?", "Are ye stupid?Z Tryin' Z't get me new home.Z"); //add add add ad  ad d
		DialogNode *node_1_1_3_1 = new DialogNode("It was at the entrance.", "'Twas hectic thar,Z dropped few thin'sZ loot few thin's");
		DialogNode *node_1_1_3_1_1 = new DialogNode("\"Loot?\" It was you!", "YARR! I'm nah lookin'Z fer a fight!", "FIGHT");
		DialogNode *node_1_1_3_1_2 = new DialogNode("Did you pick up anytihng?", "Nah matey,Z only me things.Z What's troublin' ya?");
		DialogNode *node_1_1_3_1_2_1 = new DialogNode("I got my thing stolen!", "yarr..how sad.Z Do ya know who doneZ it?");
		DialogNode *node_1_1_3_1_2_1_1 = new DialogNode("....it was YOU!", "YAAAAAARRGGG");
		DialogNode *node_1_1_3_1_2_1_2 = new DialogNode("I have to find who.", "Here,Z let me help ye.", sword);
		DialogNode *node_1_1_3_1_2_1_2_1 = new DialogNode("Woah! Thank you", "Good luck to ya.ZGoodbye matey!", "SAVE");

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
		
		node_1_1_2_1->setChoice1(node_1_1_3);

		node_1_1_3_1->setChoice1(node_1_1_3_1_1);
		node_1_1_3_1->setChoice2(node_1_1_3_1_2);

		node_1_1_3_1_2->setChoice1(node_1_1_3_1_2_1);
	
		node_1_1_3_1_2_1->setChoice1(node_1_1_3_1_2_1_1);
		node_1_1_3_1_2_1->setChoice2(node_1_1_3_1_2_1_2);

		node_1_1_3_1_2_1_2->setChoice1(node_1_1_3_1_2_1_2_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_BONNY_H

