//=============//
// My Includes //
//=============//
#include "stdafx.h"
#include "error.h"


//================//
// Not My Inludes //
//================//
//#include <string>
//#include <iostream>
//#include <vector>



//============================//
// Error Class implementation //
//============================//



/*
class errorclass
{
private:
	std::string errorBuffer;
	std::vector<std::string> errorHistory;


public:
	void newError(std::string);
	void printError();
	void printHistory();
*/

// STATIC CLASS: USE SCOPE OPERATOR TO CALL ERRORCLASS "errorclass::newError(std::string);"
// for static classes do you have to add a definition to static member variables?
int errorclass::errorBuffer;
std::vector<int> errorclass::errorHistory;
std::vector<int>::iterator errorclass::iter;



void errorclass::newError(int e)
{
	errorHistory.push_back(errorBuffer);

	errorBuffer = e;

}

void errorclass::printError()
{

	std::cout << errorBuffer << std::endl;

}

void errorclass::printHistory()
{
	for (iter = errorHistory.begin(); iter != errorHistory.end(); ++iter)
	{
			std::cout << *iter << std::endl;

	}
	std::cout << std::endl << "Current (most recent) error: " << std::endl << errorBuffer << std::endl;


}

