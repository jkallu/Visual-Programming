#ifndef DEMUXBLOCK_0_H 
#define DEMUXBLOCK_0_H 
typedef enum {
MainBlock_0_SUCCESS,
MainBlock_1_SUCCESS,
MainBlock_2_SUCCESS,
MainBlock_3_SUCCESS,
NUM_STATES
}DeMuxBlock_0_StateType;

typedef struct {
DeMuxBlock_0_StateType state;
char funcName[100];
} StateMachineType;
void * DeMuxBlock_0(void *dat);
#endif
