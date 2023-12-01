#ifndef _LIFE_CYCLE_H_
#define _LIFE_CYCLE_H_

#include "internal/ducore_init.h"

int du_run_command(_DU_CONFIG* config, _DU_ARGV* args);
int du_run_donsus(int *exitcode, _DU_ARGV *args);
int du_main_run(_DU_ARGV *args);
int Du_Main(int argc, char **argv);
#endif
