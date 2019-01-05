#include "CharacterBase.h"
#include <string>

#ifndef CHR_THOTPATROL_H
#define CHR_THOTPATROL_H

class Chr_ThotPatrol : public CharacterBase
{
public:
	Chr_ThotPatrol(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, char direction, BattleSprite battle_sprite, int &player_health, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &image_file_path,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! Hello", 'X', 23, 9),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 0) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player_health,
			BossFightDefinition(
				-1, // boss health
				40, // his smile/eyes (overlay) offset X position
				20, // his smile/eyes (overlay) offset Y position
				"THOT Patrol",
				battle_sprite.getFace(),
				battle_sprite.getOverlay()
			), attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
	{
		faceDirection(direction);

		// (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
		dialog_choice_1.push_back(std::make_tuple("Who can it be knocking at my door?", "Sorry pal, wrong song!", false));
		dialog_choice_1.push_back(std::make_tuple("I can't get to sleep", "I think about the implications", true));
		dialog_choice_1.push_back(std::make_tuple("Traveling in a fried-out combie", "Sorry pal, wrong song!", false));
		dialog_choice_1.push_back(std::make_tuple("Feel so washed up today", "Sorry pal, wrong song!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
		dialog_choice_2.push_back(std::make_tuple("Of diving in too deep", "And possibly the complications", true));
		dialog_choice_2.push_back(std::make_tuple("Can't you see that it's late at night?", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_2.push_back(std::make_tuple("On a hippie trail, head full of zombie", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_2.push_back(std::make_tuple("Haven't really got much to say", "Sorry pal, those aren't the lyrics!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
		dialog_choice_3.push_back(std::make_tuple("I met a strange lady, ", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_3.push_back(std::make_tuple("Especially at night", "I worry over situations", true));
		dialog_choice_3.push_back(std::make_tuple("Can't you see that it's late at night?", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_3.push_back(std::make_tuple("Do you come from a land down under?", "Sorry pal, those aren't the lyrics!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_4;
		dialog_choice_4.push_back(std::make_tuple("Buying bread from a man in Brussels", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_4.push_back(std::make_tuple("I'm very tired, and I'm not feeling right.", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_4.push_back(std::make_tuple("Explains the pain that's in my head", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_4.push_back(std::make_tuple("I know will be alright", "Perhaps it's just imagination", true));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_5;
		dialog_choice_5.push_back(std::make_tuple("All I wish is to be alone", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_5.push_back(std::make_tuple("Day after day it reappears", "Night after night my heartbeat shows the fear", true));
		dialog_choice_5.push_back(std::make_tuple("He was six-foot-four and full of muscles", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_5.push_back(std::make_tuple("'cause I'm walking on a high wire", "Sorry pal, those aren't the lyrics!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_6;
		dialog_choice_6.push_back(std::make_tuple("Ghosts appear and fade away", "Alone between the sheets", true));
		dialog_choice_6.push_back(std::make_tuple("Best off if you hang outside,", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_6.push_back(std::make_tuple("I said, \"do you speak-a my language?\"", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_6.push_back(std::make_tuple("Oh won't someone let me in", "Sorry pal, those aren't the lyrics!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_7;
		dialog_choice_7.push_back(std::make_tuple("Only brings exasperation", "It's time to walk the streets", true));
		dialog_choice_7.push_back(std::make_tuple("And he said", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_7.push_back(std::make_tuple("I'm stinking and I'm full of gin", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_7.push_back(std::make_tuple("Don't come in, I'll only run and hide.", "Sorry pal, those aren't the lyrics!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_8;
		dialog_choice_8.push_back(std::make_tuple("No need to close the door so fast", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_8.push_back(std::make_tuple("Smell the desperation", "At least there's pretty lights", true));
		dialog_choice_8.push_back(std::make_tuple("I've done no harm, I keep to myself", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_8.push_back(std::make_tuple("You better run, you better take cover, yeah", "Sorry pal, those aren't the lyrics!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_9;
		dialog_choice_9.push_back(std::make_tuple("I'm very fragile not built to last", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_9.push_back(std::make_tuple("Make no sound, tip-toe across the floor", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_9.push_back(std::make_tuple("And though there's little variation", "It nullifies the night", true));
		dialog_choice_9.push_back(std::make_tuple("Where women glow and men plunder?", "Sorry pal, those aren't the lyrics!", false));

		std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_10;
		dialog_choice_10.push_back(std::make_tuple("From overkill", "Well played... well played...", true));
		dialog_choice_10.push_back(std::make_tuple("Who can it be now?", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_10.push_back(std::make_tuple("Do you come from a land down under?", "Sorry pal, those aren't the lyrics!", false));
		dialog_choice_10.push_back(std::make_tuple("'cause I'm walking on a high wire", "Sorry pal, those aren't the lyrics!", false));

		dialog_choices_.push_back(dialog_choice_1);
		dialog_choices_.push_back(dialog_choice_2);
		dialog_choices_.push_back(dialog_choice_3);
		dialog_choices_.push_back(dialog_choice_4);
		dialog_choices_.push_back(dialog_choice_5);
		dialog_choices_.push_back(dialog_choice_6);
		dialog_choices_.push_back(dialog_choice_7);
		dialog_choices_.push_back(dialog_choice_8);
		dialog_choices_.push_back(dialog_choice_9);
		dialog_choices_.push_back(dialog_choice_10);

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
		AttackPatternBase *attack_pattern_1;
		attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player_health, 10, 5, 1);
		AttackPatternBase *attack_pattern_2;
		attack_pattern_2 = new Explode_Slow(screen_width, screen_height, screen_matrix, player_health, 200);
		AttackPatternBase *attack_pattern_3;
		attack_pattern_3 = new Explode_Slowest(screen_width, screen_height, screen_matrix, player_health, 50);
		AttackPatternBase *attack_pattern_4;
		attack_pattern_4 = new AttackPattern_ShootHorizontal(screen_width, screen_height, screen_matrix, player_health, 10);
		AttackPatternBase *attack_pattern_5;
		attack_pattern_5 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, screen_matrix, player_health, 10); //50
		AttackPatternBase *attack_pattern_6;
		attack_pattern_6 = new VerticleGap_VerySlow(screen_width, screen_height, screen_matrix, player_health);
		AttackPatternBase *attack_pattern_7;
		attack_pattern_7 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player_health, 1);
		AttackPatternBase *attack_pattern_8;
		attack_pattern_8 = new ShootandExplode_Fast(screen_width, screen_height, screen_matrix, player_health, 10);
		AttackPatternBase *attack_pattern_9;
		attack_pattern_9 = new ShootandExplode_Slow(screen_width, screen_height, screen_matrix, player_health, 10);
		AttackPatternBase *attack_pattern_10;
		attack_pattern_10 = new AttackPattern_ShootandSnake(screen_width, screen_height, screen_matrix, player_health, 10);
		attack_patterns_.push_back(attack_pattern_1);
		attack_patterns_.push_back(attack_pattern_8);
		attack_patterns_.push_back(attack_pattern_9);
		attack_patterns_.push_back(attack_pattern_10);
		//attack_patterns_.push_back(attack_pattern_3);
		/*attack_patterns_.push_back(attack_pattern_3);
		attack_patterns_.push_back(attack_pattern_2);
		attack_patterns_.push_back(attack_pattern_1);
		attack_patterns_.push_back(attack_pattern_5);
		attack_patterns_.push_back(attack_pattern_3);
		attack_patterns_.push_back(attack_pattern_4);
		attack_patterns_.push_back(attack_pattern_5);
		attack_patterns_.push_back(attack_pattern_6);
		attack_patterns_.push_back(attack_pattern_7);//*/
	}
};

#endif // !CHR_THOTPATROL_H
