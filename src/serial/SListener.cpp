/*
 * SListener.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: xuanlinhha
 */

#include "SListener.h"

SListener::SListener() {
	port = SerialPort::getInstance()->getPort();
	std::string message = "";
	completed = true;
}
SListener::~SListener() {
}

void SListener::run() {
	// message format:
	// [START 0 U id status checksum END] / [START 0 R ticket 1/0 checksum END]
	char c;
	while (true) {
		while (serialDataAvail(port)) {
			c = serialGetchar(port);
			if (c == FormatConst::SERIAL_START) {
				completed = false;
			} else if (c == FormatConst::SERIAL_END) {
				completed = true;
				handleMessage(message);
				message = "";
			} else {
				if (completed == false) {
					message += c;
				}
			}

		}
	}
}

void SListener::handleMessage(std::string &message) {
	// message format:
	// [0 U id status checksum] / [0 R ticket 1/0 checksum]

	// verify checksum
	if (!SChecksum::verifyChecksum(message)) {
		return;
	}

	// divide message by component separator
	std::vector<std::string> elements;
	std::istringstream iss(message);
	std::string s;
	while (std::getline(iss, s, FormatConst::COMP_SEPERATOR)) {
		elements.push_back(s);
	}

	// Size must be at least 5 components:
	if (elements.size() < 5 || elements[0] != "0") {
		return;
	}

	if (elements[1] == "R") {
		SResponse response;
		response.setTicket(std::stoi(elements[2])); // ticket
		response.setStatus(std::stoi(elements[3])); // response status

		SerialReporter::processResponse(response);

	} else if (elements[1] == "U") {
		SNotification notification;
		notification.setId(elements[2]);

		// get status components
		std::list<std::string> sStatus;
		std::istringstream iss(elements[3]);
		std::string s;
		while (std::getline(iss, s, FormatConst::COMP_SUB_SEPERATOR)) {
			sStatus.push_back(s);
		}

		// get status
		std::list<int> status;
		for (std::list<std::string>::const_iterator iterator = sStatus.begin();
				iterator != sStatus.end(); ++iterator) {
			status.push_back(std::stoi(*iterator));
		}
		notification.setStatus(status);

		SerialReporter::processNotification(notification);

	}
}
