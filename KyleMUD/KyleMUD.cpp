//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "characterclass.h"
#include "databaseclass.h"
#include "command.h"
#include "world.h"
#include "serverclass.h"

//=================//
// Not My Includes //
//=================//
//#include <sstream> //getline()
//#include <iostream> //cout
//#include <cstdlib> //rand()
//#include <time.h>// time()


//==========//
// Forwards //
//==========//
using namespace std;

bool newChar(player*, database*);
long long getRandID();		//random number - Unique 12 digit ID
int getRand(int, int);		//random number in range
void testMenu();			//testing menu

//========//
// GLOBAL // <- extern declared in global.h, must be declared here as well.
//========//
database *gdbptr;
boost::mutex console_output_lock; 

//========================//
// Main Application Start //
//========================//
int main(int argc, char* argv[])
{
	//Assign port for listening on, default: 65005. 
	unsigned int listenPort;
	if ( argc < 2 ) { listenPort = 65005; }
	else if ((*argv[1] <= 65535) && (*argv[1] > 0)) { listenPort = *argv[1]; }
	else { listenPort = 65005; }

	//=====================//
	// Initialize Database //
	//=====================//
	gdbptr = new database;

	//==================//
	// Initialize World //
	//==================//
	world *p_world = new world;
	p_world->initialize(gdbptr);

	//===================//
	// Initialize Server //
	//===================//
	boost::shared_ptr<boost::asio::io_service> p_io_service(new boost::asio::io_service);
	boost::shared_ptr<server> p_gameServer(new server(p_io_service, listenPort));
	boost::shared_ptr<boost::asio::io_service::work> p_work(new boost::asio::io_service::work(*p_io_service)); // <-- stops io_service from terminating prematurely.
	
	//==========//
	// Pointers //
	//==========//
	//fd_set *p_FDSet;		//DEPRECIATING
	//player *p_player;		//DEPRECIATING
	//string *p_string;		//DEPRECIATING

	//=======//
	// Other //
	//=======//
	//int selectRes;		//DEPRECIATING


	//Fork off worker threads:
	boost::thread_group threadGroup;
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		threadGroup.create_thread(boost::bind(&workerThread, p_io_service));
	}
	boost::this_thread::sleep( boost::posix_time::milliseconds( 3000 ) ); //<--unnecessary...



	//begin accepting connections, should continue accepting on a loop...
	p_gameServer->startAcceptLoop();









							//==============================================//
							// <<<<<<<< NEW MULTIPLAYER GAME LOOP >>>>>>>>> //
							//==============================================//
	


















	std::cin.ignore();
	p_io_service->stop();
	threadGroup.join_all();
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.ignore();
	return 0;











			//for (it2 = connectingPlayerList.begin(); it2 != connectingPlayerList.end(); ++it2)
			//{
			//	if (FD_ISSET((*it2)->getSocket(), p_FDSet))
			//	{
			//		int messagesRecvd = 0;
			//		if ((messagesRecvd = gameServer.readPlayerInput((*it2))) > 0)
			//		{
			//			p_string = new string;
			//			if ((*it2)->getTopCommand(p_string))
			//			{
			//				if (p_db->characterExists(*p_string))
			//				{
			//					p_db->loadCharacter(*p_string, (*it2));
			//					gameServer.sendStringToSocket((*it2)->getSocket(), "Character loaded.");
			//					cout << "character loaded" << endl;
			//					playerList.push_back((*it2));
			//					removeMeLater++;

			//				}
			//				else
			//				{
			//					gameServer.sendStringToSocket((*it2)->getSocket(), "Character not found. Try again.");
			//					cout << "character " << (*p_string) << " not found" << endl;
			//				}//end of if: if char exiss db check
			//			}//end of if: retreiving command
			//			delete p_string;
			//			p_string = NULL;
			//		}//end of if looking for messages received from player
			//	}// end of if looking to see if player is part ofselect()d set
			//}// end of for: iterating through list




		


	//===========//
	// Shut Down //
	//===========//
	p_world->saveWorld(gdbptr);
	//p_db->saveCharacter(p_player);
	p_io_service.reset();
	delete gdbptr;
	delete p_world;
	//delete p_player;
	return 0;
}


//===========//
// TEST MENU //
//===========//
/*
void testMenu()
{
	// <<<<< TESTING MENU >>>>> //
	world *p_testWorld = new world;
	database *p_testDB = new database;
	player *p_testPlayer = new player(p_testDB);
	bool quit = false;
	do
	{
		int choice;
		system("cls");
		std::cout << endl << " TESTING MENU   Active character: " << p_testPlayer->getName() << endl
			<< " ====================================" << endl
			<< " 1 - List all characters." << endl 
			<< " 2 - Create a new character." << endl
			<< " 3 - Display a character." << endl
			<< " 4 - Create a new room. " << endl 
			<< " 5 - Test world save. " << endl
			<< " 6 - Test RNG. " << endl
			<< endl	<< " Enter choice:   (0 to quit)" << endl << endl << endl << "#: ";

		cin >> choice;

		switch (choice)
		{
		case 1: 
			{
				system("cls");
				cout << "Character list: " << endl << "===============" << endl << endl;
				vector<string> *p_characterList = new vector<string>;
				p_testDB->characterList(p_characterList);
				vector<string>::iterator it;
			


				for (it = p_characterList->begin(); it != p_characterList->end(); it++) 
				{
					cout << *it << endl;
				}

				delete p_characterList;
				cout << endl;
				system("pause");
				break;
			}//end of case 1


		case 2: 
			{
				system("cls");
				cin.ignore(10, '\n');
				player *p_newChar = new player(p_testDB);
				mysqlpp::sql_text name;
				cout << "Enter character name: " << endl << endl << "#: ";
				std::getline(cin, name);
				
				if (!p_testDB->characterExists(name))
				{
					p_newChar->setName(name);
					cout << name << " is a new character! Choose your Race!" << endl << endl << "#: ";
					mysqlpp::sql_text race;
					getline(cin, race);
					p_newChar->setRace(race);
		
					cout << "choose your class, " << name << endl << endl << "#: ";
					mysqlpp::sql_text cls;
					getline(cin, cls);
					p_newChar->setCls(cls);

					cout << "Set your stats, starting with Strength: " << endl << endl << "#: ";
					mysqlpp::sql_int str, agi, per, wis;
					cin >> str;
					p_newChar->setStr(str);

					cout << "Set Agility: " << endl<< endl << "#: ";
					cin >> agi;
					p_newChar->setAgi(agi);

					cout << "Percision: " << endl << endl << "#: ";
					cin >> per;
					p_newChar->setPer(per);

					cout << "And Wisdom: " << endl << endl << "#: ";
					cin >> wis;
					p_newChar->setWis(wis);

					p_newChar->setLive(true);
					p_testDB->saveNewCharacter(p_newChar);
					cout << "InventoryID: " << p_newChar->getInvID() << endl;
					cout << "Character Saved!" << endl;
					system("pause.exe");
				}
				else if (p_testDB->characterExists(name))
				{
					cout << "Character already exists!" << endl << endl;
					system("pause");
				}
				else
				{
					cout << "Unable to tell if character exists or not... PROBLEM!" << endl;
					system("pause");
				}
				delete p_newChar;
				break;
			} // END OF CASE 2



		case 3:
			{
				system("cls");
				cin.ignore(10, '\n');
				player *p_dispChar = new player(p_testDB);
				mysqlpp::sql_text name;
				cout << "Enter character name: " << endl << endl << "#: ";
				std::getline(cin, name);
					
				if (p_testDB->characterExists(name))
				{
					p_testDB->loadCharacter(name, p_dispChar);
					cout << endl;
					p_dispChar->displayCharacter();
					cout << p_dispChar->getInvID() << endl;
					system("pause");
				}
				else if (!p_testDB->characterExists(name))
				{
					cout << "Could not find that character in database." << endl;
					system("pause");
				}
				else
				{
					cout << "Unable to tell if character exists or not... PROBLEM!" << endl;
					system("pause");
				}
				delete p_dispChar;
				break;
			} //end of case 3



		case 4:
			{
				system("cls");
				cin.ignore(10, '\n');

				cout << "Currently this is just creates a new room and saves it. Use a unique room ID! " << endl << endl;
				cout << "Enter a room ID: " << endl << endl << "#: ";

				int rID = 0;
				cin >> rID;
				cin.ignore(10, '\n');

				room *p_testRoom = new room;
				//initialize the new room, later these steps should probably be part of the constructor.
				p_testRoom->setRoomID(rID);
				p_testRoom->setExitStatus(0,0,0,0,0,0,0,0,0,0,0);
				p_testRoom->setLinkIDS(0,0,0,0,0,0,0,0,0,0,0);
				p_testRoom->setDescription("This is a test room.");

				cout << p_testRoom->getExitStatus(NORTH) << p_testRoom->getExitStatus(NORTHEAST) << p_testRoom->getExitStatus(EAST) << p_testRoom->getExitStatus(SOUTHEAST) 
					<< p_testRoom->getExitStatus(SOUTH) << p_testRoom->getExitStatus(SOUTHWEST) << p_testRoom->getExitStatus(WEST) << p_testRoom->getExitStatus(NORTHWEST) << 
					p_testRoom->getExitStatus(UP) << p_testRoom->getExitStatus(DOWN) << p_testRoom->getExitStatus(PORTAL) << endl;
					
				cout << p_testRoom->getLinkIDs(NORTH) << p_testRoom->getLinkIDs(NORTHEAST) << p_testRoom->getLinkIDs(EAST) << p_testRoom->getLinkIDs(SOUTHEAST) 
					<< p_testRoom->getLinkIDs(SOUTH) << p_testRoom->getLinkIDs(SOUTHWEST) << p_testRoom->getLinkIDs(WEST) << p_testRoom->getLinkIDs(NORTHWEST) << 
					p_testRoom->getLinkIDs(UP) << p_testRoom->getLinkIDs(DOWN) << p_testRoom->getLinkIDs(PORTAL) << endl;

				cout << p_testRoom->getDescription() << endl << endl;
				system("pause");

					
				p_testDB->saveRoom(p_testRoom);
				delete p_testRoom;
				cout << "Saved. Check DB." << endl << endl;
				system("pause");
				break;

			}//end of case 4



		case 5:
			{
				system("cls");
				cin.ignore(10, '\n');
				cout << "This will only make a slight change to the description of " << endl
					<< "rooms. The actual save function happens at quit." << endl << endl;
				p_testWorld->changeWorld();
				cout << "It's Done. There should now be \"...Test\" at the end of" << endl << 
					"every room desription. Quit to save." << endl << endl;
				system("pause");

			}//end of case 5



		case 6:
			{
				system("cls");
				cin.ignore(10, '\n');
				for ( int i = 1; i <= 100; ++i )
				{
					cout << (unsigned)getRand(0, 9);
					if ( i % 20 == 0)
					{
						cout << endl;
					}
				}

				long long x = getRand(0, 9);
				for (int i = 1; i < 14; ++i)
				{
					x += (pow((float)10, i) * getRand(0, 9));
				}
				cout << endl << endl << x << endl;
				system("pause");

			}// END OF CASE 6


		case 0:
			{
				quit = true;
				break;
			} // END OF CASE 0 - QUIT

		}// END OF SWITCH
	
	}while (!quit);//end of test menu loop

	delete p_testPlayer;
	delete p_testWorld;
	delete p_testDB;

}
*/

//=================//
// OTHER FUNCTIONS //
//=================//
bool newChar(player *p_newChar, database *p_db)
{
	mysqlpp::sql_text name;
	cout << "Enter character name: " << endl << endl << "#: ";
	std::getline(cin, name);
				
	if (!p_db->characterExists(name))
	{
		p_newChar->setName(name);
		cout << name << " is a new character! Choose your Race!" << endl << endl << "#: ";
		mysqlpp::sql_text race;
		getline(cin, race);
		p_newChar->setRace(race);
		
		cout << "choose your class, " << name << endl << endl << "#: ";
		mysqlpp::sql_text cls;
		getline(cin, cls);
		p_newChar->setCls(cls);

		cout << "Set your stats, starting with Strength: " << endl << endl << "#: ";
		mysqlpp::sql_int str, agi, per, wis;
		cin >> str;
		p_newChar->setStr(str);

		cout << "Set Agility: " << endl<< endl << "#: ";
		cin >> agi;
		p_newChar->setAgi(agi);

		cout << "Percision: " << endl << endl << "#: ";
		cin >> per;
		p_newChar->setPer(per);

		cout << "And Wisdom: " << endl << endl << "#: ";
		cin >> wis;
		p_newChar->setWis(wis);

		p_newChar->setLive(true);
		p_db->saveNewCharacter(p_newChar);
		cout << "InventoryID: " << p_newChar->getInvID() << endl;
		cout << "Character Saved!" << endl;
		system("pause.exe");
		return true;
	}
	else if (p_db->characterExists(name))
	{
		cout << "Character already exists!" << endl << endl;
		system("pause");
		return false;
	}
	else
	{
		cout << "Unable to tell if character exists or not... PROBLEM!" << endl;
		system("pause");
		return false;
	}




}
bool				strCompare(std::string str1, std::string str2)
{
	if (str1.length() != str2.length()) {return 0;}
	for (int i = 0; i != str1.length(); ++i)
	{
		if (toupper(str1[i]) != toupper(str2[i])) {return 0;}
	}
	return 1;
}
ExitDirection		translateDirection(std::string str)
{
	if (strCompare(str, "north") || strCompare(str, "n"))
	{
		return NORTH;
	}
	else if (strCompare(str, "northeast") || strCompare(str, "ne"))
	{
		return NORTHEAST;
	}
	else if (strCompare(str, "east") || strCompare(str, "e"))
	{
		return EAST;
	}
	else if (strCompare(str, "southeast") || strCompare(str, "se"))
	{
		return SOUTHEAST;
	}
	else if (strCompare(str, "south") || strCompare(str, "s"))
	{
		return SOUTH;
	}
	else if (strCompare(str, "southwest") || strCompare(str, "sw"))
	{
		return SOUTHWEST;
	}
	else if (strCompare(str, "west") || strCompare(str, "w"))
	{
		return WEST;
	}
	else if (strCompare(str, "northwest") || strCompare(str, "nw"))
	{
		return NORTHWEST;
	}
	else if (strCompare(str, "up") || strCompare(str, "u"))
	{
		return UP;
	}
	else if (strCompare(str, "down") || strCompare(str, "d"))
	{
		return DOWN;
	}
	else if (strCompare(str, "portal") || strCompare(str, "p"))
	{
		return PORTAL;
	}
	else 
	{
		cout << "Error: Not a direction? " << endl << endl;
		system("pause");
	}
}
long long			getRandID()
{				
	long long x = getRand(0, 9);
	for (int i = 1; i < 14; ++i)
	{
		x += (pow((float)10, i) * getRand(0, 9));
	}
	return x;
}
int					getRand(int min, int max)
{
	//srand(time(NULL)); 
	int range=(max-min)+1;
	return (min + int(range*rand()/(RAND_MAX + 1.0)));
}
void workerThread(boost::shared_ptr<boost::asio::io_service> p_io_service)
{
	console_output_lock.lock();
	std::cout << "[" << boost::this_thread::get_id() << "] Thread starting." << std::endl;
	console_output_lock.unlock();

	p_io_service->run();

	console_output_lock.lock();
	std::cout << "[" << boost::this_thread::get_id() << "] Thread ending." << std::endl;
	console_output_lock.unlock();
}



//========================//
// Old Single Player Code //
//========================//

	/*
	// <<<<< LOAD CHARACTER >>>>> //	
	bool characterLoaded = false;
	do
	{
		system("cls");
		cout << "Choose character: " << endl << endl;
		string name = "";
		getline(cin, name);

		if (p_db->characterExists(name))
		{
			p_db->loadCharacter(name, p_player);
			//p_player->setDB(p_db);
			p_player->movePlayerToRoom(p_world->getTopRoom());//puts the player in a room. 
			cout << p_player->getName() << " loaded!" << endl << endl;
			characterLoaded = true;
			system("pause");
		}
		else if (!p_db->characterExists(name))		
		{
			std::cout << "Character does not exist! " << endl;
			if (newChar(p_player, p_db))
			{
				p_player->movePlayerToRoom(p_world->getTopRoom());//puts the player in a room. 
				cout << p_player->getName() << " loaded!" << endl << endl;
				characterLoaded = true;
				system("pause");
			}
		}
	}
	while(!characterLoaded);


	
	// <<<<< GAME LOOP >>>>> //
	command *p_cmdObj = new command;
	do
	{
		system("cls");
		cout << p_player->getPlayerRoom()->getDescription() << endl;
		p_player->getPlayerRoom()->displayItems();
		
		cout << endl << endl << "#: ";
		string input = "";
		getline(cin, input);
		
		p_cmdObj->translateCommand(input, p_player, p_player->getPlayerRoom());


	}
	while (!p_player->getQuit());

	*/
