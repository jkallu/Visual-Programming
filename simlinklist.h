#ifndef SIMLINKLIST_H
#define SIMLINKLIST_H

#include <pthread.h>
#include <unistd.h>

typedef struct PData{
    char *funcName;
    size_t size;
    int nIns;
    int nInsFilled;
    char *in; // format: size_t total_size, int func_name_length, func name, int num_var, int var_index, int var size, var type, var_data
    struct PData *next;
} PData_t;

extern PData_t *simPData;
extern pthread_mutex_t simLock;
extern char flagSim;
extern char flagRun;

int popFirstSim(PData_t **head, char **data);
int isFirstListFilled(PData_t *head);


#endif // SIMLINKLIST_H
