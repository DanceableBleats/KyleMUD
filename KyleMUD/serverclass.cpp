#include "stdafx.h"
#include "serverclass.h"
#include "connectionclass.h"
#include "characterclass.h"

//=============================//
// Server Class Implementation //
//=============================//

//Constructors / destructors
server::server(boost::shared_ptr<boost::asio::io_service> p_io_service, unsigned int listenPort)
	:m_p_io_service (p_io_service), m_acceptor (*p_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), listenPort))
{

}
server::~server()
{
}


// Public member functions:
void						server::startAcceptLoop()
{
	console_output_lock.lock();
	std::cout << '[' << boost::this_thread::get_id() << "]  Starting accept loop..." << std::endl;
	console_output_lock.unlock();
	
	accept();
}




//Private member functions:
void						server::accept()
{
	connection_ptr p_conn(new connection(m_p_io_service));
	boost::shared_ptr<player> p_player(new player(gdbptr, p_conn));

	console_output_lock.lock();
	std::cout << '[' << boost::this_thread::get_id() << "]  Beginning new async_accept() operation..." << std::endl;
	console_output_lock.unlock();
	
	m_acceptor.async_accept(p_player->p_conn->m_socket, boost::bind(&server::handleAccept, this, p_player));
	
}
void						server::handleAccept(boost::shared_ptr<player> p_player)
{
	console_output_lock.lock();
	std::cout << '[' << boost::this_thread::get_id() << "]  Connection accepted." << std::endl;
	console_output_lock.unlock();

	p_player->setLogonStatus(1);

	m_logonVector_lock.lock();
	m_logonVector.push_back(p_player);
	m_logonVector_lock.unlock();

	//dispatch logon message to read/write loop here when functionality is written.
	/* logon stuff goes here */

	

	accept();
}
void						server::sendAll()
{
	m_logonVector_lock.lock();
	if (!m_logonVector.empty())
	{
		std::vector<boost::shared_ptr<player>>::iterator iter;

		for (iter = m_logonVector.begin(); iter != m_logonVector.end(); ++iter)
		{
			(*iter)->p_conn->sendMessages();

		}//end of for loop
	}//end of if statement
	m_logonVector_lock.unlock();

	m_playerVector_lock.lock();
	if (!m_playerVector.empty())
	{
		std::vector<boost::shared_ptr<player>>::iterator iter;

		for (iter = m_playerVector.begin(); iter != m_playerVector.end(); ++iter)
		{
			(*iter)->p_conn->sendMessages();

		}//end of for loop
	}//end of if statement
}




//No longer needed, instead each player object has it's own async read loop
/*
void						server::readAll() 
{
	m_playerVector_lock.lock();
	if (!m_playerVector.empty())
	{
		std::vector<boost::shared_ptr<player>>::iterator iter;
		for (iter = m_playerVector.begin(); iter != m_playerVector.end(); ++iter)
		{
			/* READ STUFF GOES HERE...

		}//end of for loop
	}//end of if statement
}
*/