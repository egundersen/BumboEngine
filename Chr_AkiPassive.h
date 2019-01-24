#ifndef CHR_AKIPASSIVE_H
#define CHR_AKIPASSIVE_H

#include "CharacterBase.h"

// Stands in the DEEP cave, will provide assistance to player if asked
class Chr_AkiPassive : public CharacterBase
{
public:
	Chr_AkiPassive(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &bitmap, AudioDefinition &audio)
		: CharacterBase(center_position_x, center_position_y, PopupDefinition(), unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 0, player, BossFightDefinition(), false, false, bitmap, audio, world_sprite)
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
		DialogNode *node_1 = new DialogNode("", "What the hell do you wan- Oh! It's you! Sorry, got any burning questions?");
			DialogNode *node_1_1 = new DialogNode("Any idea who stole it?", "Nope. Try asking around. Perhaps the culprit dropped something at the crime scene.");
			DialogNode *node_1_2 = new DialogNode("Wha' should I do?", "Just go around accusing everyone until you find who stole it. It's P.O.E.");
				DialogNode *node_1_2_1 = new DialogNode("P.O.E.?", "Process of Elimination. What, were you born yesterday?");
				DialogNode *node_1_2_2 = new DialogNode("That sounds cruel", "Pffff* no! The fate of the world's at stake! No one cares about who did what to get where.");
			DialogNode *node_1_3 = new DialogNode("Nevermind", "If you think of any questions, don't hesitate to ask~");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);

		setHeadNode(node_1);
	}
};

#endif // !CHR_AKIPASSIVE_H
