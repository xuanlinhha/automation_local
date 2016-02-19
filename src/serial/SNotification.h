/*
 * SNotification.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#ifndef SNOTIFICATION_H_
#define SNOTIFICATION_H_

#include <string>
#include <list>

class SNotification {
private:
	std::string id;
	std::list<int> status;
public:
	SNotification();
	virtual ~SNotification();

	std::string& getId();
	void setId(std::string& id);

	std::list<int>& getStatus();
	void setStatus(std::list<int>& status);
};

#endif /* SNOTIFICATION_H_ */
