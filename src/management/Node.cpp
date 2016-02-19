/*
 * Node.cpp
 *
 *  Created on: Jul 11, 2014
 *      Author: xuanlinhha
 */

#include "Node.h"

const std::string Node::SWITCH = "SWITCH";
const std::string Node::LIGHT = "LIGHT";
const std::string Node::MOOD_LIGHT = "MOOD_LIGHT";
const std::string Node::COLOR_LIGHT = "COLOR_LIGHT";

Node::Node() {
	type = "";
	id = "";
	description = "";
	status.clear();
	location = -1;
	children.clear();
}
Node::~Node() {
}

std::string& Node::getType() {
	return type;
}
void Node::setType(std::string& type) {
	this->type = type;
}

std::string& Node::getId() {
	return id;
}
void Node::setId(std::string& id) {
	this->id = id;
}

std::string& Node::getDescription() {
	return description;
}
void Node::setDescription(std::string& description) {
	this->description = description;
}

std::list<int>& Node::getStatus() {
	return status;
}
void Node::setStatus(std::list<int>& status) {
	this->status = status;
}

int Node::getLocation() {
	return location;
}
void Node::setLocation(int location) {
	this->location = location;
}

std::list<std::shared_ptr<Node>>& Node::getChildren() {
	return children;
}
void Node::setChildren(std::list<std::shared_ptr<Node>>& children) {
	this->children = children;
}

std::string Node::toDisplayString() {
	// TYPE ID DESCRIPTION STATUS
	std::string result = "";
	result.append(type);
	result += FormatConst::COMP_SEPERATOR;
	result.append(id);
	result += FormatConst::COMP_SEPERATOR;
	result.append(description);
	if (!status.empty()) {
		result += FormatConst::COMP_SEPERATOR;
		for (std::list<int>::const_iterator iterator = status.begin(), end =
				--status.end(); iterator != end; ++iterator) {
			result.append(std::to_string(*iterator));
			result += FormatConst::COMP_SUB_SEPERATOR;
		}
		result.append(std::to_string(*(--status.end())));
	}
	return result;
}
std::string Node::toFileString() {
	// TYPE ID DESCRIPTION LOCATION
	std::string result = "";
	result.append(type);
	result += FormatConst::COMP_SEPERATOR;
	result.append(id);
	result += FormatConst::COMP_SEPERATOR;
	result.append(std::to_string(location));
	result += FormatConst::COMP_SEPERATOR;
	result.append(description);
	return result;
}
