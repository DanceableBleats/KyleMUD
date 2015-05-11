//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "characterclass.h"
#include "room.h"
#include "databaseclass.h"



//=================//
// Not My Includes //
//=================//
//#include <iostream>


//==========//
// Forwards //
//==========//
using namespace std;

long long getRandID();
bool strCompare(string, string);


//=============================//
// Player Class Implimentation //
//=============================//
//Constructors and destructors
			player::player(database *db, connection_ptr conn)
{
	m_logonStatus = 0;
	p_conn = conn;
	m_quit = 0;
	m_ac = 0; // later pull/save this from/to database.
	m_db = db;
	createCharID();
	createInvID(); //creates, checks uniqueness, and saves a unique ID for the player's inventory to tie the players items to it.

	console_output_lock.lock();
	std::cout << '[' << boost::this_thread::get_id() << "]  new Player object created..." << std::endl;
	console_output_lock.unlock();
}

			/*
			player::player(database *db, SOCKET s, sockaddr a)
{
	m_quit = 0;
	m_ac = 0;
	m_db = db;
	playerSock = s;
	playerAddr = a;
	m_pendingLogon = 1;
}
*/

			player::~player()
{
	console_output_lock.lock();
	std::cout << '[' << boost::this_thread::get_id() << "]  player object destroyed." << std::endl;
	console_output_lock.unlock();
}
//Connection info
/*
void		player::setAddrInfo(SOCKET s, sockaddr a)
{
	playerSock = s;
	playerAddr = a;
}
pair<SOCKET, sockaddr> player::getAddrInfo()
{
	return make_pair<SOCKET, sockaddr>(playerSock, playerAddr);
}
int player::getSocket()
{
	return playerSock;
}
*/

//communication/commands
int player::storeCommand(std::string *p_cmdString)
{
	cout << "Storing command, list currently contains " << commandList.size() << " items. " << endl;
	commandList.push_back(p_cmdString);
	cout << "pushed back: " << *p_cmdString << endl;
	cout << "command list now contains " << commandList.size() << " items. " << endl;
	return 1;
}
int player::getTopCommand(std::string *p_string)
{
	if (!commandList.empty())
	{
		*p_string = (*(*commandList.begin()));
		cout << "grabbing string from command list: " << (*(*commandList.begin())) << endl;
		commandList.pop_front();
		return 1;
	}
	else
	{
		return 0;
	}
}
int player::peekTopCommand(std::string *p_string)
{
	if (!commandList.empty())
	{
		p_string = (*commandList.begin());
		return 1;
	}
	else
	{
		return 0;
	}
}

// Character info
void		player::setLive(bool x)
{
	m_characterLive = x;
}
bool		player::isCharacterLive()
{
	return m_characterLive;
}

void		player::createCharID()
{
	do
	{
		m_cID = getRandID();
	}
	while (m_db->cIDExists(m_cID));
}
void		player::setCharID(long long x)
{
	m_cID = x;
}
long long	player::getCharID()
{
	return m_cID;
}

void		player::createInvID()
{
	do
	{
		m_inventory.setInvID(getRandID());
	}
	while (m_db->invIDExists(m_inventory.getInvID()));
	// if invIDExists comes back false then its an unused ID, thus it's good and we stop looping.

}
void		player::setInvID(long long x)
{
	m_inventory.setInvID(x);
}
long long	player::getInvID()
{
	return m_inventory.getInvID();
}

void		player::setName(string x)
{
	m_name = x;
}
string		player::getName()
{
	return m_name;
}

void		player::setRace(string x)
{
	m_race = x;
}
string		player::getRace()
{
	return m_race;
}

void		player::setCls(string x)
{
	m_cls = x;
}
string		player::getClass()
{
	return m_cls;
}

//Character stats
void		player::setStr(int x)
{
	m_str = x;
}
void		player::adjStr(int x)
{
	m_str += x;
}
int			player::getStr()
{
	return m_str;
}

void		player::setAgi(int x)
{
	m_agi = x;
}
void		player::adjAgi(int x)
{
	m_agi += x;
}
int			player::getAgi()
{
	return m_agi;
}

void		player::setPer(int x)
{
	m_per = x;
}
void		player::adjPer(int x)
{
	m_per += x;
}
int			player::getPer()
{
	return m_per;
}

void		player::setWis(int x)
{
	m_wis = x;
}
void		player::adjWis(int x)
{
	m_wis += x;
}
int			player::getWis()
{
	return m_wis;
}

void		player::setAC(int x)
{
	m_ac = x;
}
void		player::adjAC(int x)
{
	m_ac += x;
}
int			player::getAC()
{
	return m_ac;
}

//display
void		player::displayCharacter()
{
	cout 
		<< "Name:\t\t" << m_name << endl
		<< "Race:\t\t" << m_race << endl
		<< "class:\t\t" << m_cls << endl
		<< "Str:\t\t" << m_str << endl
		<< "Agi:\t\t" << m_agi << endl
		<< "Per:\t\t" << m_per << endl
		<< "Wis:\t\t" << m_wis << endl
		<< "AC:\t\t" << m_ac << endl;
}

//movement
void		player::movePlayerToRoom(room *room)
{
	m_playerRoom = room;
	//cout << m_playerRoom->getDescription() << endl;
}
room*		player::getPlayerRoom()
{
	return m_playerRoom;
}

//quitting
bool		player::getQuit()
{
	return m_quit;
}
void		player::setQuit(bool quit)
{
	if (quit)
	{
		m_quit = true;
	}
}

//equipping and unequipping items
void		player::equipItem(string itemString)
{
	item* p_item;
	vector<item*>::iterator *it = &searchinv;
	if (m_inventory.searchInv(itemString, &p_item, it))
	{
		item *p_equipped;
		if (!m_inventory.checkEquipped(p_item->getEquipmentSlot(), &p_equipped))
		{
			adjStr(p_item->getStrBonus());
			adjAgi(p_item->getAgiBonus());
			adjPer(p_item->getPerBonus());
			adjWis(p_item->getWisBonus());
			adjAC(p_item->getACBonus());

			m_inventory.removeItem(it);
			m_inventory.addEquip(p_item);
	
			cout << p_item->getItemName() << " equipped." << endl;
			system("pause");
		}
		else
		{
			cout << "You are already wearing a " << p_equipped->getItemName() << endl;
			system("pause");
		}
	}
	else
	{
		cout << "You don't have any " << itemString << endl;
		system("pause");
	}
}
void		player::unequipItem(string itemString)
{
	item* p_item;
	map<EquipmentSlot, item*>::iterator *it = &searcheq;
	if (m_inventory.searchEquip(itemString, &p_item, it))
	{
		adjStr(0 - (p_item->getStrBonus()));
		adjAgi(0 - (p_item->getAgiBonus()));
		adjPer(0 - (p_item->getPerBonus()));
		adjWis(0 - (p_item->getWisBonus()));
		adjAC(0 - (p_item->getACBonus()));

		m_inventory.removeEquip(it);
		m_inventory.addItem(p_item);
		
		cout << p_item->getItemName() << " removed." << endl;
		system("pause");
	}
	else
	{
		cout << "You aren't wearing a " << itemString << endl;
		system("pause");
	}
}

//Spawn items for testig
void		player::spawnItem(string str)
{
	item *p_item = new item;
	m_db->spawnItem(str, p_item);
	m_inventory.addItem(p_item);

	cout << p_item->getItemName() << " spawned." << endl;
	system("pause");

}


void		player::showInventory()
{
	cout << "You are wearing: " << endl;
	m_inventory.showEquipment();

	cout << endl << "You are holding: " << endl;
	m_inventory.showInventory();

	system("pause");

}

void		player::setDB(database *db)
{
	m_db = db;
}

void		player::dropItem(string itemString)
{
	item *p_item;
	vector<item*>::iterator *it = &searchinv;
	if (m_inventory.searchInv(itemString, &p_item, it))
	{
		m_inventory.removeItem(it);
		m_playerRoom->dropItem(p_item);
	}
	else
	{
		cout << "You are not holding a " << itemString << endl;
		system("pause");
	}
}

void		player::takeItem(string itemString)
{
	item *p_item;
	p_item = m_playerRoom->pickUpItem(itemString);
	if (p_item != NULL)
	{
		m_inventory.addItem(p_item);
	}
}

playerInventory*	player::getInvPtr()
{
	return &m_inventory;
}

void		player::setLogonStatus(int i)
{
	m_logonStatus = i;
}
int			player::getLogonStatus()
{
	return m_logonStatus;
}