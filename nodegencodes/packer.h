#ifndef PACKER_H
#define PACKER_H

#include <stdlib.h>

enum Types {
            Pack_Char, Pack_uChar, Pack_Int, Pack_uInt,
            Pack_Short, Pack_uShort, Pack_Long, Pack_uLong,
            Pack_Float, Pack_Double, Pack_lDouble, Pack_String,
            Pack_func
           };

/*
typedef struct VPack {
    size_t size;
    enum Types type;
    char *data;
} VPack_t;

typedef struct DPacker {
    size_t tot_size;
    char nVar;
    VPack_t dPack;
} DPacker_t;
*/
#ifdef __cplusplus
    extern "C" {
#endif
void removeFuncName(char *data);
void packData(char **data, char no_in, enum Types type, size_t size_in, void *in);
void unPackData(char *data, enum Types *type, size_t *size_out, char **out);
void getFuncName(char *data, char **funcName);
void getData(char index, char *data, enum Types *type, size_t *size_out, char **out);
#ifdef __cplusplus
    }
#endif
#endif // PACKER_H
