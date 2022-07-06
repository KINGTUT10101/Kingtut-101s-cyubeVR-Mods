#include "GameAPI.h"
#include <fstream>

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/

UniqueID ThisModUniqueIDs[] = { 1019001, 1019002 }; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

float TickRate = 1;

/*************************************************************
//	Functions (Run automatically by the game, you can put any code you want into them)
*************************************************************/

// Run every time a block is placed
void Event_BlockPlaced(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{

}




// Run every time a block is destroyed
void Event_BlockDestroyed(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	BlockInfo aboveMachine = GetBlock(At + CoordinateInBlocks(0, 0, 1));

	if (aboveMachine.CustomBlockID == 1019002)
		SetBlock(At + CoordinateInBlocks(0, 0, 1), EBlockType::Air);

	// Spawns a block item if the block is not an extender
	if (CustomBlockID == 1019001 && Moved == false)
		SpawnBlockItem(At, 1019001);
}


// Run every time a block is hit by a tool
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{
	// Hit by axe
	if (ToolName.find(L"T_Axe") != std::wstring::npos) {
		// Removes the block if it was hit by an axe
		SetBlock(At, EBlockType::Air);
	}
	// Hit by sledgehammer
	else if (ToolName.find(L"T_Sledgehammer") != std::wstring::npos) {
		bool foundBottom = false;
		BlockInfo belowBlock;
		int i = 0;

		// Checks all blocks including and underneath the one that was hit by the stick
		// It will find the bottommost block, remove it, and teleport the player
		// It will exit the loop if it finds a block that isn't an upblock or an extender
		while (foundBottom == false) {
			belowBlock = GetBlock(At - CoordinateInBlocks(0, 0, i));
			if (belowBlock.CustomBlockID == 1019001) {
				foundBottom = true;
				SetBlock(At - CoordinateInBlocks(0, 0, i), EBlockType::Air);
				SetPlayerLocation(At - CoordinateInBlocks(0, 0, i));
			}
			else if (belowBlock.CustomBlockID == 1019002)
				i += 1;
			else
				foundBottom = true;
		}
	}
	// Hit by any other tool
	else {
		bool validSpace = true;
		BlockInfo aboveBlock;

		// Checks if there is room to spawn an upblock and teleport the player
		for (int i = 1; i <= 5; i++) {
			aboveBlock = GetBlock(At + CoordinateInBlocks(0, 0, i));
			if (aboveBlock.Type != EBlockType::Air)
				validSpace = false;
		}

		// Builds an extender above the block and teleports the player if the area is clear
		if (validSpace == true) {
			SetBlock(At + CoordinateInBlocks(0, 0, 1), 1019002);
			SetPlayerLocation(At + CoordinateInBlocks(0, 0, 1));
		}
		// Error message
		else
			SpawnHintText(At + CoordinateInBlocks(0, 0, 1), L"Not enough room!", 5);
	}
}


// Run X times per second, as specified in the TickRate variable at the top
void Event_Tick()
{

}



// Run once when the world is loaded
void Event_OnLoad(bool CreatedNewWorld)
{
	/*
	// Opens the config file
	std::ifstream config;
	config.open(GetThisModFolderPath() + L"\config.txt");

	// Reads from the config file
	// startTime
	config.ignore(50, ' ');
	config >> startTime;
	// endTime
	config.ignore(50, ' ');
	config >> endTime;
	// sleepMechanic
	config.ignore(50, ' ');
	config >> sleepMechanic;
	config.close();
	*/
}

// Run once when the world is exited
void Event_OnExit()
{

}

/*******************************************************

	Advanced functions

*******************************************************/


// Run every time any block is placed by the player
void Event_AnyBlockPlaced(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{

}

// Run every time any block is destroyed by the player
void Event_AnyBlockDestroyed(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{

}

// Run every time any block is hit by a tool
void Event_AnyBlockHitByTool(CoordinateInBlocks At, BlockInfo Type, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{

}


/*******************************************************

	For all the available game functions you can call, look at the GameAPI.h file

*******************************************************/