/*
 * Building.cpp
 *
 *  Created on: Jul 11, 2014
 *      Author: xuanlinhha
 */

#include "Building.h"

std::mutex Building::singletonMutex;
std::shared_ptr<Building> Building::instance;

Building::Building() {
	root = FileReader::readBuildingFile();
}

Building::~Building() {
}

std::shared_ptr<Building> Building::getInstance() {
	std::unique_lock<std::mutex> lock(singletonMutex);
	if (!instance) {
		instance.reset(new Building());
	}
	return instance;
}

std::shared_ptr<Node> Building::getNode(std::string id) {
	std::queue<std::shared_ptr<Node>> q;
	q.push(root);
	while (!q.empty()) {
		std::shared_ptr<Node> temp = q.front();
		if (temp->getId() == id) {
			return temp;
		} else {
			for (std::list<std::shared_ptr<Node>>::const_iterator iterator =
					temp->getChildren().begin();
					iterator != temp->getChildren().end(); ++iterator) {
				q.push(*iterator);
			}
			q.pop();
		}
	}
	return NULL;
}

void Building::resetNodeStatus(std::shared_ptr<Node> node) {
	std::list<int> status;
	if (node == NULL) {
		return;
	}
	if (!node->getStatus().empty()) {
		for (std::list<int>::iterator iterator = status.begin(), end =
				status.end(); iterator != end; ++iterator) {
			(*iterator) = 0;
		}
	}
	node->setStatus(status);
}

std::list<std::shared_ptr<Node>> Building::getSubTree(std::string id) {
	std::list<std::shared_ptr<Node>> result;
	std::shared_ptr<Node> head = getNode(id);
	if (head != NULL) {
		std::queue<std::shared_ptr<Node>> q;
		q.push(head);
		while (!q.empty()) {
			std::shared_ptr<Node> temp = q.front();
			result.push_back(temp);
			for (std::list<std::shared_ptr<Node> >::const_iterator iterator =
					temp->getChildren().begin();
					iterator != temp->getChildren().end(); ++iterator) {
				q.push(*iterator);
			}
			q.pop();
		}
	}
	return result;
}

std::list<std::shared_ptr<Node>> Building::getPathAndChildrenNodes(
		std::string id) {
	std::list<std::shared_ptr<Node>> result;
	std::stack<std::shared_ptr<Node>> s; // for DFS
	std::set<std::string> visitedNodes; // used to mark visited nodes
	s.push(root);
	visitedNodes.insert(root->getId());
	while (!s.empty()) {
		std::shared_ptr<Node> temp = s.top();

		// check if temp has unvisited children or not
		// hasUnvisitedChildren = true -> unvisitedChildren is the first children
		// Begin: hasUnvisitedChildren is No & unvisitedChildren is NULL
		bool hasUnvisitedChildren = false;
		std::shared_ptr<Node> unvisitedChildren;
		for (std::list<std::shared_ptr<Node>>::const_iterator iterator =
				temp->getChildren().begin();
				iterator != temp->getChildren().end(); ++iterator) {
			if (visitedNodes.find((*iterator)->getId()) == visitedNodes.end()) { // has children not visited or not in visited set
				hasUnvisitedChildren = true;
				unvisitedChildren = *iterator;
				break;
			}
		}

		if (hasUnvisitedChildren) {
			s.push(unvisitedChildren);
			visitedNodes.insert(unvisitedChildren->getId());
		} else {
			if (temp->getId() == id) {
				std::shared_ptr<Node> target = s.top();
				// copy stack
				while (!s.empty()) {
					result.push_front(s.top());
					s.pop();
				}
				// copy child nodes
				for (std::list<std::shared_ptr<Node>>::const_iterator iterator =
						target->getChildren().begin();
						iterator != target->getChildren().end(); ++iterator) {
					result.push_back(*iterator);
				}
			} else {
				s.pop();
			}
		}

	}
	return result;
	/*
	 1 push root to stack & mark root as visited
	 2 while stack not empty {
	 2.1 get top of stack
	 2.2 if top has children not visited {
	 2.2.1 push 1 children to stack & mark it as visited
	 }
	 2.3 else {
	 2.3.1 if top = target {
	 2.3.1.1 return content of stack
	 }
	 2.3.2 else {
	 2.3.2.1 pop
	 }
	 }
	 }
	 */
}

std::string Building::getPathAndChildrenNodesString(std::string id) {
	std::string result;
	std::list<std::shared_ptr<Node>> nodes = getPathAndChildrenNodes(id);
	if (!nodes.empty()) {
		for (std::list<std::shared_ptr<Node>>::iterator iterator =
				nodes.begin(), end = --nodes.end(); iterator != end;
				++iterator) {
			result.append((*iterator)->toDisplayString());
			result += FormatConst::LIST_SEPERATOR;
		}
		result.append((*(--nodes.end()))->toDisplayString());
	}
	return result;
}

bool Building::setStatus(std::string id, std::list<int>& status) {
	std::lock_guard<std::mutex> lock(buildingMutex);
	std::shared_ptr<Node> node = getNode(id);
	if (node == NULL) {
		return false;
	}
	if (node->getType() == Node::SWITCH && status.front() == 0) {
		std::list<std::shared_ptr<Node>> afterNodes = getSubTree(id);
		for (std::list<std::shared_ptr<Node>>::const_iterator iterator =
				afterNodes.begin(); iterator != afterNodes.end(); ++iterator) {
			resetNodeStatus(*iterator);
		}
	}
	node->setStatus(status);
	return true;
}

int Building::getLocation(std::string id) {
	std::shared_ptr<Node> node = getNode(id);
	if (node == NULL) {
		return -1;
	}
	return node->getLocation();
}

std::string Building::toFileString(std::string id) {
	std::string result = "";
	std::list<std::shared_ptr<Node>> nodes = getSubTree(id);
	unsigned int level = std::count(id.begin(), id.end(),
			FormatConst::ID_SEPERATOR); // used to track tree level
	for (std::list<std::shared_ptr<Node>>::const_iterator iterator =
			nodes.begin(); iterator != nodes.end(); ++iterator) {
		std::string id = (*iterator)->getId();
		std::string nodeData = (*iterator)->toFileString();
		// new line for next level
		if (std::count(id.begin(), id.end(), FormatConst::ID_SEPERATOR)
				> level) {
			result.append("\n");
			level++;
		}
		result.append(nodeData);
		result.append("\n");
	}
	return result;
}
std::string Building::toDisplayString(std::string id) {
	std::string result;
	std::list<std::shared_ptr<Node>> nodes = getSubTree(id);
	unsigned int level = std::count(id.begin(), id.end(),
			FormatConst::ID_SEPERATOR); // used to track tree level
	for (std::list<std::shared_ptr<Node>>::const_iterator iterator =
			nodes.begin(); iterator != nodes.end(); ++iterator) {
		std::string id = (*iterator)->getId();
		std::string nodeData = (*iterator)->toDisplayString();
		// new line for next level
		if (std::count(id.begin(), id.end(), FormatConst::ID_SEPERATOR)
				> level) {
			result.append("\n");
			level++;
		}
		result.append(nodeData);
		result.append("\n");
	}
	return result;
}
