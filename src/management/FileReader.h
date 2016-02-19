/*
 * FileReader.h
 *
 *  Created on: Jul 19, 2014
 *      Author: xuanlinhha
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <queue>
#include "Node.h"
#include "../common/FormatConst.h"

class FileReader {
private:
	static const std::string BUILDING_FILE;
	static std::string getFromBeginToLast(std::string s, char delimiter);
	static bool isEmptyOrComment(std::string data);
	static std::shared_ptr<Node> parseSegmentToNode(std::string data);
public:
	FileReader();
	virtual ~FileReader();
	static std::shared_ptr<Node> readBuildingFile();
};

#endif /* FILEREADER_H_ */
