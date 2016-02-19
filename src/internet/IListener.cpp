/*
 * IListener.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#include "IListener.h"

//const std::string IListener::ADDRESS = "0.0.0.0";
//const std::string IListener::PORT = "2190";
const short IListener::PORT = 2190;
std::mutex IListener::singletonMutex;
std::shared_ptr<IListener> IListener::instance;

IListener::IListener() :
		acceptor_(io_service_,
				boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
						PORT)), socket_(io_service_) {
}

//IListener::IListener() :
//		acceptor_(io_service_), socket_(io_service_) {
//	boost::asio::ip::tcp::resolver resolver(io_service_);
//	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(
//			{ ADDRESS, PORT });
//	acceptor_.open(endpoint.protocol());
//}

IListener::~IListener() {
}

std::shared_ptr<IListener> IListener::getInstance() {
	std::unique_lock<std::mutex> lock(singletonMutex);
	if (!instance) {
		instance.reset(new IListener());
	}
	return instance;
}

void IListener::accept() {
	acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
	{
		if (!ec)
		{
			std::make_shared<IConnection>(std::move(socket_))->start();
		}
		accept();
	});
}

void IListener::run() {
	accept();
	io_service_.run();
}
