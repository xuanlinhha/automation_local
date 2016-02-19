/*
 * IRequest.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#include "IRequest.h"

const std::string IRequest::DISPLAY = "DISPLAY";
const std::string IRequest::SET = "SET";

IRequest::IRequest() {
	type = "";
	id = "";
	autoVersionMajor = 1;
	autoVersionMinor = 0;
}
IRequest::~IRequest() {
}

std::string& IRequest::getType() {
	return type;
}
void IRequest::setType(std::string& type) {
	this->type = type;
}

std::string& IRequest::getId() {
	return id;
}
void IRequest::setId(std::string& id) {
	this->id = id;
}

int IRequest::getAutoVersionMajor() {
	return autoVersionMajor;
}
void IRequest::setAutoVersionMajor(int autoVersionMajor) {
	this->autoVersionMajor = autoVersionMajor;
}

int IRequest::getAutoVersionMinor() {
	return autoVersionMinor;
}
void IRequest::setAutoVersionMinor(int autoVersionMinor) {
	this->autoVersionMinor = autoVersionMinor;
}

std::list<int>& IRequest::getParams() {
	return params;
}
void IRequest::setParams(std::list<int>& params) {
	this->params = params;
}

std::string IRequest::toString() {
	std::string result = "";
	result.append(type);
	result += FormatConst::COMP_SEPERATOR;
	result.append(id);
	result += FormatConst::COMP_SEPERATOR;
	result.append("AUTO/");
	result.append(std::to_string(autoVersionMajor));
	result += '.';
	result.append(std::to_string(autoVersionMinor));
	result.append("\r\n");
	if (!params.empty()) {
		for (std::list<int>::iterator iterator = params.begin(), end =
				--params.end(); iterator != end; ++iterator) {
			result.append(std::to_string(*iterator));
			result += FormatConst::COMP_SUB_SEPERATOR;
		}
		result.append(std::to_string(*(--params.end())));
	}
	result.append("\r\n");
	return result;
}
