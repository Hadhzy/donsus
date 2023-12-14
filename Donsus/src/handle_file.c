// handle file
#include <stdio.h>
#include <stdlib.h>
#include "../Include/internal/ducore_init.h" // _DU_ARGV
#include "../Include/internal/ducore_file.h" // handle_file

size_t get_file_size(FILE *file){
    // TODO: Add null check
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return size;
}


struct donsus_file* handle_file(DU_ARGV * args, struct donsus_file* file_struct) {
    char *path = args->argv[1]; // get the path
    FILE *file = fopen(path, "r");

    if (file == NULL){
        printf("Error: File not found at this path: %s\n", path);
        exit(1);
    }

    size_t size = get_file_size(file);
    char* result = malloc(size + 1);

    int _counter = 0;
    int c = fgetc(file);

    if(c == EOF){
        exit(1);
    }

    result[_counter] = c;

    while (c != EOF){
        c = fgetc(file);
        _counter++;
        result[_counter] = c;
    }


    fclose(file);
    file_struct->file_content = result;
    file_struct->size = size;

    return file_struct;

}
