/*
 * SChecksum.cpp
 *
 *  Created on: Aug 3, 2014
 *      Author: xuanlinhha
 */

#include "SChecksum.h"

SChecksum::SChecksum() {
}

SChecksum::~SChecksum() {
}

char SChecksum::generateChecksum(const std::string& message) {
	// sum all character in message
	int sum = 0;
	for (const char& c : message) {
		sum += c;
	}

	// find remainder
	int remainder = sum % 256;

	// checksum value
	char result = 256 - remainder;

	// if checksum is START or END -> space
	if (result == 0x02 || result == 0x03) {
		result = ' ';
	}
	return result;
}

bool SChecksum::verifyChecksum(const std::string& fullMessage) {
	char checksum = generateChecksum(
			fullMessage.substr(0, fullMessage.length() - 2));
	if (checksum != fullMessage.at(fullMessage.length() - 1)) {
		return false;
	}
	return true;
}
