//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "command.h"
#include "room.h"
#include "characterclass.h"



//=================//
// Not My Includes //
//=================//
//#include <sstream>
//#include <iostream>


//==========//
// Forwards //
//==========//
using namespace std;

bool strCompare(string, string);
ExitDirection translateDirection(string);
void testMenu();


//===============================//
// Command Parser Implimentation //
//===============================//
command::		command()
{

}
command::		~command()
{

}


bool command::	translateCommand(string input, player* callingPlayer, room* currentRoom)
{
	istringstream command(input);
	m_callingPlayer = callingPlayer;
	m_currentRoom = currentRoom;

	do
	{
		string word1 = "";
		string word2 = "";
		command >> word1;
		
		
		// GO COMMAND
		if (strCompare(word1, "go")) 
		{
			command >> word2;
			ExitDirection dir = translateDirection(word2);
			ExitStatus ex = m_currentRoom->getExitStatus(dir);

			switch (ex)
			{
			case NO_EXIT:
				{
					cout << "You can't go that way!" << endl;
					system("pause");
					break;
				}
			case YES_EXIT:
				{
					m_targetRoom = m_currentRoom->getExitLink(dir);
					callingPlayer->movePlayerToRoom(m_targetRoom);
					//system("pause");
					break;
				}
			case EXIT_DOOR_OPEN:
				{
					m_targetRoom = m_currentRoom->getExitLink(dir);
					callingPlayer->movePlayerToRoom(m_targetRoom);
					//system("pause");
					break;
				}
			case EXIT_DOOR_CLOSED:
				{
					cout << "There is a closed door blocking your way." << endl;
					system("pause");
					break;
				}
			case EXIT_DOOR_LOCKED:
				{
					cout << "There is a closed door blocking your way!" << endl;
					system("pause");
					break;
				}
			case EXIT_OBSTRUCTION:
				{
					cout << "Something is blocking your way!" << endl;
					system("pause");
					break;
				}


			} // end of switch ex

		}// end of "GO"
		
		
		// quit/exit COMMAND
		if (strCompare(word1, "quit") || strCompare(word1, "exit")) 
		{
			//cout << "Found the QUIT command. " << endl;
			callingPlayer->setQuit(true);
			cout << "quitting..." << endl << endl;
		}// END OF "QUIT"
		
		//EQUIP COMMAND
		if (strCompare(word1, "equip") || strCompare(word1, "eq")) //equip command found
		{
			command >> word2;
			callingPlayer->equipItem(word2);
		}// end of EQUIP


		//UNEQUIP COMMAND
		if (strCompare(word1, "unequip") || strCompare(word1, "remove") || strCompare(word1, "rem"))
		{
			command >> word2;
			callingPlayer->unequipItem(word2);

		}// end of UNEQUIP

		// SPAWN ITEM
		if (strCompare(word1, "spawnitem"))
		{
			command >> word2;
			callingPlayer->spawnItem(word2);

		}// END OF SPAWN ITEM

		// DISPLAY INVENTORY
		if (strCompare(word1, "inventory") || strCompare(word1, "inv"))
		{
			callingPlayer->showInventory();
			
		}// END OF INVENTORY

		// DISPLAY STATS
		if (strCompare(word1, "stats") || strCompare(word1, "stat"))
		{
			callingPlayer->displayCharacter();
			system("pause");
			
		}// END OF DISPLAY STATS

		//DROP ITEM
		if (strCompare(word1, "drop") || strCompare(word1, "toss"))
		{
			command >> word2;
			callingPlayer->dropItem(word2);
			
		}// END OF DROP ITEM

		//GET/TAKE/PICK UP ITEM
		if (strCompare(word1, "take") || strCompare(word1, "get"))
		{
			command >> word2;
			callingPlayer->takeItem(word2);

		}//END OF TAKE/GET/PICK UP ITEM

		/*
		if (strCompare(word1, "test"))
		{
			testMenu();
		}
		*/
		


	}
	while (!command.eof());//done searching command

	return 1;
}
