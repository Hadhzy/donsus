#ifndef DU_LEXER_H
#define DU_LEXER_H
#include <stdio.h>
#include "don_array.h"
#include "../Include/parser.h"
#include "../Include/internal/ducore_file.h"

void de_printout_single_token(struct donsus_token token);
struct donsus_token donsus_lexer_next(donsus_parser * parser);
donsus_lexer new_lexer(struct donsus_file *file_struct);

#endif
