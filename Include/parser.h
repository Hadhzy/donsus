#ifndef DU_PARSER_H
#define DU_PARSER_H

#include <stdbool.h>
#include "token.h"
#include "../Include/internal/ducore_file.h"
#define DEBUG 1 // false by default

typedef struct{
    const char *string; // source code(file content)
    char cur_char; // current character
    unsigned cur_pos, cur_line; // current position, current line
} donsus_lexer;


typedef struct {
    bool error;
    struct donsus_token token;
    donsus_lexer lexer;
} donsus_parser;

donsus_parser parser_init(struct donsus_file *file_struct, donsus_lexer lexer);
struct donsus_token parser_next(donsus_parser *parser);

#endif // DU_PARSER_H
