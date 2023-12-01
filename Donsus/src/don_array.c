#include "../Include/don_array.h" // don_array / token.h
#include "stdio.h"
#include "stdbool.h"

// dynamic array implementation for the donsus programming language

void don_array_init(don_array *a, size_t initial_capacity) {
    a->array = malloc(DON_ARRAY_INITIAL_CAPACITY * sizeof(void*));
    a->size = 0;
    a->capacity = initial_capacity;
}

void** don_resize_array(void* array_elements, size_t capacity){

    void**new_array = malloc(sizeof(void*) * capacity);

    return new_array;
}

void don_array_append(don_array *a, void* element) {

    if (a->size == a->capacity){
        // resize

        a->capacity *= 2;
        a->array = don_resize_array(a->array, a->capacity);

    }

    a->array[a->size] = element;

    a->size++;

}

void don_array_remove_by_id(don_array *a, size_t index){
    if(index >= a-> size) {
        //error message
        printf("Index out of bounds");
    };

    for(size_t i = index; i< a->size - 1; i++) {
        a->array[i] = a->array[i+1];
    };

    a->size--;

}


bool compare_tokens(struct donsus_token* token1, struct donsus_token* token2){
    if(token1->kind == token2->kind){
        return true;
    }

    return false;
}

void don_array_remove_by_item(don_array *a, struct donsus_token* item){
    for(size_t i = 0; i<a->size; i++) {
        bool value = compare_tokens(item, a->array[i]);

        if (value){
            don_array_remove_by_id( a, i);
        }

    }

}

void* don_array_get(don_array *a, size_t index){
    return a->array[index];
}
