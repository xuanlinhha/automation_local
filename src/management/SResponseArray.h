/*
 * SResponseArray.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#ifndef SRESPONSEARRAY_H_
#define SRESPONSEARRAY_H_

#include <memory>
#include <mutex>
#include <atomic>
#include <ctime>
#include "TicketAgent.h"
#include "../serial/SResponse.h"

class SResponseArray {
private:
	static const int MAX_WAITING_TIME; // 5s
	static std::mutex singletonMutex;
	static std::shared_ptr<SResponseArray> instance;
	SResponseArray();
	std::atomic<int> responses[TicketAgent::SLOT_NUMBER];
public:
	static std::shared_ptr<SResponseArray> getInstance();
	virtual ~SResponseArray();
	int getStatus(int position);
	void putStatus(int position, int status);
};

#endif /* SRESPONSEARRAY_H_ */
