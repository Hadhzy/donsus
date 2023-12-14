#ifndef DU_TOKEN_H
#define DU_TOKEN_H

#define TOKEN_MAX_STRLEN 50
typedef enum{

    DONSUS_NAME, // IDENTIFIER
    DONSUS_NUMBER, // 69
    DONSUS_STRING, // "hello world"
    DONSUS_NEWLINE, // \n
    DONSUS_END, // mark the end of the code

    DONSUS_LPAR, // (
    DONSUS_RPAR, // )
    DONSUS_LSQB, // [
    DONSUS_RSQB, // ]
    DONSUS_COLO, // :
    DONSUS_COMM,  // ,
    DONSUS_PLUS, // +
    DONSUS_PLUS_EQUAL, // +=
    DONSUS_MINUS, // -
    DONSUS_MINUS_EQUAL, // -=
    DONSUS_STAR, // *
    DONSUS_STAR_EQUAL, // *=
    DONSUS_SLASH, // /
    DONSUS_SLASH_EQUAL, // /=
    DONSUS_LESS, // x < y
    DONSUS_LESS_EQUAL, // x <= y
    DONSUS_GREATER, // x > y
    DONSUS_GREATER_EQUAL, // x >= y
    DONSUS_EQUAL, // =
    DONSUS_DOUBLE_EQUAL, // ==
    DONSUS_DOT, // .
    DONSUS_PERCENT, // %
    DONSUS_LBRACE, // {
    DONSUS_RBRACE, // }
    DONSUS_CIRCUMFLEX, // ^
    DONSUS_INCREMENT, // ++
    DONSUS_DECREMENT, // --
    DONSUS_EXCLAMATION, // !
    DONSUS_COMMENT, // #
    DONSUS_SINGLE_QUOTE, // '
    DONSUS_DOUBLE_QUOTE, // "
    DONSUS_THREE_DOTS, // ...
} donsus_token_kind;


struct donsus_token{
    donsus_token_kind kind; // the type of the tokens from donsus_token_kind
    const char* value; // the value of the token as a string
    unsigned length; // the length of the token as an unsigned integer
    unsigned line; // the line where the token was created
};

struct donsus_token* token_init(donsus_token_kind kind, unsigned length, unsigned line, char * value,  struct donsus_token * token);
struct donsus_token donsus_token_identifier(donsus_token_kind type, unsigned length, unsigned line);

#endif // DU_TOKEN_H
