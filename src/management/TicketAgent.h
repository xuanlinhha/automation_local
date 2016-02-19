/*
 * TicketAgent.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#ifndef TICKETAGENT_H_
#define TICKETAGENT_H_

#include <memory>
#include <set>
#include <mutex>
#include <condition_variable>
#include "../common/FormatConst.h"

class TicketAgent {
private:
	static std::mutex singletonMutex;
	static std::shared_ptr<TicketAgent> instance;
	std::mutex ticketAgentMutex;
	std::condition_variable conditionVariable;
	std::set<int> tickets;
public:
	static const int SLOT_NUMBER = 10;
	static std::shared_ptr<TicketAgent> getInstance();
	TicketAgent();
	virtual ~TicketAgent();
	int getTicket();
	void addTicket(int ticket);
};

#endif /* TICKETAGENT_H_ */
