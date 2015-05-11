//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "databaseclass.h"
#include "ssqlscontainers.h"
#include "characterclass.h"
#include "room.h"
#include "inventory.h"
#include "item.h"


//=================//
// Not My Includes //
//=================//
//#include <string>
//#include <vector>



//==========//
// Forwards //
//==========//
using namespace std;

int getRand();				//random number
int getRand(int, int);		//random number in range


//===============================//
// Database Class Implimentation //
//===============================//
database::database() 
{
	mysqlpp::Connection con (false);
}
database::~database()
{
	
}

//Takes a player obj pointer and queries database. returns true if charater already exists, otherwise false.
bool database::characterExists(player* p)
{
	if (con.connect ("cppdb", "localhost", "root", "root"))
	{
		vector<ssqls_characters> res;
		mysqlpp::Query query = con.query("select * from characters where charname = %0q");
		query.parse(); 
		query.storein(res, p->getName());

		if (!res.empty()) return true;
		else if (res.empty()) return false;
	}
	else
	{
		cout << "Couldn't connect to database!" << endl;
		system ("pause.exe");
	}
	return false;
}
//Takes a string representing character name and queries database. returns true if charater already exists, otherwise false.
bool database::characterExists(string n)  
{
	if (con.connect ("cppdb", "localhost", "root", "root"))
	{
		vector<ssqls_characters> res;
		mysqlpp::Query query = con.query("select * from characters where charname = %0q");
		query.parse(); 
		query.storein(res, n);

		if (!res.empty()) return true;
		else if (res.empty()) return false;
	}
	else
	{
		cout << "Couldn't connect to database!" << endl;
		system ("pause.exe");
	}
	return false;
}

//takes a player pointer, returns true if the inventory ID already exists, returns false if it doesn't
bool database::invIDExists(player *p_player)
{
	if (con.connect ("cppdb", "localhost", "root", "root"))
	{
		vector<ssqls_inventories> res;
		mysqlpp::Query query = con.query("select * from inventories where invID = %0q");
		query.parse(); 
		query.storein(res, p_player->getInvID());

		if (!res.empty()) return true;
		else if (res.empty()) return false;
	}
	else
	{
		cout << "Couldn't connect to database!" << endl;
		system ("pause.exe");
	}
}
//takes the invID, returns true if the inventory ID already exists, returns false if it doesn't
bool database::invIDExists(long long x)
{
	if (con.connect ("cppdb", "localhost", "root", "root"))
	{
		vector<ssqls_inventories> res;
		mysqlpp::Query query = con.query("select * from inventories where invID = %0q");
		query.parse(); 
		query.storein(res, x);

		if (!res.empty()) return true;
		else if (res.empty()) return false;
	}
	else
	{
		cout << "Couldn't connect to database!" << endl;
		system ("pause.exe");
	}
}

bool	database::cIDExists(player *p_player)
{
	if (con.connect ("cppdb", "localhost", "root", "root"))
	{
		vector<ssqls_characters> res;
		mysqlpp::Query query = con.query("select * from characters where cID = %0q");
		query.parse(); 
		query.storein(res, p_player->getCharID());

		if (!res.empty()) return true;
		else if (res.empty()) return false;
	}
	else
	{
		cout << "Couldn't connect to database!" << endl;
		system ("pause.exe");
	}
}
bool	database::cIDExists(long long x)
{
	if (con.connect ("cppdb", "localhost", "root", "root"))
	{
		vector<ssqls_characters> res;
		mysqlpp::Query query = con.query("select * from characters where cID = %0q");
		query.parse(); 
		query.storein(res, x);

		if (!res.empty()) return true;
		else if (res.empty()) return false;
	}
	else
	{
		cout << "Couldn't connect to database!" << endl;
		system ("pause.exe");
	}
}


void database::loadCharacter(string n, player *p)
{
	if (con.connect ("cppdb", "localhost", "root", "root"))
	{
		playerInventory *p_inventory = p->getInvPtr();
		vector<ssqls_characters> res;
		vector<ssqls_characters>::iterator iter;

		mysqlpp::Query query = con.query("select * from characters where charname = %0q"); 
		query.parse(); 
		query.storein(res, n);
		if (!res.empty())
		{		
			iter = res.begin();
			p->setCharID(iter->cID);
			p->setName(iter->charname);
			p->setRace(iter->race);
			p->setCls(iter->cls);
			p->setStr(iter->str);
			p->setAgi(iter->agi);
			p->setPer(iter->per);
			p->setWis(iter->wis);
			p->setAC(iter->ac);
			p->setInvID(iter->invID);
			p->setLive(true);
		}

		query.reset();
		query = con.query("SELECT * FROM items WHERE inventoryID = %0q AND equipped = 0");
		query.parse();
		vector<ssqls_items> items;
		vector<ssqls_items>::iterator itemit;
		query.storein(items, p_inventory->getInvID());


		for (itemit = items.begin(); itemit != items.end(); ++itemit)
		{
			item *p_item = new item;
			p_item->setItemID(itemit->itemID);
			p_item->setItemName(itemit->itemName);
			p_item->setEquipmentSlot((EquipmentSlot)itemit->EQSlot);
			p_item->setStrBonus(itemit->strBonus);
			p_item->setAgiBonus(itemit->agiBonus);
			p_item->setPerBonus(itemit->perBonus);
			p_item->setWisBonus(itemit->wisBonus);
			p_item->setACBonus(itemit->acBonus);
			p_item->setDescription(itemit->description);
			p_item->setItemKeyWords(itemit->keywords);
			p_inventory->addItem(p_item);
		}

		query.reset();
		query = con.query("SELECT * FROM items WHERE inventoryID = %0q AND equipped = 1");
		query.parse();
		vector<ssqls_items> equipment;
		vector<ssqls_items>::iterator eqit;
		query.storein(equipment, p_inventory->getInvID());

		for (eqit = equipment.begin(); eqit != equipment.end(); ++eqit)
		{
			item *p_equip = new item;
			p_equip->setItemID(eqit->itemID);
			p_equip->setItemName(eqit->itemName);
			p_equip->setEquipmentSlot((EquipmentSlot)eqit->EQSlot);
			p_equip->setStrBonus(eqit->strBonus);
			p_equip->setAgiBonus(eqit->agiBonus);
			p_equip->setPerBonus(eqit->perBonus);
			p_equip->setWisBonus(eqit->wisBonus);
			p_equip->setACBonus(eqit->acBonus);
			p_equip->setDescription(eqit->description);
			p_equip->setItemKeyWords(eqit->keywords);
			p_inventory->addEquip(p_equip);
		}
		




/*		else					//DEPRECIATING
		{
			iter = res.begin();
			p->setName(n);
			p->setRace("blank");
			p->setCls("commoner");
			p->setStr(0);
			p->setAgi(0);
			p->setPer(0);
			p->setWis(0);
			p->setLive(false);
		}
*/

	}

	else
	{
		cout << "Couldn't connect to database" << endl;
		system ("pause.exe");
	}
}
void database::saveNewCharacter(player *p)
{

	try
	{
		con.connect ("cppdb", "localhost", "root", "root");

		

		mysqlpp::Query query = con.query("INSERT INTO characters (charname, race, cls, str, agi, per, wis, AC, invID, cID) VALUES (%0q, %1q, %2q, %3q, %4q, %5q, %6q, %7q, %8q, %9q)"); 
		query.parse(); 
		query.execute(p->getName(), p->getRace(), p->getClass(), p->getStr(), p->getAgi(), p->getPer(), p->getWis(), 
			p->getAC(), p->getInvID(), p->getCharID());

		query.reset();
		query = con.query("INSERT INTO inventories (InvID, InvType, associate) VALUES (%0q, %1q, %2q)");
		query.parse();
		query.execute(p->getInvID(), "character", p->getCharID());
		/*     //QUERY EMPTY, inventory contains no items yet.
		//Grab all items in inventory, add to ssqls container and mass insert the container with query.insert().
		vector<ssqls_items> inv;
		vector<item*> *p_items = p->getInvPtr()->getItemListPtr();
		vector<item*>::iterator it;
		for (it = p_items->begin(); it != p_items->end(); ++it)
		{
			ssqls_items item((*it)->getItemID(), (*it)->getItemName(), (int)(*it)->getEquipmentSlot(), 
			(*it)->getStrBonus(), (*it)->getAgiBonus(), (*it)->getPerBonus(), (*it)->getWisBonus(), (*it)->getACBonus(), 
			(*it)->getDescription(), (*it)->getKeywords(), p->getInvID());
			inv.push_back(item);
		}
		query.reset();
		query.insert(inv.begin(), inv.end());
		query.execute();
		*/
		
		/*
		query.reset();
		query = con.query("INSERT INTO items (itemID, itemname, EQSlot, strBonus, agiBonus, perBonus, wisBonus, acBonus, description, keywords, inventoryID) VALUES (%1q, %2q, %3q, %4q, %5q, %6q, %7q, %8q, %9q, %10q)");
		query.parse();
		query.execute();
		*/

	}
	catch (const mysqlpp::BadQuery& er) 
	{
        // Handle any query errors
        cout << "Query error: " << er.what() << endl;
		system("pause.exe");
	}
}

void database::loadWorldRooms(vector<room*> *list)
{
	try
	{

		con.connect ("cppdb", "localhost", "root", "root");

		vector<ssqls_rooms> res;
		vector<ssqls_rooms>::iterator it;
		
		mysqlpp::Query query = con.query("select * from rooms"); 
		query.parse(); 
		query.storein(res);

		if (!res.empty())
		{
			for (it=res.begin(); it != res.end(); it++)
			{
				room *r = new room;

				r->setRoomID(it->rID);			// set room ID

				r->setExitStatus(it->north, it->northeast, it->east, it->southeast, it->south,      //set exit statuses of each direction.
					it->southwest, it->west, it->northwest, it->up, it->down, it->portal);

				r->setLinkIDS(it->n_link, it->ne_link, it->e_link, it->se_link, it->s_link,			//set rIDs to other rooms for linking with ptrs
					it->sw_link, it->w_link, it->nw_link, it->up_link, it->dn_link, it->p_link);

				r->setDescription(it->description); // set description

				list->push_back(r);				// add to world list
			}
			cout << "World loaded " << list->size() << " rooms." << endl;
		}
	}
	catch (const mysqlpp::BadQuery& er) 
	{
        // Handle any query errors
        cout << "Query error: " << er.what() << endl;
		system("pause.exe");
	}
}
void database::characterList(vector<string> *v)
{ 
	con.connect ("cppdb", "localhost", "root", "root");
	vector<ssqls_characters> res;
	vector<ssqls_characters>::iterator it;
    mysqlpp::Query query = con.query("select * from characters");   
    query.storein(res);

	for (it = res.begin(); it != res.end(); it++) 
	{
		v->push_back(it->charname);
	}
}
void database::saveRoom(room* rm)
{
	con.connect ("cppdb", "localhost", "root", "root");
	vector<ssqls_rooms> res;
	
	mysqlpp::Query query = con.query("SELECT * FROM rooms WHERE rID = %0q");
	query.parse();
	query.storein(res, rm->getRoomID());

	try
	{
	
		if (res.empty()) //SAVE NEW ROOMS
		{
			query.reset();
			query = con.query("INSERT INTO rooms (rID, north, northeast, east, southeast, south, southwest, west, northwest, up, down, portal) VALUES (%0q, %1q, %2q, %3q, %4q, %5q, %6q, %7q, %8q, %9q, %10q, %11q)");
			query.parse();
			query.execute(rm->getRoomID(), (int)rm->getExitStatus(NORTH), (int)rm->getExitStatus(NORTHEAST), (int)rm->getExitStatus(EAST), 
				(int)rm->getExitStatus(SOUTHEAST), (int)rm->getExitStatus(SOUTH), (int)rm->getExitStatus(SOUTHWEST), (int)rm->getExitStatus(WEST), 
				(int)rm->getExitStatus(NORTHWEST), (int)rm->getExitStatus(UP), (int)rm->getExitStatus(DOWN), (int)rm->getExitStatus(PORTAL));
	
			query.reset();
			query = con.query("UPDATE rooms SET description = %1q, n_link = %2q, ne_link = %3q, e_link = %4q, se_link = %5q, s_link = %6q, sw_link = %7q, w_link = %8q, nw_link = %9q, up_link = %10q, dn_link = %11q, p_link = %12q WHERE rID = %0q");
			query.parse();
			query.execute(rm->getRoomID(), rm->getDescription(), (int)rm->getLinkIDs(NORTH), (int)rm->getLinkIDs(NORTHEAST), (int)rm->getLinkIDs(EAST), (int)rm->getLinkIDs(SOUTHEAST), 
				(int)rm->getLinkIDs(SOUTH), (int)rm->getLinkIDs(SOUTHWEST), (int)rm->getLinkIDs(WEST), (int)rm->getLinkIDs(NORTHWEST), 
				(int)rm->getLinkIDs(UP), (int)rm->getLinkIDs(DOWN), (int)rm->getLinkIDs(PORTAL));
		}
		else if (!res.empty()) //OVERWRITE EXISTING ROOMS
		{
			query.reset();
			query = con.query("UPDATE rooms SET north = %1q, northeast = %2q, east = %3q, southeast = %4q, south = %5q, southwest = %6q, west = %7q, northwest = %8q, up = %9q, down = %10q, portal = %11q WHERE rID = %0q");
			query.parse();
			query.execute(rm->getRoomID(), (int)rm->getExitStatus(NORTH), (int)rm->getExitStatus(NORTHEAST), (int)rm->getExitStatus(EAST), 
				(int)rm->getExitStatus(SOUTHEAST), (int)rm->getExitStatus(SOUTH), (int)rm->getExitStatus(SOUTHWEST), (int)rm->getExitStatus(WEST), 
				(int)rm->getExitStatus(NORTHWEST), (int)rm->getExitStatus(UP), (int)rm->getExitStatus(DOWN), (int)rm->getExitStatus(PORTAL));
	
			query.reset();
			query = con.query("UPDATE rooms SET description = %1q, n_link = %2q, ne_link = %3q, e_link = %4q, se_link = %5q, s_link = %6q, sw_link = %7q, w_link = %8q, nw_link = %9q, up_link = %10q, dn_link = %11q, p_link = %12q WHERE rID = %0q");
			query.parse();
			query.execute(rm->getRoomID(), rm->getDescription(), (int)rm->getLinkIDs(NORTH), (int)rm->getLinkIDs(NORTHEAST), (int)rm->getLinkIDs(EAST), (int)rm->getLinkIDs(SOUTHEAST), 
				(int)rm->getLinkIDs(SOUTH), (int)rm->getLinkIDs(SOUTHWEST), (int)rm->getLinkIDs(WEST), (int)rm->getLinkIDs(NORTHWEST), 
				(int)rm->getLinkIDs(UP), (int)rm->getLinkIDs(DOWN), (int)rm->getLinkIDs(PORTAL));
		}
	} //end of try block

	catch (const mysqlpp::BadQuery& er)
	{
		// Handle any query errors
        cout << "Query error: " << er.what() << endl;
		system("pause.exe");
	}
}

void database::spawnItem(string str, item *p_item)
{
	con.connect ("cppdb", "localhost", "root", "root");
	vector<ssqls_itemtemplates> res;
	vector<ssqls_itemtemplates>::iterator it;
	
	mysqlpp::Query query = con.query("SELECT * FROM itemtemplates WHERE itemname = %0q");
	query.parse();
	query.storein(res, str);

	if ( !res.empty() )
	{
		it = res.begin();
	
		p_item->setItemName(it->itemname);
		p_item->setStrBonus(getRand(it->str_min, it->str_max));
		p_item->setAgiBonus(getRand(it->agi_min, it->agi_max));
		p_item->setPerBonus(getRand(it->per_min, it->per_max));
		p_item->setWisBonus(getRand(it->wis_min, it->wis_max));
		p_item->setACBonus(getRand(it->ac_min, it->ac_max));
		p_item->setDescription(it->description);
		p_item->setItemKeyWords(it->keywords);
		p_item->setEquipmentSlot((EquipmentSlot)it->eqslot);
	}
	else
	{
		cout << "Can't spawn a '" << str << "'." << endl;
		system("pause");
	}
}


void database::saveCharacter(player *p_player)
{	

	try
	{
		con.connect ("cppdb", "localhost", "root", "root");

		if (cIDExists(p_player))
		{
			mysqlpp::Query query = con.query("UPDATE characters SET charname = %0q, race = %1q, cls = %2q, str = %3q, agi = %4q, per = %5q, wis = %6q, AC = %7q, invID = %8q WHERE cID = %9q "); 
			query.parse(); 
			query.execute(p_player->getName(), p_player->getRace(), p_player->getClass(), p_player->getStr(), p_player->getAgi(), 
				p_player->getPer(), p_player->getWis(), p_player->getAC(), p_player->getInvID(), p_player->getCharID());

			query.reset();
			query = con.query("DELETE FROM items WHERE inventoryID = %0q");
			query.parse();
			query.execute(p_player->getInvPtr()->getInvID());

			vector<item*> *p_items = p_player->getInvPtr()->getItemListPtr();
			vector<item*>::iterator it;
			for (it = p_items->begin(); it != p_items->end(); ++it)
			{
				query.reset();
				query = con.query("INSERT INTO items (itemID, itemName, EQSlot, equipped, strBonus, agiBonus, perBonus, wisBonus, acBonus, description, keywords, inventoryID) VALUES (%0q, %1q, %2q, 0, %3q, %4q, %5q, %6q, %7q, %8q, %9q, %10q) ");
				query.parse();
				query.execute((*it)->getItemID(), (*it)->getItemName(), (int)(*it)->getEquipmentSlot(), (*it)->getStrBonus(), 
					(*it)->getAgiBonus(), (*it)->getPerBonus(), (*it)->getWisBonus(), (*it)->getACBonus(), (*it)->getDescription(), 
					(*it)->getKeywords(), p_player->getInvID());
			}

			map<EquipmentSlot, item*> *p_eqmap = p_player->getInvPtr()->getEqListPtr();
			map<EquipmentSlot, item*>::iterator mapit;
			for (mapit = p_eqmap->begin(); mapit != p_eqmap->end(); ++mapit)
			{
				query.reset();
				query = con.query("INSERT INTO items (itemID, itemName, EQSlot, equipped, strBonus, agiBonus, perBonus, wisBonus, acBonus, description, keywords, inventoryID) VALUES (%0q, %1q, %2q, 1, %3q, %4q, %5q, %6q, %7q, %8q, %9q, %10q) ");
				query.parse();
				query.execute((*mapit).second->getItemID(), (*mapit).second->getItemName(), 
					(int)(*mapit).second->getEquipmentSlot(), (*mapit).second->getStrBonus(), 
					(*mapit).second->getAgiBonus(), (*mapit).second->getPerBonus(), (*mapit).second->getWisBonus(), 
					(*mapit).second->getACBonus(), (*mapit).second->getDescription(), (*mapit).second->getKeywords(), 
					p_player->getInvID());
			}


			

			/*
			query.reset();
			query = con.query("SELECT * FROM items WHERE inventoryID = %0q");
			query.parse();
			vector<ssqls_items> old;
			query.storein(old);

			//Grab all items in inventory, add to ssqls container and mass insert the container with query.insert().
			vector<ssqls_items> inv;
			vector<item*> *p_items = p_player->getInvPtr()->getItemListPtr();
			vector<item*>::iterator it;
			for (it = p_items->begin(); it != p_items->end(); ++it)
			{
				ssqls_items item((*it)->getItemID(), (*it)->getItemName(), (int)(*it)->getEquipmentSlot(), 
				(*it)->getStrBonus(), (*it)->getAgiBonus(), (*it)->getPerBonus(), (*it)->getWisBonus(), 
				(*it)->getACBonus(), (*it)->getDescription(), (*it)->getKeywords(), p_player->getInvID());
				inv.push_back(item);
			}
			query.reset();
			query.update(old, p_items);
			*/
		}
	}
		
	catch (const mysqlpp::BadQuery& er) 
	{
        // Handle any query errors
        cout << "Query error: " << er.what() << endl;
		system("pause.exe");
	}

}
