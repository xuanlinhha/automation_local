/*
 * SResponse.h
 *
 *  Created on: Jul 21, 2014
 *      Author: xuanlinhha
 */

#ifndef SRESPONSE_H_
#define SRESPONSE_H_

class SResponse {
private:
	int ticket;
	int status;
public:
	static const int NO_RESPONE;
	static const int SUCCESS;
	static const int FAIL;

	SResponse();
	virtual ~SResponse();

	int getTicket();
	void setTicket(int ticket);

	int getStatus();
	void setStatus(int status);
};

#endif /* SRESPONSE_H_ */
