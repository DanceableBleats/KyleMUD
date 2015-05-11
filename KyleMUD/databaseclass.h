#ifndef _MY_DATABASE_CLASS_H_
#define _MY_DATABASE_CLASS_H_


// THIS //
/*
#ifndef _DATABASE_
#define _DATABASE_
#include "databaseclass.h"
#endif
*/




//=============//
// My Includes //
//=============//
#include "stdafx.h"

//=================//
// Not My Includes //
//=================//
//#include <WinSock2.h>
//#include <mysql++.h>


//==========//
// Forwards //
//==========//
class player;
class room;
class item;


//============================//
// Database Class Declaration //
//============================//
class database 
{
private:
	mysqlpp::Connection con;

public:
			database();
			~database();

	bool	characterExists(player*);        //overloaded function!
	bool	characterExists(std::string);         //overloaded function! - one takes a player ptr, the other a string representing the players name.
	bool	invIDExists(player*);
	bool	invIDExists(long long);		//oveload - takes the long long invID instead of player*
	bool	cIDExists(player*);
	bool	cIDExists(long long);
	void	loadCharacter(std::string, player*);
	void	saveNewCharacter(player*);
	void	saveCharacter(std::string, player*);
	void	loadWorldRooms(std::vector<room*>*);
	void	characterList(std::vector<std::string>*);
	void	saveRoom(room*);
	void	spawnItem(std::string, item*);
	void	saveCharacter(player*);
};
#endif