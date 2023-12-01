#ifndef _DUCORE_INIT_H_
#define _DUCORE_INIT_H_

typedef struct _DU_ARGV
{
    // Represents the arguments passed to the program
    int argc; // argument count
    char **argv; // argument don_array
} _DU_ARGV;


typedef struct _DU_CONFIGS
{
    /* -------------- */
    int run_command;
    int run_module;
    int run_filename;

} _DU_CONFIG;

#endif