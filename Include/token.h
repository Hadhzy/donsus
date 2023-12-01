#ifndef DU_TOKEN_H
#define DU_TOKEN_H


typedef enum donsus_token_kind {
    DONSUS_NAME,
    DONSUS_NUMBER,
    DONSUS_STRING,
    DONSUS_NEWLINE,
    DONSUS_INDENT,
    DONSUS_DEDENT,

    DONSUS_LPAR          = '(',
    DONSUS_RPAR          = ')',
    DONSUS_LSQB          = '[',
    DONSUS_RSQB          = ']',
    DONSUS_COLON         = ':',
    DONSUS_COMMA         = ',',
    DONSUS_SEMI          = ';',
    DONSUS_PLUS          = '+',
    DONSUS_MINUS         = '-',
    DONSUS_STAR          = '*',
    DONSUS_SLASH         = '/',
    DONSUS_VBAR          = '|',
    DONSUS_AMPER         = '&',
    DONSUS_LESS          = '<',
    DONSUS_GREATER       = '>',
    DONSUS_EQUAL         = '=',
    DONSUS_DOT           = '.',
    DONSUS_PERCENT       = '%',
    DONSUS_LBRACE        = '{',
    DONSUS_RBRACE        = '}',
    DONSUS_TILDE         = '~',
    DONSUS_CIRCUMFLEX    = '^',
    DONSUS_AT            = '@',
    DONSUS_EXCLAMATION   = '!',

} donsus_token_kind;

typedef struct donsus_token_Location {
    int source_line;
    long long offset;
    long long length;
} donsus_token_Location;


struct donsus_token{
    donsus_token_kind kind;
    donsus_token_Location location;
    // different values(int, real, double)
};

#endif // DU_TOKEN_H
