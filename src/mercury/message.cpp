#include "mercury/message.h"

namespace mercury {

std::string serialize(Message msg) {
	return std::visit(Serialize(), msg);
}

} // namespace mercury