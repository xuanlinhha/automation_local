/*
 * Node.h
 *
 *  Created on: Jul 11, 2014
 *      Author: xuanlinhha
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <list>
#include <memory>
#include "../common/FormatConst.h"

class Node {
private:
	std::string type;
	std::string id;
	std::string description;
	std::list<int> status;
	int location;
	std::list<std::shared_ptr<Node>> children;
public:
	static const std::string SWITCH;
	static const std::string LIGHT;
	static const std::string MOOD_LIGHT;
	static const std::string COLOR_LIGHT;

	Node();
	virtual ~Node();

	std::string& getType();
	void setType(std::string& type);

	std::string& getId();
	void setId(std::string& id);

	std::string& getDescription();
	void setDescription(std::string& description);

	std::list<int>& getStatus();
	void setStatus(std::list<int>& status);

	int getLocation();
	void setLocation(int location);

	std::list<std::shared_ptr<Node>>& getChildren();
	void setChildren(std::list<std::shared_ptr<Node>>& children);

	std::string toDisplayString();
	std::string toFileString();
};

#endif /* NODE_H_ */
