// Test_here
#include "parser.h"
#include "lexer.h"

int test_parse(donsus_parser * par){
    // Should parse manually with respect to the generated expressions
    // E.g if the parser supposed to parse 2 tokens then it needs to be called 2 times
    // Todo: better tests cases
    de_printout_single_token(par->token);
    return 0;
}
