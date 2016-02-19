/*
 * FileReader.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: xuanlinhha
 */

#include "FileReader.h"

const std::string FileReader::BUILDING_FILE = "buildingdata/diagram";

FileReader::FileReader() {
}

FileReader::~FileReader() {
}

std::string FileReader::getFromBeginToLast(std::string s, char delimiter) {
	unsigned lastPoint = s.find_last_of(delimiter);
	return s.substr(0, lastPoint);
}

bool FileReader::isEmptyOrComment(std::string data) {
	if (data.empty() || data.at(0) == '#')
		return true;
	return false;
}

std::shared_ptr<Node> FileReader::parseSegmentToNode(std::string data) {
	// TYPE ID LOCATION DESCRIPTION
	if (data.empty()) {
		return NULL;
	}
	// divide data
	std::vector<std::string> elements;
	std::istringstream iss(data);
	std::string s;
	while (std::getline(iss, s, FormatConst::COMP_SEPERATOR)) {
		elements.push_back(s);
	}

	if (elements.size() != 4) {
		return NULL;
	}
	std::shared_ptr<Node> node(new Node());
	node->setType(elements[0]);
	node->setId(elements[1]);
	node->setLocation(std::stoi(elements[2]));
	node->setDescription(elements[3]);
	std::list<int> status;
	if (node->getType() == Node::SWITCH || node->getType() == Node::LIGHT
			|| node->getType() == Node::MOOD_LIGHT) {
		status.push_front(0);
	} else if (node->getType() == Node::COLOR_LIGHT) {
		status.push_front(0);
		status.push_front(0);
		status.push_front(0);
	}
	node->setStatus(status);
	node->setStatus(status);
	return node;
}

std::shared_ptr<Node> FileReader::readBuildingFile() {
	std::shared_ptr<Node> result;

	std::ifstream ifs(BUILDING_FILE);
	if (ifs.is_open()) {
		// get root node data
		std::string line;
		while (std::getline(ifs, line)) {
			if (!isEmptyOrComment(line)) {
				// line.pop_back();
				result = parseSegmentToNode(line);
				break;
			}
		}
		// get other nodes info
		std::queue<std::shared_ptr<Node> > q;
		q.push(result);
		std::shared_ptr<Node> parent = q.front();
		while (std::getline(ifs, line)) {
			if (!isEmptyOrComment(line)) {
				// line.pop_back();
				// create new node
				std::shared_ptr<Node> node = parseSegmentToNode(line);
				std::string parentId = getFromBeginToLast(node->getId(),
						FormatConst::ID_SEPERATOR);
				// if new node is child of parent
				if (parentId == parent->getId()) {
					// push new node to branches
					parent->getChildren().push_back(node);
				} else {
					// remove parent from queue and get new parent
					q.pop();
					parent = q.front();
					parent->getChildren().push_back(node);
				}
				// push new node to queue
				q.push(node);
			}
		}
	}
	return result;
}
