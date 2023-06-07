#include "mercury/topic.h"

namespace mercury {

Topic::Topic() {
	this->subscribers = {};
}

void Topic::add_subscriber(Subscriber* sub) {
	this->subscribers.push_back(sub);
}

void Topic::notify_subscribers(mercury::Message& msg) {
	for (auto sub : this->subscribers) {
		sub->receiveMessage(msg);
	}
}

} // namespace mercury