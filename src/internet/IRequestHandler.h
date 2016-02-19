/*
 * IRequestHandler.h
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#ifndef IREQUESTHANDLER_H_
#define IREQUESTHANDLER_H_

#include <memory>
#include <mutex>
#include "IRequest.h"
#include "IResponse.h"
#include "../serial/SRequest.h"
#include "../serial/SResponse.h"
#include "../serial/SRequestHandler.h"

class IRequestHandler {
private:
	static std::mutex singletonMutex;
	static std::shared_ptr<IRequestHandler> instance;
	IRequestHandler();
public:
	static std::shared_ptr<IRequestHandler> getInstance();
	virtual ~IRequestHandler();
	void handleIRequest(IRequest& request, IResponse& response);
};

#endif /* IREQUESTHANDLER_H_ */
