#ifndef CHR_CHECKPOINTGUARD_H
#define CHR_CHECKPOINTGUARD_H

#include "CharacterBase.h"

class Chr_CheckpointGuard : public CharacterBase
{
public:
	Chr_CheckpointGuard(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, BattleSprite battle_sprite, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
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
				4, // boss health
				40, // (overlay) offset X position
				20, // (overlay) offset Y position
				"Security",
				"Bee_Gees_-_Stayin_Alive.mp3",
				battle_sprite.getFace(),
				battle_sprite.getOverlay()
			), attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Can't we talk this out?", "Can't you just die?", false));
		dialog_choice_1.push_back(std::make_tuple("Who are ye anyway?", "First name: Checkpoint. Last name: security. Middle initial: a space", false));
		dialog_choice_1.push_back(std::make_tuple("Wha' did that kid do?", "Kid? I don't see no kid. He was CLEARLY an adult", false));
		dialog_choice_1.push_back(std::make_tuple("Ahoy look, a flyin' saucer!", "A wha- ... You can't distract me that easily! Who do you take me for?", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("Checkpoint Security", "That's right... and it's my solemn duty to protect this checkpoint!", false));
		dialog_choice_2.push_back(std::make_tuple("A pushover!", "I'll show you who will be pushed over!", false));
		dialog_choice_2.push_back(std::make_tuple("A yellow-bellied cur!", "I'll show you which one of us drinks yellow curry!", false));
		dialog_choice_2.push_back(std::make_tuple("Nobody cares! Har har har!", "Are you <MOCKING> me?", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("Blisterin' Barnacles, no... (Yes)", "I shall not be made a fool!", false));
		dialog_choice_3.push_back(std::make_tuple("No", "Good! (Last thing I want is to be made fun of)", false));
		dialog_choice_3.push_back(std::make_tuple("Aye", "That's why this battlefield will be your grave!", false));
		dialog_choice_3.push_back(std::make_tuple("Har har har!", "Stop laughing! Why can't you take this seriously!", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_4;
		dialog_choice_4.push_back(std::make_tuple("'cause I be better than ye!", "Impossible! Prove it! Prove your are better than me!", true));
		dialog_choice_4.push_back(std::make_tuple("'cause I don't like ye", "That's fine, I don't like you either!", false));
		dialog_choice_4.push_back(std::make_tuple("I dunno", "I hate people governed by indecisiveness!", false));
		dialog_choice_4.push_back(std::make_tuple("Eh... I don't really care", "If you don't CARE, then I don't CARE!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_5;
		dialog_choice_5.push_back(std::make_tuple("I don't go around terrorisin' pirates!", "Farrdin' pirates and their self-righteous attitude...", false));
		dialog_choice_5.push_back(std::make_tuple("Me jacket be tailor-made", "And I'm wearing designer jeans.", false));
		dialog_choice_5.push_back(std::make_tuple("I don't CAPITALIZE everythin' I say", "NO! IT CAN'T BE TRUE!!!! NO O O O O O O O!", false));
		dialog_choice_5.push_back(std::make_tuple("I won't stoop t' yer level!", "<MY LEVEL>? I BE NO PIRATE!!!! wait...", true));

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
		for (int i = 0; i < 3; i++) {
			AttackPatternBase *attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 15, 40, 1750); // [EASY] SLOW
			AttackPatternBase *attack_pattern_2 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 3, 30, 1750); // [MEDIUM] SLOW
			AttackPatternBase *attack_pattern_3 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
			AttackPatternBase *attack_pattern_4 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 20, 9, 1, 500); // [Medium] FAST
			AttackPatternBase *attack_pattern_5 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast

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
		Item energy_drink("Energy Drink", "HEAL", 9, "C0L4! Drink to restore full health.");

		/* ACTIONS (Mini-Tutorial)
		*	"FIGHT"		Will start a battle with the NPC
		*	item		Including an Item will have the NPC give the player the provided item
		*	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		*				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		*/

		// CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "Well if it isn't... Haven't I seen you somewhere before. YES?");
		DialogNode *node_1_1 = new DialogNode("Um... what?", "Look I'm a busy man. Everyone looks alike. Just say what you gotta say or get lost!");
		DialogNode *node_1_1_1 = new DialogNode("I was pick pocketed!", "Yeah so? Thats not my pro- wait... I'm checkpoint security. That <IS> my problem!");
		DialogNode *node_1_1_1_1 = new DialogNode("Any idea who?", "Any IDEA!? His name is Sharktooth, and he definetly stole from you.");
		DialogNode *node_1_1_1_1_1 = new DialogNode("Are ye sure?", "No, But I've been waiting for a poor excuse to lock up this guy for ages!");
		DialogNode *node_1_1_1_1_1_1 = new DialogNode("Evidence?", "Well no... I have absolutely no evidence that he ever did anything wrong. I just don't like him.");
		DialogNode *node_1_1_1_1_1_1_1 = new DialogNode("(Give Cigar Box)", "This is... HIS CIGAR BOX! I knew it was him! Good work, now I'm tasking YOU with finding him.");
		DialogNode *node_1_1_1_1_1_1_1_1 = new DialogNode("Thanks...", "No need to thank me, fulfilling heroic duties is why I'm checkpoint security! >:D", "SAVE");
		DialogNode *node_1_1_1_1_1_1_2 = new DialogNode("(Give Feather)", "What do I look like, some kind of bird? What am I supposed to do with this?");
		DialogNode *node_1_1_1_1_1_1_2_1 = new DialogNode("'tis evidence", "Thats not evidence. Now GET LOST!", "SAVE");
		DialogNode *node_1_1_1_1_1_1_3 = new DialogNode("So ye're speculatin'", "I never said that. I'm merely guestimating. Now GET LOST!");
		DialogNode *node_1_1_1_1_1_1_3_1 = new DialogNode("\"Guestimating?\"", "Are you questioning the legitimacy of my vocabulary?");
		DialogNode *node_1_1_1_1_1_1_3_1_1 = new DialogNode("YES", "Free speech is dead and you'll be too!", "FIGHT");
		DialogNode *node_1_1_1_1_1_1_3_1_2 = new DialogNode("NO", "Really? Because it seemed like you were.");
		DialogNode *node_1_1_1_1_1_1_3_1_2_1 = new DialogNode("Thats 'cause I was!", "You think your better than me.", "FIGHT");
		DialogNode *node_1_1_1_1_1_1_3_1_2_2 = new DialogNode("No, sir", "Thats right. Bow your head to me!", "SAVE");
		DialogNode *node_1_1_1_1_1_1_3_2 = new DialogNode("Goodbye", "Be about your business, pirate!", "SAVE");
		DialogNode *node_1_2 = new DialogNode("Nevermind", "Be about your business, pirate!");
		DialogNode *node_2 = new DialogNode("", "I think I get it now...", "SAVE"); // =FIGHT
		DialogNode *node_2_1 = new DialogNode("You do?", "You want to be checkpoint security as well!");
		DialogNode *node_2_1_1 = new DialogNode("Yes", "I knew it! Now, as your first assignment... BUZZ OFF, KID!"); // 1=
		DialogNode *node_2_1_2 = new DialogNode("No", "No need to be shy. What, need some help? Perhaps an energy drink would suffice", energy_drink); // 1=
		DialogNode *node_3 = new DialogNode("Yes", "BUZZ OFF, KID! Can't you see I'm doing something!?", "SAVE"); // =1

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);

		node_1_1->setChoice1(node_1_1_1);
		node_1_1_1->setChoice1(node_1_1_1_1);
		node_1_1_1_1->setChoice1(node_1_1_1_1_1);
		node_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1);

		node_1_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1_1);
		node_1_1_1_1_1_1->setChoice2(node_1_1_1_1_1_1_2);
		node_1_1_1_1_1_1->setChoice3(node_1_1_1_1_1_1_3);

		node_1_1_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1_1_1);
		node_1_1_1_1_1_1_2->setChoice1(node_1_1_1_1_1_1_2_1);
		node_1_1_1_1_1_1_3->setChoice1(node_1_1_1_1_1_1_3_1);
		node_1_1_1_1_1_1_3->setChoice2(node_1_1_1_1_1_1_3_2);

		node_1_1_1_1_1_1_3_1->setChoice1(node_1_1_1_1_1_1_3_1_1);
		node_1_1_1_1_1_1_3_1->setChoice2(node_1_1_1_1_1_1_3_1_2);
		node_1_1_1_1_1_1_3_1_2->setChoice1(node_1_1_1_1_1_1_3_1_2_1);
		node_1_1_1_1_1_1_3_1_2->setChoice2(node_1_1_1_1_1_1_3_1_2_2);

		node_2->setChoice1(node_2_1);
		node_2_1->setChoice1(node_2_1_1);
		node_2_1->setChoice2(node_2_1_2);

		// Seperated Links:
		node_1_1_1_1_1_1_3_1_1->setChoice1(node_2); // FIGHT
		node_1_1_1_1_1_1_3_1_2_1->setChoice1(node_2);
		node_2_1_1->setChoice1(node_3); // 1=
		node_2_1_2->setChoice1(node_3);

		setHeadNode(node_1);
	}
};

#endif // !CHR_CHECKPOINTGUARD_H
