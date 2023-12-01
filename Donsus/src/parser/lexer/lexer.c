// Lexer of the Donsus programming language
#include "../Include/token.h"
#include "../Include/lexer.h"
#include "../Include/internal/ducore_file.h"
#include <stdio.h>


char peek(struct donsus_lexer *lexer){
    // getting the next character without increasing position
    size_t _cur_pos = lexer->position;

    char next_char = lexer->file_struct->file_content[_cur_pos + 1];

    lexer->position = _cur_pos;

    return next_char;
}


struct donsus_token* identify_token(struct donsus_lexer *lexer, struct donsus_token *token){
    // identify the token
    char cur = lexer->cur;

    switch(cur){
        case '+':
            // ignore whitespace
            break;

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

    while (file_content[lexer->position] != '\0') {
        struct donsus_token* token;

        lexer->cur = file_content[lexer->position];

         struct donsus_token* output = identify_token(lexer, token); // identify the token

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

