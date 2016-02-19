/*
 * SerialReporter.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: xuanlinhha
 */

#include "SerialReporter.h"

SerialReporter::SerialReporter() {
}
SerialReporter::~SerialReporter() {
}

void SerialReporter::processNotification(SNotification& notification) {
	// update local data
	Building::getInstance()->setStatus(notification.getId(),
			notification.getStatus());

	// send update to server

}

void SerialReporter::processResponse(SResponse& response) {
	SResponseArray::getInstance()->putStatus(response.getTicket(),
			response.getStatus());
}
