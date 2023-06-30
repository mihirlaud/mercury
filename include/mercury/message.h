#pragma once

#include <string>

namespace mercury {

class Message {
public:
	virtual std::string to_string() = 0;
};

} // namespace mercury