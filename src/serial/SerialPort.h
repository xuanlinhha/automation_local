/*
 * SerialPort.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <iostream>
#include <string.h>
#include <memory>
#include <mutex>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

class SerialPort {
private:
	int port;
	bool isOk;
	bool initialize();
	static std::mutex singletonMutex;
	static std::shared_ptr<SerialPort> instance;
	SerialPort();
public:
	virtual ~SerialPort();
	static std::shared_ptr<SerialPort> getInstance();
	int& getPort();
};

#endif /* SERIALPORT_H_ */
