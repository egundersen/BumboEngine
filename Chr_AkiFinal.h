#ifndef CHR_AKIFINAL_H
#define CHR_AKIFINAL_H

#include "CharacterBase.h"

class Chr_AkiFinal : public CharacterBase
{
public:
	Chr_AkiFinal(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,  Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! hello ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			14,
			"AKI (INSANE)",
			"Peter_Schilling_-_Major_Tom.mp3",
			"aki_insane_neutral_happy.bmp", 
			"aki_mad.bmp", 
			"aki_angry_neutral.bmp",
			"aki_insane_nervous_dead.bmp"
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 10022) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player, boss_fight_definition, attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("We can talk this out", "We're long past that point...", false));

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
		AttackPatternBase *attack_pattern_1 = new AttackPattern_SnakeHailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'l', 1, 'd', true, false, 2000, 15000, 75); // [INSANE]
		AttackPatternBase *attack_pattern_2 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 150, 120, 10, 'd', 0, ' ', false, false, 0); // [HARD] --FAST
		AttackPatternBase *attack_pattern_3 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 5, 25000, 100); // [INSANE] 5
		AttackPatternBase *attack_pattern_4 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 10, 7, 100, 800); // [Hard] CLUMP
		AttackPatternBase *attack_pattern_5 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
		AttackPatternBase *attack_pattern_6 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'l', 1, 'u', true, false, 2000); // [HARD]
		AttackPatternBase *attack_pattern_7 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 400, 1, 250, 'r', 1, 'd', false, false, 0); // [INSANE] --SINGLECOLUMN
		AttackPatternBase *attack_pattern_8 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'l', 1, 'u', false, false, 0); // [HARD]
		AttackPatternBase *attack_pattern_9 = new ShootExplode_Fast(screen_width, screen_height, screen_matrix, player, 50); // [Hard]
		AttackPatternBase *attack_pattern_10 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player); // [Hard] Wavy
		AttackPatternBase *attack_pattern_11 = new AttackPattern_CoordinatedStorm(screen_width, screen_height, screen_matrix, player, 400, 50, 100, 'l', 1, 'd', false, false, 1000); // [INSANE] Rows
		AttackPatternBase *attack_pattern_12 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 45000, 100); // [INSANE] Long
		AttackPatternBase *attack_pattern_13 = new AttackPattern_ShootSnake(screen_width, screen_height, screen_matrix, player, 36, 30000, 100); // [INSANE] Long
	
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
		DialogNode *node_1 = new DialogNode("", "Seriously!? You're still alive?");
		DialogNode *node_1_1 = new DialogNode("I be unstoppable!", "Gonna stop ya right there... How did you get past my roadies?"); // 4=
		DialogNode *node_1_2 = new DialogNode("You be one to talk", "Fair enough... But how did you get past my roadies?"); // =4 (Options 1 & 2)
		DialogNode *node_1_2_1 = new DialogNode("They were tough!", "Obviously not tough enough if you're still alive..."); // 1=
		DialogNode *node_1_2_2 = new DialogNode("They were a breeze", "Really? Worthless pawns... ");
		DialogNode *node_1_2_2_1 = new DialogNode("Jus' give up!", "Me? Really? But we're just getting started! Did you at least enjoy the show I put on for you?"); // =1
		DialogNode *node_1_2_2_1_1 = new DialogNode("What show?", "Don't act so innocent. I even wrote out scripts for my roadies to follow and everything.");
		DialogNode *node_1_2_2_1_1_1 = new DialogNode("I be unimpressed!", "Then I'm sorry to hear that.");
		DialogNode *node_1_2_2_1_1_1_1 = new DialogNode("Show's over! Me package!", "What package? What ABOUT a package? I don't remember any sort of package.");
		DialogNode *node_1_2_2_1_1_1_1_1 = new DialogNode("Me father's package", "OH, THAT PACKAGE! Do you really want that old thing?");
		DialogNode *node_1_2_2_1_1_1_1_1_1 = new DialogNode("Aye", "Sorry, but I'm not going to be handing it over any time soon, so...");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1 = new DialogNode("Return it or die!", "Tisk, tisk, tisk. You still can't see the full picture. It was never about the package...");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1 = new DialogNode("...", "I gave you an adventure, sending you up, down, left, right, fighting literally everyone.");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1 = new DialogNode("...", "The best part? None of them had any idea I was doing any of this. It was brilliant!");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1 = new DialogNode("...", "And tricking you into killing pirates along the way? Another brilliant move on my part >:D");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1 = new DialogNode("...", "So... I keep the package, and YOU get the satisfaction of knowing you beat the game!");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1 = new DialogNode("Yes", "Glad to hear it- Glad to hear something positive come from filthy pirate scum.");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1 = new DialogNode("Wha' was that?", "FILTHY PIRATE SCUM. I can spell it out if you need me to~");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1_1 = new DialogNode("Take it back!", "NEVER~! Piracy destroys the animation community, making your very existance a threat.");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1 = new DialogNode("...", "You're the reason that my favorite anime was canceled!"); // 3=
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2 = new DialogNode("NO!", "*ugh*! You still can't see all the good I've done for you?");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1 = new DialogNode("...", "I made you a story. It was cheesy, sure, but at least you learned something!");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1 = new DialogNode("...", "(Thats more than I can say about my data structures class).");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1 = new DialogNode("Wha' was that?", "What, too soon? Sorry,  but it's hard to converse when all I say are outdated references.");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1 = new DialogNode("But why us pirates?", "Why do I hate them so much? Thats complicated... Can't we just agree on our love of anime?");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1 = new DialogNode("No", "Why so cold all of a sudden? It's just an art style, not like you could guess my favorite~");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1 = new DialogNode("My Hero Academia", "Actually, I prefer Lucky Star and Eromanga Sensei~"); // =3
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1_1 = new DialogNode("NO! You're the worst kind of anime fan!", "Heh heh heh... So are we done here... or?");
		DialogNode *node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1_1_1 = new DialogNode("Hand over me package!", "No, Heh ha hah. Go to hell!", "FIGHT");
		DialogNode *node_2 = new DialogNode("", "W-well... you won...", "SAVE"); // =FIGHT
		DialogNode *node_2_1 = new DialogNode("YES I DID!", "I... don't know... if it was worth it...");
		DialogNode *node_2_1_1 = new DialogNode("It was", "I hope you're happy.", "EVENT");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);
		node_1_2_2->setChoice1(node_1_2_2_1);
		node_1_2_2_1->setChoice1(node_1_2_2_1_1);
		node_1_2_2_1_1->setChoice1(node_1_2_2_1_1_1);
		node_1_2_2_1_1_1->setChoice1(node_1_2_2_1_1_1_1);
		node_1_2_2_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1);

		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1->setChoice2(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1_1);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1_1_1);

		node_2->setChoice1(node_2_1);
		node_2_1->setChoice1(node_2_1_1);

		// Seperated Links:
		node_1_2_1->setChoice1(node_1_2_2_1); // 1=
		node_1_1->setChoice1(node_1_2_1); // 4=
		node_1_1->setChoice1(node_1_2_2);
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1->setChoice1(node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1); // 3=
		node_1_2_2_1_1_1_1_1_1_1_1_1_1_1_2_1_1_1_1_1_1_1_1->setChoice1(node_2); // FIGHT

		setHeadNode(node_1);
	}

	// Sets ANYTHING you want about a specific character (If more than 1 character uses this, try refactoring your code)
	void setUniqueAttributes() 
	{
		setPersistent();
	}
};

#endif // !CHR_AKIFINAL_H




