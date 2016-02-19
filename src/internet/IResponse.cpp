/*
 * IResponse.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#include "IResponse.h"

const std::string IResponse::BAD_REQUEST = "BAD REQUEST";
const std::string IResponse::SUCCESS = "SUCCESS";
const std::string IResponse::FAIL = "FAIL";

IResponse::IResponse() {
	status = "";
	data = "";
}
IResponse::~IResponse() {
}

std::string& IResponse::getStatus() {
	return status;
}
void IResponse::setStatus(std::string& status) {
	this->status = status;
}

std::string& IResponse::getData() {
	return data;
}
void IResponse::setData(std::string& data) {
	this->data = data;
}

std::vector<boost::asio::const_buffer> IResponse::toBuffers() {
	std::vector<boost::asio::const_buffer> buffers;
	std::string statusString = status.append("\r\n");
	buffers.push_back(boost::asio::buffer(statusString));
	std::string dataString = data.append("\r\n");
	buffers.push_back(boost::asio::buffer(dataString));
	return buffers;
}

std::string IResponse::toString() {
	std::string result = "";
	result.append(status);
	result.append("\r\n");
	result.append(data);
	result.append("\r\n");
	return result;
}
