#include "../include/Test.h"

bool Test::testing = false;

void Test::run() {
	if (!testing)
		testFailures.emplace_back(TestFailData("Test", "Attempting to run test when testing has ended or has not been started"));
	test();
}

void printCharNumOfTimes(char charToPrint, unsigned long numOfTimes, bool newline) {
	for (int i = 0; i < numOfTimes; ++i)
		std::cout << charToPrint;
	if (newline)
		std::cout << std::endl;
}

void Test::stopTests() {
	Test::testing = false;

	if (testFailures.empty()) {
		std::cout << "Tests completed without error" << std::endl;
		std::cout << "No error reports will be generated" << std::endl;
	} else {
		printCharNumOfTimes('+', 40, true);
		std::cout << testFailures.size() << " tests failed, error reports will be displayed for each" << std::endl;
		for (const TestFailData &data : testFailures) {
			printCharNumOfTimes('~', 40, true);
			std::cout << "Source: " << data.getSource() << std::endl;
			std::cout << "Message: " << data.getMessage() << std::endl;
		}
		printCharNumOfTimes('+', 40, true);
	}
}
