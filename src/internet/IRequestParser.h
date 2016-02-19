/*
 * IRequestParser.h
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#ifndef IREQUESTPARSER_H_
#define IREQUESTPARSER_H_

#include <tuple>
#include "IRequest.h"
#include "../common/FormatConst.h"

enum IRequestStatus {
	GOOD, INDETERMINATE, BAD
};

enum IParserState {
	IREQUEST_TYPE_START,
	IREQUEST_TYPE,
	IREQUEST_ID_START,
	IREQUEST_ID,
	AUTO_VERSION_A,
	AUTO_VERSION_U,
	AUTO_VERSION_T,
	AUTO_VERSION_O,
	AUTO_VERSION_SLASH,
	VERSION_MAJOR_START,
	VERSION_MAJOR,
	VERSION_NINOR_START,
	VERSION_NINOR,
	EXPECTING_NEWLINE_1,
	PARAM_START,
	PARAM_VALUE,
	EXPECTING_NEWLINE_END
};

class IRequestParser {
private:
	IRequestStatus consume(IRequest& request, char input);
	IParserState state;
	static bool isChar(int c); // 0 <= c <= 127
	static bool isControl(int c); // 0 <= c <= 31
	static bool isSpecial(int c);
	static bool isDigit(int c); // 0 <= c <= 9
	static bool isNormal(int c); // 31 < c < 127 && !isSpecial
public:
	template<typename InputIterator>
	std::tuple<IRequestStatus, InputIterator> parse(IRequest& request,
			InputIterator begin, InputIterator end) {
		while (begin != end) {
			IRequestStatus result = consume(request, *begin++);
			if (result == IRequestStatus::GOOD
					|| result == IRequestStatus::BAD) {
				return std::make_tuple(result, begin);
			}
		}
		return std::make_tuple(IRequestStatus::INDETERMINATE, begin);
	}
	IRequestParser();
	virtual ~IRequestParser();
};

#endif /* IREQUESTPARSER_H_ */
