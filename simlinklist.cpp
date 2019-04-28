#include "simlinklist.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "./nodegencodes/packer.h"

pthread_mutex_t simLock = PTHREAD_MUTEX_INITIALIZER;

int popFirstSim(PData_t **head, char **data)
{
    while(pthread_mutex_trylock(&simLock))
    {
        printf("\rTRYING TO LOCK MUTEX %s", __FUNCTION__);
    }
    printf("\nLOCKED MUTEX %s\n", __FUNCTION__);
    //pthread_mutex_lock(&simLock);
    //PData_t **head = &gPData;
    if ((*head) == nullptr) {
        *data = nullptr;
        pthread_mutex_unlock(&simLock);
        return -1;
    }
    *data = (char*) malloc((*head)->size);
    printf("sizeee %ld\n", (*head)->size);
    if(*data == nullptr)
    {
        fprintf(stderr, "malloc error\n");

        pthread_mutex_unlock(&simLock);
        return -1;
    }
    printf("HHHHHH sss\n");
    memcpy(*data, (*head)->in, (*head)->size);
    PData_t * tmp = *head;
    *head = (*head)->next;
    free (tmp);

  /*
    printf("HHHHHH dd\n");

    Types type;
    size_t size_0, size_1;
    char *data_0 = NULL, *data_1 = NULL;
    getData(0, *data, &type, &size_0, &data_0);
    getData(1, *data, &type, &size_1, &data_1);

    printf("SIZE FROM LINK PACK FOR TEST ***** %ld %ld\n", size_0, size_1);
*/
    pthread_mutex_unlock(&simLock);
    return 1;
}

int isFirstListFilled(PData_t *head)
{

    if(head == nullptr)
    {
        return 0;
    }

    if(head->nIns > 0 && head->nInsFilled > 0 && head->nIns == head->nInsFilled)
    {
        return 1;
    }
    else {
        return 0;
    }
}

