#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace mercury {

class Value {

public:
	Value() {
	}

	std::string to_string() {
		return "";
	}
};

class Bool : public Value {

private:
	bool b;

public:
	Bool() : b(false) {
	}

	Bool(bool b) : b(b) {
	}

	std::string to_string() {
		return std::to_string(this->b);
	}
};

class Number : public Value {

private:
	double d;

public:
	Number() : d(0.0) {
	}

	Number(double d) : d(d) {
	}

	std::string to_string() {
		return std::to_string(this->d);
	}
};

class String : public Value {

private:
	std::string s;

public:
	String() : s("") {
	}

	String(std::string s) : s(s) {
	}

	std::string to_string() {
		return this->s;
	}
};

class Array : public Value {
private:
	std::vector<Value> arr;

public:
	Array() {
		this->arr = {};
	}

	Array(std::vector<bool> vec) {
		this->arr = {};
		for (bool b : vec) {
			arr.push_back(Bool(b));
		}
	}

	Array(std::vector<double> vec) {
		this->arr = {};
		for (double d : vec) {
			arr.push_back(Number(d));
		}
	}

	Array(std::vector<std::string> vec) {
		this->arr = {};
		for (std::string s : vec) {
			arr.push_back(String(s));
		}
	}

	Array(std::vector<Value> vec) {
		this->arr = vec;
	}

	std::string to_string() {
		std::string s = "[";
		for (Value& v : this->arr) {
			s += v.to_string() + ",";
		}
		s += "]";
		return s;
	}
};

class Object : public Value {

private:
	std::unordered_map<std::string, Value> m;

public:
};

class Message {

public:
	Message() {
	}

	virtual std::string to_string() = 0;
};

} // namespace mercury