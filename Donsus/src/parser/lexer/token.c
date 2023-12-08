#include "token.h"


struct donsus_token token_init(donsus_token_kind type, const char *position, unsigned size, unsigned line, char* value) {
    struct donsus_token token;
    token.kind = type;
    token.position = position;
    token.size = size;
    token.line = line;
    token.value = value;
    return token;
}

struct donsus_token donsus_token_identifier(donsus_token_kind type, const char*position, unsigned size, unsigned line){
    struct donsus_token token;
    token.kind = type;
    token.position = position;
    token.size = size;
    token.line = line;
    return token;
}

