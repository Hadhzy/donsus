#ifndef DU_TOKEN_H
#define DU_TOKEN_H

// Todo: Add more tokens/comment describing them, separate tokens system for operators, names .etc

#define TOKEN_MAX_STRLEN 50
typedef enum {
    // Identifier
    DONSUS_NAME,
    DONSUS_NUMBER,
    DONSUS_STRING,
    DONSUS_NEWLINE,
    DONSUS_INDENT,
    DONSUS_DEDENT,

    DONSUS_LPAR,
    DONSUS_RPAR,
    DONSUS_LSQB,
    DONSUS_RSQB,
    DONSUS_COLO,
    DONSUS_COMM,
    DONSUS_SEMI,
    DONSUS_PLUS,
    DONSUS_PLUS_EQUAL,
    DONSUS_MINUS,
    DONSUS_MINUS_EQUAL,
    DONSUS_STAR,
    DONSUS_STAR_EQUAL,
    DONSUS_SLASH,
    DONSUS_SLASH_EQUAL,
    DONSUS_SLAS,
    DONSUS_VBAR,
    DONSUS_AMPE,         
    DONSUS_LESS,
    DONSUS_LESS_EQUAL,
    DONSUS_GREATER,
    DONSUS_GREATER_EQUAL,
    DONSUS_EQUAL,
    DONSUS_DOUBLE_EQUAL,
    DONSUS_DOT,
    DONSUS_PERCENT,
    DONSUS_LBRACE,
    DONSUS_RBRACE,
    DONSUS_TILDE,
    DONSUS_CIRCUMFLEX,
    DONSUS_AT,
    DONSUS_EXCLAMATION

} donsus_token_kind;


struct donsus_token{
    donsus_token_kind kind;
    const char* position;
    unsigned size;
    const char * value;
    unsigned line;
};

struct donsus_token token_init(donsus_token_kind type, const char * position, unsigned length, unsigned line, char* value);
struct donsus_token donsus_token_identifier(donsus_token_kind type, const char*position, unsigned size, unsigned line);

#endif // DU_TOKEN_H
