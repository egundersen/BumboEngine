#ifndef CHR_MINIBOSS2_H
#define CHR_MINIBOSS2_H

#include "CharacterBase.h"

class Chr_MiniBoss2 : public CharacterBase
{
public:
	Chr_MiniBoss2(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,  Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),


		// Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
		BossFightDefinition boss_fight_definition = BossFightDefinition(
			7,
			"J.K. Literal",
			"The_Who_-_Behind_Blue_Eyes.mp3",
			"mini_boss_2_neutral_happy.bmp",
			"mini_boss_2_angry.bmp",
			"mini_boss_2_angry.bmp",
			"mini_boss_2_nervous_dead.bmp"
		),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 10024) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player, boss_fight_definition, attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("We can talk this out", "HOO HOO HA HA HA! IMPOSSIBLE! WHO DO YOU TAKE ME FOR?", true));
		dialog_choice_1.push_back(std::make_tuple("Who are you?", "J.K. LITERAL.", true));
		dialog_choice_1.push_back(std::make_tuple("Why are you attacking me?", "ALL PIRATES MUST BE CLEANSED FROM OUR WORLD!", true));
		dialog_choice_1.push_back(std::make_tuple("Something's wrong...", "No. Nothing's wrong.", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("We can talk this out", "HOO HOO HA HA HA! IMPOSSIBLE! WHO DO YOU TAKE ME FOR?", true));
		dialog_choice_2.push_back(std::make_tuple("Who are you?", "J.K. LITERAL.", true));
		dialog_choice_2.push_back(std::make_tuple("Why are you attacking me?", "ALL PIRATES MUST BE CLEANSED FROM OUR WORLD!", true));
		dialog_choice_2.push_back(std::make_tuple("Something's wrong...", "No. Nothing's wrong.", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("We can talk this out", "HOO HOO HA HA HA! IMPOSSIBLE! WHO DO YOU TAKE ME FOR?", true));
		dialog_choice_3.push_back(std::make_tuple("Who are you?", "J.K. LITERAL.", true));
		dialog_choice_3.push_back(std::make_tuple("Why are you attacking me?", "ALL PIRATES MUST BE CLEANSED FROM OUR WORLD!", true));
		dialog_choice_3.push_back(std::make_tuple("Something's wrong...", "No. Nothing's wrong.", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_4;
		dialog_choice_4.push_back(std::make_tuple("We can talk this out", "HOO HOO HA HA HA! IMPOSSIBLE! WHO DO YOU TAKE ME FOR?", true));
		dialog_choice_4.push_back(std::make_tuple("Who are you?", "J.K. LITERAL.", true));
		dialog_choice_4.push_back(std::make_tuple("Why are you attacking me?", "ALL PIRATES MUST BE CLEANSED FROM OUR WORLD!", true));
		dialog_choice_4.push_back(std::make_tuple("Something's wrong...", "No. Nothing's wrong.", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_5;
		dialog_choice_5.push_back(std::make_tuple("Surrender! I've exhausted all of your dialog!", "Only if you promise... to never forget me. EVER!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_6;
		dialog_choice_6.push_back(std::make_tuple("I promise", "You have just given me your soul. Deh Devil thanks you.", true));
		dialog_choice_6.push_back(std::make_tuple("What was your name again?", "Close enough.", true));

		dialog_choices_.push_back(dialog_choice_1);
		dialog_choices_.push_back(dialog_choice_2);
		dialog_choices_.push_back(dialog_choice_3);
		dialog_choices_.push_back(dialog_choice_4);
		dialog_choices_.push_back(dialog_choice_5);
		dialog_choices_.push_back(dialog_choice_6);

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
		attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 10, 5, 1);
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
		DialogNode *node_1 = new DialogNode("", "HALT! I THE GREAT AND POWERFUL J.K. LITUH- Uh... hmm... Hold on... Gimme a second...");
		DialogNode *node_1_1 = new DialogNode("Ok", "I found my script! It's written right here... I... -wait- I can't read that word...");
		DialogNode *node_1_1_1 = new DialogNode("Go on", "Ah yes: *ehem!* *Let me just get back in character:* WHERE DO YOU THINK YOU'RE GOING?");
		DialogNode *node_1_1_1_1 = new DialogNode("I needs t' get past ye", "IMPOSSIBLE! FOR YOU SEE: I AM GUARDING THIS DOOR.");
		DialogNode *node_1_1_1_1_1 = new DialogNode("Are ye really though?", "YES. I. AM."); // 2=
		DialogNode *node_1_1_1_1_2 = new DialogNode("Not fer long!", "That sounded vague enough to be a threat! PREPARE THINE SELF! FOR COMBAT!", "FIGHT");
		DialogNode *node_1_1_1_2 = new DialogNode("Where do you think YOU'RE going?", "I'M GUARDING THIS HALLWAY.");
		DialogNode *node_1_1_1_2_1 = new DialogNode("Are ye?", "YES. I. AM.");
		DialogNode *node_1_1_1_2_1_1 = new DialogNode("But are ye REALLY?", "YES"); // =2
		DialogNode *node_1_1_1_2_1_1_1 = new DialogNode("But are ye REEEAAAAALLLY?", "YES"); // 1=
		DialogNode *node_1_1_1_2_2 = new DialogNode("No ye're not", "Wait you can't say that, it's not on the script. I have no way to respond to that!"); // =1
		DialogNode *node_1_1_1_2_2_1 = new DialogNode("Ye're nah guardin' this gangway", "I'm not? But I thought... well then what am I doing?");
		DialogNode *node_1_1_1_2_2_1_1 = new DialogNode("Ye're tryin' t' get past me!", "I am?");
		DialogNode *node_1_1_1_2_2_1_1_1 = new DialogNode("Aye, but ye're failin' at it!", "No!");
		DialogNode *node_1_1_1_2_2_1_1_1_1 = new DialogNode("Aye!", "This is terrible news! What am I to do?");
		DialogNode *node_1_1_1_2_2_1_1_1_1_1 = new DialogNode("Ye should go right", "And then what?");
		DialogNode *node_1_1_1_2_2_1_1_1_1_1_1 = new DialogNode("Don't stop. Jus' go right", "I'll do my best not to let you down.", "EVENT");
		DialogNode *node_1_1_1_2_2_1_1_1_1_1_1_1 = new DialogNode("", "I tried to go right... but I got lost. Sorry for letting you down.", "SAVE");
		DialogNode *node_1_1_1_2_2_1_1_1_1_2 = new DialogNode("We should fight!", "Ok, I'll do my best not to let you down.", "FIGHT");
		DialogNode *node_1_2 = new DialogNode("Hold that thought...", "I understand completely. I'll do my best not to let you down.");
		DialogNode *node_2 = new DialogNode("", "I do hope I will see you again soon...", "SAVE"); // =FIGHT
		DialogNode *node_2_1 = new DialogNode("I don't", "...maybe even sooner than you think.", "EVENT");
		DialogNode *node_2_1_1 = new DialogNode("", "Surprise! I'm still here!", "SAVE");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1_1->setChoice1(node_1_1_1);
		node_1_1_1->setChoice1(node_1_1_1_1);
		node_1_1_1_1->setChoice1(node_1_1_1_1_1);
		node_1_1_1_1->setChoice2(node_1_1_1_1_2);

		node_1_1_1->setChoice2(node_1_1_1_2);
		node_1_1_1_2->setChoice1(node_1_1_1_2_1);
		node_1_1_1_2_1->setChoice1(node_1_1_1_2_1_1);
		node_1_1_1_2_1_1->setChoice1(node_1_1_1_2_1_1_1);

		node_1_1_1_2->setChoice2(node_1_1_1_2_2);
		node_1_1_1_2_2->setChoice1(node_1_1_1_2_2_1);
		node_1_1_1_2_2_1->setChoice1(node_1_1_1_2_2_1_1);
		node_1_1_1_2_2_1_1->setChoice1(node_1_1_1_2_2_1_1_1);
		node_1_1_1_2_2_1_1_1->setChoice1(node_1_1_1_2_2_1_1_1_1);
		node_1_1_1_2_2_1_1_1_1->setChoice1(node_1_1_1_2_2_1_1_1_1_1);
		node_1_1_1_2_2_1_1_1_1_1->setChoice1(node_1_1_1_2_2_1_1_1_1_1_1);
		node_1_1_1_2_2_1_1_1_1_1_1->setChoice1(node_1_1_1_2_2_1_1_1_1_1_1_1);

		node_1_1_1_2_2_1_1_1_1->setChoice2(node_1_1_1_2_2_1_1_1_1_2);

		node_2->setChoice1(node_2_1);
		node_2_1->setChoice1(node_2_1_1);

		// Seperated Links:
		node_1_1_1_2_1_1_1->setChoice1(node_1_1_1_2_2); // 1=
		node_1_1_1_1_1->setChoice1(node_1_1_1_2_1_1_1); // 2=
		node_1_1_1_1_2->setChoice1(node_2); // FIGHT
		node_1_1_1_2_2_1_1_1_1_2->setChoice1(node_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_MINIBOSS1_H
