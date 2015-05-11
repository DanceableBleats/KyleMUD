

//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "world.h"
#include "databaseclass.h"


//==========//
// Forwards //
//==========//
using namespace std;


//============================//
// World Class Implimentation //
//============================//
world::world()
{
	//pRoomList = &worldRooms;
}
world::~world()
{


}

void world::initialize(database *db)
{
	//instances world objects for each row retrned and adds a ptr to each obj to worldRooms
	db->loadWorldRooms(&worldRooms);

	//link rooms together
	vector<room*>::iterator it;
	for (it = worldRooms.begin(); it != worldRooms.end(); it++) //iterate through each room in the world.
	{
		room *rm;
		rm = *it;
		rm->linkRooms(&worldRooms);
	}


}

room* world::getTopRoom()
{
	return worldRooms.front();
}

void world::saveWorld(database *db)
{
	vector<room*>::iterator it;
	for (it = worldRooms.begin(); it != worldRooms.end(); it++) //iterate through each room in the world.
	{
		room *rm;
		rm = *it;
		db->saveRoom(rm);
	}
	
}

void world::changeWorld() //TEST FUNCTION FOR TESTING SAVEWORLD --^
{
	vector<room*>::iterator it;
	for (it = worldRooms.begin(); it != worldRooms.end(); it++) //iterate through each room in the world.
	{
		string description = "";
		room *rm;
		rm = *it;
		description = rm->getDescription();
		description.append(" ...Test");
		rm->setDescription(description);
	}
	
}

void world::addPlayerToWorld(player *p_player)
{
	m_worldPlayers.push_back(p_player);
}

void world::removePlayerfromWorld(player *p_player)
{
	vector<player*>::iterator it;
	for (it = m_worldPlayers.begin(); it != m_worldPlayers.end(); ++it)
	{
		if ( p_player->getName() == (*it)->getName() )
		{

			m_worldPlayers.erase(it);
		}
	}
	
}