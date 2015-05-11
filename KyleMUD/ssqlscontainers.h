#ifndef _MY_SSQLS_CONTAINERS_H_
#define _MY_SSQLS_CONTAINERS_H_


// THIS //
/*
#ifndef _SSQLS_
#define _SSQLS_
#include "ssqlscontainers.h"
#endif
*/


//=============//
// My Includes //
//=============//
#include "stdafx.h"

//=================//
// Not My Includes //
//=================//
//#include <mysql++.h>
//#include <ssqls.h>


//======================//
// Characters Container //
//======================//
sql_create_10(ssqls_characters, 1, 10,
    mysqlpp::sql_bigint, cID,
    mysqlpp::sql_text, charname,         
    mysqlpp::sql_text, race,  
    mysqlpp::sql_text, cls,
	mysqlpp::sql_int, str,
	mysqlpp::sql_int, agi,
	mysqlpp::sql_int, per,
	mysqlpp::sql_int, wis,
	mysqlpp::sql_int, ac,
	mysqlpp::sql_bigint, invID);


//=================//
// Rooms Container //
//=================//
sql_create_24(ssqls_rooms, 1, 24,
    mysqlpp::sql_int, rID,
    mysqlpp::sql_int, north,         
    mysqlpp::sql_int, northeast,  
    mysqlpp::sql_int, east,
	mysqlpp::sql_int, southeast,
	mysqlpp::sql_int, south,
	mysqlpp::sql_int, southwest,
	mysqlpp::sql_int, west,
	mysqlpp::sql_int, northwest,
	mysqlpp::sql_int, up,
	mysqlpp::sql_int, down,
	mysqlpp::sql_int, portal,
	mysqlpp::sql_text, description,
	mysqlpp::sql_int, n_link,
	mysqlpp::sql_int, ne_link,
	mysqlpp::sql_int, e_link,
	mysqlpp::sql_int, se_link,
	mysqlpp::sql_int, s_link, 
	mysqlpp::sql_int, sw_link,
	mysqlpp::sql_int, w_link,
	mysqlpp::sql_int, nw_link,
	mysqlpp::sql_int, up_link,
	mysqlpp::sql_int, dn_link,
	mysqlpp::sql_int, p_link);


//==========================//
// Item Templates Container //
//==========================//
sql_create_14(ssqls_itemtemplates, 1, 14,
	mysqlpp::sql_text, itemname,
	mysqlpp::sql_int, eqslot,
	mysqlpp::sql_int, str_min,
	mysqlpp::sql_int, str_max,
	mysqlpp::sql_int, agi_min,
	mysqlpp::sql_int, agi_max,
	mysqlpp::sql_int, per_min,
	mysqlpp::sql_int, per_max,
	mysqlpp::sql_int, wis_min,
	mysqlpp::sql_int, wis_max,
	mysqlpp::sql_int, ac_min,
	mysqlpp::sql_int, ac_max,
	mysqlpp::sql_text, description,
	mysqlpp::sql_text, keywords);


//=======================//
// Inventories Container //
//=======================//
sql_create_3(ssqls_inventories, 1, 3,
	mysqlpp::sql_bigint, invID,
	mysqlpp::sql_text, invType,
	mysqlpp::sql_bigint, associate);


//=================//
// Items Container //
//=================//
sql_create_11(ssqls_items, 1, 11,
	mysqlpp::sql_bigint, itemID,
	mysqlpp::sql_text, itemName,
	mysqlpp::sql_int, EQSlot,
	mysqlpp::sql_int, strBonus,
	mysqlpp::sql_int, agiBonus,
	mysqlpp::sql_int, perBonus,
	mysqlpp::sql_int, wisBonus,
	mysqlpp::sql_int, acBonus,
	mysqlpp::sql_text, description,
	mysqlpp::sql_text, keywords,
	mysqlpp::sql_bigint, inventoryID);
	
	









#endif