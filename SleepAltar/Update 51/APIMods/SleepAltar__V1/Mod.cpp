#include "GameAPI.h"
#include <fstream>

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/

UniqueID ThisModUniqueIDs[] = { 1019010, 1019011 }; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

float TickRate = 1;							 // Set how many times per second Event_Tick() is called. 0 means the Event_Tick() function is never called.

float startTime = 1750, endTime = 700;
bool sleepMechanic = true;

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

}


// Run every time a block is hit by a tool
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{
	// Checks if the block was hit with an axe
	if (ToolName.find(L"T_Axe") == std::wstring::npos) {

		// Base block (1019010)
		if (CustomBlockID == 1019010) {
			BlockInfo above = GetBlock(At + CoordinateInBlocks(0, 0, 1));

			// Checks if the multiblock is complete
			if (above.CustomBlockID == 1019011) {
				float time = GetTimeOfDay();

				// Checks if it is evening/nighttime or if the player has disabled the sleep mechanic
				if (sleepMechanic == false)
					SetTimeOfDay(endTime);
				else if (time >= startTime || time < endTime)
					SetTimeOfDay(endTime);
				else
					SpawnHintText(At + CoordinateInBlocks(0, 0, 2), L"You don't feel tired yet... (" + std::to_wstring(int(time)) + L")", 3);
			}
			else
				SpawnHintText(At + CoordinateInBlocks(0, 0, 1), L"Multiblock is incomplete!", 5);
		}
		// Head block (1019011)
		else {
			BlockInfo below = GetBlock(At - CoordinateInBlocks(0, 0, 1));

			// Checks if the multiblock is complete
			if (below.CustomBlockID == 1019010) {
				float time = GetTimeOfDay();

				// Checks if it is evening/nighttime or if the player has disabled the sleep mechanic
				if (sleepMechanic == false)
					SetTimeOfDay(endTime);
				else if (time >= startTime || time < endTime)
					SetTimeOfDay(endTime);
				else
					SpawnHintText(At + CoordinateInBlocks(0, 0, 1), L"You don't feel tired yet... (" + std::to_wstring(int(time)) + L")", 3);
			}
			else
				SpawnHintText(At + CoordinateInBlocks(0, 0, 1), L"Multiblock is incomplete!", 5);
		}


	}
	else {
		// Deletes the block and spawns the corresponding block item
		SetBlock(At, EBlockType::Air);
		if (CustomBlockID == 1019010)
			SpawnBlockItem(At, 1019010);
		else
			SpawnBlockItem(At, 1019011);
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