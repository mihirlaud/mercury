#pragma once

#include <variant>

#include "mercury/msgs/Bool.h"
#include "mercury/msgs/Double.h"
#include "mercury/msgs/Integer.h"
#include "mercury/msgs/Point.h"
#include "mercury/msgs/String.h"

namespace mercury {

using Message = std::variant<Bool, Double, Integer, Point, String>;

struct visitor {
	void operator()(Bool&) {}
	void operator()(Double&) {}
	void operator()(Integer&) {}
	void operator()(Point&) {}
	void operator()(String&) {}
};

}
