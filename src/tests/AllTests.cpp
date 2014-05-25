/*
 * AllTests.cpp
 *
 *  Created on: May 25, 2014
 *      Author: boris
 */

#include <tests/AllTests.hpp>

int tests_run = 0;

AllTests::AllTests(int _type) {
	type_tests = _type;
}

AllTests::~AllTests() {
	// TODO Auto-generated destructor stub
}

char* AllTests::all_tests(){
	if (type_tests & CMD_PARSER_TESTS)
		mu_run_test(cmdtests.runTests);
	if (type_tests & TLM_PARSER_TESTS)
		mu_run_test(tlmtests.runTests);
	if (type_tests & COMMUNICATION_HANDLER_TESTS)
		mu_run_test(tlmtests.runTests);
	return 0;
}

void AllTests::run_all_tests(){
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	}
	else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
}

