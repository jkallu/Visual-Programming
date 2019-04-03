#include "simulate.h"
#include "/home/jin/qt_pgms/nodegencodes/packer.h"


char flagSim = 1;
//pthread_mutex_t simLock;
PData_t *simPData;
char flagRun = 0;


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
}

void Simulate::addSource(QString src)
{
    sourceList.append(src + " ");
}

void Simulate::createLib(QString dir)
{
    cout << "CREATING LIBS\n";
    QStringList list = sourceList.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    QString path;

    path = "rm -f libmylib.so";
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "No prev libmylib.so found\n";
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
        path = "rm -f " + list.at(i) + ".o";
        if(system(path.toStdString().c_str()) == -1)
        {
            cout << "No prev " << list.at(i).toStdString() <<".o found\n";
        }

        path = "gcc -fPIC -c " + dir + list.at(i) + ".c" + " -I " + dir;
        if(system(path.toStdString().c_str()) == -1)
        {
            cout << "Error\n";
            return;
        }
    }

    path = "gcc -shared -o libmylib.so eventLoop.o ";
    for(int i = 0; i < list.size(); i++)
    {
        path += list.at(i) + ".o ";
    }
    path += "linkedList.o packer.o -L. -lpthread -lm";
    if(system(path.toStdString().c_str()) == -1)
    {
        cout << "Error\n";
        return;
    }
}

void Simulate::start(char *callFunc, QString dir)
{
    createLib(dir);

    printf("Main thread start\n");
    char *error;
    void *handle;
    void (*exec)(char *, pthread_mutex_t *, char, PData_t **);

    handle = dlopen ("./libmylib.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    }
    simLoopData_t *simLoopD = (simLoopData_t *)malloc(sizeof (simLoopData_t));
    simLoopD->handle = handle;
    simLoopD->sim = this;

    pthread_t thread_id;
    if(pthread_create(&thread_id, nullptr, simLoop, (void*)simLoopD))
    {
        fprintf(stderr, "Error creating thread\n");
        return;
    }

    //simLoop(handle);
    (*exec)(callFunc, &simLock, flagSim, &simPData);

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

void *simLoop(void *simLoopD)
{
    simLoopData_t *loopData = (simLoopData_t *)simLoopD;
    void *handle = loopData->handle;
    Simulate *sim = loopData->sim;
    char *error;
    int (*isFirstListFilled)(PData_t *, int*);
    isFirstListFilled = (int (*)(PData_t*, int*))dlsym(handle, "isFirstListFilled");
    if ((error = dlerror()) != nullptr)
    {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }
    char *data = nullptr;
    char *funcName = nullptr;
    while(1)
    {
        //pthread_mutex_lock(&simLock);
        if(simPData != nullptr)
        {
            printf("SIZE   FROM SIM %ld\n", simPData->size);
            popFirstSim(&simPData, &data);


            if(data != nullptr)
            {
                getFuncName(data, &funcName);

                Func_t func = sim->getFunc(funcName);
                switch (func.type)
                {
                case BlockItem::BlockType::Graph:
                    sim->mBlocks->graphs[func.arrayNum]->createInpuData(data);
                    break;
                }

                cout << "FUNC NAME FROM SIM " << func.funcName << " " << func.type << " " << func.arrayNum << endl;
            }
        }
        //pthread_mutex_unlock(&simLock);

        usleep(10);
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
