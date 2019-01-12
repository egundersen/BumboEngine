#ifndef CHR_PACINGPIRATE_H
#define CHR_PACINGPIRATE_H

#include "CharacterBase.h"

class Chr_PacingPirate : public CharacterBase
{
public:
	Chr_PacingPirate(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap)
		: CharacterBase(center_position_x, center_position_y, PopupDefinition(), unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 10014, player, BossFightDefinition(), false, false, bitmap, world_sprite)
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
		DialogNode *node_1 = new DialogNode("", "I be so ANGRY! I can nah believe they be gone! All o' me Cubans!");
			DialogNode *node_1_1 = new DialogNode("Cigars?", "No. Not cigars.", "EVENT"); // START EVENT
			DialogNode *node_1_2 = new DialogNode("(Show 'im Cigar Box)", "Aren't those Sharktooth's? He'll scuttle ye if ye don't return them.");
				DialogNode *node_1_2_1 = new DialogNode("They be nah yers?", "No");
					DialogNode *node_1_2_1_1 = new DialogNode("(Quietly leave)", "Ye better return those t' Sharktooth ASAP!", "SAVE");
			DialogNode *node_1_3 = new DialogNode("(Quietly leave)", "What am I t' do?");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);
		node_1_2->setChoice1(node_1_2_1);
		node_1_2_1->setChoice1(node_1_2_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_PACINGPIRATE_H
