#ifndef _CONNECTION_CLASS_H_
#define _CONNECTION_CLASS_H_
#include "stdafx.h"

class player;

//=============================//
// Connection Class Definition //
//=============================//
class connection //: public boost::enable_shared_from_this<connection>
{
public:
	//Construction / Destruction
	connection(boost::shared_ptr<boost::asio::io_service>);
	~connection();

	//public members:
	boost::asio::ip::tcp::socket m_socket;


	//public member functions:
	void sendMessages();
	void startReading();


private:
	//private members
	std::deque<boost::shared_ptr<std::string>> m_outDeque;
	std::deque<boost::shared_ptr<std::string>> m_inDeque;
	boost::mutex m_outDeque_lock;
	boost::mutex m_inDeque_lock;
	int m_msgLength;
	char m_unnamedBuffer[7];
	char m_msgBuffer[1000];


	//private member functions
	void addMessage(boost::shared_ptr<std::string>);
	void writeOne();
	void handleWrite();
	void readHeader();
	void readBody();
	void handleBody();
	void startLogon();
	void readUserNameHeader();
	void handleUserNameHeader();
	void readUserNameBody();
	void handleUserNameBody();



};
#endif