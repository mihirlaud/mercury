#pragma once

#include "mercury/message.h"
#include "mercury/publisher.h"
#include "mercury/subscriber.h"
#include "mercury/topic.h"

#include <string>
#include <unordered_map>

namespace mercury {

class Server {

private:
	std::unordered_map<std::string, mercury::Topic> topics;

	Server() {
		this->topics = {};
	}

	static Server& getInstance() {
		static Server instance; // Guaranteed to be destroyed.
		                        // Instantiated on first use.
		return instance;
	}

	friend mercury::Publisher;
	friend mercury::Subscriber;

	void create_topic(std::string name);
	void push_to_topic(std::string name, mercury::Message& msg);
	void subscribe_to_topic(std::string name, Subscriber* sub);
};

} // namespace mercury