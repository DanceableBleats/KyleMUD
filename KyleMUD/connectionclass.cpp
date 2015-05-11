#include "stdafx.h"
#include "connectionclass.h"


//=================================//
// Connection Class Implementation //
//=================================//


//Constructors / destructors
connection::		connection(boost::shared_ptr<boost::asio::io_service> p_io_service)
	: m_socket(*p_io_service)
{
	m_msgLength = 0;

	console_output_lock.lock();
	std::cout << '[' << boost::this_thread::get_id() << "]  New connection object created." << std::endl;
	console_output_lock.unlock();
}
connection::		~connection()
{
		console_output_lock.lock();
	std::cout << '[' << boost::this_thread::get_id() << "]  Connection object destroyed." << std::endl;
	console_output_lock.unlock();
}

//Public member functions
void				connection::sendMessages()
{
	m_outDeque_lock.lock();
	if (!m_outDeque.empty())
	{
		this->writeOne();
	}
	m_outDeque_lock.unlock();
}
void				connection::startReading()
{
	this->readHeader();
}

//private member functions
void				connection::addMessage(boost::shared_ptr<std::string> p_string)
{
	m_outDeque_lock.lock();
	m_outDeque.push_back(p_string);
	m_outDeque_lock.unlock();
}
void				connection::writeOne()
{
	m_outDeque_lock.lock();
	if (!m_outDeque.empty())
	{
		boost::asio::async_write(m_socket, boost::asio::buffer(*m_outDeque.front(), m_outDeque.front()->size()), boost::bind(&connection::handleWrite, this));
	}
	m_outDeque_lock.unlock();
}
void				connection::handleWrite()
{
	m_outDeque_lock.lock();
	if (!m_outDeque.empty())
	{
		m_outDeque.pop_front();
	}
	m_outDeque_lock.unlock();
	this->writeOne();
}

//player's async read loop. Lead into this from completion of authentication/logon (not written yet)
void				connection::readHeader()
{
	if (m_socket.is_open())
	{
		memset (m_unnamedBuffer, '0', 7);
		boost::asio::async_read(m_socket, boost::asio::buffer(m_unnamedBuffer, 7), boost::bind(&connection::readBody, this));
	}//end of if statement
	else
	{
		/* disconnect stuff goes here */
	}//end of else statement
}
void				connection::readBody()
{
	if (m_socket.is_open())
	{
		m_msgLength = 0;
		m_msgLength = (m_unnamedBuffer[2] * 100) + (m_unnamedBuffer[3] * 10) + m_unnamedBuffer[4];
		memset(m_msgBuffer, '0', 1000);
		boost::asio::async_read(m_socket, boost::asio::buffer(m_msgBuffer, m_msgLength), boost::bind(&connection::handleBody, this));
	}//end of if statement.
	else
	{
		/* disco stuff goes here... */
	}//end of else
}
void				connection::handleBody()
{
	boost::shared_ptr<std::string> p_msgString(new std::string);

	for (int i = 0; i < m_msgLength; ++i)
	{
		if (m_msgBuffer[i] == '~')
		{
			switch (m_messageBuffer[i+1])
			{
			case ~:
				{
					p_msgString->append("~");
					++i;
					break;
				}//end case: ~
			default:
				{
					++i;
				}
			}//end of switch
		}//end of "if (m_messageBuffer[i] == '~')"
		p_msgString->append(*m_msgBuffer[i]);
	}// end of for loop

	m_inDeque_lock.lock();
	m_inDeque.push_back(p_msgString);
	m_inDeque_lock.unlock();



	if (m_socket.is_open())
	{
		this->readHeader();
	}
}


//async logon
void				connection::startLogon()
{
	boost::shared_ptr<std::string> p_string(new std::string("Enter username: "));
	this->addMessage(p_string);
	
	if (m_socket.is_open())
	{
		memset (m_unnamedBuffer, '0', 7);
		boost::asio::async_read(m_socket, boost::asio::buffer(m_unnamedBuffer, 7), boost::bind(&connection::readUserNameHeader, this));
	}//end of if statement
	else
	{
		/* disconnect stuff goes here */
	}//end of else statement
}
void				connection::handleUSerNameHeader()
{
}