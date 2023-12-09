#ifndef DU_LEXER_H
#define DU_LEXER_H
#include <stdio.h>
#include "don_array.h"

#include "../Include/internal/ducore_file.h"

#define DEBUG 1 // false by default

typedef struct{
    const char *string; // source code(file content)
    const char *cursor; // tabs?
    unsigned line; // line position
} donsus_lexer;



void de_printout_single_token(struct donsus_token token);
struct donsus_token donsus_lexer_next(donsus_lexer * lexer);
donsus_lexer new_lexer(struct donsus_file *file_struct);

#endif