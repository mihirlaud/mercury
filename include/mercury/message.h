#pragma once

#include <map>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace mercury {

struct Null;
struct Bool;
struct Number;
struct String;
struct Array;
struct Object;
using Message = std::variant<Null, Bool, Number, String, Array, Object>;

struct Null {};

struct Bool {
	bool b;
};

struct Number {
	double num;
};

struct String {
	std::string s;
};

struct Array {
	std::vector<Message> arr;
};

struct Object {
	std::map<std::string, Message> mp;
};

struct Serialize {
	std::string operator()(Null&) {
		return "null";
	}

	std::string operator()(Bool& val) {
		return std::to_string(val.b);
	}

	std::string operator()(Number& val) {
		return std::to_string(val.num);
	}

	std::string operator()(String& val) {
		return val.s;
	}

	std::string operator()(Array& val) {
		std::string ret = "[";

		for (auto element : val.arr) {
			ret += std::visit(Serialize(), element) + ", ";
		}

		ret = ret.substr(0, ret.size() - 2);
		ret += "]";

		return ret;
	}

	std::string operator()(Object& val) {
		std::string ret = "{";

		for (auto& key_val : val.mp) {
			std::string val_ser = std::visit(Serialize(), key_val.second);
			ret += "\"" + key_val.first + "\"" + ": " + +", ";
		}

		ret = ret.substr(0, ret.size() - 2);
		ret += "}";

		return ret;
	}
};

std::string serialize(Message msg);

} // namespace mercury