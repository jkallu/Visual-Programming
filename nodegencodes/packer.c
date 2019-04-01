#include "packer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void packData(char **data, char no_in, enum Types type, size_t size_in, void *in)
{
    size_t new_size = 0;
    char nv = 0; // number of variables
    size_t add_size = 0;
    if((*data) == NULL)
    {
        printf("Data is not initialized*****\n");
        // total size     = place to hold toal size + number of variables + input number + var size holder + type + data
        new_size = sizeof (size_t) + sizeof (char) + sizeof (char) + sizeof(size_t) + sizeof (type);
        switch(type)
        {
        case Pack_Int:
            new_size += size_in * sizeof (int);
            break;
        case Pack_func:
            new_size += (size_in) * sizeof (char);
            printf( "name %s %ld\n", (char*)in, size_in);
            break;
        }

        (*data) = (char *) malloc(new_size);
        if((*data) == NULL)
        {
            printf("Could not allocate memory\n");
            exit(0);
        }
        memcpy((*data + add_size), &new_size, sizeof (new_size));
        nv++;
        add_size += sizeof (size_t);
        memcpy((*data + add_size), &nv, sizeof (char));
        add_size += sizeof (char);
    }
    else
    {
        printf("Data already initialized#####\n");
        size_t old_size;
        memcpy(&old_size, (*data), sizeof (old_size));
        add_size = old_size;
        new_size = old_size + sizeof (char) + sizeof(size_t) + sizeof (type);
        switch(type)
        {
        case Pack_Int:
            new_size += size_in * sizeof (int);
            break;
        case Pack_func:
            new_size += (size_in) * sizeof (char);
            break;
        }
        (*data) = (char *) realloc((*data), new_size);
        if((*data) == NULL)
        {
            printf("Could not allocate memory\n");
            exit(0);
        }
        memcpy(&nv, (*data) + sizeof (size_t), sizeof (char));
        memcpy((*data), &new_size, sizeof (new_size));
        nv++;
        //add_size += sizeof (size_t);
        memcpy((*data + sizeof (size_t)), &nv, sizeof (char));
        //add_size += sizeof (char);
    }
    printf("New size %ld\n", new_size);

    memcpy(*data + add_size, &no_in, sizeof (char));
    add_size += sizeof (char);

    memcpy(*data + add_size, &size_in, sizeof(size_t));
    add_size += sizeof(size_t);

    memcpy(*data + add_size, &type, sizeof (type));
    add_size += sizeof (type);

    switch (type) {
    case Pack_Int:
        memcpy(*data + add_size, in, size_in * sizeof (int));
        break;
    case Pack_func:
        memcpy(*data + add_size, in, size_in * sizeof (char));
        //add_size += size_in * sizeof (char);
        //char chNull = '\0';
        //memcpy(*data + add_size - 1, &chNull, sizeof (char));
        break;
    }
}

void unPackData(char *data, enum Types *type, size_t *size_out, char **out)
{
    if(data == NULL)
    {
        fprintf(stderr, "Data is empty\n");
        return;
    }

    size_t tot_size;
    size_t add_size = 0;
    memcpy(&tot_size, data + add_size, sizeof (tot_size));
    printf("Total size %ld\n", tot_size);
    char nv;
    add_size += sizeof (size_t);
    memcpy(&nv, data + add_size, sizeof (char));
    printf("number of var %d\n", nv);
    add_size += sizeof (char);
    memcpy(type, data + add_size, sizeof (*type));
    printf("Type %d\n", *type);
    add_size += sizeof (*type);
    memcpy(size_out, data + add_size, sizeof(size_t));
    printf("size in %ld\n", *size_out);
    add_size += sizeof(size_t);
    switch (*type) {
    case Pack_Int:
        if(*out == NULL)
        {
            *out = malloc(*size_out * sizeof (int));
        }
        memcpy(*out, data + add_size, *size_out * sizeof (int));
        break;
    case Pack_func:
        if(*out == NULL)
        {
            *out = (char*)malloc(*size_out * sizeof (char));
        }
        memcpy(*out, data + add_size, *size_out * sizeof (char));
        break;
    }
}

void getFuncName(char *data, char **funcName)
{
    if(data == NULL)
    {
        fprintf(stderr, "Data is empty\n");
        return;
    }
    enum Types type;
    size_t size_out;

    getData(-1, data, &type, &size_out, funcName);
}

void removeFuncName(char *data)
{
    if(data == NULL)
    {
        fprintf(stderr, "Data is empty\n");
        return;
    }

    size_t tot_size;
    size_t add_size = 0;

    memcpy(&tot_size, data + add_size, sizeof (tot_size));
    printf("Total size %ld\n", tot_size);

    char nv;
    add_size += sizeof (size_t);
    memcpy(&nv, data + add_size, sizeof (char));
    printf("number of var %d\n", nv);
    add_size += sizeof (char);


}

void getData(char index, char *data, enum Types *type, size_t *size_out, char **out)
{
    if(data == NULL)
    {
        fprintf(stderr, "Data is empty\n");
        return;
    }

    size_t tot_size;
    size_t add_size = 0;
    char no_in = -2;
    memcpy(&tot_size, data + add_size, sizeof (tot_size));
    printf("Total size %ld\n", tot_size);
    char nv;
    add_size += sizeof (size_t);
    memcpy(&nv, data + add_size, sizeof (char));
    printf("number of var %d\n", nv);
    add_size += sizeof (char);

    for(int i = 0; i < nv; i++)
    {
        memcpy(&no_in, data + add_size, sizeof (char));
        printf("number of input %d\n", no_in);
        add_size += sizeof (char);

        memcpy(size_out, data + add_size, sizeof(size_t));
        printf("size in %ld\n", *size_out);
        add_size += sizeof(size_t);

        memcpy(type, data + add_size, sizeof (*type));
        printf("Type %d\n", *type);
        add_size += sizeof (*type);

        if(index == no_in)
        {
            switch (*type)
            {
            case Pack_Int:
                if(*out == NULL)
                {
                    *out = (char*)malloc(*size_out * sizeof (int));
                }
                memcpy(*out, data + add_size, *size_out * sizeof (int));
                add_size += *size_out * sizeof (int);
                break;
            case Pack_func:
                if(*out == NULL)
                {
                    *out = (char*)malloc(*size_out * sizeof (char));
                }
                memcpy(*out, data + add_size, *size_out * sizeof (char));
                add_size += *size_out * sizeof (char);
                break;
            }
            break;
        }
        else
        {
            switch (*type)
            {
                case Pack_Int:
                    add_size += *size_out * sizeof (int);
                break;
                case Pack_func:
                    add_size += *size_out * sizeof (char);
                    //i--;
                break;
            }
        }
    printf("ADDED SIZE %ld\n", add_size);
    }
    printf("TOTAL ADDED SIZE %ld\n", add_size);
}
