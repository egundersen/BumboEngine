#ifndef CHR_EVERYTHINGSALESMAN_H
#define CHR_EVERYTHINGSALESMAN_H

#include "CharacterBase.h"

class Chr_EverythingSalesman : public CharacterBase
{
public:
	Chr_EverythingSalesman(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap)
		: CharacterBase(center_position_x, center_position_y, PopupDefinition(), unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 0, player, BossFightDefinition(), false, false, bitmap, world_sprite)
	{
		faceDirection(direction);
	}

	/* Advanced Dialog	(Shows multiple text screens with dialog options. Leave BLANK for minor characters) */
	void setDialogNodes()
	{
		Item android("Android", "ATTACKUP", 1, "Explosive core doubles player damage for the next attack.");

		/* ACTIONS (Mini-Tutorial)
		*	"FIGHT"		Will start a battle with the NPC
		*	item		Including an Item will have the NPC give the player the provided item
		*	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		*				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		*/

		// CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "Everythin' else fer sale! Jus' $400 'n ye get two o' them! AND they be better!");
			DialogNode *node_1_1 = new DialogNode("Wha' are ye sellin'?", "Everythin' else. Wha' does it look like? Wants some (two)?");
				DialogNode *node_1_1_1 = new DialogNode("Aye", "Thank ye, come again!", android);
					DialogNode *node_1_1_1_1 = new DialogNode("", "Thank ye, come again!", "SAVE");
				DialogNode *node_1_1_2 = new DialogNode("No", "That be too bad...");
			DialogNode *node_1_2 = new DialogNode("No thanks", "That be too bad...");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);

		node_1_1->setChoice1(node_1_1_1);
		node_1_1->setChoice2(node_1_1_2);

		node_1_1_1->setChoice1(node_1_1_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_EVERYTHINGSALESMAN_H
