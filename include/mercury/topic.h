#pragma once

#include <vector>

#include "mercury/msgs/message.h"
#include "mercury/subscriber.h"

namespace mercury {

class Topic {
private:
	std::vector<mercury::Subscriber*> subscribers;

public:
	Topic();

	void add_subscriber(Subscriber* sub);
	void notify_subscribers(mercury::Message& msg);
};

} // namespace mercury