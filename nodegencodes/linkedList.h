#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <pthread.h>



typedef struct PData{
    char *funcName;
    size_t size;
    int nIns;
    int nInsFilled;
    char *in; // format: size_t total_size, int func_name_length, func name, int num_var, int var_index, int var size, var type, var_data
    struct PData *next;
} PData_t;
#ifdef __cplusplus
extern "C" PData_t *gPData;
extern "C" pthread_mutex_t lock;
extern "C" char *global_data;
extern "C" pthread_mutex_t global_lock;
#else
extern PData_t *gPData;
extern pthread_mutex_t lock;
extern char *global_data;
extern pthread_mutex_t global_lock;
#endif

void* mallocAndCheck(size_t size);

int searchFunc(char *funcName);
PData_t ** findPosOfLastFilled();
void appendData(char *funcName, char noIn, char nov, char *data);
void pushToEnd(char *funcName, char noIn, char nov, char *data);
void pushSim(PData_t **head, char *data);
void pushToBegin(PData_t **head, char *data);
void localProcedureCall(char *funcName, char noIn, char nov, char *data);
void pushAfter(PData_t *prev_node);


int isFirstListFilled(PData_t *head);
size_t sizeOfFirstList(void);
int popFirst(char **data);
int popFilled(char **data);


#endif // LINKEDLIST_H
