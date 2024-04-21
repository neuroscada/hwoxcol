


int gen_values_file_2(POINTPARAMNUM ppn[], unsigned int num_points, char host[]);
int detect_pointnums(REQUEST_POINTPARAMNAMES rp[], POINTPARAMNUM ppn[], int number_of_points, char host[]);
int new_detect_pointnums(REQUEST_POINTPARAMNAMES rp[], POINTPARAMNUM ppn[], int number_of_points, char host[]);
int new_detect_pointnums_v3(REQUEST_POINTPARAMNAMES rp[], POINTPARAMNUM ppn[], int number_of_points, char host[]);
int gen_values_file(POINTPARAMNUM ppn[], unsigned int num_points, char host[]);
int request_one_value(int param_num, int point_num, char hostname[]);
int request_one_prm(int point_num, char prm_name[], char hostname[]);
char* current_datetime();