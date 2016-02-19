/*
 * IRequestHandler.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#include "IRequestHandler.h"

std::mutex IRequestHandler::singletonMutex;
std::shared_ptr<IRequestHandler> IRequestHandler::instance;

IRequestHandler::IRequestHandler() {
}
IRequestHandler::~IRequestHandler() {
}

std::shared_ptr<IRequestHandler> IRequestHandler::getInstance() {
	std::unique_lock<std::mutex> lock(singletonMutex);
	if (!instance) {
		instance.reset(new IRequestHandler());
	}
	return instance;
}

void IRequestHandler::handleIRequest(IRequest& request, IResponse& response) {
	if (request.getType() == IRequest::DISPLAY) {
		std::string id = request.getId();
		std::string data =
				Building::getInstance()->getPathAndChildrenNodesString(id);
		std::string status = IResponse::SUCCESS;
		response.setStatus(status);
		response.setData(data);
	} else if (request.getType() == IRequest::SET) {
		// pass id and parameters for serial request
		SRequest sRequest;
		sRequest.setId(request.getId());
		sRequest.setParams(request.getParams());

		// use serial request handler to process serial request
		int result = SRequestHandler::getInstance()->handleSRequest(sRequest);

		if (result == SResponse::SUCCESS) {
			std::string iResponseStatus = IResponse::SUCCESS;
			response.setStatus(iResponseStatus);
		} else {
			std::string iResponseStatus = IResponse::FAIL;
			response.setStatus(iResponseStatus);
		}
	}
}
