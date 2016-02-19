/*
 * IResponse.h
 *
 *  Created on: Jul 18, 2014
 *      Author: xuanlinhha
 */

#ifndef IRESPONSE_H_
#define IRESPONSE_H_

#include <string>
#include <vector>
#include <boost/asio.hpp>

class IResponse {
private:
	std::string status;
	std::string data;
public:
	static const std::string BAD_REQUEST;
	static const std::string SUCCESS;
	static const std::string FAIL;

	IResponse();
	virtual ~IResponse();

	std::string& getStatus();
	void setStatus(std::string& status);

	std::string& getData();
	void setData(std::string& data);

	std::vector<boost::asio::const_buffer> toBuffers();
	std::string toString();
};

#endif /* IRESPONSE_H_ */
