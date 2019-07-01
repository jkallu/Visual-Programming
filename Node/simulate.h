#ifndef SIMULATE_H
#define SIMULATE_H

#include <QObject>

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


//typedef struct PData{
//    //char *funcName;
//    size_t size;
//    int nIns;
//    int nInsFilled;
//    char *in; // format: size_t total_size, int func_name_length, func name, int num_var, int var_index, int var size, var type, var_data
//    struct PData *next;
//} PData_t;

//extern PData_t *simPData;
//extern pthread_mutex_t simLock;
//extern char flagSim;



using namespace std;

class ManageBlocks;

class Simulate : public QObject
{

    Q_OBJECT
public:
    Simulate(ManageBlocks *mBlk);
    ~Simulate();
    void createLib(QString dir, QString libName);
    void start(char *callFunc, QString dir, QString libName);
    void stop();
    void addSource(QString src);
    Func_t getFunc(string funcName);
    static void * simLoop(void *simLoopD);

    QString sourceList;


    ManageBlocks *mBlocks;
    vector <Func_t> func;
    void *handle;
    pthread_t thread_id_sim;

public slots:
    void setData(char *data, BlockIO *blockIo);

signals:
    void dataReady(char *data, BlockIO *blockIo);

};

typedef struct simLoopData{
    void *handle;
    Simulate *sim;
} simLoopData_t;

#endif // SIMULATE_H
