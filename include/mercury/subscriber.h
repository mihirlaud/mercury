#pragma once

#include "mercury/message.h"

#include <functional>
#include <string>

namespace mercury {
class Subscriber {

private:
	std::function<void(mercury::Message&)> fn;

public:
	Subscriber(std::string topic_name, std::function<void(mercury::Message&)> fn);

	void receiveMessage(mercury::Message& msg);
};
} // namespace mercury