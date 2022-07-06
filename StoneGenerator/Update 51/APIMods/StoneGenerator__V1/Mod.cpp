#include "GameAPI.h"
#include <fstream>

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/

UniqueID ThisModUniqueIDs[] = { 1019000 }; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

float TickRate = 1;							 // Set how many times per second Event_Tick() is called. 0 means the Event_Tick() function is never called.

// Used to limit the speed at which the blocks spawn. They are initialized to 0
int tickCount = 0, tickMax = 0;
// Determines the chance a certain block will spawn. They are initialized to 0
int stone_chance = 0;
int coal_chance = 0;
int iron_chance = 0;
int copper_chance = 0;
int gold_chance = 0;
int crystal_chance = 0;

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
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName)
{
	if (ToolName != L"T_Axe_Stone" && ToolName != L"T_Axe_Copper" && ToolName != L"T_Axe_Iron") {
		// Replaces the block if it is destroyed using the wrong tool
		SetBlock(At, 1019000);
		
		// Counts the number of seconds to limit block spawning to 2 second intervals
		if (tickCount >= tickMax) {
			// Sets random value
			uint64_t rng = GetRandomInt<0, 100>();

			// Spawns stone/ore when the user hits the mod block
			if (rng <= stone_chance) // Stone
				SetBlock(At + CoordinateInBlocks(0, 0, 1), EBlockType::Stone);
			else if (rng <= coal_chance) // Coal
				SetBlock(At + CoordinateInBlocks(0, 0, 1), EBlockType::Ore_Coal);
			else if (rng <= iron_chance) // Iron
				SetBlock(At + CoordinateInBlocks(0, 0, 1), EBlockType::Ore_Iron);
			else if (rng <= copper_chance) // Copper
				SetBlock(At + CoordinateInBlocks(0, 0, 1), EBlockType::Ore_Copper);
			else if (rng <= gold_chance) // Gold
				SetBlock(At + CoordinateInBlocks(0, 0, 1), EBlockType::Ore_Gold);
			else if (rng <= crystal_chance) // Crystal
				SetBlock(At + CoordinateInBlocks(0, 0, 1), EBlockType::CrystalBlock);

			tickCount = 0;
		}
	}
}


// Run X times per second, as specified in the TickRate variable at the top
void Event_Tick()
{
	// Increments tickCount if it hasn't hit the max yet
	tickCount = (tickCount >= tickMax)? tickCount: tickCount+1;
}



// Run once when the world is loaded
void Event_OnLoad()
{
	// Opens the config file
	std::ifstream config;
	config.open(GetThisModFolderPath () + L"\config.txt");

	// Reads from the config file
	// tickMax
	config.ignore(50, ' ');
	config >> tickMax;
	tickCount = tickMax;
	// Stone chance
	config.ignore(50, ' ');
	config >> stone_chance;
	// Coal chance
	config.ignore(50, ' ');
	config >> coal_chance;
	// Iron chance
	config.ignore(50, ' ');
	config >> iron_chance;
	// Copper chance
	config.ignore(50, ' ');
	config >> copper_chance;
	// Gold chance
	config.ignore(50, ' ');
	config >> gold_chance;
	// Crystal chance
	config.ignore(50, ' ');
	config >> crystal_chance;
	config.close();


	coal_chance += stone_chance;
	iron_chance += coal_chance;
	copper_chance += iron_chance;
	gold_chance += copper_chance;
	crystal_chance += gold_chance;
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
void Event_AnyBlockHitByTool(CoordinateInBlocks At, BlockInfo Type, wString ToolName)
{

}


/*******************************************************

	For all the available game functions you can call, look at the GameAPI.h file

*******************************************************/