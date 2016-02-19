/*
 * TicketAgent.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#include "TicketAgent.h"

//const int TicketAgent::SLOT_NUMBER = 10;
std::mutex TicketAgent::singletonMutex;
std::shared_ptr<TicketAgent> TicketAgent::instance;

TicketAgent::TicketAgent() {
	for (int i = 0; i < SLOT_NUMBER; i++) {
		tickets.insert(i);
	}
}

TicketAgent::~TicketAgent() {
}

std::shared_ptr<TicketAgent> TicketAgent::getInstance() {
	std::unique_lock<std::mutex> lock(singletonMutex);
	if (!instance) {
		instance.reset(new TicketAgent());
	}
	return instance;
}

int TicketAgent::getTicket() {
	std::unique_lock<std::mutex> lock(ticketAgentMutex);
	while (tickets.size() == 0) {
		conditionVariable.wait(lock);
	}
	std::set<int>::iterator it = tickets.begin();
	int ticket = *it;
	tickets.erase(it);
	return ticket;
}

void TicketAgent::addTicket(int ticket) {
	std::unique_lock<std::mutex> lock(ticketAgentMutex);
	tickets.insert(ticket);
	conditionVariable.notify_one();
}
