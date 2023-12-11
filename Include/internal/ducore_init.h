#ifndef _DUCORE_INIT_H_
#define _DUCORE_INIT_H_

typedef struct DU_ARGV
{
    // Represents the arguments passed to the program
    int argc; // argument count
    char **argv; // argument don_array
} DU_ARGV;


typedef struct DU_CONFIG
{
    /* -------------- */
    int run_command;
    int run_module;
    int run_filename;

} DU_CONFIG;

#endif