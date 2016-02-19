/*
 * IConnection.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#include "IConnection.h"

IConnection::IConnection(boost::asio::ip::tcp::socket socket) :
		socket_(std::move(socket)) {

}
IConnection::~IConnection() {
}

void IConnection::start() {
	readRequest();
}
void IConnection::stop() {
	socket_.close();
}

void IConnection::readRequest() {
	auto self(shared_from_this());
	socket_.async_read_some(boost::asio::buffer(buffer_),
			[this, self](boost::system::error_code ec, std::size_t bytesTransferred)
			{
				if (!ec)
				{
					// process request data
					IRequestStatus status;
					std::tie(status, std::ignore) = requestParser.parse(request, buffer_.data(), buffer_.data() + bytesTransferred);
					if (status == IRequestStatus::GOOD)
					{
						//process and write response
						IRequestHandler::getInstance()->handleIRequest(request, response);
						writeResponse();
					}
					else if(status == IRequestStatus::BAD) {
						std::string badRequest = IResponse::BAD_REQUEST;
						response.setStatus(badRequest);
						writeResponse();
					}
					else {
						readRequest();
					}
				}
				else if (ec != boost::asio::error::operation_aborted)
				{
					shared_from_this()->stop();
				}
			});
}

void IConnection::writeResponse() {
	auto self(shared_from_this());
	boost::asio::async_write(socket_, response.toBuffers(),
			[this, self](boost::system::error_code ec, std::size_t)
			{
				if (!ec)
				{
					boost::system::error_code ignored_ec;
					socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
							ignored_ec);
				}
				if (ec != boost::asio::error::operation_aborted)
				{
					shared_from_this()->stop();
				}
			});
}
