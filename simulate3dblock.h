#ifndef SIMULATE3DBLOCK_H
#define SIMULATE3DBLOCK_H

#include "blockio.h"
#include "simulate3d.h"

class BlockIO;
class Simulate3d;

class Simulate3dBlock : virtual public BlockIO
{
public:
    Simulate3dBlock(int i);

    void init() override;

    Qt3DExtras::Qt3DWindow *view;
};

#endif // SIMULATE3DBLOCK_H
