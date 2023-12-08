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
// Todo: lexer should be passed in everywhere


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
        case DONSUS_SEMI: return "DONSUS_SEMI";
        case DONSUS_PLUS: return "DONSUS_PLUS";
        case DONSUS_PLUS_EQUAL: return "DONSUS_PLUS_EQUAL";
        case DONSUS_MINUS: return "DONSUS_MINUS";
        case DONSUS_MINUS_EQUAL: return "DONSUS_MINUS_EQUAL";
        case DONSUS_STAR: return "DONSUS_STAR";
        case DONSUS_STAR_EQUAL: return "DONSUS_STAR_EQUAL";
        case DONSUS_SLASH: return "DONSUS_SLASH";
        case DONSUS_DOUBLE_SLASH: return "DONSUS_DOUBLE_SLASH";
        case DONSUS_SLAS: return "DONSUS_SLAS";
        case DONSUS_VBAR: return "DONSUS_VBAR";
        case DONSUS_AMPE: return "DONSUS_AMPE";
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
        case DONSUS_TILDE: return "DONSUS_TILDE";
        case DONSUS_CIRCUMFLEX: return "DONSUS_CIRCUMFLEX";
        case DONSUS_AT: return "DONSUS_AT";
        case DONSUS_EXCLAMATION: return "DONSUS_EXCLAMATION";

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

static const char* next_identifier(donsus_lexer * lexer, donsus_token * token){
    char* result = NULL;
    char first = *--lexer->cursor; // TODO: Avoid this in the future
    while (iscontinue(*lexer->cursor)) {
        lexer->cursor++;
        char* tmp = (char*)realloc(result, sizeof(char) * token->size); //
        tmp[token->size] = *lexer->cursor; // *(tmp+token->size) = *lexer->cursor
        token->size++;
        result = tmp;

    }
    --token->size; // better solution in the future? TBD
    result[0] = first;
    return result;
}

static const char* next_number(donsus_lexer * lexer, donsus_token * token) {
    char * result = NULL;
    char first = *--lexer->cursor;
    while (isdigit(*lexer->cursor)){
        lexer->cursor++;
        char* tmp = (char*)realloc(result, sizeof(char) * token->size);
        tmp[token->size] = *lexer->cursor;
        token->size++;
        result = tmp;
    }
    --token->size;
    result[0] = first;
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
                return token_init(DONSUS_INDENT, lexer->cursor++,  1, lexer->line, "");
            }

            case ' ':
                lexer->cursor++;
                break;

            case '\n':
                lexer->cursor++; // go to the next character
                lexer->line++;
                break;

            // Arithmetic operators
            case '+': {
                if (peek(lexer) == '=') return token_init(DONSUS_PLUS_EQUAL, lexer->cursor++, 2, lexer->line, "+=") ;
                return token_init(DONSUS_PLUS, lexer->cursor++, 1, lexer->line, "+");

            }

            case '-': {
                if (peek(lexer) == '=') return token_init(DONSUS_MINUS_EQUAL, lexer->cursor++, 2, lexer->line, "-=");

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

            case '>': {
                if (peek(lexer) == '=') return token_init(DONSUS_GREATER_EQUAL, lexer->cursor++, 2, lexer->line, ">=") ;
                return token_init(DONSUS_GREATER, lexer->cursor++, 1, lexer->line, ">");
            }

            case '<': {
                if (peek(lexer) == '=') return token_init(DONSUS_LESS_EQUAL, lexer->cursor++, 2, lexer->line, "<=") ;
                return token_init(DONSUS_LESS, lexer->cursor++, 1, lexer->line, "<");
            }

            default: {
                // check for identifier
                if (isstart(*lexer->cursor)) {
                    struct donsus_token token = donsus_token_identifier(DONSUS_NAME, lexer->cursor++, 1, lexer->line);
                    const char * value = next_identifier(lexer, &token);
                    token.value = value;

                    return token;

                }

                if isdigit(*lexer->cursor){
                    struct donsus_token token;
                    token = donsus_token_identifier(DONSUS_NUMBER, lexer->cursor++, 1, lexer->line);
                    const char * value = next_number(lexer, &token);
                    token.value = value;

                    return token;
                }

                perror("CAN'T FIND TOKENS");
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
