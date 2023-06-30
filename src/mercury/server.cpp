#include "mercury/server.h"

namespace mercury {

void Server::create_topic(std::string name) {
	this->topics_mutex.take();
	if (this->topics.find(name) == this->topics.end()) {
		mercury::Topic new_topic;
		this->topics[name] = new_topic;
	}
	this->topics_mutex.give();
}

void Server::subscribe_to_topic(std::string name, Subscriber* sub) {
	this->topics_mutex.take();
	this->topics[name].add_subscriber(sub);
	this->topics_mutex.give();
}

void Server::push_to_topic(std::string name, mercury::Message msg) {
	this->queue_mutex.take();
	this->msg_queue.push({name, msg});
	this->queue_mutex.give();
}

} // namespace mercury