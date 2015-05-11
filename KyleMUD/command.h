#ifndef _MY_COMMAND_H_
#define _MY_COMMAND_H_


// THIS //
/*
#ifndef _COMMAND_
#define _COMMAND_
#include "command.h"
#endif
*/




//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "enum.h"



//=================//
// Not My Includes //
//=================//
//#include <string>


//==========//
// Forwards //
//==========//
class player;
class room;


//============================//
// Command Parser Declaration //
//============================//
class command 
{
private:
	room* m_targetRoom;
	room* m_currentRoom;
	player* m_targetPlayer;
	player* m_callingPlayer;


	Action m_action; //enum Action
	std::string m_modifier;
	std::string m_content;


	
public:
	friend class room;
				
				command();
				~command();
	
	bool		translateCommand(std::string, player*, room*);


};
#endif