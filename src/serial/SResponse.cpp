/*
 * SResponse.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#include "SResponse.h"

const int SResponse::NO_RESPONE = 0;
const int SResponse::SUCCESS = 1;
const int SResponse::FAIL = 2;

SResponse::SResponse() {
	ticket = -1;
	status = 0;
}
SResponse::~SResponse() {
}

int SResponse::getTicket() {
	return ticket;
}
void SResponse::setTicket(int ticket) {
	this->ticket = ticket;
}

int SResponse::getStatus() {
	return status;
}
void SResponse::setStatus(int status) {
	this->status = status;
}
