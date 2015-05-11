#pragma once
#include "stdafx.h"

//=========//
// Defines //
//=========//
#define MAX_THREADS 2
class database;
class connection;

//==========//
// Typedefs //
//==========//
typedef boost::shared_ptr<connection> connection_ptr;

//================//
// Global Objects //
//================//
extern boost::mutex console_output_lock;
extern database *gdbptr;

//==================//
// Global Functions //
//==================//
void workerThread(boost::shared_ptr<boost::asio::io_service>);
