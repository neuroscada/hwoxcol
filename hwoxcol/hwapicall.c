#include "wox_types.h"
#include <hscnapi.h>
#include <time.h>
#include <string.h>
#include "hwapicall.h"
#include "reciever_global_variables.h"
#include "remote_reciever.h"


#define REQ_BLOCK_SIZE 50

int detect_pointnums(REQUEST_POINTPARAMNAMES rp[], POINTPARAMNUM ppn[], int number_of_points, char host[]) {
    char hostname[] = "localhost";
    char buf[1024];
    int status = 0;
    int total_points_processed = 0;
    POINT_NUMBER_DATA_2 pnd2[REQ_BLOCK_SIZE];
    PARAM_NUMBER_DATA_2 parnd2[REQ_BLOCK_SIZE];
    FILE* pointparamnums = fopen("pointparamnums.csv", "w"); 
    int i;

    if (pointparamnums == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    while (total_points_processed < number_of_points) {
        int points_per_request = (number_of_points - total_points_processed < REQ_BLOCK_SIZE) ? (number_of_points - total_points_processed) : REQ_BLOCK_SIZE;

        for (i = 0; i < points_per_request; i++) {
            pnd2[i].szPntName = rp[total_points_processed + i].pointname; 
        }

        status = rhsc_point_numbers_2(host, points_per_request, pnd2);
        if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
            hsc_napierrstr(status, buf);
			printf("%s, %d \n",buf, status);
            return -1;
        }

        for (i = 0; i < points_per_request; i++) {
            ppn[total_points_processed + i].pointnum = pnd2[i].nPnt;
        }

        // Заполнение массива parnd2
        for (i = 0; i < points_per_request; i++) {
            parnd2[i].szPrmName = rp[total_points_processed + i].paramname; 
            parnd2[i].nPnt = pnd2[i].nPnt;
        }

		status = rhsc_param_numbers_2(host, points_per_request, parnd2);
		if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
			hsc_napierrstr(status, buf);
			printf("%s, %d \n",buf, status);
			return -1;
		}

		for (i = 0; i < points_per_request; i++) {
			if (parnd2[i].nPnt != pnd2[i].nPnt) {
				return -1;
			}
			ppn[total_points_processed + i].paramnum = parnd2[i].nPrm;
		}


        for (i = 0; i < points_per_request; i++) {
            fprintf(pointparamnums, "%s;%u;%u\n",rp[total_points_processed + i].pointname, ppn[total_points_processed + i].pointnum, ppn[total_points_processed + i].paramnum); 
        }

        total_points_processed += points_per_request;
    }

    fclose(pointparamnums);
    return total_points_processed; 
}


int new_detect_pointnums(REQUEST_POINTPARAMNAMES rp[], POINTPARAMNUM ppn[], int number_of_points, char host[]) {
    char hostname[] = "localhost";
    char buf[1024];
    int status = 0;
    int total_points_processed = 0;
    POINT_NUMBER_DATA_2 pnd2[REQ_BLOCK_SIZE];
    PARAM_NUMBER_DATA_2 parnd2[REQ_BLOCK_SIZE];
    FILE* pointparamnums = fopen("pointparamnums.csv", "w"); 
    int i;

    if (pointparamnums == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    while (total_points_processed < number_of_points) {
        int points_per_request = (number_of_points - total_points_processed < REQ_BLOCK_SIZE) ? (number_of_points - total_points_processed) : REQ_BLOCK_SIZE;

        // Заполнение массива pnd2
        for (i = 0; i < points_per_request; i++) {
            pnd2[i].szPntName = rp[total_points_processed + i].pointname; 
        }

        status = rhsc_point_numbers_2(host, points_per_request, pnd2);
        if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
            hsc_napierrstr(status, buf);
            printf("%s, %d \n",buf, status);
            return -1;
        }

        // Заполнение массива parnd2
        for (i = 0; i < points_per_request; i++) {
			printf("DEBUG1:%s", rp[total_points_processed+i].paramname);
            parnd2[i].szPrmName = rp[total_points_processed + i].paramname; 
			printf("prmName_after_achieving: %s", parnd2[i].szPrmName);
            parnd2[i].nPnt = pnd2[i].nPnt;
        }

        status = rhsc_param_numbers_2(host, points_per_request, parnd2);
        if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
            hsc_napierrstr(status, buf);
            printf("%s, %d \n",buf, status);
            return -1;
        }

        for (i = 0; i < points_per_request; i++) {
            if (parnd2[i].nPnt != pnd2[i].nPnt) {
                return -1;
            }
			//DEBUG
			printf("DEBUG 1: npnt: %d, nparam: %d\n, nparamText: %s", pnd2[i].nPnt, parnd2[i].nPrm, parnd2[i].szPrmName);
            ppn[total_points_processed + i].pointnum = pnd2[i].nPnt;
            ppn[total_points_processed + i].paramnum = parnd2[i].nPrm;
        }

        for (i = 0; i < points_per_request; i++) {
            fprintf(pointparamnums, "%s;%u;%u\n", rp[total_points_processed + i].pointname, ppn[total_points_processed + i].pointnum, ppn[total_points_processed + i].paramnum); 
        }

        total_points_processed += points_per_request;
    }

    fclose(pointparamnums);
    return total_points_processed; 
}

int new_detect_pointnums_v3(REQUEST_POINTPARAMNAMES rp[], POINTPARAMNUM ppn[], int number_of_points, char host[]) {
    char buf[1024];
    int status = 0;
    int total_points_processed = 0;
	char* hex_rep;
	size_t len;
    POINT_NUMBER_DATA_2 pnd2[REQ_BLOCK_SIZE];
    PARAM_NUMBER_DATA_2 parnd2[REQ_BLOCK_SIZE];
    FILE* pointparamnums = fopen("pointparamnums.csv", "w"); 
    int i;

    if (pointparamnums == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    while (total_points_processed < number_of_points) {
        int points_per_request = (number_of_points - total_points_processed < REQ_BLOCK_SIZE) ? (number_of_points - total_points_processed) : REQ_BLOCK_SIZE;

        // Заполнение массива pnd2
        for (i = 0; i < points_per_request; i++) {
            pnd2[i].szPntName = rp[total_points_processed + i].pointname; 
        }

        status = rhsc_point_numbers_2(host, points_per_request, pnd2);
        if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
            hsc_napierrstr(status, buf);
            printf("%s, %d \n", buf, status);
            return -1;
        }

        // Заполнение массива parnd2
        for (i = 0; i < points_per_request; i++) {
            // Выделение памяти для копии строки paramname
            parnd2[i].szPrmName = malloc(strlen(rp[total_points_processed + i].paramname) + 1);
            strcpy(parnd2[i].szPrmName, rp[total_points_processed + i].paramname); 
            parnd2[i].nPnt = pnd2[i].nPnt;
        }


        status = rhsc_param_numbers_2(host, points_per_request, parnd2);
        if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
            hsc_napierrstr(status, buf);
            printf("%s, %d \n", buf, status);
            return -1;
        }

        for (i = 0; i < points_per_request; i++) {
            if (parnd2[i].nPnt != pnd2[i].nPnt) {
                return -1;
            }
            //DEBUG
            printf("DEBUG 1: npnt: %d, nparam: %d\n, nparamText: %s", pnd2[i].nPnt, parnd2[i].nPrm, parnd2[i].szPrmName);
            ppn[total_points_processed + i].pointnum = pnd2[i].nPnt;
            ppn[total_points_processed + i].paramnum = parnd2[i].nPrm;
        }

        for (i = 0; i < points_per_request; i++) {
            fprintf(pointparamnums, "%s;%u;%u\n", rp[total_points_processed + i].pointname, ppn[total_points_processed + i].pointnum, ppn[total_points_processed + i].paramnum); 
            // Освобождение памяти, выделенной под копии строк paramname
            free(parnd2[i].szPrmName);
        }

        total_points_processed += points_per_request;
    }

    fclose(pointparamnums);
    return total_points_processed; 
}


char* current_datetime() {
    // Получаем текущее время
    time_t rawtime;
    struct tm *timeinfo;
    char *buffer = (char*)malloc(80 * sizeof(char)); // выделение памяти для строки

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Форматируем дату и время
    strftime(buffer, 80, "%Y-%m-%d_%H-%M-%S", timeinfo);
    return buffer;
}


#define MAX_REQUESTS_PER_BATCH 60 // Максимальное количество запросов в одной партии

int gen_values_file(POINTPARAMNUM ppn[], unsigned int num_points, char host[]) {
	char filename[100];
    char *datetime = current_datetime();
	char hostname[] = "localhost";
    int status;
	FILE *fp;
    int i, j, k;
    PARAM_VALUE_DATA_2 *pvd2 = (PARAM_VALUE_DATA_2 *)malloc(num_points * sizeof(PARAM_VALUE_DATA_2));
    sprintf(filename, "%s.csv", datetime);
	fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        return -1;
    }

    if (pvd2 == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return -1;
    }

    for (i = 0; i < num_points; i += MAX_REQUESTS_PER_BATCH) {
        int batch_size = (num_points - i) < MAX_REQUESTS_PER_BATCH ? (num_points - i) : MAX_REQUESTS_PER_BATCH;
        
        for (j = 0; j < batch_size; j++) {
            pvd2[j].pupvValue = (PARvalue *)malloc(sizeof(PARvalue));
            if (pvd2[j].pupvValue == NULL) {
                printf("Memory allocation failed for pupvValue\n");
                // Clean up previously allocated memory
                for (k = 0; k < j; k++) {
                    free(pvd2[k].pupvValue);
                }
                free(pvd2);
                fclose(fp);
                return -1;
            }
            pvd2[j].nPnt = ppn[i + j].pointnum;
            pvd2[j].nPrm = ppn[i + j].paramnum;
            pvd2[j].nPrmOffset = 0;
        }

        status = rhsc_param_values_2(host, NADS_ONE_SHOT, batch_size, pvd2);

        if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
            char buf[1024];
            hsc_napierrstr(status, buf);
            printf("SUPER_ERROR: %s\n", buf);

            for (j = 0; j < batch_size; j++) {
                free(pvd2[j].pupvValue);
            }

            free(pvd2);
            fclose(fp);
            return -1;
        }

        for (j = 0; j < batch_size; j++) {
            if (pvd2[j].pupvValue != NULL) {
                // Process obtained values
				//Тут баг, если вдруг он находит какой-то один параметр, то остальное он отбросит.
                switch (pvd2[j].nType) {
                    case DT_ENUM:
						fprintf(fp, "%lu;%hu;%ld*%s\n", ppn[i + j].pointnum, ppn[i + j].paramnum,pvd2[j].pupvValue->en.ord, pvd2[j].pupvValue->en.text);
                        //fprintf(fp, "%lu;%hu;%ld\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->en.ord);
                        break;
                    case DT_CHAR:
                        //last_version
						//fprintf(fp, "%lu;%hu;%s\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->text);
                        //new
						fprintf(fp, "%lu;%hu;%s\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->en.text);
						break;
                    case DT_INT2:
                        fprintf(fp, "%lu;%hu;%hi\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->int2);
                        break;
                    case DT_INT4:
                        fprintf(fp, "%lu;%hu;%li\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->int4);
                        break;
                    case DT_REAL:
                        fprintf(fp, "%lu;%hu;%f\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->real);
                        break;
                    case DT_DBLE:
                        fprintf(fp, "%lu;%hu;%lf\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->dble);
                        break;
                    default:
                        break;
                }
                free(pvd2[j].pupvValue);
            } else {
                // If value is NULL, write -1 to the file
                fprintf(fp, "%lu;%hu;-1\n", ppn[i + j].pointnum, ppn[i + j].paramnum);
            }
        }
    }

    free(pvd2);
    fclose(fp);


    printf("Values written to %s\n", filename);

    return 0;
}


int gen_values_file_2(POINTPARAMNUM ppn[], unsigned int num_points, char host[]) {
	char filename[100];
    char *datetime = current_datetime();
	char hostname[] = "localhost";
    int status;
	FILE *fp;
    int i, j, k;
    PARAM_VALUE_DATA_2 *pvd2 = (PARAM_VALUE_DATA_2 *)malloc(num_points * sizeof(PARAM_VALUE_DATA_2));
    sprintf(filename, "%s.csv", datetime);
	fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file %s\n", filename);
        return -1;
    }

    if (pvd2 == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return -1;
    }

    for (i = 0; i < num_points; i += MAX_REQUESTS_PER_BATCH) {
        int batch_size = (num_points - i) < MAX_REQUESTS_PER_BATCH ? (num_points - i) : MAX_REQUESTS_PER_BATCH;
        
        for (j = 0; j < batch_size; j++) {
            pvd2[j].pupvValue = (PARvalue *)malloc(sizeof(PARvalue));
            if (pvd2[j].pupvValue == NULL) {
                printf("Memory allocation failed for pupvValue\n");
                // Clean up previously allocated memory
                for (k = 0; k < j; k++) {
                    free(pvd2[k].pupvValue);
                }
                free(pvd2);
                fclose(fp);
                return -1;
            }
            pvd2[j].nPnt = ppn[i + j].pointnum;
            pvd2[j].nPrm = ppn[i + j].paramnum;
            pvd2[j].nPrmOffset = 0;
        }

        status = rhsc_param_values_2(host, NADS_ONE_SHOT, batch_size, pvd2);

        if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
            char buf[1024];
            hsc_napierrstr(status, buf);
            printf("SUPER_ERROR: %s\n", buf);

            for (j = 0; j < batch_size; j++) {
                free(pvd2[j].pupvValue);
            }

            free(pvd2);
            fclose(fp);
            return -1;
        }

        for (j = 0; j < batch_size; j++) {
            if (pvd2[j].pupvValue != NULL) {
                // Process obtained values
				//Тут баг, если вдруг он находит какой-то один параметр, то остальное он отбросит.
                switch (pvd2[j].nType) {
                    case DT_ENUM:
						fprintf(fp, "%lu;%hu;%ld*%s\n", ppn[i + j].pointnum, ppn[i + j].paramnum,pvd2[j].pupvValue->en.ord, pvd2[j].pupvValue->en.text);
                        //fprintf(fp, "%lu;%hu;%ld\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->en.ord);
                        break;
                    case DT_CHAR:
                        //last_version
						//fprintf(fp, "%lu;%hu;%s\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->text);
                        //new
						fprintf(fp, "%lu;%hu;%s\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->en.text);
						break;
                    case DT_INT2:
                        fprintf(fp, "%lu;%hu;%hi\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->int2);
                        break;
                    case DT_INT4:
                        fprintf(fp, "%lu;%hu;%li\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->int4);
                        break;
                    case DT_REAL:
                        fprintf(fp, "%lu;%hu;%f\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->real);
                        break;
                    case DT_DBLE:
                        fprintf(fp, "%lu;%hu;%lf\n", ppn[i + j].pointnum, ppn[i + j].paramnum, pvd2[j].pupvValue->dble);
                        break;
                    default:
                        break;
                }
                free(pvd2[j].pupvValue);
            } else {
                // If value is NULL, write -1 to the file
                fprintf(fp, "%lu;%hu;-1\n", ppn[i + j].pointnum, ppn[i + j].paramnum);
            }
        }
    }

    free(pvd2);
    fclose(fp);
	printf("Values written to %s\n", filename);

	status = send_to_remote_reciever(filename);
	if(status==0){
		printf("file has been successfully sended to remote reciever, deleting current file %s", filename);
		if (remove(filename) == 0) {
			printf("File %s has been successfully sent.\n", filename);
			return 0;
		 } else {
			printf("error while delete file %s \n", filename);
			return -1;
		}
	}


    return 0;
}



int request_one_prm(int point_num, char prm_name[], char hostname[]){
	PARAM_NUMBER_DATA_2 pn[1];
	int status;
	char buf[200];
	pn[0].nPnt = point_num;
	pn[0].szPrmName = prm_name;
	
	status = rhsc_param_numbers_2(hostname,1,pn);
	if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
    hsc_napierrstr(status, buf);
    printf("%s, %d \n",buf, status);
    return -1;
	}
	printf("Param number is: %d", pn[0].nPrm);
	return 0;
}

int request_one_value(int param_num, int point_num, char hostname[]){
	PARAM_VALUE_DATA_2 pvd2[1];
	int status;
	char buf[200];
	pvd2[0].nPnt = point_num;
	pvd2[0].nPrm = param_num;
	pvd2[0].nPrmOffset = 0;
	status = rhsc_param_values_2(hostname,0,1,pvd2);
	if (status != 0 && status != NADS_PARTIAL_FUNC_FAIL) {
		hsc_napierrstr(status, buf);
		printf("%s, %d \n",buf, status);
		return -1;
	}
	switch (pvd2[0].nType)
						{
						case DT_ENUM:
								printf("pupvValue.en.ord=%ld pupvValue->en.text=%s",
										pvd2[0].pupvValue->en.ord,
										pvd2[0].pupvValue->en.text);
								break;
						case DT_CHAR:
								printf("pupvValue.text=%s", pvd2[0].pupvValue->text);
								break;
						case DT_INT2:
								printf("pupvValue.int2=%hi", pvd2[0].pupvValue->int2);
								break;
						case DT_INT4:
								printf("pupvValue.int4=%li", pvd2[0].pupvValue->int4);
								break;
						case DT_REAL:
								printf("pupvValue.real=%f", pvd2[0].pupvValue->real);
								break;
						case DT_DBLE:
								printf("pupvValue.dble=%lf", pvd2[0].pupvValue->dble);
								break;
						default:
								break;
						}
	return 0;
}