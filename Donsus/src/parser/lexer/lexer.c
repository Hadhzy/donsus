// Lexer of the Donsus programming language
#include <stdio.h>
#include <ctype.h> // dl_name_identifier
#include <stdbool.h>
#include <string.h>
// Donsus internals
#include "../Include/token.h"
#include "../Include/lexer.h"
#include "don_array.h"

typedef struct donsus_token donsus_token;

static
char* de_get_token_from_name(donsus_token_kind kind) {
    switch (kind) {
        case DONSUS_NAME: return "DONSUS_NAME";
        case DONSUS_NUMBER: return "DONSUS_NUMBER";
        case DONSUS_STRING: return "DONSUS_STRING";
        case DONSUS_NEWLINE: return "DONSUS_NEWLINE";
        case DONSUS_INDENT: return "DONSUS_INDENT";
        case DONSUS_DEDENT: return "DONSUS_DEDENT";
        case DONSUS_LPAR: return "DONSUS_LPAR";
        case DONSUS_RPAR: return "DONSUS_RPAR";
        case DONSUS_LSQB: return "DONSUS_LSQB";
        case DONSUS_RSQB: return "DONSUS_RSQB";
        case DONSUS_COLO: return "DONSUS_COLO";
        case DONSUS_COMM: return "DONSUS_COMM";
        case DONSUS_PLUS: return "DONSUS_PLUS";
        case DONSUS_PLUS_EQUAL: return "DONSUS_PLUS_EQUAL";
        case DONSUS_MINUS: return "DONSUS_MINUS";
        case DONSUS_MINUS_EQUAL: return "DONSUS_MINUS_EQUAL";
        case DONSUS_STAR: return "DONSUS_STAR";
        case DONSUS_STAR_EQUAL: return "DONSUS_STAR_EQUAL";
        case DONSUS_SLASH: return "DONSUS_SLASH";
        case DONSUS_SLASH_EQUAL: return "DONSUS_SLASH_EQUAL";
        case DONSUS_LESS: return "DONSUS_LESS";
        case DONSUS_LESS_EQUAL: return "DONSUS_LESS_EQUAL";
        case DONSUS_GREATER: return "DONSUS_GREATER";
        case DONSUS_GREATER_EQUAL: return "DONSUS_GREATER_EQUAL";
        case DONSUS_EQUAL: return "DONSUS_EQUAL";
        case DONSUS_DOUBLE_EQUAL: return "DONSUS_DOUBLE_EQUAL";
        case DONSUS_DOT: return "DONSUS_DOT";
        case DONSUS_PERCENT: return "DONSUS_PERCENT";
        case DONSUS_LBRACE: return "DONSUS_LBRACE";
        case DONSUS_RBRACE: return "DONSUS_RBRACE";
        case DONSUS_CIRCUMFLEX: return "DONSUS_CIRCUMFLEX";
        case DONSUS_EXCLAMATION: return "DONSUS_EXCLAMATION";
        case DONSUS_COMMENT: return "DONSUS_COMMENT";
        case DONSUS_SINGLE_QUOTE : return "DONSUS_SINGLE_QUOTE";
        case DONSUS_DOUBLE_QUOTE : return "DONSUS_DOUBLE_QUOTE";
        case DONSUS_THREE_DOTS: return "DONSUS_THREE_DOTS";
        case DONSUS_NULL_VALUE: return "DONSUS_NULL_VAL";

        default:
            return "UNKNOWN_TOKEN_KIND";
    }
}


void de_printout_single_token(donsus_token token){
    printf("------------------------\n");
    printf("Name: %s\n", de_get_token_from_name(token.kind));

    char buffer[TOKEN_MAX_STRLEN];
    snprintf(buffer, TOKEN_MAX_STRLEN, "%.*s", token.size, token.value);

    printf("Value: %s\n", buffer);
    printf("Line: %d\n", token.line);
    printf("Size: %d\n", token.size);
    printf("------------------------\n");
}

static bool isstart(char c){
    return isalpha(c) || c == '_';
}

static bool iscontinue(char c){
    return isstart(c) || isdigit(c);
}

static bool isstring_continue(const char c){
    if(c == '\'' || c == '"') return false;
    return true;
}

static const char* next_identifier(donsus_lexer * lexer, donsus_token * token){
    --token->size; // better solution in the future? TBD
    while (iscontinue(*lexer->cursor)) {
        ++token->size;
        ++lexer->cursor;
    }
    char *result = malloc(token->size);
    memcpy(result, lexer->cursor-token->size, token->size);
    return result;
}

static const char* next_number(donsus_lexer * lexer, donsus_token * token) {
    while (isdigit(*lexer->cursor)) {
        ++token->size;
        ++lexer->cursor;
    }
    char *result = malloc(token->size);
    memcpy(result, lexer->cursor-token->size, token->size);
    return result;
}


static const char * next_string(donsus_lexer * lexer, donsus_token * token){
    ++lexer->cursor;
    --token->size; // better solution in the future? TBD
    while (isstring_continue(*lexer->cursor) == true) {
        ++token->size;
        ++lexer->cursor;
    }
    char *result = malloc(token->size);
    memcpy(result, lexer->cursor-token->size, token->size);
    return result;
}

static char *int_to_string(int number) {
    // Determine the number of digits in the integer
    int digits = snprintf(NULL, 0, "%d", number);

    // Allocate memory for the string, including space for the null-terminator
    char *result = malloc(digits + 1);
    if (result == NULL) {
        // Handle allocation failure
        exit(EXIT_FAILURE);
    }

    // Format the integer into the string
    snprintf(result, digits + 1, "%d", number);

    return result;
}

char peek(donsus_parser * parser){
    char result = *++parser->lexer.cursor;
    return result;
}

struct donsus_token peek_for_token(donsus_parser * parser){
    parser->lexer.cursor++;
    struct donsus_token token = donsus_lexer_next(parser);
    return token;
}


struct donsus_token donsus_lexer_next(donsus_parser *parser){
    while(*parser->lexer.cursor) {

        ReRun:
        switch(*parser->lexer.cursor) {

            // Handles special line characters
            case '\t': {
                return token_init(DONSUS_INDENT, parser->lexer.cursor++,  1, parser->lexer.line, NULL);
            }

            case ' ': {
                int space_counter = 0;
                while (*parser->lexer.cursor == ' ') {
                    space_counter++;
                    *parser->lexer.cursor++;
                }
                if(space_counter % 4 == 0) {
                    int space_result = space_counter / 4;
                    char *space_result_str = int_to_string(space_result);

                    return token_init(DONSUS_INDENT, parser->lexer.cursor, 1, parser->lexer.line, space_result_str);
                }
                break;
            }

            case '\n': {
                // Problem here is that if we peek for the next token, we will increase the lexer->cursor and then if the token is not indent then we have to return back a dedent however the token then will be lost
                // TODO: Fix this by having two separate lexers, one for peeking and one for the current token
                parser->lexer.cursor++;
                parser->lexer.line++;
                break;
            }


            case '!':
                return token_init(DONSUS_EXCLAMATION, parser->lexer.cursor, 1, parser->lexer.line++, "!");

                // Arithmetic operators
            case '+': {
                if (peek(parser) == '=') return token_init(DONSUS_PLUS_EQUAL, parser->lexer.cursor++, 2, parser->lexer.line, "+=") ;
                if (peek(parser) == '+') return token_init(DONSUS_INCREMENT, parser->lexer.cursor++, 2, parser->lexer.line, "++") ;
                return token_init(DONSUS_PLUS, parser->lexer.cursor++, 1, parser->lexer.line, "+");
            }

            case '-': {
                if (peek(parser) == '=') return token_init(DONSUS_MINUS_EQUAL, parser->lexer.cursor++, 2, parser->lexer.line, "-=");
                if (peek(parser) == '-') return token_init(DONSUS_DECREMENT, parser->lexer.cursor++, 2, parser->lexer.line, "--") ;
                return token_init(DONSUS_MINUS, parser->lexer.cursor++, 1, parser->lexer.line, "-");
            }

            case '*': {
                if (peek(parser) == '=') return token_init(DONSUS_STAR_EQUAL, parser->lexer.cursor++, 2, parser->lexer.line, "*=") ;
                return token_init(DONSUS_STAR, parser->lexer.cursor++, 1, parser->lexer.line, "*");
            }

            case '/': {
                if (peek(parser) == '=') return token_init(DONSUS_SLASH_EQUAL, parser->lexer.cursor++, 2, parser->lexer.line, "/=") ;
                return token_init(DONSUS_SLASH, parser->lexer.cursor++, 1, parser->lexer.line, "/");
            }

            case '=': {
                if (peek(parser) == '=') return token_init(DONSUS_DOUBLE_EQUAL, parser->lexer.cursor++, 2, parser->lexer.line, "==") ;
                return token_init(DONSUS_EQUAL, parser->lexer.cursor++, 1, parser->lexer.line, "=");
            }

            case '(': {
                return token_init(DONSUS_LPAR, parser->lexer.cursor++, 1, parser->lexer.line, "(");
            }

            case ')': {
                return token_init(DONSUS_RPAR, parser->lexer.cursor++, 1, parser->lexer.line, ")");
            }

            case '[': {
                return token_init(DONSUS_LSQB, parser->lexer.cursor++, 1, parser->lexer.line, "[");
            }

            case ']': {
                return token_init(DONSUS_RSQB, parser->lexer.cursor++, 1, parser->lexer.line, "]");
            }

            case '{': {
                return token_init(DONSUS_LBRACE, parser->lexer.cursor++, 1, parser->lexer.line, "{");
            }

            case '}': {
                return token_init(DONSUS_RBRACE, parser->lexer.cursor++, 1, parser->lexer.line, "}");
            }

            case '^': {
                return token_init(DONSUS_CIRCUMFLEX, parser->lexer.cursor++, 1, parser->lexer.line, "^");
            }

            case ':': {
                return token_init(DONSUS_COLO, parser->lexer.cursor++, 1, parser->lexer.line, ":");
            }

            case ',': {
                return token_init(DONSUS_COMM, parser->lexer.cursor++, 1, parser->lexer.line, ",");
            }

            case '.': {
                if (peek(parser) == '.' && peek(parser) == '.')
                    return token_init(DONSUS_DOT, parser->lexer.cursor++, 1, parser->lexer.line, ".");
            }

            case '%': {
                return token_init(DONSUS_PERCENT, parser->lexer.cursor++, 1, parser->lexer.line, "%");
            }

            case '#': {
                return token_init(DONSUS_COMMENT, parser->lexer.cursor++, 1, parser->lexer.line, "#");
            }

            case '>': {
                if (peek(parser) == '=') return token_init(DONSUS_GREATER_EQUAL, parser->lexer.cursor++, 2, parser->lexer.line, ">=") ;
                return token_init(DONSUS_GREATER, parser->lexer.cursor++, 1, parser->lexer.line, ">");
            }

            case '<': {
                if (peek(parser) == '=') return token_init(DONSUS_LESS_EQUAL, parser->lexer.cursor++, 2, parser->lexer.line, "<=") ;
                return token_init(DONSUS_LESS, parser->lexer.cursor++, 1, parser->lexer.line, "<");
            }
                // DONSUS_STRING sdljfsdfjlsdlfjsd DONSUS_STRING
            case '"': {
                // Add more stuff here
                return token_init(DONSUS_DOUBLE_QUOTE, parser->lexer.cursor++, 1, parser->lexer.line, "\"");
            }


            case '\'': {
                // Add more stuff here
                return token_init(DONSUS_SINGLE_QUOTE, parser->lexer.cursor++, 1, parser->lexer.line, "\'");
            }

            default: {
                //check for string
                if (*--parser->lexer.cursor == '"' || *parser->lexer.cursor == '\'') {
                    struct donsus_token token = donsus_token_identifier(DONSUS_STRING, parser->lexer.cursor, 1, parser->lexer.line);
                    const char * value = next_string(&parser->lexer, &token);
                    token.value = value;

                    return token;
                }

                // check for identifier
                *parser->lexer.cursor++;
                if (isstart(*parser->lexer.cursor)) {
                    struct donsus_token token = donsus_token_identifier(DONSUS_NAME, parser->lexer.cursor, 1, parser->lexer.line);
                    const char * value = next_identifier(&parser->lexer, &token);
                    token.value = value;

                    return token;

                }
                // check for number
                if (isdigit(*parser->lexer.cursor)) {
                    struct donsus_token token;
                    token = donsus_token_identifier(DONSUS_NUMBER, parser->lexer.cursor++, 1, parser->lexer.line);
                    const char * value = next_number(&parser->lexer, &token);
                    token.value = value;

                    return token;
                }


                // Check for string

                perror("CAN'T FIND TOKENS"); // Todo: Make this better in the future
                // Throw an error message

            }

        }
    }
}

donsus_lexer new_lexer(struct donsus_file *file_struct) {
    // create new lexer
    donsus_lexer lexer;
    lexer.string = file_struct->file_content;
    lexer.cursor = file_struct->file_content;
    lexer.line = 1;

    return lexer;
}