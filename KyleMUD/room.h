#ifndef _MY_ROOM_H_
#define _MY_ROOM_H_


// THIS //
/*
#ifndef _ROOM_
#define _ROOM_
#include "room.h"
#endif
*/


//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "enum.h"
#include "item.h"
#include "inventory.h"

//=================//
// Not My Includes //
//=================//
//#include <string>
//#include <iostream>
//#include <vector>


//==========//
// Forwards //
//==========//
class world;
class player;
class roomInventory;


//=======================//
// Room Class Definition //
//=======================//
class room
{
private:
	int	m_roomID;
	std::string m_description;
	std::vector<player*> m_players;
	roomInventory m_inventory;

	ExitStatus //member variables for each exit direction showing the exit status
		m_n,	m_ne,	m_e,	m_se,
		m_s,	m_sw,	m_w,	m_nw,
		m_up,	m_dn,	m_p;

	int //rID's of linked room
		m_nLinkID,	m_neLinkID,	m_eLinkID,
		m_seLinkID,	m_sLinkID,	m_swLinkID,
		m_wLinkID,	m_nwLinkID,	m_upLinkID,
		m_dnLinkID,	m_pLinkID;

	room // to be filled in with ptr to linked room
		*m_nLink,	*m_neLink,	*m_eLink,
		*m_seLink,	*m_sLink,	*m_swLink,
		*m_wLink,	*m_nwLink,	*m_upLink,
		*m_dnLink,	*m_pLink;




public:  
	friend class world;
	std::vector<item*>::iterator searchInv;
	
							room();
							~room();
	
	int						getRoomID();
	std::string				getDescription();
	std::vector<player*>*	getPlayersInRoom();

	void					setRoomID(int);
	void					setExitStatus(int, int, int, int, int, int, int, int, int, int, int);
	void					setLinkIDS(int, int, int, int, int, int, int, int, int, int, int);
	void					linkRooms(std::vector<room*>*);
	void					setDescription(std::string);
	void					printExits();
	void					printLinks();
	void					playerEnter(player*);
	void					playerExit(player*);
		
	room*					getExitLink(ExitDirection); 
	ExitStatus				getExitStatus(ExitDirection);   
	int						getLinkIDs(ExitDirection);

	void					dropItem(item*);
	item*					pickUpItem(std::string);
			
	void					displayItems();
					
};



#endif