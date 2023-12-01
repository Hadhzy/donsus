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

void don_array_init(don_array *a, size_t initial_capacity);
void don_array_append(don_array *a, void* element);
void *don_array_get(don_array *a, size_t index);
void don_array_remove_by_id(don_array *a, size_t index);
void don_array_remove_by_item(don_array *a, struct donsus_token* item);


#endif // DU_DON_ARRAY



