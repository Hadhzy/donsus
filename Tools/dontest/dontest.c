#include <stdio.h>
#include  <stdlib.h>
#include "dontest.h"

struct DonFile{
    const char* filename;
    int current_line_number;
    int current_test_number;
    int number_of_tests;
    int number_of_failures;
};

struct DonFile TestRunner;

void DonTestBegin(const char *filename) {
    /*
     * Begin the test runner
     * Setting up basic information about the files
     */
    TestRunner.filename = filename;
    TestRunner.current_test_number = 0;
    TestRunner.number_of_tests = 0;
    TestRunner.number_of_failures = 0;
}

void DonTestDefaultRun(void (*func)(void), const int lineNumber) {
    /*
     * Execute the test function(func)
     * */
    TestRunner.current_line_number = lineNumber;
    TestRunner.current_test_number++;
    TestRunner.number_of_tests++;
    func();

}
int don_test_assert_int(int expected, int actual){
    /*
     * Basic test assert for int
     * Call success() if the test passed
     * Call error() if the test failed
     * Call finished in both cases()
     */

    atexit(success);
    setup();

    if (expected != actual) {
        printf("Test failed: expected %d, actual %d\n", expected, actual);
        finished();
        error();
        abort();
    }

    finished();
    return 0;

}
