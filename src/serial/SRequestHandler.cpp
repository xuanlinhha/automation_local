/*
 * SRequestHandler.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: xuanlinhha
 */

#include "SRequestHandler.h"

std::mutex SRequestHandler::singletonMutex;
std::shared_ptr<SRequestHandler> SRequestHandler::instance;

SRequestHandler::SRequestHandler() {
	port = SerialPort::getInstance()->getPort();
}

SRequestHandler::~SRequestHandler() {
}

std::shared_ptr<SRequestHandler> SRequestHandler::getInstance() {
	std::unique_lock<std::mutex> lock(singletonMutex);
	if (!instance) {
		instance.reset(new SRequestHandler());
	}
	return instance;
}

int SRequestHandler::handleSRequest(SRequest& request) {
	// get location for serial request
	int location = Building::getInstance()->getLocation(request.getId());
	request.setLocation(location);

	// get ticket
	int ticket = TicketAgent::getInstance()->getTicket();
	request.setTicket(ticket);

	// send message to serial port
	serialPrintf(port, request.toString().c_str());

	// wait for response
	int result = SResponseArray::getInstance()->getStatus(request.getTicket());
	if (result == SResponse::SUCCESS) {
		Building::getInstance()->setStatus(request.getId(),
				request.getParams());
	}

	// return ticket
	TicketAgent::getInstance()->addTicket(request.getTicket());

	return result;
}
