// Only errors occurring when constructing a new token
#ifndef DU_LEXER_ERROR
#define DU_LEXER_ERROR

struct lexer_error{
    char *message;
    int *value;
};

#endif // DU_LEXER_ERROR