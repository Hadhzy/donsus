#include "../Include/internal/ducore_init.h" // _DU_ARGB
#include "../Include/internal/ducore_file.h" // handle_file
#include "../Include/lexer.h" // new_lexer

int du_run_command(_DU_CONFIG* config, _DU_ARGV* args){
    // 4. layer

    // handle inpout file
    struct donsus_file file_struct;

    struct donsus_file* result = handle_file(args, &file_struct);

    new_lexer(result);

    return 0;
}

int
du_run_donsus(int *exitcode, _DU_ARGV *args) {
    // 3.layer

    /*
        1.
        2.
        3.
    */

    // TBD
    _DU_CONFIG config;
    config.run_command = 1;
    config.run_module = 0;
    config.run_filename = 0;

    if (config.run_command){
        du_run_command(&config, args);
    }

    return 0;
}

int
du_main_run(_DU_ARGV *args){
    // 2. layer
    int exitcode = 0;
    du_run_donsus(&exitcode, args);

    return exitcode;
}

int
Du_Main(int argc, char **argv){
    // 1. layer
    _DU_ARGV args = {
            .argc = argc,
            .argv = argv
    };

    return du_main_run(&args);
}
