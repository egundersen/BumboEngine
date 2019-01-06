#include "CharacterBase.h"
#include <string>

#ifndef CHR_BADENDINGGUY_H
#define CHR_BADENDINGGUY_H

class Chr_BadEndingGuy : public CharacterBase
{
public:
	Chr_BadEndingGuy(int center_position_x, int center_position_y, int unique_object_ID, WorldSprite world_sprite, char direction, PlayerDefinition &player, int screen_width, int screen_height, Matrix &world_matrix, std::vector<std::vector<std::pair<int, int>>> &element_has_object, Matrix &screen_matrix, BitmapDefinition &image_file_path)
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
		DialogNode *node_1 = new DialogNode("", "Oh! A fellow Pirate! Ain't it great?");
		DialogNode *node_1_1 = new DialogNode("Ain't wha' great?", "We won th' war! 'n 'tis all thanks t' ye!");
		DialogNode *node_1_1_1 = new DialogNode("Um... Ye're Welcome?", "Yeah. Now we can finish clearin' out these filthy purists! ON WITH THE REVOLUTION!!!");
		DialogNode *node_1_1_1_1 = new DialogNode("...", "Wha' that? Ye look like ye wanna ask somethin'.");
		DialogNode *node_1_1_1_1_1 = new DialogNode("'ave ye seen a package?", "Lots o' them: Tons o' stolen property... MAKES ME SICK. So we had a \"Boston Teaparty\" o' sorts...");
		DialogNode *node_1_1_1_1_1_1 = new DialogNode("Wha'?", "We through everythin' we found into th' ocean.");
		DialogNode *node_1_1_1_1_1_1_1 = new DialogNode("EVERYTHING!?", "Every single bit o' stolen material was destroyed. Out wit' th' old 'n in wit' th' new, so t' speak.");
		DialogNode *node_1_1_1_1_1_1_1_1 = new DialogNode("But... me package!", "Sorry, pal, but 'tis o'er.");
		DialogNode *node_1_1_1_1_1_1_1_1_1 = new DialogNode("...", "THANK YOU FOR PLAYING", "SAVE");
		DialogNode *node_1_1_1_1_1_1_1_1_1_1 = new DialogNode("...", "Not that you'd be interested, but the game has another ending, a good ending.");
		DialogNode *node_1_1_1_1_1_1_1_1_1_1_1 = new DialogNode("How do I get it?", "Try beating the final boss without killing them.");

		// Link Dialog Nodes
		node_1->setChoice1(node_1_1);
		node_1_1->setChoice1(node_1_1_1);
		node_1_1_1->setChoice1(node_1_1_1_1);
		node_1_1_1_1->setChoice1(node_1_1_1_1_1);
		node_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1);
		node_1_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1_1);
		node_1_1_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1_1_1);
		node_1_1_1_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1_1_1_1);
		node_1_1_1_1_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1_1_1_1_1);
		node_1_1_1_1_1_1_1_1_1_1->setChoice1(node_1_1_1_1_1_1_1_1_1_1_1);

		setHeadNode(node_1);
	}
};

#endif // !CHR_BADENDINGGUY
