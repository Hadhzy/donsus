#ifndef _LIFE_CYCLE_H_
#define _LIFE_CYCLE_H_

#include "internal/ducore_init.h"

int du_run_command(DU_CONFIG* config, DU_ARGV* args);
int du_run_donsus(int *exitcode, DU_ARGV *args);
int du_main_run(DU_ARGV *args);
int Du_Main(int argc, char **argv);
#endif
