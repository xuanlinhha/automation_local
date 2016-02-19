//============================================================================
// Name        : automation_local.cpp
// Author      : xuanlinhha
// Version     :
// Copyright   : Your copyright notice
// Description : Automation application running on local, Ansi-style
//============================================================================

#include <thread>
#include "internet/IListener.h"
#include "serial/SListener.h"

int main() {
	std::thread t { SListener() };
	t.detach();
	IListener::getInstance()->run();
	return 0;
}
