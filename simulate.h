#ifndef SIMULATE_H
#define SIMULATE_H

#include <iostream>
#include <dlfcn.h>
#include <cstdlib>
//#include "eventLoop.h"
#include <QString>
#include <QStringList>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "simlinklist.h"
#include "constarrayblock.h"
#include "manageblocks.h"

typedef struct  Func {
    std::string funcName;
    BlockItem::BlockType type;
    int arrayNum;
} Func_t;


/*typedef struct PData{
    //char *funcName;
    size_t size;
    int nIns;
    int nInsFilled;
    char *in; // format: size_t total_size, int func_name_length, func name, int num_var, int var_index, int var size, var type, var_data
    struct PData *next;
} PData_t;

extern PData_t *simPData;
extern pthread_mutex_t simLock;
extern char flagSim;*/



using namespace std;

class ManageBlocks;

class Simulate
{
public:
    Simulate(ManageBlocks *mBlk);
    void createLib(QString dir);
    void start(char *callFunc, QString dir);
    void stop();
    void addSource(QString src);
    Func_t getFunc(string funcName);

    QString sourceList;


    ManageBlocks *mBlocks;
    vector <Func_t> func;
    void *handle;
    pthread_t thread_id_sim;

};

typedef struct simLoopData{
    void *handle;
    Simulate *sim;
} simLoopData_t;
void * simLoop(void *simLoopD);

#endif // SIMULATE_H
