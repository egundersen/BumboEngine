#ifndef CHR_RYUUKO_H
#define CHR_RYUUKO_H

#include "CharacterBase.h"

class Chr_Ryuuko : public CharacterBase
{
public:
	Chr_Ryuuko(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,  Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			11,
			"RYUUKO",
			"Led_Zeppelin_-_Achilles_Last_Stand.mp3",
			140, 
			138, 
			137,
			139
		),//*/

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 3) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player, boss_fight_definition, attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("You are no hero", "SCUM! How dare you say such a thing!", false));
		dialog_choice_1.push_back(std::make_tuple("Ryuuko the villain! ", "You are!", false));
		dialog_choice_1.push_back(std::make_tuple("Look, pal. I know you pickpocketed me!", "This is the first I've heard of it!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("LIAR !!!!", "I never lie!", false));
		dialog_choice_2.push_back(std::make_tuple("Die!", "A hero never dies!", false));
		dialog_choice_2.push_back(std::make_tuple("Coward!", "You're the coward.", false));
		dialog_choice_2.push_back(std::make_tuple("I saw you at the checkpoint!", "So? Everyone was there. Thats not a crime!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("You literally walked up to me", "I just wanted to say hello", true));
		dialog_choice_3.push_back(std::make_tuple("OBJECTION", "GYAAAAA", false));
		dialog_choice_3.push_back(std::make_tuple("Today is the fall of Ryuuko! ", "NOOOOOOO", false));
		dialog_choice_3.push_back(std::make_tuple("Now I see why pirates hate anime!", "We hate pirates!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_4;
		dialog_choice_4.push_back(std::make_tuple("Too a random stranger?", "Makes sense to me! Can't you believe me?", true));
		dialog_choice_4.push_back(std::make_tuple("Where's your proof", "I have none. You just have to believe me!", true));
		dialog_choice_4.push_back(std::make_tuple("I'd say attacking me is evidence enough", "This is always how I settle an argument", false));
		dialog_choice_4.push_back(std::make_tuple("Today is the fall of Ryuuko! ", "NOOOOOOO", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_5;
		dialog_choice_5.push_back(std::make_tuple("I believe you", "Makes sense to me!", true));
		dialog_choice_5.push_back(std::make_tuple("I don't believe you", "Believe what you want, I stick to my ideals!", false));
		dialog_choice_5.push_back(std::make_tuple("This is why I hate anime!", "We hate pirates!", false));

		dialog_choices_.push_back(dialog_choice_1);
		dialog_choices_.push_back(dialog_choice_2);
		dialog_choices_.push_back(dialog_choice_3);
		dialog_choices_.push_back(dialog_choice_4);
		dialog_choices_.push_back(dialog_choice_5);

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
		AttackPatternBase *attack_pattern_1 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'r', 1, 'd', false, false, 0); // [EASY]
		AttackPatternBase *attack_pattern_2 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'l', 0, ' ', false, false, 0); // [EASY]
		AttackPatternBase *attack_pattern_3 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 50, 100, 'r', 1, 'u', false, false, 0); // [EASY] --SINGLECOLUMN
		AttackPatternBase *attack_pattern_4 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 20, 9, 1, 500); // [Medium] FAST
		AttackPatternBase *attack_pattern_5 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 350, 10, 'u', 0, ' ', false, false, 0); // [EASY] --FAST
		AttackPatternBase *attack_pattern_6 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
		AttackPatternBase *attack_pattern_7 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 150, 50, 'l', 1, 'u', false, false, 0); // [MEDIUM]
		AttackPatternBase *attack_pattern_8 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 150, 50, 'r', 0, ' ', false, false, 0); // [MEDIUM]
		AttackPatternBase *attack_pattern_9 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 250, 10, 'd', 1, 'l', false, false, 0); // [MEDIUM] --FAST
		AttackPatternBase *attack_pattern_10 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 50, 100, 'l', 0, ' ', false, false, 0); // [MEDIUM] --SINGLECOLUMN
		AttackPatternBase *attack_pattern_11 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'd', 0, ' ', false, false, 0); // [HARD]
		AttackPatternBase *attack_pattern_12 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player); // [Hard] Wavy
		AttackPatternBase *attack_pattern_13 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 150, 120, 10, 'l', 1, 'u', false, false, 0); // [HARD] --FAST
		AttackPatternBase *attack_pattern_14 = new AttackPattern_CoordinatedStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'r', 1, 'd', false, false, 0); // [MEDIUM]
		AttackPatternBase *attack_pattern_15 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 150, 120, 10, 'r', 1, 'd', false, false, 0); // [HARD] --FAST
		AttackPatternBase *attack_pattern_16 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 100, 30, 100, 'l', 1, 'd', false, false, 0); // [HARD] --SINGLECOLUMN
		AttackPatternBase *attack_pattern_17 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'd', 1, 'r', false, false, 0); // [HARD]
		AttackPatternBase *attack_pattern_18 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 400, 20, 250, 'r', 1, 'd', false, false, 0); // [INSANE] --SINGLECOLUMN

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
		DialogNode *node_1 = new DialogNode("", "Woah there! I've never seen a pirate in the CLEAR cave before!");
		DialogNode *node_1_1 = new DialogNode("Whats yer name?", "The one and only: Ryuuko!");
		DialogNode *node_1_1_1 = new DialogNode("What a weird name", "OF COURSE IT IS, For I am... <THE> Ryuuko!");
		DialogNode *node_1_1_1_1 = new DialogNode("Nevermind", "Wait, leaving already?");
		DialogNode *node_1_2 = new DialogNode("Be this your Sword?", "Wow! How did you find it?!");
		DialogNode *node_1_2_1 = new DialogNode("Ye wrote yer name upon it", "You'd have to agree that I'm pretty smart :D");
		DialogNode *node_1_2_1_1 = new DialogNode("It was you wasn't it?!", "That accusation... Are you challenging me... to... a... f-FIGHT?"); // 2=
		DialogNode *node_1_2_1_2 = new DialogNode("Steal anythin'?", "I would never steal ANYTHING! Were you robbed? Maybe I could help!"); // 1=
		DialogNode *node_1_2_1_2_1 = new DialogNode("I don't trust ye", "I say we settle this in battle. En guard!", "FIGHT");
		DialogNode *node_1_2_2 = new DialogNode("Pick up anythin'?", "Pick up something? ...Care to elaborate?");
		DialogNode *node_1_2_2_1 = new DialogNode("It was you, wasn't it?!", "That accusation... Are you challenging me... to... a... f-FIGHT?"); // =2
		DialogNode *node_1_2_2_1_1 = new DialogNode("No", "Too bad, this is MY CHOICE!", "FIGHT");
		DialogNode *node_1_2_2_1_2 = new DialogNode("Aye", "Then prepare yourself!", "FIGHT");
		DialogNode *node_1_2_2_2 = new DialogNode("I was pickpocketed", "OH NO! Thats sounds terrible! I feel SOOOO bad for you!");
		DialogNode *node_1_2_2_2_1 = new DialogNode("Thanks fer th' concern", "No problem. Could I help with your search?"); // =1
		DialogNode *node_1_2_2_2_1_1 = new DialogNode("Can I trust ye?", "If you trust me,  I'll trust you. We're in this together!", "SAVE"); // =FIGHT
		DialogNode *node_1_2_2_2_1_1_1 = new DialogNode("How will ye help?", "Have no fear! If you need my help in a fight, I'll be there!", "SAVE");
		DialogNode *node_1_2_2_2_1_1_1_1 = new DialogNode("Goodbye...", "Oh? leaving already?");
		DialogNode *node_1_2_2_2_1_2 = new DialogNode("I don't trust ye", "I say we settle this in battle. En guard!", "FIGHT");
		DialogNode *node_1_2_2_2_1_3 = new DialogNode("Why do ye want t' know?", "I'm just curious senpai?");
		DialogNode *node_1_2_2_2_1_3_1 = new DialogNode("you done messed up...", "What do you mean?");
		DialogNode *node_1_2_2_2_1_3_1_1 = new DialogNode("That 'word' has... ", "What about it?");
		DialogNode *node_1_2_2_2_1_3_1_1_1 = new DialogNode("no place in english!", "...", "FIGHT");
		DialogNode *node_1_2_2_2_2 = new DialogNode("Be that sarcasm?", "WHAT!!!??? Noo...... ");
		DialogNode *node_1_2_2_2_2_1 = new DialogNode("I don't trust ye", "I say we settle this in battle. En guard!", "FIGHT");
		DialogNode *node_1_2_2_2_2_2 = new DialogNode("I believe ye", "Fabulous! Now could I help with your search?"); // 1=
		DialogNode *node_1_3 = new DialogNode("Goodbye...", "Oh? leaving already?");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);
		node_1_1->setChoice1(node_1_1_1);
		node_1_1_1->setChoice1(node_1_1_1_1);
		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);
		node_1_2_1->setChoice1(node_1_2_1_1);
		node_1_2_1->setChoice2(node_1_2_1_2);
		node_1_2_1_2->setChoice1(node_1_2_1_2_1);

		node_1_2_2->setChoice1(node_1_2_2_1);
		node_1_2_2->setChoice2(node_1_2_2_2);
		node_1_2_2_1->setChoice1(node_1_2_2_1_1);
		node_1_2_2_1->setChoice2(node_1_2_2_1_2);
		node_1_2_2_2->setChoice1(node_1_2_2_2_1);
		node_1_2_2_2->setChoice2(node_1_2_2_2_2);
		node_1_2_2_2_2->setChoice1(node_1_2_2_2_2_1);
		node_1_2_2_2_2->setChoice2(node_1_2_2_2_2_2);

		node_1_2_2_2_1->setChoice1(node_1_2_2_2_1_1);
		node_1_2_2_2_1->setChoice2(node_1_2_2_2_1_2);
		node_1_2_2_2_1->setChoice3(node_1_2_2_2_1_3);
		node_1_2_2_2_1_1->setChoice1(node_1_2_2_2_1_1_1);
		node_1_2_2_2_1_1_1->setChoice1(node_1_2_2_2_1_1_1_1);

		node_1_2_2_2_1_3->setChoice1(node_1_2_2_2_1_3_1);
		node_1_2_2_2_1_3_1->setChoice1(node_1_2_2_2_1_3_1_1);
		node_1_2_2_2_1_3_1_1->setChoice1(node_1_2_2_2_1_3_1_1_1);

		// Seperated Links:
		node_1_2_1_2->setChoice2(node_1_2_2_2_1_1); // 1=
		node_1_2_1_2->setChoice3(node_1_2_2_2_1_3);
		node_1_2_2_2_2_2->setChoice1(node_1_2_2_2_1_1); // 1=
		node_1_2_2_2_2_2->setChoice2(node_1_2_2_2_1_2);
		node_1_2_2_2_2_2->setChoice3(node_1_2_2_2_1_3);
		node_1_2_1_1->setChoice1(node_1_2_2_1_1); // 2=
		node_1_2_1_1->setChoice2(node_1_2_2_1_2);
		node_1_2_1_2_1->setChoice1(node_1_2_2_2_1_1); // FIGHT
		node_1_2_2_1_1->setChoice1(node_1_2_2_2_1_1);
		node_1_2_2_1_2->setChoice1(node_1_2_2_2_1_1);
		node_1_2_2_2_1_2->setChoice1(node_1_2_2_2_1_1);
		node_1_2_2_2_1_3_1_1_1->setChoice1(node_1_2_2_2_1_1);
		node_1_2_2_2_2_1->setChoice1(node_1_2_2_2_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_RYUUKO_H



