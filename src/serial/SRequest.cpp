/*
 * SRequest.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#include "SRequest.h"

SRequest::SRequest() {
	location = -1;
	id = "";
	ticket = -1;
}
SRequest::~SRequest() {
}

int SRequest::getLocation() {
	return location;
}
void SRequest::setLocation(int location) {
	this->location = location;
}

int SRequest::getTicket() {
	return ticket;
}
void SRequest::setTicket(int ticket) {
	this->ticket = ticket;
}

std::string& SRequest::getId() {
	return id;
}
void SRequest::setId(std::string& id) {
	this->id = id;
}

std::list<int>& SRequest::getParams() {
	return params;
}
void SRequest::setParams(std::list<int>& params) {
	this->params = params;
}

std::string SRequest::toString() {

	// prepare message [location ticket id status]
	std::string message = "";
	message.append(std::to_string(location));
	message += FormatConst::COMP_SEPERATOR;
	message.append(std::to_string(ticket));
	message += FormatConst::COMP_SEPERATOR;
	message.append(id);
	if (!params.empty()) {
		message += FormatConst::COMP_SEPERATOR;
		for (std::list<int>::const_iterator iterator = params.begin(), end =
				--params.end(); iterator != end; ++iterator) {
			message.append(std::to_string(*iterator));
			message += FormatConst::COMP_SUB_SEPERATOR;
		}
		message.append(std::to_string(*(--params.end())));
	}

	// checksum for for message
	char checksum = SChecksum::generateChecksum(message);

	// final: [START location ticket id status checksum END]
	std::string result = "";
	result += FormatConst::SERIAL_START;
	result += message;
	result += FormatConst::COMP_SUB_SEPERATOR;
	result += checksum;
	result += FormatConst::SERIAL_END;
	return result;
}
