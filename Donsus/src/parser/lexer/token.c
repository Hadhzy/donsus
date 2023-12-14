#include "token.h"
#include "stdlib.h"

struct donsus_token* token_init(donsus_token_kind kind, unsigned length, unsigned line, char* value, struct donsus_token * token) {
    /*
    Initialise a new token with all the properties.
     * */
    token->kind = kind;
    token->length = length;
    token->line = line;
    token->value = value;
    return token;
}

struct donsus_token donsus_token_identifier(donsus_token_kind type,unsigned length, unsigned line){
    /*
     * Initialise a new token without the value property.
     * */
    struct donsus_token token;
    token.kind = type;
    token.length = length;
    token.line = line;
    return token;
}

