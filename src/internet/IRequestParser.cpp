/*
 * IRequestParser.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#include "IRequestParser.h"

IRequestParser::IRequestParser() :
		state(IParserState::IREQUEST_TYPE_START) {
}

IRequestParser::~IRequestParser() {
}

IRequestStatus IRequestParser::consume(IRequest& request, char input) {
	switch (state) {
	case IParserState::IREQUEST_TYPE_START:
		if (isNormal(input)) {
			state = IParserState::IREQUEST_TYPE;
			request.getType() += input;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::IREQUEST_TYPE:
		if (input == FormatConst::COMP_SEPERATOR) {
			state = IParserState::IREQUEST_ID_START;
			return IRequestStatus::INDETERMINATE;
		} else if (isNormal(input)) {
			request.getType() += input;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::IREQUEST_ID_START:
		if (isNormal(input)) {
			state = IParserState::IREQUEST_ID;
			request.getId() += input;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::IREQUEST_ID:
		if (input == FormatConst::COMP_SEPERATOR) {
			state = IParserState::AUTO_VERSION_A;
			return IRequestStatus::INDETERMINATE;
		} else if (isNormal(input)) {
			request.getId() += input;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::AUTO_VERSION_A:
		if (input == 'A') {
			state = IParserState::AUTO_VERSION_U;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::AUTO_VERSION_U:
		if (input == 'U') {
			state = IParserState::AUTO_VERSION_T;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::AUTO_VERSION_T:
		if (input == 'T') {
			state = IParserState::AUTO_VERSION_O;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::AUTO_VERSION_O:
		if (input == 'O') {
			state = IParserState::AUTO_VERSION_SLASH;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::AUTO_VERSION_SLASH:
		if (input == '/') {
			state = IParserState::VERSION_MAJOR_START;
			request.setAutoVersionMajor(0);
			request.setAutoVersionMinor(0);
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::VERSION_MAJOR_START:
		if (isDigit(input)) {
			request.setAutoVersionMajor(
					request.getAutoVersionMajor() * 10 + input - '0');
			state = IParserState::VERSION_MAJOR;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::VERSION_MAJOR:
		if (input == '.') {
			state = IParserState::VERSION_NINOR_START;
			return IRequestStatus::INDETERMINATE;
		} else if (isDigit(input)) {
			request.setAutoVersionMajor(
					request.getAutoVersionMajor() * 10 + input - '0');
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::VERSION_NINOR_START:
		if (isDigit(input)) {
			request.setAutoVersionMinor(
					request.getAutoVersionMinor() * 10 + input - '0');
			state = IParserState::VERSION_NINOR;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::VERSION_NINOR:
		if (input == '\r') {
			state = IParserState::EXPECTING_NEWLINE_1;
			return IRequestStatus::INDETERMINATE;
		} else if (isDigit(input)) {
			request.setAutoVersionMinor(
					request.getAutoVersionMinor() * 10 + input - '0');
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::EXPECTING_NEWLINE_1:
		if (input == '\n') {
			state = IParserState::PARAM_START;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::PARAM_START:
		if (input == '\r') {
			state = IParserState::EXPECTING_NEWLINE_END;
			return IRequestStatus::INDETERMINATE;
		} else if (isDigit(input)) {
			request.getParams().push_back(input - '0');
			state = IParserState::PARAM_VALUE;
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::PARAM_VALUE:
		if (input == FormatConst::COMP_SUB_SEPERATOR) {
			state = IParserState::PARAM_START;
			return IRequestStatus::INDETERMINATE;
		} else if (input == '\r') {
			state = IParserState::EXPECTING_NEWLINE_END;
			return IRequestStatus::INDETERMINATE;
		} else if (isDigit(input)) {
			request.getParams().back() = request.getParams().back() * 10 + input
					- '0';
			return IRequestStatus::INDETERMINATE;
		} else {
			return IRequestStatus::BAD;
		}

	case IParserState::EXPECTING_NEWLINE_END:
		return (input == '\n') ? IRequestStatus::GOOD : IRequestStatus::BAD;

	default:
		return IRequestStatus::BAD;

	}
}

bool IRequestParser::isChar(int c) {
	return c >= 0 && c <= 127;
}

bool IRequestParser::isControl(int c) {
	return (c >= 0 && c <= 31) || (c == 127);
}

bool IRequestParser::isSpecial(int c) {
	switch (c) {
	case '(':
	case ')':
	case '<':
	case '>':
	case '@':
	case ',':
	case ';':
	case ':':
	case '\\':
	case '"':
	case '/':
	case '[':
	case ']':
	case '?':
	case '=':
	case '{':
	case '}':
	case ' ':
	case '\t':
		return true;
	default:
		return false;
	}
}

bool IRequestParser::isDigit(int c) {
	return c >= '0' && c <= '9';
}

bool IRequestParser::isNormal(int c) {
	return (c > 31 && c < 127 && !isSpecial(c));
}
