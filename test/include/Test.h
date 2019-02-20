#ifndef NCHESS_TEST_H
#define NCHESS_TEST_H

#include <vector>
#include <string>
#include <iostream>

class TestFailData {
public:
	std::string getSource() const { return source; }
	std::string getMessage() const { return message; }

	TestFailData(const std::string &source, const std::string &message) {
		this->source = source;
		this->message = message;
	}

private:
	std::string source;
	std::string message;
};

class Test {
public:
	static void startTests() {Test::testing = true;}
	static void stopTests();
	virtual void run() final;
private:
	virtual bool test() = 0;

	static bool testing;
	static std::vector<TestFailData> testFailures;
};

#endif //NCHESS_TEST_H
