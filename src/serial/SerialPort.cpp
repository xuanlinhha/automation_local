/*
 * SerialPort.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#include "SerialPort.h"

std::mutex SerialPort::singletonMutex;
std::shared_ptr<SerialPort> SerialPort::instance;

SerialPort::SerialPort() {
	isOk = initialize();

}
SerialPort::~SerialPort() {
}

bool SerialPort::initialize() {
	if ((port = serialOpen("/dev/ttyAMA0", 115200)) < 0) {
		std::cout << "Unable to open serial device: " << strerror(errno)
				<< "\n";
		return false;
	}
	if (wiringPiSetup() == -1) {
		std::cout << "Unable to start wiringPi: " << strerror(errno) << "\n";
		return false;
	}
	return true;
}

std::shared_ptr<SerialPort> SerialPort::getInstance() {
	std::unique_lock<std::mutex> lock(singletonMutex);
	if (!instance) {
		instance.reset(new SerialPort());
	}
	return instance;
}

int& SerialPort::getPort() {
	return port;
}
