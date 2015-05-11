//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "room.h"
#include "characterclass.h"


//==========//
// Forwards //
//==========//
using namespace std;

bool strCompare(std::string, std::string);


//===========================//
// Room Class Implimentation //
//===========================//
//construction and destruction
room::						room()
{
		m_nLinkID = 0,	m_neLinkID = 0,	m_eLinkID = 0,
		m_seLinkID = 0,	m_sLinkID = 0,	m_swLinkID = 0,
		m_wLinkID = 0,	m_nwLinkID = 0,	m_upLinkID = 0,
		m_dnLinkID = 0,	m_pLinkID = 0;	
}
room::						~room()
{

}

//get functions
int room::					getRoomID()
{
	return m_roomID;
}
std::string room::				getDescription()
{
	return m_description;
}
std::vector<player*>* room::getPlayersInRoom()
{
	return &m_players;

}

//set functions
void room::					setRoomID(int x)
{
	m_roomID = x;
}
void room::					setExitStatus(int n, int ne, int e, int se, int s, int sw, int w, int nw, int up, int dn, int p)
{
	m_n = (ExitStatus)n;  //cast int into ExitStatus
	m_ne = (ExitStatus)ne;
	m_e = (ExitStatus)e;
	m_se = (ExitStatus)se;
	m_s = (ExitStatus)s;
	m_sw = (ExitStatus)sw;
	m_w = (ExitStatus)w;
	m_nw = (ExitStatus)nw;
	m_up = (ExitStatus)up;
	m_dn = (ExitStatus)dn;
	m_p = (ExitStatus)p;
}
void room::					setLinkIDS(int n, int ne, int e, int se, int s, int sw, int w, int nw, int up, int dn, int p)
{
	m_nLinkID = n;
	m_neLinkID = ne;
	m_eLinkID = e;
	m_seLinkID = se;
	m_sLinkID = s;
	m_swLinkID = sw;
	m_wLinkID = w;
	m_nwLinkID = nw;
	m_upLinkID = up;
	m_dnLinkID = dn;
	m_pLinkID = p;	
}
void room::					linkRooms(std::vector<room*> *worldRooms)
{
	vector<room*>::iterator it; 

	if (m_nLinkID > 0)
	{

		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_nLinkID == rm->getRoomID())
			{
				m_nLink = rm;
				cout << "linking room: " << m_roomID << " north to " << rm->getRoomID() << endl;
			}
		}
	}	


	if (m_neLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_neLinkID == rm->m_roomID)
			{
				m_neLink = rm;
				cout << "linking room: " << m_roomID << " northeast to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_eLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_eLinkID == rm->m_roomID)
			{
				m_eLink = rm;
				cout << "linking room: " << m_roomID << " east to " << rm->getRoomID() << endl;

			}
		}
	}


	if (m_seLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_seLinkID == rm->m_roomID)
			{
				m_seLink = rm;
				cout << "linking room: " << m_roomID << " southeast to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_sLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_sLinkID == rm->m_roomID)
			{
				m_sLink = rm;
				cout << "linking room: " << m_roomID << " south to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_swLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_swLinkID == rm->m_roomID)
			{
				m_swLink = rm;
				cout << "linking room: " << m_roomID << " southwest to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_wLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_wLinkID == rm->m_roomID)
			{
				m_wLink = rm;
				cout << "linking room: " << m_roomID << " west to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_nwLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_nwLinkID == rm->m_roomID)
			{
				m_nwLink = rm;
				cout << "linking room: " << m_roomID << " northwest to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_upLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_upLinkID == rm->m_roomID)
			{
				m_upLink = rm;
				cout << "linking room: " << m_roomID << " up to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_dnLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_dnLinkID == rm->m_roomID)
			{
				m_dnLink = rm;
				cout << "linking room: " << m_roomID << " down to " << rm->getRoomID() << endl;
			}
		}
	}


	if (m_pLinkID > 0)
	{
		for (it = worldRooms->begin(); it != worldRooms->end(); it++)
		{
			room *rm;
			rm = *it;
			if (m_pLinkID == rm->m_roomID)
			{
				m_pLink = rm;
				cout << "linking room: " << m_roomID << " portal to " << rm->getRoomID() << endl;
			}
		}
	}



}
void room::					setDescription(std::string str)
{
	m_description = str;
}

//enter and exit
void room::					playerEnter(player *pplayer)
{
	m_players.push_back(pplayer);
}
void room::					playerExit(player *pplayer)
{
	vector<player*>::iterator iter;
	for (iter = m_players.begin(); iter != m_players.end(); iter++)
	{
		player *p;
		p = *iter;
		if (p->getName() == pplayer->getName())
		{
			m_players.erase(iter);
		}
	}
}

//travel
room* room::				getExitLink(ExitDirection x) //only works for north right now.
{
	switch (x)
	{
	case NORTH:
		{
			//cout << m_nLink->getDescription() << endl; // fails here.
			return m_nLink;
		}
	case NORTHEAST:
		{
			return m_neLink;
		}
	case EAST:
		{
			return m_eLink;
		}
	case SOUTHEAST:
		{
			return m_seLink;
		}
	case SOUTH:
		{
			return m_sLink;
		}
	case SOUTHWEST:
		{
			return m_swLink;
		}
	case WEST:
		{
			return m_wLink;
		}
	case NORTHWEST:
		{
			return m_nwLink;
		}
	case UP:
		{
			return m_upLink;
		}
	case DOWN:
		{
			return m_dnLink;
		}
	case PORTAL:
		{
			return m_pLink;
		}

	}
}
ExitStatus room::			getExitStatus(ExitDirection x)
{
	switch (x)
	{
	case NORTH:
		{
			return m_n;
			break;
		}
	case NORTHEAST:
		{
			return m_ne;
			break;
		}
	case EAST:
		{
			return m_e;
			break;
		}
	case SOUTHEAST:
		{
			return m_se;
			break;
		}
	case SOUTH:
		{
			return m_s;
			break;
		}
	case SOUTHWEST:
		{
			return m_sw;
			break;
		}
	case WEST:
		{
			return m_w;
			break;
		}
	case NORTHWEST:
		{
			return m_nw;
			break;
		}
	case UP:
		{
			return m_up;
			break;
		}
	case DOWN:
		{
			return m_dn;
			break;
		}
	case PORTAL:
		{
			return m_p;
			break;
		}

	}//end of switch
}
int room::					getLinkIDs(ExitDirection x)
{
	switch (x)
	{
	case NORTH:
		{
			return m_nLinkID;
			break;
		}
	case NORTHEAST:
		{
			return m_neLinkID;
			break;
		}
	case EAST:
		{
			return m_eLinkID;
			break;
		}
	case SOUTHEAST:
		{
			return m_seLinkID;
			break;
		}
	case SOUTH:
		{
			return m_sLinkID;
			break;
		}
	case SOUTHWEST:
		{
			return m_swLinkID;
			break;
		}
	case WEST:
		{
			return m_wLinkID;
			break;
		}
	case NORTHWEST:
		{
			return m_nwLinkID;
			break;
		}
	case UP:
		{
			return m_upLinkID;
			break;
		}
	case DOWN:
		{
			return m_dnLinkID;
			break;
		}
	case PORTAL:
		{
			return m_pLinkID;
			break;
		}

	}//end of switch
}


void room::dropItem(item *p_item)
{
	m_inventory.addItem(p_item);

}

item* room::pickUpItem(std::string itemString)
{
	item *p_item;
	vector<item*>::iterator *it = &searchInv;
	if (m_inventory.searchInv(itemString, &p_item, it))
	{
		m_inventory.removeItem(it);
		return p_item;
	}
	else
	{
		cout << "There is no " << itemString << " here." << endl;
		system("pause");
		return NULL;
	}

}

void room::displayItems()
{
	m_inventory.showInventory();
}




