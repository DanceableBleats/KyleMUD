#ifndef _SERVER_CLASS_H_
#define _SERVER_CLASS_H_
#include "stdafx.h"


class connection;
class player;

class server : public boost::enable_shared_from_this<server>
{
public:
	//Constructors / destructors
	server(boost::shared_ptr<boost::asio::io_service>, unsigned int);
	~server();

	//Public members:
	boost::shared_ptr<boost::asio::io_service> m_p_io_service;

	//public member functions:
	void startAcceptLoop();


private:
	//Private members
	boost::mutex m_logonVector_lock;
	boost::mutex m_playerVector_lock;
	
	std::vector<boost::shared_ptr<player>> m_logonVector;
	std::vector<boost::shared_ptr<player>> m_playerVector;

	boost::asio::ip::tcp::acceptor m_acceptor;



	//Private member functions
	void accept();
	void handleAccept(boost::shared_ptr<player>);
	
	void sendAll();

	void readAll();
};
#endif