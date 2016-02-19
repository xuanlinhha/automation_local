/*
 * Building.h
 *
 *  Created on: Jul 11, 2014
 *      Author: xuanlinhha
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include <string>
#include <list>
#include <mutex>
#include <fstream>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include "Node.h"
#include "FileReader.h"

class Building {
private:
	std::mutex buildingMutex;
	static std::mutex singletonMutex;
	static std::shared_ptr<Building> instance;
	std::shared_ptr<Node> root;
	std::shared_ptr<Node> getNode(std::string id);
	std::list<std::shared_ptr<Node>> getSubTree(std::string id);
	void resetNodeStatus(std::shared_ptr<Node> node);
	std::list<std::shared_ptr<Node>> getPathAndChildrenNodes(std::string id);
	Building();
public:
	~Building();
	static std::shared_ptr<Building> getInstance();
	//--------------------------------------------
	std::string getPathAndChildrenNodesString(std::string id);
	bool setStatus(std::string id, std::list<int>& status);
	int getLocation(std::string id);
	//--------------------------------------------
	std::string toFileString(std::string id);
	std::string toDisplayString(std::string id);
};

#endif /* BUILDING_H_ */
