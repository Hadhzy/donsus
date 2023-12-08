#ifndef DU_DON_ARRAY_H
#define DU_DON_ARRAY_H
#include <stdlib.h>
#include "../Include/token.h"

#define DON_ARRAY_INITIAL_CAPACITY 100

typedef struct don_array{
    void **array;
    size_t size;
    size_t capacity;

} don_array;
//Todo: Add .pop in the future replace it in lexer
void don_array_init(don_array *a, size_t initial_capacity);
void don_array_append(don_array *a, void* element);
void don_array_merge(don_array *first, don_array *second);
void *don_array_get(don_array *a, size_t index);
void don_array_remove_by_id(don_array *a, size_t index);
void don_array_remove_by_item(don_array *a, struct donsus_token* item);
char * don_array_add_elements_as_char(don_array *a);

#endif // DU_DON_ARRAY_H



