#include "parser.h"
#include "lexer.h"

// Initialise parser
donsus_parser parser_init(struct donsus_file *file_struct, donsus_lexer lexer) {
    donsus_parser parser;
    parser.lexer = lexer;
    parser.token = donsus_lexer_next(&parser);
    parser.error = false;
    return parser;
}

/* returns next token */
struct donsus_token parser_next(donsus_parser *parser) {
    return parser->token = donsus_lexer_next(parser);
}
