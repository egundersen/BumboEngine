#ifndef CHR_THOTPATROL_H
#define CHR_THOTPATROL_H

#include "CharacterBase.h"

// BONUS boss battle at end of game. Uses every attack in the game. Infinite health
class Chr_ThotPatrol : public CharacterBase
{
public:
	Chr_ThotPatrol(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, BattleSprite battle_sprite, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object,  Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio,
		// START CONFIGURABLE VARIABLES HERE -------------------------------------------------


		// Character will attack player immediatly, upon seeing them.
		bool attack_on_sight = false,

		// TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
		bool use_basic_dialog = false,
		// Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
		PopupDefinition popup_sprite = PopupDefinition("This is my only dialog! Hello", 'X', 23, 9),

		/* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
		int event_ID = 10021) // 0 = no event

		: CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, event_ID, player,
			BossFightDefinition(
				-9999, // boss health
				40, // his smile/eyes (overlay) offset X position
				20, // his smile/eyes (overlay) offset Y position
				"THOT Patrol",
				"Initial D - Deja Vu.mp3",
				battle_sprite.getFace(),
				battle_sprite.getOverlay()
			), attack_on_sight, use_basic_dialog, bitmap, audio, world_sprite)
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
	void initializeAttackPatterns(int screen_width, int screen_height, Matrix &screen_matrix, PlayerDefinition &player)
	{
		for (int i = 0; i < 3; i++) {
			AttackPatternBase *attack_pattern_1 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 15000, 100); // [EASY]
			AttackPatternBase *attack_pattern_2 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 15, 40, 1000); // [EASY] SLOW
			AttackPatternBase *attack_pattern_3 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 15, 10, 500); // [EASY] FAST
			AttackPatternBase *attack_pattern_4 = new Explode_Fast(screen_width, screen_height, screen_matrix, player, 150); // [Easy] Fast
			AttackPatternBase *attack_pattern_5 = new Explode_Slow(screen_width, screen_height, screen_matrix, player, 75); // [Easy] Slow
			AttackPatternBase *attack_pattern_6 = new Explode_Slowest(screen_width, screen_height, screen_matrix, player, 25); // [Easy] Slowest
			AttackPatternBase *attack_pattern_7 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 250, 50, 'l', 1, 'u', false, false, 0); // [EASY]
			AttackPatternBase *attack_pattern_8 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 350, 20, 'r', 1, 'd', false, false, 0); // [EASY] --FAST
			AttackPatternBase *attack_pattern_9 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 50, 100, 'd', 0, ' ', false, false, 0); // [EASY] --SINGLECOLUMN
			AttackPatternBase *attack_pattern_10 = new AttackPattern_SnakeHailStorm(screen_width, screen_height, screen_matrix, player, 50, 250, 120, 'r', 1, 'd', false, false, 0, 15000); // [EASY]
			AttackPatternBase *attack_pattern_11 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 15000, 75); // [Medium]
			AttackPatternBase *attack_pattern_12 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 2, 15000, 100); // [Medium] 2
			AttackPatternBase *attack_pattern_13 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 2, 20000, 100); // [Medium] 2
			AttackPatternBase *attack_pattern_14 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 3, 30, 1750); // [MEDIUM] SLOW
			AttackPatternBase *attack_pattern_15 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 9, 7, 10, 1000); // [Medium] FAST (Wide)
			AttackPatternBase *attack_pattern_16 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 20, 9, 1, 500); // [Medium] FAST
			AttackPatternBase *attack_pattern_17 = new Explode_Fast(screen_width, screen_height, screen_matrix, player, 650); // [Medium] Fast
			AttackPatternBase *attack_pattern_18 = new Explode_Slow(screen_width, screen_height, screen_matrix, player, 300); // [Medium] Slow
			AttackPatternBase *attack_pattern_21 = new SafeSquares_Fast(screen_width, screen_height, screen_matrix, player, 8); // [Easy-Hard] Fast
			AttackPatternBase *attack_pattern_22 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
			AttackPatternBase *attack_pattern_23 = new VerticleGap_Slow(screen_width, screen_height, screen_matrix, player); // [Medium] Slow
			AttackPatternBase *attack_pattern_24 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 150, 50, 'r', 1, 'd', false, false, 0); // [MEDIUM]
			AttackPatternBase *attack_pattern_25 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 50, 250, 20, 'l', 0, ' ', false, false, 0); // [MEDIUM] --FAST
			AttackPatternBase *attack_pattern_26 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 75, 50, 100, 'd', 1, 'l', false, false, 0); // [MEDIUM] --SINGLECOLUMN
			AttackPatternBase *attack_pattern_27 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 25000, 50); // [Hard]
			AttackPatternBase *attack_pattern_28 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 3, 15000, 150); // [Hard] 3
			AttackPatternBase *attack_pattern_29 = new AttackPattern_ShootSnake(screen_width, screen_height, screen_matrix, player, 10, 13000, 60); // [Hard]
			AttackPatternBase *attack_pattern_30 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 6, 1, 28, 1750); // [Hard] SLOW
			AttackPatternBase *attack_pattern_31 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 28, 19, 1, 350); // [Hard] FAST
			AttackPatternBase *attack_pattern_32 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 10, 7, 100, 800); // [Hard] CLUMP
			AttackPatternBase *attack_pattern_33 = new Explode_Slowest(screen_width, screen_height, screen_matrix, player, 100); // [Hard] Slowest
			AttackPatternBase *attack_pattern_34 = new ShootExplode_Fast(screen_width, screen_height, screen_matrix, player, 50); // [Hard]
			AttackPatternBase *attack_pattern_35 = new SafeSquares_Slow(screen_width, screen_height, screen_matrix, player, 6); // [Easy-Hard] Slow
			AttackPatternBase *attack_pattern_36 = new SafeSquares_Slow(screen_width, screen_height, screen_matrix, player, 6); // [Easy-Hard] Slowest
			AttackPatternBase *attack_pattern_37 = new SafeSquares_Slowest(screen_width, screen_height, screen_matrix, player, 3); // [Easy-Hard] Slowest
			AttackPatternBase *attack_pattern_38 = new AttackPattern_Wall(screen_width, screen_height, screen_matrix, player, 10, 7, 100, 800); // [Hard] CLUMP
			AttackPatternBase *attack_pattern_39 = new VerticleGap_VeryFast(screen_width, screen_height, screen_matrix, player); // [Medium] Fast
			AttackPatternBase *attack_pattern_40 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 50, 'l', 1, 'u', true, false, 16000); // [HARD]
			AttackPatternBase *attack_pattern_41 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 400, 40, 250, 'r', 1, 'd', false, false, 0); // [INSANE] --SINGLECOLUMN
			AttackPatternBase *attack_pattern_42 = new AttackPattern_HailStorm(screen_width, screen_height, screen_matrix, player, 200, 75, 15, 'r', 0, ' ', false, false, 0); // [HARD]
			AttackPatternBase *attack_pattern_43 = new ShootExplode_Fast(screen_width, screen_height, screen_matrix, player, 10); // [Hard]
			AttackPatternBase *attack_pattern_44 = new VerticleGap_Wavy(screen_width, screen_height, screen_matrix, player); // [Hard] Wavy
			AttackPatternBase *attack_pattern_45 = new AttackPattern_CoordinatedStorm(screen_width, screen_height, screen_matrix, player, 400, 50, 100, 'l', 1, 'd', false, false, 1000); // [INSANE] Rows
			AttackPatternBase *attack_pattern_46 = new AttackPattern_Snake(screen_width, screen_height, screen_matrix, player, 1, 45000, 100); // [INSANE] Long

			attack_patterns_.push_back(attack_pattern_46);
			attack_patterns_.push_back(attack_pattern_45);
			attack_patterns_.push_back(attack_pattern_44);
			attack_patterns_.push_back(attack_pattern_43);
			attack_patterns_.push_back(attack_pattern_42);
			attack_patterns_.push_back(attack_pattern_41);
			attack_patterns_.push_back(attack_pattern_40);
			attack_patterns_.push_back(attack_pattern_39);
			attack_patterns_.push_back(attack_pattern_38);
			attack_patterns_.push_back(attack_pattern_37);
			attack_patterns_.push_back(attack_pattern_36);
			attack_patterns_.push_back(attack_pattern_35);
			attack_patterns_.push_back(attack_pattern_34);
			attack_patterns_.push_back(attack_pattern_33);
			attack_patterns_.push_back(attack_pattern_32);
			attack_patterns_.push_back(attack_pattern_31);
			attack_patterns_.push_back(attack_pattern_30);
			attack_patterns_.push_back(attack_pattern_29);
			attack_patterns_.push_back(attack_pattern_28);
			attack_patterns_.push_back(attack_pattern_27);
			attack_patterns_.push_back(attack_pattern_26);
			attack_patterns_.push_back(attack_pattern_25);
			attack_patterns_.push_back(attack_pattern_24);
			attack_patterns_.push_back(attack_pattern_23);
			attack_patterns_.push_back(attack_pattern_22);
			attack_patterns_.push_back(attack_pattern_21);
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
	}
};

#endif // !CHR_THOTPATROL_H
