#include "CharacterBase.h"
#include <string>

#ifndef CHR_SHARKTOOTH_H
#define CHR_SHARKTOOTH_H

class Chr_Sharktooth : public CharacterBase
{
public:
	Chr_Sharktooth(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, char direction, int &player_health, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			8,
			"SHARKTOOTH", 
			"sharktooth_neutral.bmp", 
			"sharktooth_angry.bmp",
			"sharktooth_happy.bmp",
			"sharktooth_nervous_dead.bmp"
		),//*/

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 2) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Where be me package!?", "WE'D BE HERE FOR MONTHS IF I HAD TO LIST EVERY PACKAGE A SMUGGLED", true));
		dialog_choice_1.push_back(std::make_tuple("Be this EZ mode?", "I HATE OVERWATCH REFERENCES- IF ANYTHING, D.VA's THE WORST! ! !", false));
		dialog_choice_1.push_back(std::make_tuple("I shall prove that ye be weak! ", "YOU DON'T SCARE ME, HERO!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("By 'smuggled', ye mean stolen, right?", "WELL I DON'T RECKON IT BE LEGAL!", false));
		dialog_choice_2.push_back(std::make_tuple("Did ye pickpocket me?", "pickpocket... do ye take me fer some PETTY THIEF?", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("Oh... well I guess ye're innocent...", "AND!? I'M STILL GOING TO KILL YOU!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_4;
		dialog_choice_4.push_back(std::make_tuple("Wait, ye don't wanna do this!", "OH BUT I DO", false));
		dialog_choice_4.push_back(std::make_tuple("Then I shall end ye!", "GOOD LUCK", false));
		dialog_choice_4.push_back(std::make_tuple("'ave any interest in booty?", "GO HEAD, KEEP WASTING YOUR TIME CHATTING WITH THE INEVITABLE!", false));
		dialog_choice_4.push_back(std::make_tuple("See if I care...", "THATS THE KIND OF NON-CARING ATTITUDE I LIKE TO SEE!!", true)); // 2=

		dialog_choices_.push_back(dialog_choice_1);
		dialog_choices_.push_back(dialog_choice_2);
		dialog_choices_.push_back(dialog_choice_3);
		dialog_choices_.push_back(dialog_choice_4);

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
	void initializeAttackPatterns(int screen_width, int screen_height, Matrix &screen_matrix, int &player_health)
	{
		for (int i = 0; i < 6; i++)
		{
			AttackPatternBase *attack_pattern_1;
			attack_pattern_1 = new Explode_Fast(screen_width, screen_height, screen_matrix, player_health, 200);
			AttackPatternBase *attack_pattern_2;
			attack_pattern_2 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player_health, 10, 3, 35);
			AttackPatternBase *attack_pattern_3;
			attack_pattern_3 = new VerticleGap_Slow(screen_width, screen_height, screen_matrix, player_health);
			AttackPatternBase *attack_pattern_4;
			attack_pattern_4 = new AttackPattern_ShootHorizontal(screen_width, screen_height, screen_matrix, player_health, 20);
			AttackPatternBase *attack_pattern_5;
			attack_pattern_5 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player_health);
			attack_patterns_.push_back(attack_pattern_1);
			attack_patterns_.push_back(attack_pattern_2);
			attack_patterns_.push_back(attack_pattern_3);
			attack_patterns_.push_back(attack_pattern_4);
			attack_patterns_.push_back(attack_pattern_5);
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
		DialogNode *node_1 = new DialogNode("", "AAAARRRGGGHGH! WHOOOO STEPSON ME TERRITORY?");
		DialogNode *node_1_1 = new DialogNode("Whats yer name?", "MEEEEE NAME BE S-H-A-R-K T-O-O-T-H.");
		DialogNode *node_1_1_1 = new DialogNode("O' th' Blood Sea??", "ARRRGGGG! IT IS I, SHARKTOOTH! THE NAME WHICH CASTS FEAR IN MANY A MAN.");
		DialogNode *node_1_1_1_1 = new DialogNode("Were ye at th' border?", "SO WHAT IF I WAS??"); // 1=
		DialogNode *node_1_1_1_2 = new DialogNode("Goodbye", "LEAVE ME TERRITORY!");
		DialogNode *node_1_1_2 = new DialogNode("Were ye at th' border?", "SO WHAT IF I WAS??"); // =1
		DialogNode *node_1_1_2_1 = new DialogNode("Did ye lose anythin'?", "I BE MISSIN' ME PRECIOUS CIGAR BOX.");
		DialogNode *node_1_1_2_2 = new DialogNode("Be THIS yer cigar box?", "TIS MINE ITS TRUE...AND HOW... PRAYTELL... DID. YOU. GET. THIS.?");
		DialogNode *node_1_1_2_2_1 = new DialogNode("I found it", "WELL I THANK YE FOR THAT.");
		DialogNode *node_1_1_2_2_1_1 = new DialogNode("Regardin' th' border...", "WHAT ABOUT IT? SPIT IT OUT LAD! I HAVEN'T ALL DAY!");
		DialogNode *node_1_1_2_2_1_1_1 = new DialogNode("See anyone suspicious?", "E'RYONE IS SUSPICIOUS IN MY EYES  ...EVEN YA.", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2 = new DialogNode("Thars this package-", "CUT YE OFF RIGHT 'ERE. YE THINK IT WAS ME WHO STOLE IT! DON'T KNOW NOTHING ABOUT THAT ... HEH.");
		DialogNode *node_1_1_2_2_1_1_2_1 = new DialogNode("Ye did pilfer it!", "SHUT YER TRAP! I'M SICK OF YOU!", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2_2 = new DialogNode("I 'ave a suspicion...", "JUST A SUSPICION?! YE HAVEN'T THE COURAGE NOR THE BRAVERY TO FACE ME! TIME TO DIE, COWARD.");
		DialogNode *node_1_1_2_2_1_1_2_2_1 = new DialogNode("I be no yellow-bellied cur!", "FINALLY SOME APTITUDE! DIE WIT' A SWORD IN YE HAND!", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2_2_2 = new DialogNode("No, I dont wants t' fight", "WHEN WILL YE LEARN!? NO MATTER THE CHOICE YE MAKE, THIS WILL ALWAYS END THE SAME WAY!", "FIGHT");
		DialogNode *node_1_1_2_2_1_1_2_3 = new DialogNode("No, nah at all!", "YA CALLING ME A SEA BARNACLE?", "FIGHT");
		DialogNode *node_1_1_2_2_1_2 = new DialogNode("Take anythin' recently?", "ARE YE ACCUSING ME OF SOMETHING?! IF THAT BE THE CASE I'LL SEE YE 'N HELL.", "FIGHT");
		DialogNode *node_1_1_2_2_2 = new DialogNode("I plundered it", "THEN BY BALGRUFF'S BEARD I WILL END YOU!", "FIGHT");
		DialogNode *node_1_1_3 = new DialogNode("Ne'er heard o' ye...", "PERHAPS I'LL GIVE YE SOMETHING TO REMEMBER ME BY!", "FIGHT");
		DialogNode *node_1_2 = new DialogNode("Ye cant claim territory", "DOOOOOOOOON'T TELL ME WHAT TO DO !!!!!", "FIGHT");
		DialogNode *node_1_3 = new DialogNode("Goodbye...", "LEAVE ME TERRITORY!");
		DialogNode *node_2 = new DialogNode("", "PERHAPS I WAS WRONG ABOUT YE", "SAVE"); // =2
		DialogNode *node_2_1 = new DialogNode("Well-", "SHUT UP 'n GET LOST afore th' feds find me.");
		DialogNode *node_2_1_1 = new DialogNode("perhaps ye could hel-", "NOT INTERESTED.");
		DialogNode *node_2_1_2_1 = new DialogNode("Bye", "JUST GET LOST ALREADY!", "SAVE");
		DialogNode *node_2_1_2 = new DialogNode("Bye", "GET LOST!", "SAVE");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);
		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);
		node_1_1->setChoice3(node_1_1_3);
		node_1_1_1->setChoice1(node_1_1_1_1);
		node_1_1_1->setChoice2(node_1_1_1_2);

		node_1_1_2->setChoice1(node_1_1_2_1);
		node_1_1_2->setChoice2(node_1_1_2_2);
		node_1_1_2_2->setChoice1(node_1_1_2_2_1);
		node_1_1_2_2->setChoice2(node_1_1_2_2_2);
		node_1_1_2_2_1->setChoice1(node_1_1_2_2_1_1);
		node_1_1_2_2_1->setChoice2(node_1_1_2_2_1_2);
		node_1_1_2_2_1_1->setChoice1(node_1_1_2_2_1_1_1);
		node_1_1_2_2_1_1->setChoice2(node_1_1_2_2_1_1_2);
		node_1_1_2_2_1_1_2->setChoice1(node_1_1_2_2_1_1_2_1);
		node_1_1_2_2_1_1_2->setChoice2(node_1_1_2_2_1_1_2_2);
		node_1_1_2_2_1_1_2->setChoice3(node_1_1_2_2_1_1_2_3);

		node_1_1_2_2_1_1_2_2->setChoice1(node_1_1_2_2_1_1_2_2_1);
		node_1_1_2_2_1_1_2_2->setChoice2(node_1_1_2_2_1_1_2_2_2);

		node_2->setChoice1(node_2_1);
		node_2_1->setChoice1(node_2_1_1);
		node_2_1->setChoice2(node_2_1_2);
		node_2_1_1->setChoice1(node_2_1_2);

		// Seperated Links:
		node_1_1_1_1->setChoice1(node_1_1_2_1); // 1=
		node_1_1_1_1->setChoice2(node_1_1_2_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_SHARKTOOTH_H


