#include "mercury/subscriber.h"
#include "mercury/server.h"

namespace mercury {

Subscriber::Subscriber(std::string topic_name, mercury::visitor* fn) {
	auto& server = mercury::Server::getInstance();
	server.subscribe_to_topic(topic_name, this);

	this->fn = fn;
}

void Subscriber::receiveMessage(mercury::Message msg) {
	std::visit(*fn, msg);
}

} // namespace mercury