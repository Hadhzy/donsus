// Test_here
#include "parser.h"
#include "lexer.h"
#include "dontest.h" // test library

void setup(void){
    // Setup the test
    // E.g: create a file, create a variable, etc
}

void finished(void){
    // Finished the test
    // E.g: delete a file, delete a variable, etc
}

void success(void){
    // Test passed
    // E.g: print a message, etc
}

void error(void){
    // Test failed
    // E.g: print a message, etc
}

int test_parse(donsus_parser * par){
    // Should parse manually with respect to the generated expressions
    // E.g if the parser supposed to parse 2 tokens then it needs to be called 2 times
    // Todo: better tests cases
    test_assert_int(1, 1);
    return 0;
}