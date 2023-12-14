/* Minimal main program --everything is loaded from the library*/

#include <stdio.h>

#include "../Include/Donsus.h"

#define VERSION_STRING "v0.0.1"

const char* usage_text = "TBD";

void print_usage(){
    printf("%s\n", usage_text);
}

int main (int argc, char **argv){
    if (argc <= 1) print_usage();

    printf("Donsus compiler %s\n", VERSION_STRING);
    return Du_Main(argc, argv); // start layer 1 main

};
