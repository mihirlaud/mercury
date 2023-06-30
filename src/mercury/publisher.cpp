#include "mercury/publisher.h"
#include "mercury/server.h"

namespace mercury {

Publisher::Publisher(std::string name) : name(name) {
	auto& server = mercury::Server::getInstance();
	server.create_topic(name);
}

void Publisher::publish(mercury::Message& msg) {
	auto& server = mercury::Server::getInstance();
	server.push_to_topic(this->name, msg);
}

} // namespace mercury