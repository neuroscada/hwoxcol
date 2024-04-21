#include "csv.h"
#include <stdio.h>
#include "hwapicall.h"
#include <src/defs.h>
#include <src/points.h>
#include "remote_reciever.h"


#define MAX_REQUEST_POINTPARAMNAMES 5000
#define MAX_REQUEST_POINTPARAMNUMS 5000

int generate_pointnums_paramnums_csv(char filepath[], char host[]){
    REQUEST_POINTPARAMNAMES rp[MAX_REQUEST_POINTPARAMNAMES];
	POINTPARAMNUM ppn[MAX_REQUEST_POINTPARAMNUMS];
	int writed;
    int readed = reader_pointnames_paramnames(filepath,rp);
    printf("readed from pointnames/paramnames CSV file %d values\n", readed);
	if (readed!=-1)
	{
		writed = new_detect_pointnums(rp,ppn,readed, host);
		if(writed!=-1)
		{
			printf("output file successfuly generated\n");
		}else{
			printf("can't generate file \n");
			return 0;
		}
	}
    return 0;
}


int generate_pv_from_template(char filepath[], char host[]){
	POINTPARAMNUM ppn[MAX_REQUEST_POINTPARAMNUMS];
	int stat;
	stat = reader_pointparamnums(filepath,ppn);
	if(stat== -1){
		printf("some errors during point reading occured");
	}
	stat = gen_values_file(ppn,stat,host);
	if (stat ==-1){
		printf("error while requesting point value by nums");
	}
	printf("successfully parsed %d values", stat);

	return 0;
}

//number of ms
int generate_pv_from_template_cycle(char filepath[], char host[], int interval){
	POINTPARAMNUM ppn[MAX_REQUEST_POINTPARAMNUMS];
	int status;
	int readed;
	readed = reader_pointparamnums(filepath,ppn);
	if(readed== -1){
		printf("some errors during point reading occured");
		return -1;
	}
	printf("pointparamnums readed");
	while(TRUE)
		{
			status = gen_values_file_2(ppn,readed,host);
			printf("gen_values_file_2 error");
			if (status ==-1){
				printf("error while requesting point value by nums");
				return -1;
				
			}
			printf("collected\n");
			Sleep(interval);
		}

	
	printf("successfully parsed %d values", readed);

	return 0;
}

int request_one_prm_routine(int point_num, char prm_name[], char hostname[]){
	int status;
	status = request_one_prm(point_num,prm_name, hostname);
	if(status!=0){
		printf("error while requesting in one_prm_routine\n");
		return -1;
	}
	return 0;
}

int request_one_value_routine(int point_num,int param_num, char hostname[]){
		int status;
	status = request_one_value(param_num,point_num, hostname);
	if(status!=0){
		printf("error while requesting in one_prm_routine \n");
		return -1;
	}
	return 0;
}

int test_routine(){
	int status;
	char filename[] = "2024-04-14_15-31-12.csv";
	printf("test");
	status = send_to_remote_reciever(filename);
	if (status!=0){
		printf("some error in test_routine occured");
		return -1;
	}
	return 0;
}

