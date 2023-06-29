#include "mercury/subscriber.h"
#include "mercury/server.h"

namespace mercury {

Subscriber::Subscriber(std::string topic_name,
                       std::function<void(mercury::Message&)> fn) {
	auto& server = mercury::Server::getInstance();
	server.subscribe_to_topic(topic_name, this);

	this->fn = fn;
}

void Subscriber::receiveMessage(mercury::Message& msg) {
	this->fn(msg);
}

} // namespace mercury