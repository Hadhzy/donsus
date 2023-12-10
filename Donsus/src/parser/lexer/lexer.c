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

char* _de_get_token_from_name(donsus_token_kind kind) {
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

        default:
            return "UNKNOWN_TOKEN_KIND";
    }
}


void de_printout_single_token(donsus_token token){
    printf("------------------------\n");
    printf("Name: %s\n", _de_get_token_from_name(token.kind));

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



const char peek(donsus_lexer * lexer){
    char result = *++lexer->cursor;
    return result;
}


struct donsus_token donsus_lexer_next(donsus_lexer * lexer){
    while(*lexer->cursor) {
        switch(*lexer->cursor) {

            // Handles special line characters
            case '\t': {
                return token_init(DONSUS_INDENT, lexer->cursor++,  1, lexer->line, NULL);
            }

            case ' ':
                printf("Here");
                lexer->cursor++;
                break;

            case '\n':
                lexer->cursor++; // go to the next character
                lexer->line++;
                break;

            case '!':
                return token_init(DONSUS_EXCLAMATION, lexer->cursor++, 1, lexer->line, "!");

            // Arithmetic operators
            case '+': {
                if (peek(lexer) == '=') return token_init(DONSUS_PLUS_EQUAL, lexer->cursor++, 2, lexer->line, "+=") ;
                if (peek(lexer) == '+') return token_init(DONSUS_INCREMENT, lexer->cursor++, 2, lexer->line, "++") ;
                return token_init(DONSUS_PLUS, lexer->cursor++, 1, lexer->line, "+");
            }

            case '-': {
                if (peek(lexer) == '=') return token_init(DONSUS_MINUS_EQUAL, lexer->cursor++, 2, lexer->line, "-=");
                if (peek(lexer) == '-') return token_init(DONSUS_DECREMENT, lexer->cursor++, 2, lexer->line, "--") ;
                return token_init(DONSUS_MINUS, lexer->cursor++, 1, lexer->line, "-");
            }

            case '*': {
                if (peek(lexer) == '=') return token_init(DONSUS_STAR_EQUAL, lexer->cursor++, 2, lexer->line, "*=") ;
                return token_init(DONSUS_STAR, lexer->cursor++, 1, lexer->line, "*");
            }

            case '/': {
                if (peek(lexer) == '=') return token_init(DONSUS_SLASH_EQUAL, lexer->cursor++, 2, lexer->line, "/=") ;
                return token_init(DONSUS_SLASH, lexer->cursor++, 1, lexer->line, "/");
            }

            case '=': {
                if (peek(lexer) == '=') return token_init(DONSUS_DOUBLE_EQUAL, lexer->cursor++, 2, lexer->line, "==") ;
                return token_init(DONSUS_EQUAL, lexer->cursor++, 1, lexer->line, "=");
            }

            case '(': {
                return token_init(DONSUS_LPAR, lexer->cursor++, 1, lexer->line, "(");
            }

            case ')': {
                return token_init(DONSUS_RPAR, lexer->cursor++, 1, lexer->line, ")");
            }

            case '[': {
                return token_init(DONSUS_LSQB, lexer->cursor++, 1, lexer->line, "[");
            }

            case ']': {
                return token_init(DONSUS_RSQB, lexer->cursor++, 1, lexer->line, "]");
            }

            case '{': {
                return token_init(DONSUS_LBRACE, lexer->cursor++, 1, lexer->line, "{");
            }

            case '}': {
                return token_init(DONSUS_RBRACE, lexer->cursor++, 1, lexer->line, "}");
            }

            case '^': {
                return token_init(DONSUS_CIRCUMFLEX, lexer->cursor++, 1, lexer->line, "^");
            }

            case ':': {
                return token_init(DONSUS_COLO, lexer->cursor++, 1, lexer->line, ":");
            }

            case ',': {
                return token_init(DONSUS_COMM, lexer->cursor++, 1, lexer->line, ",");
            }

            case '.': {
                if (peek(lexer) == '.' && peek(lexer) == '.')
                return token_init(DONSUS_DOT, lexer->cursor++, 1, lexer->line, ".");
            }

            case '%': {
                return token_init(DONSUS_PERCENT, lexer->cursor++, 1, lexer->line, "%");
            }

            case '#': {
                return token_init(DONSUS_COMMENT, lexer->cursor++, 1, lexer->line, "#");
            }

            case '>': {
                if (peek(lexer) == '=') return token_init(DONSUS_GREATER_EQUAL, lexer->cursor++, 2, lexer->line, ">=") ;
                return token_init(DONSUS_GREATER, lexer->cursor++, 1, lexer->line, ">");
            }

            case '<': {
                if (peek(lexer) == '=') return token_init(DONSUS_LESS_EQUAL, lexer->cursor++, 2, lexer->line, "<=") ;
                return token_init(DONSUS_LESS, lexer->cursor++, 1, lexer->line, "<");
            }
            // DONSUS_STRING sdljfsdfjlsdlfjsd DONSUS_STRING
            case '"': {
                // Add more stuff here
                return token_init(DONSUS_DOUBLE_QUOTE, lexer->cursor++, 1, lexer->line, "\"");
            }


            case '\'': {
                // Add more stuff here
                return token_init(DONSUS_SINGLE_QUOTE, lexer->cursor++, 1, lexer->line, "\'");
            }

            default: {
                //check for string
                if (*--lexer->cursor == '"' || *lexer->cursor == '\'') {
                    struct donsus_token token = donsus_token_identifier(DONSUS_STRING, lexer->cursor, 1, lexer->line);
                    const char * value = next_string(lexer, &token);
                    token.value = value;

                    return token;
                }

                // check for identifier
                *lexer->cursor++;
                if (isstart(*lexer->cursor)) {
                    struct donsus_token token = donsus_token_identifier(DONSUS_NAME, lexer->cursor, 1, lexer->line);
                    const char * value = next_identifier(lexer, &token);
                    token.value = value;

                    return token;

                }
                // check for number
                if (isdigit(*lexer->cursor)) {
                    struct donsus_token token;
                    token = donsus_token_identifier(DONSUS_NUMBER, lexer->cursor++, 1, lexer->line);
                    const char * value = next_number(lexer, &token);
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
