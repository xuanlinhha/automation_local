/*
 * SRequest.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#ifndef SREQUEST_H_
#define SREQUEST_H_

#include <string>
#include <list>
#include "SChecksum.h"
#include "../common/FormatConst.h"

class SRequest {
private:
	int location;
	int ticket;
	std::string id;
	std::list<int> params;
public:
	SRequest();
	virtual ~SRequest();
	int getLocation();
	void setLocation(int location);

	int getTicket();
	void setTicket(int ticket);

	std::string& getId();
	void setId(std::string& id);

	std::list<int>& getParams();
	void setParams(std::list<int>& params);
	//-------------------------------------
	std::string toString();
};

#endif /* SREQUEST_H_ */
