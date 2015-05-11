#ifndef _MY_ERROR_H_
#define _MY_ERROR_H_

// THIS //
/*
#ifndef _ERROR_
#define _ERROR_
#include "error.h"
#endif
*/

//=====================//
// Pre-compiled header //
//=====================//
#include "stdafx.h"

//=================//
// Not My Includes //
//=================//
//#include <string>
//#include <vector>


//========================//
// Error Class Definition //
//========================//

// STATIC CLASS: USE SCOPE OPERATOR TO CALL ERRORCLASS "errorclass::newError(std::string);"
class errorclass
{
//private: //No private/public for static classes?
public:
	static int errorBuffer;
	static std::vector<int> errorHistory;
	static std::vector<int>::iterator iter;
//public:
	errorclass();
	~errorclass();
	static void newError(int);
	static void printError();
	static void printHistory();


};





#endif