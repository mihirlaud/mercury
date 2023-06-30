#pragma once

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace mercury {

struct Bool;
struct Number;
struct String;
struct Array;
struct Object;
using Message = std::variant<Bool, Number, String, Array, Object>;

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

struct visitor {
	void operator()(Bool&) {
	}
	void operator()(Number&) {
	}
	void operator()(String&) {
	}
	void operator()(Array&) {
	}
	void operator()(Object&) {
	}
};

} // namespace mercury