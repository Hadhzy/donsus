#ifndef DU_LEXER_H
#define DU_LEXER_H
#include <stdio.h>

#include "../Include/internal/ducore_file.h"

struct donsus_lexer{
    char cur;
    size_t position;
    struct donsus_file* file_struct;
    int source_id;

};

struct donsus_file* new_lexer(struct donsus_file *file_struct);

#endif