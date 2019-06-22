#ifndef COMMONHEADER_H
#define COMMONHEADER_H

#include <iostream>
#include <string>
#include <vector>

typedef struct ParseTree{
    std::string symbol;
    std::vector <ParseTree *> child;
} ParseTree_t; // when make any changes to ParseTree_t, also reflect inside compilertoc.h


#endif // COMMONHEADER_H
