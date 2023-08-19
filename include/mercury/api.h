/***************************************************************************************
 *
 * Mercury Template for PROS 3.4.3
 *
 * Mercury is a publisher-subscriber system designed to make communication
 * between subsystems on the robot seamless and safe. The template is designed
 * to be similar in syntax to ROS, a widely used operating system for
 * programming robots.
 *
 * Mercury operates with the Observer design pattern. Publishers are objects
 * that publish messages to a Topic object, which notifies a list of Subscriber
 * objects that then call a function on the received message. This facilitates a
 * many-to-many system, where multiple Publishers can publish to a Topic that
 * serves multiple Subscribers. Topics are stored in a map contained in a
 * singleton Server object that serves as the message broker.
 *
 ****************************************************************************************/

#pragma once

// Include statements
#include "pros/rtos.hpp"
#include <any>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

// Mercury namespace
namespace mercury {

// Forward declaration of Publisher and Subscriber for use in Server and Topic
// classes
template <class> class Publisher;
template <class> class Subscriber;

// Topic class template
template <class MessageT> class Topic {

private:
	// List of subscribers, stored as pointers
	// Subscribers have the same template type as their topic to facilitate type
	// checking
	std::vector<mercury::Subscriber<MessageT>*> subscribers;

public:
	// Constructor for Topic
	Topic() {
		this->subscribers = {};
	}

	// add_subscriber
	// Adds a pointer to a Subscriber to the Topic's list
	void add_subscriber(Subscriber<MessageT>* sub) {
		this->subscribers.push_back(sub);
	}

	// notify_subscribers
	// Pushes the given message to each Subscriber in the list
	void notify_subscribers(MessageT msg) {
		for (auto sub : this->subscribers) {
			sub->receive_message(msg);
		}
	}
};

// Server class
class Server {

private:
	// Unordered map lists Topics by name
	std::unordered_map<std::string, std::any> topics;

	// Unordered map lists a mutex lock in the form of a bool for each topic name.
	// This allows only one Publisher to publish to a topic at once, but for two
	// Topics to be accessed simultaneously
	std::unordered_map<std::string, bool> mutices;

	// Server constructor
	Server() {
	}

	// getInstance
	// Uses Meyers' lazy initialization implementation of a Singleton design
	// pattern. Only calls the constructor one time during the first call of
	// getInstance
	static Server& getInstance() {
		static Server instance;

		return instance;
	}

	// Declare Publisher and Subscriber as friends so that they can use private
	// Server member functions. This allows Server to be completely private to
	// discourage client from editing topics or messaging manually
	template <class> friend class mercury::Publisher;
	template <class> friend class mercury::Subscriber;

	// create_topic
	// Checks if topics already has an instance of a Topic with the given name. If
	// not, creates a new Topic object and mutex lock and adds them to their
	// respective maps
	template <class MessageT> void create_topic(std::string name) {
		if (this->topics.find(name) == this->topics.end()) {
			mercury::Topic<MessageT> new_topic;
			this->topics[name] = new_topic;
			this->mutices[name] = false;
		}
	}

	// publish_to_topic
	// Locks topic mutex, notifies subscribers to the topic about new message, and
	// unlocks topic mutex
	template <class MessageT>
	void publish_to_topic(std::string name, MessageT msg) {
		while (this->mutices[name])
			;
		this->mutices[name] = true;
		auto topic = std::any_cast<Topic<MessageT>>(this->topics[name]);
		topic.notify_subscribers(msg);
		this->mutices[name] = false;
	}

	// add_subscriber
	// Locks topic mutex, registers subscriber with topic, and unlocks topic mutex
	template <class MessageT>
	void add_subscriber(std::string name, Subscriber<MessageT>* sub) {
		while (this->mutices[name])
			;
		this->mutices[name] = true;
		if (this->topics.find(name) != this->topics.end()) {
			auto topic = std::any_cast<Topic<MessageT>>(this->topics[name]);
			topic.add_subscriber(sub);
			this->topics[name] = topic;
		}
		this->mutices[name] = false;
	}
};

// Publisher class
template <class MessageT> class Publisher {

	// Name of topic stored as string
	std::string name;

public:
	// Publisher constructor
	// Creates new topic for the publisher immediately if it does not exist
	Publisher(std::string name) : name(name) {
		auto& server = mercury::Server::getInstance();
		server.create_topic<MessageT>(name);
	}

	// publish
	// Uses Server to publish given message to topic
	void publish(MessageT msg) {
		auto& server = mercury::Server::getInstance();
		server.publish_to_topic(name, msg);
	}
};

// Subscriber class
template <class MessageT> class Subscriber {

private:
	// Callback function that is called with received messages as input
	std::function<void(MessageT)> fn;

public:
	// Subscriber constructor
	// Immediately registers itself with the necessary topic if the topic exists
	Subscriber(std::string name, std::function<void(MessageT)> fn) : fn(fn) {
		auto& server = mercury::Server::getInstance();
		server.add_subscriber(name, this);
	}

	// receive_message
	// Calls the fn callback function on the given message
	void receive_message(MessageT msg) {
		fn(msg);
	}
};

} // namespace mercury