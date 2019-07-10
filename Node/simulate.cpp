#include "simulate.h"
#include "./nodegencodes/packer.h"


char flagSim = 1;
//pthread_mutex_t simLock;
PData_t *simPData;
char flagRun = 1;


Simulate::Simulate(ManageBlocks *mBlk)
{
    mBlocks = mBlk;
    /*    //simPData = NULL;
#ifdef __cplusplus
    if(pthread_mutex_init(&simLock, nullptr))
#else
    if(pthread_mutex_init(&simLock, NULL))
#endif
    {
        fprintf(stderr, "Mutex init has failed\n");
        exit(1);
    }*/
    flagSim = 1;

    //*simPData = NULL;
    connect(this, SIGNAL(dataReady(char*, BlockIO*)), this, SLOT(setData(char*, BlockIO*)));
}

Simulate::~Simulate()
{

}

void Simulate::setData(char *data, BlockIO *blockIo)
{
    blockIo->setData(data);
}

void Simulate::addSource(QString src)
{
    sourceList.append(src + " ");
}

void Simulate::createLib(QString dir, QString libName)
{
    cout << "CREATING LIBS\n";
    QStringList list = sourceList.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QString path;

    path = "rm -f " + libName;
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "No prev " + libName.toStdString() + " found\n";
    }

    path = "rm -f eventLoop.o";
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "No prev eventLoop.o found\n";
    }

    path = "gcc -fPIC -c " + dir + "eventLoop.c -L. -lpthread -lm -I " + dir;
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "Error\n";
        return;
    }

    path = "rm -f linkedList.o";
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "No prev linkedList.o found\n";
    }

    path = "gcc -fPIC -c " + dir + "linkedList.c -I " + dir;
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "Error\n";
        return;
    }

    path = "rm -f packer.o";
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "No prev packer.o found\n";
    }

    path = "gcc -fPIC -c " + dir + "packer.c -I " + dir;
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "Error\n";
        return;
    }


    for(int i = 0; i < list.size(); i++)
    {
        cout << list.at(i).toStdString() << endl;
        path = "rm -f " + list.at(i) + ".o";
        if(system(path.toStdString().c_str()) == -1)
        {
            cout << "No prev " << list.at(i).toStdString() <<".o found\n";
        }

        path = "gcc -fPIC -c " + dir + list.at(i) + ".c" + " -I " + dir;
        if(system(path.toStdString().c_str()) == -1)
        {
            cout << "Error " << path.toStdString() << endl;
            return;
        }
    }

    path = "gcc -shared -o " + libName + " eventLoop.o ";
    for(int i = 0; i < list.size(); i++)
    {
        path += list.at(i) + ".o ";
    }
    path += "linkedList.o packer.o -L. -lpthread -lm";
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "Error " << path.toStdString() << endl;
        return;
    }
}

void Simulate::start(char *callFunc, QString dir, QString libName)
{
    createLib(dir, libName);

    printf("Main thread start\n");
    char *error;

    void (*exec)(char *, pthread_mutex_t *, char, PData_t **);

    handle = dlopen (QString("./" + libName ).toStdString().c_str(), RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return;
        //exit(EXIT_FAILURE);
    }
    /*void **sPData = (void **)dlsym(handle, "simPData");
#ifdef __cplusplus
    if ((error = dlerror()) != nullptr)
#else
    if ((error = dlerror()) != NULL)
#endif
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    */
    //simPData = (PData_t **) sPData;
#ifdef __cplusplus
    simPData = nullptr;
#else
    simPData = NULL;
#endif
    flagRun = 1;
    *(void **) (&exec) = dlsym(handle, "exec");
    if ((error = dlerror()) != nullptr)
    {
        fprintf(stderr, "%s\n", error);
        return;
        //exit(EXIT_FAILURE);
    }
    simLoopData_t *simLoopD = (simLoopData_t *)malloc(sizeof (simLoopData_t));
    simLoopD->handle = handle;
    simLoopD->sim = this;


    if(pthread_create(&thread_id_sim, nullptr, simLoop, (void*)simLoopD))
    {
        fprintf(stderr, "Error creating thread\n");
        return;
    }

    //simLoop(handle);
    (*exec)(callFunc, &simLock, flagSim, &simPData);

    //simLoop((void*)simLoopD);

    printf("Main thread end\n");
    //dlclose(handle);
}

Func_t Simulate::getFunc(string funcName)
{
    Func_t locFunc;
    for (size_t i = 0; i < func.size(); i++)
    {
        if(func.at(i).funcName == funcName)
        {
            locFunc.funcName = func.at(i).funcName;
            locFunc.type = func.at(i).type;
            locFunc.arrayNum = func.at(i).arrayNum;
            break;
        }

        if(i == func.size() - 1)
        {
            cout << "Error! could not find the func name" << endl;

        }
    }

    return locFunc;
}

void * Simulate::simLoop(void *simLoopD)
{
    simLoopData_t *loopData = (simLoopData_t *)simLoopD;
    //void *handle = loopData->handle;
    Simulate *sim = loopData->sim;
    char *error;
    /*int (*isFirstListFilled)(PData_t *, int*);
    isFirstListFilled = (int (*)(PData_t*, int*))dlsym(handle, "isFirstListFilled");
    if ((error = dlerror()) != nullptr)
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }*/
    char *data = nullptr;
    char *funcName = nullptr;
    while(flagRun)
    {
        //pthread_mutex_lock(&simLock);
        if(simPData != nullptr)
        {
            data = nullptr;
            printf("SIZE   FROM SIM %ld\n", simPData->size);
            popFirstSim(&simPData, &data);


            if(data != nullptr)
            {
                getFuncName(data, &funcName);

                Func_t func = sim->getFunc(funcName);
                switch (func.type)
                {
                //case BlockItem::BlockType::Graph:
                //    sim->mBlocks->graphs[func.arrayNum]->setData(data);
                //    break;
                default:
                    for(size_t i = 0; i < sim->mBlocks->blockIO.size(); i++)
                    {
                        if(func.type == sim->mBlocks->blockIO.at(i)->getType() &&
                                func.arrayNum == sim->mBlocks->blockIO.at(i)->getId())
                        {


                            //if(func.type == BlockItem::Graph || func.type == BlockItem::Split)
                            //{
                                ///sim->mBlocks->blockIO.at(i)->setData(data);
                                emit sim->dataReady(data, sim->mBlocks->blockIO.at(i));
                            //}
                            //else
                            /*{
                                for(int j = -1; j < sim->mBlocks->blockIO.at(i)->numOfInputs; j++)
                                {
                                    Types type = Types::PACK_COUNT_MAX;
                                    size_t size = 0;
                                    char *data_out = nullptr;

                                    getData(j, data, &type, &size, &data_out);

                                    if(size > 0)
                                    {

                                        QMetaObject::invokeMethod(sim->mBlocks->blockIO.at(i)->teData, "append",
                                                                  Q_ARG(QString, "SIZE " + QString::number(size)));
                                        switch(type)
                                        {
                                        case Types::Pack_func:
                                            QMetaObject::invokeMethod(sim->mBlocks->blockIO.at(i)->teData, "append",
                                                                      Q_ARG(QString, "FUNCTION NAME " + QString::fromStdString(data_out)));
                                            break;
                                        case Types::Pack_Float:
                                            float d_f;
                                            for(int k = 0; k < size; k++)
                                            {
                                                memcpy(&d_f, data + k * sizeof (d_f), sizeof (d_f));
                                                QMetaObject::invokeMethod(sim->mBlocks->blockIO.at(i)->teData, "append",
                                                                          Q_ARG(QString, "DATA_ " + QString::number(k) + " " + QString::number(d_f)));

                                            }
                                            break;
                                        case Types::Pack_Int:
                                            int d_i;
                                            for(int k = 0; k < size; k++)
                                            {
                                                memcpy(&d_i, data + k * sizeof (d_i), sizeof (d_i));
                                                QMetaObject::invokeMethod(sim->mBlocks->blockIO.at(i)->teData, "append",
                                                                          Q_ARG(QString, "DATA_ " + QString::number(k) + " " + QString::number(d_i)));

                                            }
                                            break;
                                        }

                                    }

                                    if(data_out != nullptr || data_out != NULL)
                                    {
                                        free(data_out);
                                        data_out = nullptr;
                                    }
                                }
                            }*/


                            break;
                        }
                    }

                }

                cout << "FUNC NAME FROM SIM " << func.funcName << " " << func.type << " " << func.arrayNum << endl;
            }
            if(data != nullptr)
            {
                free(data);
                data = nullptr;
            }
            if(funcName != nullptr)
            {
                free(funcName);
                funcName = nullptr;
            }
        }
        //pthread_mutex_unlock(&simLock);

        usleep(10);

    }
}
/*
void * simLoop(void *)
{
    char *data;
    while (1)
    {
        if(flagRun == 1)
        {
            pthread_mutex_lock(&simLock);
            if(*simPData != NULL)
            {
                printf("SIZE   FROM SIM %ld\n", (*simPData)->size);
                popFirst(simPData, &data);
            }
            pthread_mutex_unlock(&simLock);
        }
        usleep(10);
    }
}
*/

void Simulate::stop()
{
    char *error;
    pthread_t (*getEventLoopTId)(void);
    *(void **) (&getEventLoopTId) = dlsym(handle, "getEventLoopTId");
    if ((error = dlerror()) != nullptr)
    {
        fprintf(stderr, "%s\n", error);
        return;
        //exit(EXIT_FAILURE);
    }

    void (*setFlagRun)(int);
    *(void **) (&setFlagRun) = dlsym(handle, "setFlagRun");
    if ((error = dlerror()) != nullptr)
    {
        fprintf(stderr, "%s\n", error);
        return;
        //exit(EXIT_FAILURE);
    }

    if(pthread_kill(thread_id_sim, 0))
    {
        printf("SimLoop thread is not running\n");
    }
    else
    {
        //pthread_kill(thread_id_sim, SIGTERM);
        flagRun = 0;
    }


    pthread_t id =(*getEventLoopTId)();
    // check if the thrad is running
    if(pthread_kill(id, 0))
    {
        printf("EvntLoop thread is not running\n");
    }
    else
    {
        (*setFlagRun)(0);
    }
    dlclose(handle);

    //pthread_kill(id, SIGKILL);

    //dlclose(handle);
    return;
}
