#include "mercury/server.h"

namespace mercury {

void Server::create_topic(std::string name) {
	if (this->topics.find(name) == this->topics.end()) {
		mercury::Topic new_topic;
		this->topics[name] = new_topic;
	}
}

void Server::subscribe_to_topic(std::string name, Subscriber* sub) {
	this->topics[name].add_subscriber(sub);
}

void Server::push_to_topic(std::string name, mercury::Message& msg) {
	this->topics[name].notify_subscribers(msg);
}

} // namespace mercury