/*
 * SListener.h
 *
 *  Created on: Jul 29, 2014
 *      Author: xuanlinhha
 */

#ifndef SLISTENER_H_
#define SLISTENER_H_

#include <string>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "SerialPort.h"
#include "SerialReporter.h"
#include "SChecksum.h"
#include "../common/FormatConst.h"

class SListener {
private:
	int port;
	std::string message;bool completed;
public:
	void operator()() {
		run();
	}
	SListener();
	virtual ~SListener();
	void run();
	void handleMessage(std::string &message);
};

#endif /* SLISTENER_H_ */
