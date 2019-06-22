#ifndef SIMULATE3DBLOCK_H
#define SIMULATE3DBLOCK_H

#include "blockio.h"
#include "simulate3d.h"
#include "vector"

#include <QComboBox>
#include <QLabel>

class BlockIO;
class Simulate3d;

class Simulate3dBlock : virtual public BlockIO
{
public:
    Simulate3dBlock(int i);

    void init() override;
    void setData(char *data) override;
    void show();

    Qt3DExtras::Qt3DWindow *view;
    Simulate3d *simulate3d;
    Qt3DAnimation::QClipAnimator *animator;
    Qt3DAnimation::QAnimationClip *animationClip;

    std::vector <double> x_data, y_data, z_data, t_data;

    QLabel *lblAxis;
    QComboBox *cbAxis;
};

#endif // SIMULATE3DBLOCK_H
