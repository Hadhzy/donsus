#ifndef DU_TOKEN_H
#define DU_TOKEN_H

// Todo: Add more tokens

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
    DONSUS_MINU,
    DONSUS_STAR,
    DONSUS_SLAS,
    DONSUS_VBAR,
    DONSUS_AMPE,         
    DONSUS_LESS,
    DONSUS_GREATER,
    DONSUS_EQUAL,
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
} donsus_token_Location;


struct donsus_token{
    donsus_token_kind kind;
    donsus_token_location location;

    // different values(int, real, double)
};

#endif // DU_TOKEN_H
