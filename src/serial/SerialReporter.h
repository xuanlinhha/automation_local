/*
 * SerialReporter.h
 *
 *  Created on: Jul 29, 2014
 *      Author: xuanlinhha
 */

#ifndef SERIALREPORTER_H_
#define SERIALREPORTER_H_

#include "SResponse.h"
#include "SNotification.h"
#include "../management/Building.h"
#include "../management/SResponseArray.h"

class SerialReporter {
public:
	SerialReporter();
	virtual ~SerialReporter();
	static void processNotification(SNotification& notification);
	static void processResponse(SResponse& response);
};

#endif /* SERIALREPORTER_H_ */
