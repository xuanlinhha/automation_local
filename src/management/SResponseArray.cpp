/*
 * SResponseArray.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#include "SResponseArray.h"

const int SResponseArray::MAX_WAITING_TIME = 5; // 5s
std::mutex SResponseArray::singletonMutex;
std::shared_ptr<SResponseArray> SResponseArray::instance;

SResponseArray::SResponseArray() {
	for (int i = 0; i < TicketAgent::SLOT_NUMBER; i++) {
		responses[i] = SResponse::NO_RESPONE; // no response
	}
}

SResponseArray::~SResponseArray() {
}

std::shared_ptr<SResponseArray> SResponseArray::getInstance() {
	std::unique_lock<std::mutex> lock(singletonMutex);
	if (!instance) {
		instance.reset(new SResponseArray());
	}
	return instance;
}

int SResponseArray::getStatus(int position) {
	time_t begin = time(0);

	while (responses[position].load() == SResponse::NO_RESPONE) { //wait for response
		time_t current = time(0);
		if (current - begin > MAX_WAITING_TIME) {
			return SResponse::NO_RESPONE;
		}
	};

	int result = responses[position].load();

	// reset status
	responses[position] = SResponse::NO_RESPONE;
	return result;
}

void SResponseArray::putStatus(int position, int status) {
	responses[position] = status;
}
