#pragma once

#include "mercury/message.h"
#include "mercury/publisher.h"
#include "mercury/subscriber.h"
#include "mercury/topic.h"
#include "pros/rtos.hpp"

#include <queue>
#include <string>
#include <unordered_map>

namespace mercury {

class Server {

private:
	std::unordered_map<std::string, mercury::Topic> topics;
	std::queue<std::pair<std::string, mercury::Message&>> msg_queue;

	pros::Mutex topics_mutex;
	pros::Mutex queue_mutex;

	Server() {
		this->topics = {};

		pros::Task server_task([=](void) {
			while (true) {
				this->queue_mutex.take();
				if (!this->msg_queue.empty()) {
					auto msg_pair = this->msg_queue.front();
					msg_queue.pop();

					this->topics_mutex.take();
					this->topics[msg_pair.first].notify_subscribers(msg_pair.second);
					this->topics_mutex.give();
				}
				this->queue_mutex.give();

				pros::delay(10);
			}
		});
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