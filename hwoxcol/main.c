
#include <stdio.h>
#include "csv.h"
#include <Windows.h>
#include "routines.h"
#include "hwapicall.h"
#include "reciever_global_variables.h"

#define MAX_HOST 100



char host[50];
char reciever_host_endpoint[250];

int main(int argc, char *argv[]) {
	int i;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // Option found
            if (strcmp(argv[i], "-g") == 0) {
                if(i+1<argc && argv[i+1][0] != '-'){
                    int status = generate_pointnums_paramnums_csv(argv[i+1], host);
                    if (status!=0)
                    {
                        printf("Error while generating point_number_param_number.csv from point_names\n");
                    };
                    i++;
                }
            } else if (strcmp(argv[i], "-t") == 0) {
				if(i+1<argc && argv[i+1][0] != '-'){
					int status;
					printf("option t recs");
					status = generate_pv_from_template(argv[i+1],host);
                    if (status!=0)
                    {
                        printf("Error while generating point_number_param_number.csv from point_names\n");
                    };
					i++;
                }
            }else if (strcmp(argv[i], "-rhep") == 0) {
				if(i+1<argc && argv[i+1][0] != '-'){
					strcpy(reciever_host_endpoint, argv[i+1]);
					printf("you specified remote reciever endpoint: %s\n", reciever_host_endpoint);
					i++;
                }
            }else if (strcmp(argv[i], "-h") == 0) {
				if(i+1<argc && argv[i+1][0] != '-'){
					strcpy(host,argv[i+1]);
					printf("You specified host: %s\n", host);
					i++;
                }
            }else if (strcmp(argv[i], "-rpan") == 0) {
			if (i + 2 < argc && argv[i+1][0] != '-' && argv[i+2][0] != '-') {
				int status = request_one_prm_routine(atoi(argv[i+1]), argv[i+2], host);
				if (status != 0) {
				printf("Error while requesting one parameter.\n");
					}
				i += 2;
				}
			}else if (strcmp(argv[i], "-test") == 0) {
				int status;
				if(i+1<argc && argv[i+1][0] != '-'){
				strcpy(reciever_host_endpoint, argv[i+1]);
				printf("you specified remote reciever endpoint: %s\n", reciever_host_endpoint);
				status = test_routine();
				printf("test routine\n");
				if (status != 0) {
				printf("error while requesting\n");
					}
				i += 2;
				}
			}else if (strcmp(argv[i], "-start") == 0) {
			if (i + 2 < argc && argv[i+1][0] != '-' && argv[i+2][0] != '-') {
				int status;
				printf("start collection\n");
				status = generate_pv_from_template_cycle(argv[i+1],host,atoi(argv[i+2]));
				if (status != 0) {
				printf("Error while requesting cycle.\n");
				return -1;
				}
				i += 2;
				}
			}else if (strcmp(argv[i], "-rval") == 0) {
				if (i + 2 < argc && argv[i+1][0] != '-' && argv[i+2][0] != '-') {
					int status = request_one_value_routine(atoi(argv[i+1]), atoi(argv[i+2]), host);
					if (status != 0) {
					printf("Error while requesting one parameter.\n");
						}
					i += 2;
				}
				}else if (strcmp(argv[i], "-c") == 0) {
                if (i + 1 < argc && argv[i+1][0] != '-') {
                    printf("Option -c specified with value %s\n", argv[i+1]);
                    i++; 
                } else {
                    printf("Option -c requires an argument\n");
                }
            } else if (strcmp(argv[i], "-?") == 0) {
                printf(
                        "HELP:\n\
                        \n-g for generate point_number_param_number.csv from point_names. Example: hwoxcol -g './pointnames.csv'\n\
                        \n-t for specify point_number_param_number.csv file config and start collecting in current dir. Example: hwoxcol './point_number_param_number.csv' \n\
                        \n-n for get one point value by names. Example: hwoxcol -o 'point_name' 'param_name'\n\
                        \n-b for get one point number by name. Example: hwoxcol -b 'point_name'\n\
                        \n-c for get one param number by name. Example: hwoxcol -c 'point_number' 'param_name'\n\
                        \n-k for get one param value by number. Example: hwoxcol -k 'point_number' 'param_number'\n\
                        \
                        "
                        );
            }
            else {
                printf("Unknown option: %s\n", argv[i]);
            }
        } else {
            // Argument without '-' prefix
            printf("Argument: %s\n", argv[i]);
        }
    }

    return 0;
}