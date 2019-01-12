#ifndef CHR_DIALOGEXAMPLE_H
#define CHR_DIALOGEXAMPLE_H

#include "CharacterBase.h"

class Chr_DialogExample : public CharacterBase
{
public:
	Chr_DialogExample(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio)
		: CharacterBase(center_position_x, center_position_y, PopupDefinition(), unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 0, player, BossFightDefinition(), false, false, bitmap, audio, world_sprite)
	{
		faceDirection(direction);
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
		DialogNode *node_1 = new DialogNode("", "Oh hello, heh he heh fancy seeing you here");
		DialogNode *node_1_1 = new DialogNode("Whats your name?", "All MIGHT! Can you guess why?");
		DialogNode *node_1_2 = new DialogNode("Want to hear a joke?", "Sure! I love me a good joke!");
		DialogNode *node_1_3 = new DialogNode("Goodbye...", "SEE YOU LATER!");
		DialogNode *node_1_1_1 = new DialogNode("No", "You irritated me! Let's fight!!!!", "FIGHT");
		DialogNode *node_1_1_2 = new DialogNode("Because you're ALL MIGHT", "You guess it! Here, have my most valuble possession!", health_potion);
		DialogNode *node_1_1_3 = new DialogNode("*sigh* and walk away", "Hey! where are you going!!!?");
		DialogNode *node_1_2_1 = new DialogNode("Whats smiling and red?", "I dont know... What?");
		DialogNode *node_1_2_2 = new DialogNode("Too bad! ha ha ha!", "YOU DARE!!! DIE!! DIE!!! DIEE!!!", "FIGHT");
		DialogNode *node_1_2_3 = new DialogNode("YOUR EXPRESSION! get it?", "I will never speak with you again");
		DialogNode *node_1_2_1_1 = new DialogNode("YOUR FACE WHEN I BREAK IT", "...", "FIGHT");
		DialogNode *node_1_1_2_1 = new DialogNode("Goodbye", "Back again I see. Sorry, I only had the one item...", "SAVE");
		DialogNode *node_1_1_1_1 = new DialogNode("Goodbye", "I lost", "SAVE");

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

#endif // !CHR_DIALOGEXAMPLE_H
