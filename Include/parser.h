#ifndef DU_PARSER_H
#define DU_PARSER_H
#include <stdbool.h>
#include "token.h"
#include "lexer.h"

typedef struct {
    bool error;
    struct donsus_token token;
    donsus_lexer lexer;
} donsus_parser;

donsus_parser parser_init(struct donsus_file *file_struct, donsus_lexer lexer);
struct donsus_token parser_next(donsus_parser *parser);

#endif