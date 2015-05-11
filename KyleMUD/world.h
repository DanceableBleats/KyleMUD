#ifndef _MY_WORLD_H_
#define _MY_WORLD_H_


// THIS // 
/*
#ifndef _WORLD_
#define _WORLD_
#include "world.h"
#endif
*/

//============//
//My Includes //
//============//
#include "stdafx.h"
#include "room.h"
#include "characterclass.h"
#include "databaseclass.h"

//=================//
// Not My Includes //
//=================//
//#include <string>
//#include <vector>


//==========//
// Forwards //
//==========//
class database;
class room;


//========================//
// World Class Definition //
//========================/
class world
{
private:
	std::vector<room*> worldRooms;
	std::vector<player*> m_worldPlayers;

public:
				world();
				~world();

	void		initialize(database*);
	room*		getTopRoom();
	void		display();
	void		saveWorld(database*);
	void		changeWorld();

	void		addPlayerToWorld(player*);
	void		removePlayerfromWorld(player*);

};



#endif