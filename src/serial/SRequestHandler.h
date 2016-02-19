/*
 * SRequestHandler.h
 *
 *  Created on: Jul 30, 2014
 *      Author: xuanlinhha
 */

#ifndef SREQUESTHANDLER_H_
#define SREQUESTHANDLER_H_

#include <memory>
#include <mutex>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "SerialPort.h"
#include "SRequest.h"
#include "SResponse.h"
#include "../management/SResponseArray.h"
#include "../management/Building.h"
#include "../management/TicketAgent.h"

class SRequestHandler {
private:
	int port;
	static std::mutex singletonMutex;
	static std::shared_ptr<SRequestHandler> instance;
	SRequestHandler();
public:
	static std::shared_ptr<SRequestHandler> getInstance();
	virtual ~SRequestHandler();
	int handleSRequest(SRequest& request);
};

#endif /* SREQUESTHANDLER_H_ */
