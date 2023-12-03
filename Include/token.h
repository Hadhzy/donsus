#ifndef DU_TOKEN_H
#define DU_TOKEN_H

// Todo: Add more tokens/comment describing them, separate tokens system for operators, names .etc

typedef enum {
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
    DONSUS_DOUBLE_SLASH,
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

typedef struct {
    int source_id;
    size_t offset;
    long long length;
} donsus_token_location;


typedef struct {
    const char *data;
    long long length;
} don_string_view;

struct donsus_token{
    donsus_token_kind kind;
    donsus_token_location* location;
    don_string_view value;
    // different values(int, real, double)
};

#endif // DU_TOKEN_H
