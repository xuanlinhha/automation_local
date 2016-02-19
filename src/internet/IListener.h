/*
 * IListener.h
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#ifndef ILISTENER_H_
#define ILISTENER_H_

#include <memory>
#include <mutex>
#include <boost/asio.hpp>
#include "IConnection.h"

class IListener {
private:
//	static const std::string ADDRESS;
//	static const std::string PORT;
	static const short PORT;
	static std::mutex singletonMutex;
	static std::shared_ptr<IListener> instance;
	// io_service must declared before acceptor and socket
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
	IListener();
	void accept();
public:
	static std::shared_ptr<IListener> getInstance();
	void run();
	virtual ~IListener();
};

#endif /* ILISTENER_H_ */
