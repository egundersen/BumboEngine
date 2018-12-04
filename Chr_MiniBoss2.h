#include "CharacterBase.h"
#include <string>

#ifndef CHR_MINIBOSS2_H
#define CHR_MINIBOSS2_H

class Chr_MINIBOSS2 : public CharacterBase
{
public:
    Chr_MINIBOSS2(int center_position_x, int center_position_y, int &player_health, int unique_object_ID, int screen_width, int screen_height, std::vector<std::vector<char>> &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, std::vector<std::vector<std::string>> &matrix_display, std::pair<std::string, int> &image_file_path,
                  // START CONFIGURABLE VARIABLES HERE -------------------------------------------------
                  
                  
                  // Character will attack player immediatly, upon seeing them.
                  bool attack_on_sight = false,
                  
                  // TRUE -> Basic Popup dialog | FALSE -> Advanced Dialog with player choices
                  bool use_basic_dialog = false,
                  // Basic Popup Dialog (Only used if use_basic_dialog == TRUE)
                  PopupDefinition popup_sprite = PopupDefinition("This is my onlyZdialog! helloZ", 'X', 23, 9),
                  
                  
                  // Advanced ASCII (Highly detailed) and read from a file as a screenshot/image
                  BossFightDefinition boss_fight_definition = BossFightDefinition(
                   22, // Boss health
                   "Mini Boss 2", // name
                   "resources\\mini boss 2_neuHappy.png", // Neutral Expression (Image Location/Name)
                   "resources\\mini boss 2_angry.png", // Angry Expression (Image Location/Name)
                   "resources\\mini boss 2_neuHappy.png",
                   "resources\\mini boss 2_nervousDead.png"
                                                                                  ),//*/
                  
                  /* Sets the sprite ascii for the NPC world sprite */
                  WorldSprite world_sprite = WorldSprite(
                                                         "   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O ZO ######O Z  %U  U%  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  O%###%O Z   %%  %  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O%###%O  Z  %  %%   Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  XXX@@X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O###### OZ  %U  U%  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX O Z  O#XX#O  Z %%O#%#   Z %=  %%   Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z O XXX@   Z  O#XX#O  Z   #%#O%% Z   %%  =% Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  X@@@XX  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  X[][]X  Z   XXXX   Z O#XXXX#O Z O######O Z  %U  U%  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  @@X[]X  Z   @XXX   Z  O#XX#O  Z  ######O Z  %U  U%  Z",
                                                         "   -/\\-   Z \\=/--\\=/ Z  X[]X@@  Z   XXX@   Z  O#XX#O  Z O######  Z  %U  U%  Z"
                                                         ),
                  
                  /* Use Event at end of battle (Whether slay or spare is called) | Must match ID of an actual event in the events folder */
                  int event_ID = 5) // 0 = no event
    
    : CharacterBase(center_position_x, center_position_y, popup_sprite, unique_object_ID, world_matrix, element_has_object, matrix_display, screen_width, screen_height, event_ID, player_health, boss_fight_definition, attack_on_sight, use_basic_dialog, image_file_path, world_sprite)
    {
        
        // (In-Battle) Dialog:		( player dialog choice; boss's response; should progress dialog? )
        std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_1;
        dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.1", "1.1 NO", false));
        dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.2", "1.2 NO", false));
        dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.C", "1.C YES", true));
        dialog_choice_1.push_back(std::make_tuple("HELLO WORLD 1.4", "1.4 NO", false));
        
        std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_2;
        dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.1", "2.1 NO", false));
        dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.2", "2.2 NO", false));
        dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.3", "2.3 NO", false));
        dialog_choice_2.push_back(std::make_tuple("HELLO WORLD 2.C", "2.C YES", true));
        
        std::vector<std::tuple<std::string, std::string, bool>> dialog_choice_3;
        dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.C", "3.C YES", true));
        dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.2", "3.2 NO", false));
        dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.3", "3.3 NO", false));
        dialog_choice_3.push_back(std::make_tuple("HELLO WORLD 3.4", "3.4 NO", false));
        
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
        AttackPatternBase *attack_pattern_1;
        attack_pattern_1 = new AttackPattern_Wall(screen_width, screen_height, matrix_display, player_health, 10, 5, 1);
        AttackPatternBase *attack_pattern_2;
        attack_pattern_2 = new Explode_Slow(screen_width, screen_height, matrix_display, player_health, 200);
        AttackPatternBase *attack_pattern_3;
        attack_pattern_3 = new Explode_Slowest(screen_width, screen_height, matrix_display, player_health, 50);
        AttackPatternBase *attack_pattern_4;
        attack_pattern_4 = new AttackPattern_ShootHorizontal(screen_width, screen_height, matrix_display, player_health, 10);
        AttackPatternBase *attack_pattern_5;
        attack_pattern_5 = new AttackPattern_ShootAtPlayer(screen_width, screen_height, matrix_display, player_health, 10); //50
        AttackPatternBase *attack_pattern_6;
        attack_pattern_6 = new VerticleGap_VerySlow(screen_width, screen_height, matrix_display, player_health);
        attack_patterns_.push_back(attack_pattern_2);
        attack_patterns_.push_back(attack_pattern_3);
        attack_patterns_.push_back(attack_pattern_2);
        attack_patterns_.push_back(attack_pattern_1);
        attack_patterns_.push_back(attack_pattern_5);
        attack_patterns_.push_back(attack_pattern_3);
        attack_patterns_.push_back(attack_pattern_4);
        attack_patterns_.push_back(attack_pattern_5);
        attack_patterns_.push_back(attack_pattern_6);//*/
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
        DialogNode *node_1 = new DialogNode("", "Oh hello, heh he heh Zfancy seeing you hereZ");
        DialogNode *node_1_1 = new DialogNode("Whats your name?", "All MIGHT! ZCan you guess why?Z");
        DialogNode *node_1_2 = new DialogNode("Want to hear a joke?", "Sure! I love meZ a good joke!Z");
        DialogNode *node_1_3 = new DialogNode("Goodbye...", "SEE YOU LATER!");
        DialogNode *node_1_1_1 = new DialogNode("No", "You irritated me!ZLet's fight!!!!Z", "FIGHT");
        DialogNode *node_1_1_2 = new DialogNode("Because you're ALL MIGHT", "You guess it! Here,Zhave my most valubleZpossession!Z", health_potion);
        DialogNode *node_1_1_3 = new DialogNode("*sigh* and walk away", "Hey! where areZyou going!!!?Z");
        DialogNode *node_1_2_1 = new DialogNode("Whats smiling and red?", "i dont know...ZWhat is it?Z");
        DialogNode *node_1_2_2 = new DialogNode("Too bad! ha ha ha!", "YOU DARE!!! DIE!!ZDIE!!! DIEE!!!Z", "FIGHT");
        DialogNode *node_1_2_3 = new DialogNode("YOUR EXPRESSION! get it?", "I will neverZspeak with youZagainZ");
        DialogNode *node_1_2_1_1 = new DialogNode("YOUR FACE WHEN I BREAK IT", "...Z", "FIGHT");
        DialogNode *node_1_1_2_1 = new DialogNode("Goodbye", "Back again I see.ZSorry, I only had theZone item...Z", "SAVE");
        DialogNode *node_1_1_1_1 = new DialogNode("Goodbye", "I lostZ", "SAVE");
        
        // Link Dialog Nodes
        node_1->setChoice1(node_1_1);
        node_1->setChoice2(node_1_2);
        node_1->setChoice3(node_1_3);
        
        node_1_1->setChoice1(node_1_1_1);
        node_1_1->setChoice2(node_1_1_2);
        node_1_1->setChoice3(node_1_1_3);
        
        node_1_2->setChoice1(node_1_2_1);
        node_1_2->setChoice2(node_1_2_2);
        node_1_2->setChoice3(node_1_2_3);
        
        node_1_2_1->setChoice1(node_1_2_1_1);
        node_1_1_2->setChoice1(node_1_1_2_1);
        node_1_1_1->setChoice1(node_1_1_1_1);
        
        setHeadNode(node_1);
    }
};

#endif // !CHR_MINIBOSS1_H
