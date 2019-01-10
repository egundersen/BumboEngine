#ifndef CHR_FEATHERSALESMAN_H
#define CHR_FEATHERSALESMAN_H

#include "CharacterBase.h"

class Chr_FeatherSalesman : public CharacterBase
{
public:
	Chr_FeatherSalesman(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &image_file_path)
		: CharacterBase(center_position_x, center_position_y, PopupDefinition(), unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 0, player, BossFightDefinition(), false, false, image_file_path, world_sprite)
	{
		faceDirection(direction);
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
		DialogNode *node_1 = new DialogNode("", "Feathers fer sale! Get yer feathers!");
		DialogNode *node_1_1 = new DialogNode("Sell any recently?", "I did sell one... t' th' scallywag standin' right next t' me.");
		DialogNode *node_1_2 = new DialogNode("Nevermind", "If ye ever needs feathers, ye know who t' find!");
		DialogNode *node_1_1_1 = new DialogNode("Thanks", "Don't mention it.");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);

		node_1_1->setChoice1(node_1_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_FEATHERSALESMAN_H
