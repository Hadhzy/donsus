// Lexer of the Donsus programming language
#include <stdio.h>
#include <ctype.h> // dl_name_identifier
#include <stdbool.h>
#include <string.h>
// Donsus internals
#include "../Include/lexer.h"
#include "../Include/parser.h"
#include "don_array.h"

static
char* de_get_token_from_name(donsus_token_kind kind) {
    switch (kind) {
        case DONSUS_NAME: return "DONSUS_NAME";
        case DONSUS_NUMBER: return "DONSUS_NUMBER";
        case DONSUS_STRING: return "DONSUS_STRING";
        case DONSUS_NEWLINE: return "DONSUS_NEWLINE";
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
        case DONSUS_END: return "DONSUS_END";

        default:
            return "UNKNOWN_TOKEN_KIND";
    }
}


void de_printout_single_token(struct donsus_token token){
    printf("------------------------\n");
    printf("Name: %s\n", de_get_token_from_name(token.kind));

    char buffer[TOKEN_MAX_STRLEN];
    snprintf(buffer, TOKEN_MAX_STRLEN, "%.*s", token.length, token.value);

    printf("Value: %s\n", buffer);
    printf("Line: %d\n", token.line);
    printf("length: %d\n", token.length);
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



char peek(donsus_parser * parser){
    // return next character
    if (parser->lexer.string[parser->lexer.cur_pos + 1] != EOF){
        return parser->lexer.string[parser->lexer.cur_pos + 1];
    }
    return '\0';
}

struct donsus_token peek_for_token(donsus_parser* parser){
    // return next token
    donsus_lexer old_lexer = parser->lexer;
    parser->token = donsus_lexer_next(parser);
    parser->lexer = old_lexer;
    return parser->token;
}

bool eat(donsus_parser *parser){
    // Increase the current position by one and set the character to the next one
    if ((parser->lexer.cur_char = parser->lexer.string[++parser->lexer.cur_pos]) != '\0'){
        return true;
    }
    return false;
}

static const char* next_number(donsus_parser * parser, struct donsus_token * token) {
    eat(parser);
    while (isdigit(parser->lexer.cur_char)) {
        ++token->length;
        eat(parser);
    }
    char *result = malloc(token->length);
    memcpy(result, parser->lexer.string, token->length);
    return result;
}

static const char* next_identifier(donsus_parser * parser, struct donsus_token * token){
    eat(parser);
    while (iscontinue(parser->lexer.cur_char) == true) {
        ++token->length;
        eat(parser);
    }
    char *result = malloc(token->length);
    memcpy(result, parser->lexer.string, token->length);
    return result;
}

// remove quotes from string
static void remove_quotes(char *result){
    // remove quotes from string
    char *result_out = malloc(strlen(result) - 2);
    memcpy(result, result + 1, strlen(result) - 2);
    result = result_out;
}

static const char * next_string(donsus_parser * parser , struct donsus_token * token){
    eat(parser);
    while (isstring_continue(parser->lexer.cur_char) == true) {
        ++token->length;
        eat(parser);
    }
    char *result = malloc(token->length);
    memcpy(result, parser->lexer.string, token->length);
    remove_quotes(result);
    return result;
}


struct donsus_token donsus_lexer_next(donsus_parser *parser) {
    struct donsus_token token;
    struct donsus_token *cur_token = token_init(DONSUS_END, (unsigned int) "", 0, 0, &token);

    switch(parser->lexer.cur_char){
        case '\r':
        case '\t':
        case ' ': {

            if(eat(parser) == false){
                cur_token->kind = DONSUS_END;
                cur_token->line = parser->lexer.cur_line;
                return *cur_token;
            }

            break;
        }

        case '\n': {
            cur_token->line = ++parser->lexer.cur_line;
            cur_token->kind = DONSUS_NEWLINE;
            cur_token->length = 5;
            eat(parser);
            return *cur_token;
        }

        case '!': {
            cur_token->kind = DONSUS_EXCLAMATION;
            cur_token->length = 1;
            cur_token->value = "!";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '+': {
            if (peek(parser) == '='){
                eat(parser);
                cur_token->kind = DONSUS_PLUS_EQUAL;
                cur_token->length = 2;
                cur_token->value = "+=";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            if (peek(parser) == '+'){
                eat(parser);
                cur_token->kind = DONSUS_INCREMENT;
                cur_token->length = 2;
                cur_token->value = "++";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            cur_token->kind = DONSUS_PLUS;
            cur_token->length = 1;
            cur_token->value = "+";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;

        }

        case '-':{
            if (peek(parser) == '='){
                eat(parser);
                cur_token->kind = DONSUS_MINUS_EQUAL;
                cur_token->length = 2;
                cur_token->value = "-=";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            if (peek(parser) == '-'){
                eat(parser);
                cur_token->kind = DONSUS_DECREMENT;
                cur_token->length = 2;
                cur_token->value = "--";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            cur_token->kind = DONSUS_MINUS;
            cur_token->length = 1;
            cur_token->value = "-";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '*': {
            if (peek(parser) == '=') {
                eat(parser);
                cur_token->kind = DONSUS_STAR_EQUAL;
                cur_token->length = 2;
                cur_token->value = "*=";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            cur_token->kind = DONSUS_STAR;
            cur_token->length = 1;
            cur_token->value = "*";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '/': {
            if (peek(parser) == '=') {
                eat(parser);
                cur_token->kind = DONSUS_SLASH_EQUAL;
                cur_token->length = 2;
                cur_token->value = "/=";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            cur_token->kind = DONSUS_SLASH;
            cur_token->length = 1;
            cur_token->value = "/";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '=': {
            if (peek(parser) == '=') {
                eat(parser);
                cur_token->kind = DONSUS_DOUBLE_EQUAL;
                cur_token->length = 2;
                cur_token->value = "==";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            cur_token->kind = DONSUS_EQUAL;
            cur_token->length = 1;
            cur_token->value = "=";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '(': {
            cur_token->kind = DONSUS_LPAR;
            cur_token->length = 1;
            cur_token->value = "(";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case ')': {
            cur_token->kind = DONSUS_RPAR;
            cur_token->length = 1;
            cur_token->value = ")";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '[': {
            cur_token->kind = DONSUS_LSQB;
            cur_token->length = 1;
            cur_token->value = "[";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case ']': {
            cur_token->kind = DONSUS_RSQB;
            cur_token->length = 1;
            cur_token->value = "]";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case ':': {
            cur_token->kind = DONSUS_COLO;
            cur_token->length = 1;
            cur_token->value = ":";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case ',': {
            cur_token->kind = DONSUS_COMM;
            cur_token->length = 1;
            cur_token->value = ",";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '.': {
            cur_token->kind = DONSUS_DOT;
            cur_token->length = 1;
            cur_token->value = ".";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '%': {
            cur_token->kind = DONSUS_PERCENT;
            cur_token->length = 1;
            cur_token->value = "%";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '{': {
            cur_token->kind = DONSUS_LBRACE;
            cur_token->length = 1;
            cur_token->value = "{";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '}': {
            cur_token->kind = DONSUS_RBRACE;
            cur_token->length = 1;
            cur_token->value = "}";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '^': {
            cur_token->kind = DONSUS_CIRCUMFLEX;
            cur_token->length = 1;
            cur_token->value = "^";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '#': {
            cur_token->kind = DONSUS_COMMENT;
            cur_token->length = 1;
            cur_token->value = "#";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '<': {
            if (peek(parser) == '=') {
                eat(parser);
                cur_token->kind = DONSUS_LESS_EQUAL;
                cur_token->length = 2;
                cur_token->value = "<=";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            cur_token->kind = DONSUS_LESS;
            cur_token->length = 1;
            cur_token->value = "<";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '>': {
            if (peek(parser) == '=') {
                eat(parser);
                cur_token->kind = DONSUS_GREATER_EQUAL;
                cur_token->length = 2;
                cur_token->value = ">=";
                cur_token->line = parser->lexer.cur_line;
                eat(parser);
                return *cur_token;
            }

            cur_token->kind = DONSUS_GREATER;
            cur_token->length = 1;
            cur_token->value = ">";
            cur_token->line = parser->lexer.cur_line;
            eat(parser);
            return *cur_token;
        }

        case '"':
        case '\'': {
            cur_token->kind = DONSUS_STRING;
            cur_token->length = 0;
            cur_token->value = next_string(parser, cur_token);
            cur_token->line = parser->lexer.cur_line;
            printf("last_char: %c\n", parser->lexer.cur_char);
            eat(parser);
            printf("last_char1: %c\n", parser->lexer.cur_char);
            return *cur_token;
        }

        default:
            // ERROR handling
            // IDENTIFIER
            if(isstart(parser->lexer.cur_char)){
                cur_token->kind = DONSUS_NAME;
                cur_token->length = 0;
                cur_token->value = next_identifier(parser, cur_token);
                cur_token->line = parser->lexer.cur_line;
                return *cur_token;
            }

            // NUMBER
            if(isdigit(parser->lexer.cur_char)){
                cur_token->kind = DONSUS_NUMBER;
                cur_token->length = 0;
                cur_token->value = next_number(parser, cur_token);
                cur_token->line = parser->lexer.cur_line;
                return *cur_token;
            }

            // END TOKEN
            if (peek(parser) == '\0'){
                cur_token->kind = DONSUS_END;
                cur_token->line = parser->lexer.cur_line;
                return *cur_token;
            }
            return *cur_token;

    }

}


donsus_lexer new_lexer(struct donsus_file *file_struct) {
    // create new lexer
    donsus_lexer lexer;
    lexer.string = file_struct->file_content;
    lexer.cur_char = file_struct->file_content[0];
    lexer.cur_pos = 0;
    lexer.cur_line = 1;

    return lexer;
}