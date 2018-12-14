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
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! hello ", 'X', 23, 9),


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
		dialog_choice_1.push_back(std::make_tuple("I hope yer happy wit' yer fate!", "Ne'er matey!", false));
		dialog_choice_1.push_back(std::make_tuple("Admit it! Ye stole me package!", "Ye'll ne'er get me t' speak!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("This is fer th' good o' everyone!", "YAAARRRRR, I care not for others!", false));
		dialog_choice_2.push_back(std::make_tuple("Let's work this out", "No, I said I'll ne'er speak t' ya!", false));
		dialog_choice_2.push_back(std::make_tuple("I'll tell everyone yer a yellow-bellied cur! ", "Wait no! I- I smuggle packages fer Sharktooth! But I didn' plunder yer loot", true));
		dialog_choice_2.push_back(std::make_tuple("Wanna die today!?", "Wait no! I- I smuggle packages fer Sharktooth! But I didn' plunder yer loot", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("I believe ye", "Thank th' stars!!!", true)); // 5=
		dialog_choice_3.push_back(std::make_tuple("I still don't believe ye", "I' nah be lyin'!", false));

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
		DialogNode *node_1 = new DialogNode("", "AHOOOYY THERE. Ne'er seen ye 'round here afore?");
		DialogNode *node_1_1 = new DialogNode("Whats yer name?", "Bonny, me good ol'mate.");
		DialogNode *node_1_1_1 = new DialogNode("Ye mean Bonny t' Coward?", "COWARDLY?! I'll show ya who be lily-livered!", "FIGHT");
		DialogNode *node_1_1_2 = new DialogNode("Were ye at th' border?", "Come t' reckon o' it, I may 'ave passed through once or twice!"); // =3
		DialogNode *node_1_1_2_1 = new DialogNode("Wha' were ye doin'?", "Are ye squiffy? Tryin' 't find me new home: tis cave");
		DialogNode *node_1_1_2_1_1 = new DialogNode("Be this yer feather?", "Maybe, looks like me dead birdie's."); // 2=
		DialogNode *node_1_1_2_1_2 = new DialogNode("STEAL ANYTHING?", "YARR! I be not lookin' fer a fight! I didn't steal anything!"); // 1=
		DialogNode *node_1_1_3 = new DialogNode("Be this yer feather?", "Maybe, looks like me dead birdie's."); // =2
		DialogNode *node_1_1_3_1 = new DialogNode("It was at th' checkpoint", "'Twas hectic thar, dropped a few thin's... loot few thin's..."); // =4
		DialogNode *node_1_1_3_1_1 = new DialogNode("\"Loot?\" you DID steal it!", "YARR! I be nah lookin' fer a fight, but I'll defend meself!", "FIGHT");
		DialogNode *node_1_1_3_1_2 = new DialogNode("Did ye pick up anythin'?", "Nah matey, only me thin's. Wha''s troublin' ya?");
		DialogNode *node_1_1_3_1_2_1 = new DialogNode("I was pickpocketed!", "Yarr.. how sad (fer ye). Do ya know who done it?");
		DialogNode *node_1_1_3_1_2_1_1 = new DialogNode("....'twas YOU!", "YARR! I be nah lookin' fer a fight! Twas nah me!"); // =1
		DialogNode *node_1_1_3_1_2_1_1_1 = new DialogNode("Then who?", "I dunno! Maybe Sharktooth, he's a bad scallywag...");
		DialogNode *node_1_1_3_1_2_1_1_1_1 = new DialogNode("Fine, I believe ye", "Thank th' stars! 'n... perhaps I could offer somethin' as a token o' me thanks?"); // =5
		DialogNode *node_1_1_3_1_2_1_1_1_1_1 = new DialogNode("No thanks necessary", "Ye are truly a kind sort.");
		DialogNode *node_1_1_3_1_2_1_1_1_1_1_1 = new DialogNode("Goodbye", "Good luck t' ya. Goodbye matey!", "SAVE");
		DialogNode *node_1_1_3_1_2_1_1_1_1_2 = new DialogNode("Much appreciated!", "'Tis a cutlass, maybe nah th' best, but I've owned it all me life!", sword);
		DialogNode *node_1_1_3_1_2_1_1_1_1_2_1 = new DialogNode("Thank ye", "Good luck t' ya. Goodbye matey!", "SAVE");
		DialogNode *node_1_1_3_1_2_1_1_1_2 = new DialogNode("I don't believe ye", "'N wha' will ye do about it, hm?");
		DialogNode *node_1_1_3_1_2_1_1_1_2_1 = new DialogNode("I be goin' t' take it", "GET BACK! ye reckon ye can loot me!?", "FIGHT");
		DialogNode *node_1_1_3_1_2_1_1_2 = new DialogNode("Die wit' honor!", "Nooooooo!", "FIGHT");
		DialogNode *node_1_1_3_1_2_1_2 = new DialogNode("I dunno", "If I was t' offer me advise, I'd say 'twas Sharktooth.");
		DialogNode *node_1_1_3_1_2_1_2_1 = new DialogNode("Thanks fer th' tip", "Tis been a pleasure", "SAVE");
		DialogNode *node_1_1_3_1_2_1_2_2 = new DialogNode("BTW, ye stole it!", "WHAT!? Are ye accusin' me... o' lootin' from ye?", "SAVE");
		DialogNode *node_1_1_3_2 = new DialogNode("LIAR! ! !", "Wha'? Tis true, I cried fer hours!");
		DialogNode *node_1_1_3_2_1 = new DialogNode("I believe ye", "Thats good t' hear... but where did ye find me feather?");
		DialogNode *node_1_1_3_2_1_1 = new DialogNode("'twas at th' checkpoint", "'Oh, I supposed it twas hectic thar, dropped a few thin's... loot few thin's..."); // 4=
		DialogNode *node_1_1_3_2_2 = new DialogNode("No, ye bought it!", "Shhhh! Yeah I bought th' feather, I was too scared t' own a parrot. Where did ye find it?");
		DialogNode *node_1_1_3_2_2_1 = new DialogNode("'twas at th' checkpoint", "'Oh, I supposed it twas hectic thar, dropped a few thin's... loot few thin's..."); // 4=
		DialogNode *node_1_2 = new DialogNode("Where am I?", "Where am I? Tis th' pirate faction's side o' th' cave, ya wit' ya own kind");
		DialogNode *node_1_2_1 = new DialogNode("Were ye at th' border?", "Come t' reckon o' it, I may 'ave passed through once or twice!"); // 3=
		DialogNode *node_1_2_2 = new DialogNode("Goodbye", "Sea ya around matey!");
		DialogNode *node_1_3 = new DialogNode("Goodbye", "Sea ya around matey!");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);
		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);
		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);
		node_1_1->setChoice3(node_1_1_3);
		node_1_1_2->setChoice1(node_1_1_2_1);
		node_1_1_2_1->setChoice1(node_1_1_2_1_1);
		node_1_1_2_1->setChoice2(node_1_1_2_1_2);

		node_1_1_3->setChoice1(node_1_1_3_1);
		node_1_1_3->setChoice2(node_1_1_3_2);
		node_1_1_3_2->setChoice1(node_1_1_3_2_1);
		node_1_1_3_2->setChoice2(node_1_1_3_2_2);
		node_1_1_3_2_1->setChoice1(node_1_1_3_2_1_1);
		node_1_1_3_2_2->setChoice1(node_1_1_3_2_2_1);

		node_1_1_3_1->setChoice1(node_1_1_3_1_1);
		node_1_1_3_1->setChoice2(node_1_1_3_1_2);
		node_1_1_3_1_2->setChoice1(node_1_1_3_1_2_1);
		node_1_1_3_1_2_1->setChoice1(node_1_1_3_1_2_1_1);
		node_1_1_3_1_2_1->setChoice2(node_1_1_3_1_2_1_2);
		node_1_1_3_1_2_1_2->setChoice1(node_1_1_3_1_2_1_2_1);
		node_1_1_3_1_2_1_2->setChoice2(node_1_1_3_1_2_1_2_2);

		node_1_1_3_1_2_1_1->setChoice1(node_1_1_3_1_2_1_1_1);
		node_1_1_3_1_2_1_1->setChoice2(node_1_1_3_1_2_1_1_2);
		node_1_1_3_1_2_1_1_1->setChoice1(node_1_1_3_1_2_1_1_1_1);
		node_1_1_3_1_2_1_1_1->setChoice2(node_1_1_3_1_2_1_1_1_2);
		node_1_1_3_1_2_1_1_1_2->setChoice1(node_1_1_3_1_2_1_1_1_2_1);

		node_1_1_3_1_2_1_1_1_1->setChoice1(node_1_1_3_1_2_1_1_1_1_1);
		node_1_1_3_1_2_1_1_1_1->setChoice2(node_1_1_3_1_2_1_1_1_1_2);
		node_1_1_3_1_2_1_1_1_1_1->setChoice1(node_1_1_3_1_2_1_1_1_1_1_1);
		node_1_1_3_1_2_1_1_1_1_2->setChoice1(node_1_1_3_1_2_1_1_1_1_2_1);

		// Seperated Links:
		node_1_1_2_1_2->setChoice1(node_1_1_3_1_2_1_1_1); // 1=
		node_1_1_2_1_2->setChoice2(node_1_1_3_1_2_1_1_2);
		node_1_1_2_1_1->setChoice1(node_1_1_3_1); // 2=
		node_1_1_2_1_1->setChoice2(node_1_1_3_2);
		node_1_2_1->setChoice1(node_1_1_2_1); // 3=
		node_1_1_3_2_1_1->setChoice1(node_1_1_3_1_1); // 4=
		node_1_1_3_2_1_1->setChoice2(node_1_1_3_1_2);
		node_1_1_3_2_2_1->setChoice1(node_1_1_3_1_1); // 4=
		node_1_1_3_2_2_1->setChoice2(node_1_1_3_1_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_BONNY_H

