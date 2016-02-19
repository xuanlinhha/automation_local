/*
 * SChecksum.h
 *
 *  Created on: Aug 3, 2014
 *      Author: xuanlinhha
 */

#ifndef SCHECKSUM_H_
#define SCHECKSUM_H_

#include <string>
#include "../common/FormatConst.h"

class SChecksum {
public:
	SChecksum();
	virtual ~SChecksum();
	static char generateChecksum(const std::string& message);
	static bool verifyChecksum(const std::string& fullMessage);
};

#endif /* SCHECKSUM_H_ */
