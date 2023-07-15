#pragma once

#include "mercury/msgs/message.h"

#include <functional>
#include <queue>
#include <string>
#include <unordered_map>

namespace mercury {

template <class MessageT> class Publisher;
template <class MessageT> class Subscriber;

template <class MessageT> class Topic {
private:
	std::vector<mercury::Subscriber<MessageT>*> subscribers;

public:
	Topic() {
		this->subscribers = {};
	}

	void add_subscriber(Subscriber<MessageT>* sub) {
		this->subscribers.push_back(sub);
	}

	void notify_subscribers(MessageT msg) {
		for (auto sub : this->subscribers) {
			sub->receiveMessage(msg);
		}
	}
};

class Server {

private:
	std::unordered_map<std::string, mercury::Topic<Message>> topics;

	Server() {
		this->topics = {};
	}

	static Server& getInstance() {
		static Server instance; // Guaranteed to be destroyed.
		                        // Instantiated on first use.
		return instance;
	}

	template <class MessageT> friend class mercury::Publisher;
	template <class MessageT> friend class mercury::Subscriber;

	// void create_topic(std::string name);
	// void push_to_topic(std::string name, mercury::Message msg);
	// void subscribe_to_topic(std::string name, Subscriber<class MessageT>* sub);
};

template <class MessageT> class Publisher {

	std::string name;

public:
	Publisher(std::string name) : name(name) {
		auto& server = mercury::Server::getInstance();
		if (server.topics.find(name) == server.topics.end()) {
			mercury::Topic<mercury::Message> new_topic;
			server.topics[name] = new_topic;
		}
	}

	void publish(MessageT msg) {
		auto& server = mercury::Server::getInstance();
		server.topics[name].notify_subscribers(msg);
	}
};

template <class MessageT> class Subscriber {

private:
	std::function<void(MessageT)> fn;

public:
	Subscriber(std::string name, std::function<void(MessageT)> fn) : fn(fn) {
		auto& server = mercury::Server::getInstance();
		server.topics[name].add_subscriber(this);
	}

	void receiveMessage(MessageT msg) {
		printf("msg received\n");
		fn(msg);
	}
};

} // namespace mercury