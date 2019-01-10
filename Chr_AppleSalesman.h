#ifndef CHR_APPLESALESMAN_H
#define CHR_APPLESALESMAN_H

#include "CharacterBase.h"

class Chr_AppleSalesman : public CharacterBase
{
public:
	Chr_AppleSalesman(int center_position_x, int center_position_y, int unique_object_ID, WorldSpriteContainer world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &image_file_path)
		: CharacterBase(center_position_x, center_position_y, PopupDefinition(), unique_object_ID, world_matrix, element_has_object, screen_matrix, screen_width, screen_height, 0, player, BossFightDefinition(), false, false, image_file_path, world_sprite)
	{
		faceDirection(direction);
	}

	/* Advanced Dialog	(Shows multiple text screens with dialog options. Leave BLANK for minor characters) */
	void setDialogNodes()
	{
		Item apple("Apple", "SHIELD", 1, "The glass case lets you survive an extra hit.");

		/* ACTIONS (Mini-Tutorial)
		*	"FIGHT"		Will start a battle with the NPC
		*	item		Including an Item will have the NPC give the player the provided item
		*	"SAVE"		Will Save the current position in the dialog. So if the player exits the
		*				dialog and re-opens it, the conservsation will start at the "SAVE"d dialog choice
		*/

		// CREATE DIALOG NODES
		DialogNode *node_1 = new DialogNode("", "Apples fer sale! Wants some apples? Only $1000 an elder!");
		DialogNode *node_1_1 = new DialogNode("I'll take one", "Splendid! Here ya go! Tell yer mateys t' get one too (Jus' nah th' friends ye wants t' keep).", apple); //1=
		DialogNode *node_1_1_1 = new DialogNode("", "Tell yer mateys t' get one too (Jus' nah th' friends ye wants t' keep).", "SAVE"); // =1
		DialogNode *node_1_2 = new DialogNode("Don't 'ave th' doubloons", "Belay that! Ye can finance it wit' yer student loans!");
		DialogNode *node_1_2_1 = new DialogNode("Sounds good t' me!", "Tell yer mateys t' get one too (Jus' nah th' friends ye wants t' keep).", apple); // 1=
		DialogNode *node_1_2_2 = new DialogNode("I be nah interested", "Then stop wastin' me time!");
		DialogNode *node_1_3 = new DialogNode("Nevermind", "Oh, leavin' so soon?");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1->setChoice2(node_1_2);
		node_1->setChoice3(node_1_3);

		node_1_2->setChoice1(node_1_2_1);
		node_1_2->setChoice2(node_1_2_2);

		// Seperated Links:
		node_1_1->setChoice1(node_1_1_1); // 1=
		node_1_2_1->setChoice1(node_1_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_APPLESALESMAN_H
