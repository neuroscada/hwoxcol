#include <src/defs.h>
int generate_pointnums_paramnums_csv(char filepath[], char host[]);
int generate_pv_from_template(char filepath[], char host[]);
int request_one_value_routine(int param_num, int point_num, char hostname[]);
int request_one_prm_routine(int point_num, char prm_name[], char hostname[]);
int generate_pv_from_template_cycle(char filepath[], char host[], int interval);
int test_routine();