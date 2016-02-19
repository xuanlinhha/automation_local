/*
 * IRequest.h
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#ifndef IREQUEST_H_
#define IREQUEST_H_

#include <string>
#include <list>
#include "../common/FormatConst.h"

class IRequest {
private:
	std::string type;
	std::string id;
	int autoVersionMajor;
	int autoVersionMinor;
	std::list<int> params;
public:
	static const std::string DISPLAY;
	static const std::string SET;

	IRequest();
	virtual ~IRequest();

	std::string& getType();
	void setType(std::string& type);

	std::string& getId();
	void setId(std::string& id);

	int getAutoVersionMajor();
	void setAutoVersionMajor(int autoVersionMajor);

	int getAutoVersionMinor();
	void setAutoVersionMinor(int autoVersionMinor);

	std::list<int>& getParams();
	void setParams(std::list<int>& params);

	//------------------------------------
	std::string toString();
};

#endif /* IREQUEST_H_ */
