// Lexer of the Donsus programming language
#include "../Include/token.h"
#include "../Include/lexer.h"
#include "../Include/internal/ducore_file.h"
#include <stdio.h>
#include  <stdlib.h>
// Donsus internals
#include "../Include/token.h"
#include "../Include/lexer.h"
#include "../Include/internal/ducore_file.h"
#include "don_array.h"


char peek(struct donsus_lexer *lexer){
    // getting the next character without increasing position
    size_t _cur_pos = lexer->position;

    char next_char = lexer->file_struct->file_content[_cur_pos + 1];

    lexer->position = _cur_pos;

    return next_char;
}


int create_tokens(struct donsus_lexer *lexer, struct don_array *tokens){
    // identify the token
    char cur = lexer->cur;

    switch(cur){
        case '+': {
            /*
             * Obtaining tokens:
             *  - +
             *  - +=
             */

            token_kind = DONSUS_PLUS;

            if (peek(lexer) == '=') {
                // add token(+=)
                token_kind =
                out_token.kind = token_kind;

                // token location
                token_location.length = 2;
                token_location.source_id = lexer->source_id;
                token_location.offset = lexer->position; // TODO: might need to make this more complicated

                out_token.location = token_location;

                don_array_append(tokens, &out_token);

                break;
            }

            token_kind = DONSUS_PLUS;
            out_token.kind = token_kind;

            token_location.length = 1;
            token_location.source_id = lexer->source_id;
            token_location.offset = lexer->position;

            out_token.location = token_location;

            don_array_append(tokens, &out_token);
            // add token(+)
            break;
        }

        case '\n':
            // ignore newline
            break;

        default:
            return 0;
    }
    return 0;
}


int main_lexer_loop(struct donsus_lexer *lexer){
    // loop through every character
    char *file_content = lexer->file_struct->file_content;

    don_array tokens; // array of tokens
    don_array_init(&tokens, DON_ARRAY_INITIAL_CAPACITY); // initial capacity of 4

    while (file_content[lexer->position] != '\0') {

        lexer->cur = file_content[lexer->position];


         int output = create_tokens(lexer, &tokens); // identify the token

        ++lexer->position; // Move to the next character
    }
    return 0;
}


struct donsus_file* new_lexer(struct donsus_file *file_struct){
    // create new lexer
    struct donsus_lexer lexer = {
        .cur = '\0',
        .position = 0,
        .file_struct = file_struct
    };

    main_lexer_loop(&lexer);
    // loop through the characters
    return 0;
}

