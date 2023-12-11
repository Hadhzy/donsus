#ifndef DU_TOKEN_H
#define DU_TOKEN_H

// Todo: Add more tokens/comment describing them, separate tokens system for operators, names .etc

#define TOKEN_MAX_STRLEN 50
typedef enum _{
    // Identifier
    DONSUS_NAME, // IDENTIFIER
    DONSUS_NUMBER, // 69
    DONSUS_STRING, // "hello world"
    DONSUS_NEWLINE, // \n
    DONSUS_INDENT, //----something here
    DONSUS_DEDENT, // first token after indent

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
    DONSUS_NULL_VALUE

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
