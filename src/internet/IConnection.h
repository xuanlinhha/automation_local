/*
 * IConnection.h
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#ifndef ICONNECTION_H_
#define ICONNECTION_H_

#include <memory>
#include <boost/asio.hpp>
#include "IRequestParser.h"
#include "IRequest.h"
#include "IResponse.h"
#include "IRequestHandler.h"

class IConnection: public std::enable_shared_from_this<IConnection> {
private:
	static const unsigned int BUFFER_SIZE = 8192;
	boost::asio::ip::tcp::socket socket_;
	IRequestParser requestParser;
	IRequest request;
	IResponse response;

	std::array<char, BUFFER_SIZE> buffer_;
public:
	IConnection(boost::asio::ip::tcp::socket socket);
	virtual ~IConnection();
	boost::asio::ip::tcp::socket& socket();
	void start();
	void readRequest();
	void writeResponse();
	void stop();
};

#endif /* ICONNECTION_H_ */
