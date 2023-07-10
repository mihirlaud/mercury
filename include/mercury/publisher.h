#pragma once

#include "mercury/msgs/message.h"

#include <string>

namespace mercury {

class Publisher {

	std::string name;

public:
	Publisher(std::string name);

	void publish(mercury::Message msg);
};

} // namespace mercury