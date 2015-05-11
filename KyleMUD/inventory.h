#ifndef _MY_INVENTORY_H_
#define _MY_INVENTORY_H_


// THIS //
/*
#ifndef _INVENTORY_
#define _INVENTORY_
#include "inventory.h"
#endif
*/





//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "enum.h"
#include "item.h"


//================//
//Not My Includes //
//================//
//#include <vector>
//#include <map>


//==========//
// Forwards //
//==========//
class item;
class equipment;
class container;


//==================================//
// Base Inventory Class Declaration //
//==================================//

class inventory //base class for inventory derived objects, will never actually be instanced.
{
private:
	long long m_inventoryID;
public:
	long long	getInvID();
	void		setInvID(long long);
//	void		createNewInvID();
};



//====================================//
// Player Inventory Class Declaration //
//====================================//

class playerInventory : public inventory  // player inventory, root inventory object for all player objects.
{
private:
	std::vector<item*> m_itemList;
	std::vector<container*> m_containerList;
	std::map<EquipmentSlot, item*, std::less<EquipmentSlot>> m_equippedItems; //less might not work on ENUMs like EquipmentSlot //apparently it does...

	
public:

	bool			searchInv(std::string, item**, std::vector<item*>::iterator*);
	bool			searchEquip(std::string, item**, std::map<EquipmentSlot, item*>::iterator*);
	bool			addItem(item*);
	bool			addEquip(item*);
	bool			removeItem(std::vector<item*>::iterator*);
	bool			removeEquip(std::map<EquipmentSlot, item*>::iterator*);
	
	void			showInventory();
	void			showEquipment();

	bool			checkEquipped(EquipmentSlot, item**);
	
	
	std::vector<item*>*				getItemListPtr();
	std::map<EquipmentSlot, item*>* getEqListPtr();

};

//==================================//
// Room Inventory Class Declaration //
//==================================//

class roomInventory : public inventory
{
private:
	std::vector<item*> m_itemList;
	std::vector<container*> m_containerList;



public:
	void	addItem(item*);
	bool	searchInv(std::string str, item **x, std::vector<item*>::iterator *it1);
	bool	removeItem(std::vector<item*>::iterator*);
	void	showInventory();


};





#endif