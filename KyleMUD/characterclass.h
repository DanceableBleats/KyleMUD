#ifndef _MY_CHARACTERCLASS_H_
#define _MY_CHARACTERCLASS_H_
//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "inventory.h"
#include "room.h"
#include "serverclass.h"
#include "connectionclass.h"

//==========//
// Forwards //
//==========//
class room;
class database;
class connection;

//=============================//
// Character Class Declaration //
//=============================//
class player 
{
	friend class connection;
private:
	std::string m_name, m_race, m_cls;
	int m_str, m_agi, m_per, m_wis, m_ac;
	room *m_playerRoom;
	playerInventory m_inventory;
	long long m_inventoryID, m_cID;
	database *m_db;
	bool m_quit;
	bool m_characterLive;
	std::list<std::string*> commandList;
	int m_logonStatus;


public:
	std::vector<item*>::iterator searchinv;
	std::map<EquipmentSlot, item*>::iterator searcheq;
	connection_ptr p_conn;
	
						player(database*, connection_ptr);
						~player();


	int					storeCommand(std::string*);
	int					getTopCommand(std::string*);
	int					peekTopCommand(std::string*);

	void				setLive(bool);
	bool				isCharacterLive();

	void				createCharID();
	void				setCharID(long long);
	long long			getCharID();

	void				createInvID();
	void				setInvID(long long);
	long long			getInvID();

	void				setName(std::string);
	std::string			getName();

	void				setRace(std::string);
	std::string			getRace();

	void				setCls(std::string);
	std::string			getClass();

	void				setStr(int);
	void				adjStr(int);
	int					getStr();

	void				setAgi(int);
	void				adjAgi(int);
	int					getAgi();

	void				setPer(int);
	void				adjPer(int);
	int					getPer();

	void				setWis(int);
	void				adjWis(int);
	int					getWis();

	void				setAC(int);
	void				adjAC(int);
	int					getAC();

	void				displayCharacter();
		
	void				movePlayerToRoom(room*);
	room*				getPlayerRoom();

	bool				getQuit();
	void				setQuit(bool);

	void				equipItem(std::string);
	void				unequipItem(std::string);


	void				spawnItem(std::string);

	void				showInventory();

	void				setDB(database*);

	void				dropItem(std::string);
	void				takeItem(std::string);

	playerInventory*	getInvPtr();
	void				setLogonStatus(int);
	int					getLogonStatus();




};
#endif