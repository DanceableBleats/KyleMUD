#ifndef _MY_ENUM_H_
#define _MY_ENUM_H_

// THIS //
/*
#ifndef _ENUM_
#define _ENUM_
#include "enum.h"
#endif
*/

//=====================//
// Pre-compiled header //
//=====================//
#include "stdafx.h"


enum ExitStatus
{
	NO_EXIT = 0,			// 0
	YES_EXIT,				// 1
	EXIT_DOOR_OPEN,			// 2	
	EXIT_DOOR_CLOSED,		// 3
	EXIT_DOOR_LOCKED,		// 4
	EXIT_OBSTRUCTION		// 5
};

enum ExitDirection
{
	NORTH,			//   0 
	NORTHEAST,		//   1
	EAST,			//   2
	SOUTHEAST,		//   3
	SOUTH,			//   4
	SOUTHWEST,		//   5
	WEST,			//   6
	NORTHWEST,		//   7
	UP,				//   8
	DOWN,			//   9
	PORTAL			//  10

};

enum Action
{
	GO				// 1





};

enum EquipmentSlot
{
	NOEQUIP = -1,	// -1 error cant equip this item
	HEAD = 0,		// 0
	NECK,			// 1
	SHOULDERS,		// 2
	ARMS,			// 3
	LHAND,			// 4
	RHAND,			// 5
	FINGER,			// 6
	CHEST,			// 7
	BELT,			// 8
	LEGS,			// 9
	FEET,			// 10
};

enum FileDescSet //readfds, recvfds, writefds, exceptfds, pendingfds, masterfds, listenfds;
{
	FDSETERROR = -1,	//-1
	READFDS = 0,		// 0
	WRITEFDS,			// 1
	EXCEPTFDS,			// 2
	RECVFDS,			// 3
	PENDINGFDS,			// 4
	MASTERFDS,			// 5
	LISTENFDS			// 6
};






#endif