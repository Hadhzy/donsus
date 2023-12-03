// Lexer of the Donsus programming language
#include <stdio.h>
#include <ctype.h> // dl_name_identifier
// Donsus internals
#include "../Include/token.h"
#include "../Include/lexer.h"
#include "don_array.h"

typedef struct donsus_token donsus_token;
// Todo: lexer should be passed in everywhere

// Debug functions
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

void _de_print_out_tokens(struct don_array *a){
    for (size_t i = 0; i < a->size; i++) {

        struct donsus_token* _token = don_array_get(a, i);
        donsus_token_location *_token_location = _token->location;

        printf("----------------------------------\n");
        printf("token_name: %s\n", _de_get_token_from_name(_token->kind));
        printf("token position: %zu\n", _token_location->offset);
        printf("token source_id: %d\n", _token_location->source_id);
        printf("token value: %c\n", *_token->value.data);
        printf("----------------------------------\n");
    }
}


char peek(struct donsus_lexer *lexer){
    // getting the next character without increasing position
    size_t _cur_pos = lexer->position;

    char next_char = lexer->file_struct->file_content[_cur_pos + 1];

    lexer->position = _cur_pos;

    return next_char;
}

// Helper functions
int dlh_name_identifier(struct donsus_lexer *lexer, char entry_point, don_array * save, size_t length){
    /*
     * Within the ASCII range (U+0001.U+007F), the valid characters for
     * identifiers are the uppercase and lowercase letters A through Z,
     * the underscore _ and, except for the first character, the digits 0 through 9.
     *
     * Checks identifier, once it reaches the end return what it collected.
     */
    // 0 -> if succeed
    // 1 -> if failed

    // peek here

    // Todo: Recursion

    if (isdigit(entry_point)){

        if (length == 0){
            return 1; // can't start with a digit
        }

        don_array_append(save, &entry_point);
        length++;

        // Start recursion, looking for more characters
        if (dlh_name_identifier(lexer, peek(lexer), save, length) == 1){
            return 0;
        }

        return 0;
    }
    if (isalpha(entry_point)){
        don_array_append(save, &entry_point);
        length++;

        // Start recursion, looking for more characters
        if (dlh_name_identifier(lexer, peek(lexer), save, length) == 1){
            return 0;
        }

        return 0;
    }

    if (entry_point == '_'){
        don_array_append(save, &entry_point);
        length++;

        // Start recursion, looking for more characters
        if (dlh_name_identifier(lexer, peek(lexer), save, length) == 1){
            return 0;
        }

        return 0;
    }

    return 1;
}

// Todo: rewrite with less arguments and prefer lexer
donsus_token_location* construct_token_location(struct donsus_lexer *lexer, donsus_token_location* token_location, long long length,
        size_t offset, int source_id)
{
    token_location->length = length;
    token_location->offset = offset;
    token_location->source_id = source_id;

    return token_location;
}

void construct_name_token(struct donsus_lexer *lexer, don_array *identifier, size_t* length, donsus_token_location *_token_location, donsus_token *_token){
    // Construct tokens from identifiers list
    _token->kind = DONSUS_NAME;

    _token_location->source_id = lexer->source_id;
    _token_location->offset = lexer->position;
    _token_location->length = *length;

    _token->location = _token_location;

    // [h,e,l,l,o,w,o,r,l,d] -> data type here
    char **_value = malloc(sizeof(char)*identifier->size);

    for(size_t i = 0; i< identifier->size; i++) {
        _value[i] = don_array_get(identifier, i);
        don_array_remove_by_id(identifier, i);
    };
    // Todo: free identifier and just add the token into global "tokens" without creating a list
    _token->value.data = *_value;
    _token->value.length = *length; // same as the location's offset for now

    don_array_append(identifier, _token);
}

int create_tokens(struct donsus_lexer *lexer, struct don_array *tokens){
    // identify the token
    char cur = lexer->cur;

    struct donsus_token out_token;

    donsus_token_kind token_kind;
    donsus_token_location token_location;

    switch(cur){
        case '+': {
            /*
             * Obtaining tokens:
             *  +
             *  +=
             */
            if (peek(lexer) == '=') {
                // add token(+=)
                token_kind = DONSUS_PLUS_EQUAL;
                out_token.kind = token_kind;

                // token location
                out_token.location = construct_token_location(lexer, &token_location, 2,
                                                              lexer->position,
                                                              lexer->source_id);

                don_array_append(tokens, &out_token); // push it to the dynamic array

                break;
            }

            // add token(+)
            token_kind = DONSUS_PLUS;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }

        case '-': {
            /*
             * Obtaining tokens:
             *  -
             *  -=
             */
            if (peek(lexer) == '=') {
                // add token(-=)
                token_kind = DONSUS_MINUS_EQUAL;
                out_token.kind = token_kind;

                // token location
                out_token.location = construct_token_location(lexer, &token_location, 2,
                                                              lexer->position,
                                                              lexer->source_id);

                don_array_append(tokens, &out_token); // push it to the dynamic array

                break;
            }

            // add token(-)
            token_kind = DONSUS_MINUS;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }

        case '=': {
            /*
             * Obtaining tokens:
             *  =
             *  ==
             */
            if (peek(lexer) == '=') {
                // add token(==)
                token_kind = DONSUS_DOUBLE_EQUAL;
                out_token.kind = token_kind;

                // token location
                out_token.location = construct_token_location(lexer, &token_location, 2,
                                                              lexer->position,
                                                              lexer->source_id);

                don_array_append(tokens, &out_token); // push it to the dynamic array

                break;
            }

            // add token(=)
            token_kind = DONSUS_EQUAL;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }

        case '*': {
            /*
             * Obtaining tokens:
             *  *
             *  *=
             */
            if (peek(lexer) == '=') {
                // add token(*=)
                token_kind = DONSUS_STAR_EQUAL;
                out_token.kind = token_kind;

                // token location
                out_token.location = construct_token_location(lexer, &token_location, 2,
                                                              lexer->position,
                                                              lexer->source_id);

                don_array_append(tokens, &out_token); // push it to the dynamic array

                break;
            }

            // add token(*)
            token_kind = DONSUS_STAR;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }

        case '/': {
            /*
            * Obtaining tokens:
            *  /
            *  /=
            *
            */

            if (peek(lexer) == '=') {
                // add token(/=)
                token_kind = DONSUS_DOUBLE_SLASH;
                out_token.kind = token_kind;

                // token location
                out_token.location = construct_token_location(lexer, &token_location, 2,
                                                              lexer->position,
                                                              lexer->source_id);

                don_array_append(tokens, &out_token); // push it to the dynamic array

                break;
            }

            // add token(/)
            token_kind = DONSUS_SLASH;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;

        }
        case '(': {
            /*
            * Obtaining token:
            *  (
            */

            // add token(()
            token_kind = DONSUS_LPAR;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }
        case ')': {
            /*
            * Obtaining token:
            *  )
            */

            // add token())
            token_kind = DONSUS_RPAR;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }

        case '>': {
            /*
            * Obtaining tokens:
            *  >
            *  >=
            *
            */

            if (peek(lexer) == '=') {
                // add token(>=)
                token_kind = DONSUS_GREATER_EQUAL;
                out_token.kind = token_kind;

                // token location
                out_token.location = construct_token_location(lexer, &token_location, 2,
                                                              lexer->position,
                                                              lexer->source_id);

                don_array_append(tokens, &out_token); // push it to the dynamic array

                break;
            }

            // add token(>)
            token_kind = DONSUS_GREATER;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }

        case '<': {
            /*
            * Obtaining tokens:
            *  <
            *  <=
            *
            */

            if (peek(lexer) == '=') {
                // add token(<=)
                token_kind = DONSUS_LESS_EQUAL;
                out_token.kind = token_kind;

                // token location
                out_token.location = construct_token_location(lexer, &token_location, 2,
                                                              lexer->position,
                                                              lexer->source_id);

                don_array_append(tokens, &out_token); // push it to the dynamic array

                break;
            }

            // add token(<)
            token_kind = DONSUS_LESS;
            out_token.kind = token_kind;

            // token location
            out_token.location = construct_token_location(lexer, &token_location, 1,
                                                          lexer->position,
                                                          lexer->source_id);

            don_array_append(tokens, &out_token); // push it to the dynamic array
            break;
        }


        case '\n':
            break;

        default: {
            // when it's not a special character it's an identifier
            // create temp array
            don_array _identifiers;
            don_array_init(&_identifiers, DON_ARRAY_INITIAL_CAPACITY);


            size_t _length = 0; // length to make sure

            // step - 1 -> fill in identifier
            if (dlh_name_identifier(lexer, cur, &_identifiers, _length) == 1) {
                return 1;
            }

            donsus_token_location _location; // for token creating
            donsus_token _token; // we only need this

            // construct tokens from identifier
            construct_name_token(lexer, &_identifiers, &_length, &_location, &_token);

            // merge them together
            don_array_merge(tokens, &_identifiers); // add name token back

            // Printing out tokens
            #ifdef DEBUG
            _de_print_out_tokens(tokens);
            #endif

            return 0;
        }

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


struct donsus_file *new_lexer(struct donsus_file *file_struct) {
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

