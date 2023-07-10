#pragma once

#include "mercury/msgs/message.h"

#include <functional>
#include <string>

namespace mercury {
class Subscriber {

private:
	mercury::visitor fn;

public:
	Subscriber(std::string topic_name, mercury::visitor fn);

	void receiveMessage(mercury::Message msg);
};
} // namespace mercury