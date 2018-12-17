#include "CharacterBase.h"
#include <string>

#ifndef CHR_AKI_H
#define CHR_AKI_H

class Chr_Aki : public CharacterBase
{
public:
	Chr_Aki(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, int &player_health, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! hello ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			13,
			"AKI", 
			"aki_happy_neutral.bmp",
			"aki_angry_neutral.bmp",
			"aki_happy_neutral.bmp",
			"aki_nervous.bmp"
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 4) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("You STOLE my package!", "Where's your proof?!", true));
		dialog_choice_1.push_back(std::make_tuple("You wanted me to eliminate the entire pirate faction!", "Well, maybe THAT part some some truth to it...", false));
		dialog_choice_1.push_back(std::make_tuple("Admit it! You stole my father's package!", "Never!", true));
		dialog_choice_1.push_back(std::make_tuple("Whats in the package, EXACTLY?", "Aww... If I told you that, then it wouldn't be a surprise.", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("You condemn my father's name", "I never knew your father.", false));
		dialog_choice_2.push_back(std::make_tuple("Untrustworthy", "Thats a matter of perspective", false));
		dialog_choice_2.push_back(std::make_tuple("You're a thief! ", "Don't get ahead of yourself, you still need definitive proof", false));
		dialog_choice_2.push_back(std::make_tuple("You're not lying?", "Of course not! Who do you take me for?", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("Fine, I take your word for it", "Yes! Please no more!", true)); // 5=
		dialog_choice_3.push_back(std::make_tuple("I still don't believe you!", "That's alright, I can promise a quick and painless death.", false));
		dialog_choice_3.push_back(std::make_tuple("Can't take any chances", "I guess I did tell you to accuse everyone... that one's on me.", false));
		dialog_choice_3.push_back(std::make_tuple("Anime should die", "I don't agree.", false));

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
	void initializeAttackPatterns(int screen_width, int screen_height, Matrix &screen_matrix, int &player_health)
	{
		for (int i = 0; i < 6; i++)
		{
			AttackPatternBase *attack_pattern_1;
			attack_pattern_1 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player_health);
			AttackPatternBase *attack_pattern_2;
			attack_pattern_2 = new Explode_Fast(screen_width, screen_height, screen_matrix, player_health, 600);
			AttackPatternBase *attack_pattern_3;
			attack_pattern_3 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player_health, 10, 3, 25);

			AttackPatternBase *attack_pattern_4;
			attack_pattern_4 = new Explode_Slow(screen_width, screen_height, screen_matrix, player_health, 200);
			AttackPatternBase *attack_pattern_13;
			attack_pattern_13 = new VerticleGap_Slow(screen_width, screen_height, screen_matrix, player_health);
			AttackPatternBase *attack_pattern_5;
			attack_pattern_5 = new AttackPattern_ShootHorizontal(screen_width, screen_height, screen_matrix, player_health, 30);
			AttackPatternBase *attack_pattern_6;
			attack_pattern_6 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player_health, 1);
			AttackPatternBase *attack_pattern_7;
			attack_pattern_7 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player_health, 10, 1, 35);

			AttackPatternBase *attack_pattern_8;
			attack_pattern_8 = new Explode_Slowest(screen_width, screen_height, screen_matrix, player_health, 50);
			AttackPatternBase *attack_pattern_9;
			attack_pattern_9 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player_health, 4);
			AttackPatternBase *attack_pattern_10;
			attack_pattern_10 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player_health, 10, 3, 15);
			AttackPatternBase *attack_pattern_11;
			attack_pattern_11 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, screen_matrix, player_health, 30);

			AttackPatternBase *attack_pattern_12;
			attack_pattern_12 = new VerticleGap_VerySlow(screen_width, screen_height, screen_matrix, player_health);

			attack_patterns_.push_back(attack_pattern_1);
			attack_patterns_.push_back(attack_pattern_2);
			attack_patterns_.push_back(attack_pattern_3);
			attack_patterns_.push_back(attack_pattern_4);
			attack_patterns_.push_back(attack_pattern_13); // <----- This was intentional
			attack_patterns_.push_back(attack_pattern_5);
			attack_patterns_.push_back(attack_pattern_6);
			attack_patterns_.push_back(attack_pattern_7);
			attack_patterns_.push_back(attack_pattern_8);
			attack_patterns_.push_back(attack_pattern_9);
			attack_patterns_.push_back(attack_pattern_10);
			attack_patterns_.push_back(attack_pattern_11);
			attack_patterns_.push_back(attack_pattern_12);
		}
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
		DialogNode *node_1 = new DialogNode("", "Hey {player}, any progress in finding the package?");
		DialogNode *node_1_1 = new DialogNode("No", "Really? *sigh*... I could of sworn Ryuuko would of had it.");
		DialogNode *node_1_1_1 = new DialogNode("Him? Impossible.", "Not that he would try and steal something, he's just such an idiot that there's a possibility..."); // 1=
		DialogNode *node_1_1_2 = new DialogNode("I checked already", "And how hard was that? I swear they never should have let him past the checkpoint..."); // =1
		DialogNode *node_1_1_2_1 = new DialogNode("So... wha' now?", "While you were searching, I conducted my own investigation.");
		DialogNode *node_1_1_2_1_1 = new DialogNode("And?", "I think the pirates were all working together as a whole...");
		DialogNode *node_1_1_2_1_1_1 = new DialogNode("Are you sure?", "They staged the siege on the CLEAR cave, who KNOWS what they could do? They're all disgusting animals...");
		DialogNode *node_1_1_2_1_1_1_1 = new DialogNode("Huh?", "Oh no! Ignore that!"); // 2=
		DialogNode *node_1_1_2_1_1_1_2 = new DialogNode("Disgustin'?", "I didn't mean that! There's just tension among the two factions, thats all."); // 2=
		DialogNode *node_1_1_2_1_1_1_3 = new DialogNode("... I'm a pirate.", "I'm sorry, I didn't mean that..."); // =2
		DialogNode *node_1_1_2_1_1_1_3_1 = new DialogNode("Back to the package", "Oh course. How could I of been distracted? There's still one place left to check.");
		DialogNode *node_1_1_2_1_1_1_3_1_1 = new DialogNode("Where?", "Just to the right of this room, I'll remove the rock blocking the entrance.");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1 = new DialogNode("Thank ye", "Oh hey, I have a glove that looks just like yours, I used to have a pair but I...");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_1 = new DialogNode("Welp, see ya", "Of course. Here, let me remove the rock for you."); // =3
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_1_1 = new DialogNode("Goodbye", "'Good luck' finding your father's package.", "SAVE"); // ROCK EVENT
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2 = new DialogNode("'But you...' what?", "Nothing, I merely misplaced it. Thats all, why does it even matter?");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_1 = new DialogNode("'twas at th' checkpoint", "I don't see what you're getting at here... we're wasting valubale time!");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_1_1 = new DialogNode("Does it belong t' ye?", "Maybe... it does bare some resemblence to mine, but why does that matter?"); // 6=
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2 = new DialogNode("It's yers!", "I suppose it does bare some resemblence to mine, but why does that matter?"); // =6
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_1 = new DialogNode("I dunno", "That's right. Now about that boulder... how about I clear it so you can progress?");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_1_1 = new DialogNode("Sure", "It'll only take a second..."); // 3=
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_1_2 = new DialogNode("No", "Why? Do you have an idea of who might have stolen your package?");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_1_2_1 = new DialogNode("Yeah! 'twas ye!", "Are you accusing me of stealing from you?"); // 4=
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2 = new DialogNode("'cause 'twas ye!", "Are you accusing me of something? Remember, I've been helping you this whole time."); // =4
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2_1 = new DialogNode("Give me my package!", "Touchy...", "FIGHT");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2_2 = new DialogNode("Fer yer owns gain", "Uhh-what? If I had taken it, I wouldn't have tasked you with finding it!");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1 = new DialogNode("Why? Whats in it?", "I already explained myself, something very dangerous! Now, do you believe me or not?");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1_1 = new DialogNode("I don't believe ye", "Then you're even more of a fool than I took you for!", "FIGHT");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1_2 = new DialogNode("I believe ye", "What a relief... Now for that boulder: I'll clear it so you can progress."); // 3=
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_2 = new DialogNode("'cause ye hate pirates", "Where are you going with this? It's not like I wanted you to-");
		DialogNode *node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_2_1 = new DialogNode("eliminate th' pirates", "Are you DONE? Let's just get this over with...", "FIGHT");
		DialogNode *node_2 = new DialogNode("", "Thank you for believeing me. I PROMISE you won't regret this later.", "SAVE"); // =5 ROCK EVENT

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);
		node_1_1_2->setChoice1(node_1_1_2_1);
		node_1_1_2_1->setChoice1(node_1_1_2_1_1);
		node_1_1_2_1_1->setChoice1(node_1_1_2_1_1_1);
		node_1_1_2_1_1_1->setChoice1(node_1_1_2_1_1_1_1);
		node_1_1_2_1_1_1->setChoice2(node_1_1_2_1_1_1_2);
		node_1_1_2_1_1_1->setChoice3(node_1_1_2_1_1_1_3);
		node_1_1_2_1_1_1_3->setChoice1(node_1_1_2_1_1_1_3_1);
		node_1_1_2_1_1_1_3_1->setChoice1(node_1_1_2_1_1_1_3_1_1);
		node_1_1_2_1_1_1_3_1_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1);
		node_1_1_2_1_1_1_3_1_1_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_1);
		node_1_1_2_1_1_1_3_1_1_1->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2);
		node_1_1_2_1_1_1_3_1_1_1_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_1_1);

		node_1_1_2_1_1_1_3_1_1_1_2->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_1);
		node_1_1_2_1_1_1_3_1_1_1_2->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2);
		node_1_1_2_1_1_1_3_1_1_1_2_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_1_1);
		node_1_1_2_1_1_1_3_1_1_1_2_2->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_1);
		node_1_1_2_1_1_1_3_1_1_1_2_2->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2_2);
		node_1_1_2_1_1_1_3_1_1_1_2_2_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_1_1);
		node_1_1_2_1_1_1_3_1_1_1_2_2_1->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2_1_2);
		node_1_1_2_1_1_1_3_1_1_1_2_2_1_2->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_1_2_1);

		node_1_1_2_1_1_1_3_1_1_1_2_2_2->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_2_1);
		node_1_1_2_1_1_1_3_1_1_1_2_2_2->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2_2_2);
		node_1_1_2_1_1_1_3_1_1_1_2_2_2_2->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1);
		node_1_1_2_1_1_1_3_1_1_1_2_2_2_2->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_2);
		node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1_1);
		node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1_2);
		node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_2->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_2_1);

		// Seperated Links:
		node_1_1_1->setChoice1(node_1_1_2_1); // 1=
		node_1_1_2_1_1_1_1->setChoice1(node_1_1_2_1_1_1_3_1); // 2=
		node_1_1_2_1_1_1_2->setChoice1(node_1_1_2_1_1_1_3_1); // 2=
		node_1_1_2_1_1_1_3_1_1_1_2_2_1_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_1_1); // 3=
		node_1_1_2_1_1_1_3_1_1_1_2_2_2_2_1_2->setChoice1(node_1_1_2_1_1_1_3_1_1_1_1_1); // 3=
		node_1_1_2_1_1_1_3_1_1_1_2_2_1_2_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_2_1); // 4=
		node_1_1_2_1_1_1_3_1_1_1_2_2_1_2_1->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2_2_2);
		node_1_1_2_1_1_1_3_1_1_1_2_1_1->setChoice1(node_1_1_2_1_1_1_3_1_1_1_2_2_1); // 6=
		node_1_1_2_1_1_1_3_1_1_1_2_1_1->setChoice2(node_1_1_2_1_1_1_3_1_1_1_2_2_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_AKI_H



