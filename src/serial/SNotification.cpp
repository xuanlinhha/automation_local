/*
 * SNotification.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#include "SNotification.h"

SNotification::SNotification() {
	id = "";
}

SNotification::~SNotification() {
}

std::string& SNotification::getId() {
	return id;
}
void SNotification::setId(std::string& id) {
	this->id = id;
}

std::list<int>& SNotification::getStatus() {
	return status;
}
void SNotification::setStatus(std::list<int>& status) {
	this->status = status;
}
