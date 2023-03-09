#pragma once
#include "ObjectBase.h"

class ObjectRingBase :
    public ObjectBase
{
public:
    ObjectRingBase();
    virtual ~ObjectRingBase() {}

    virtual void Init();

    virtual void SetPos(float X, float Y);

    virtual void Update();

    virtual void Draw(int scroll, int color);

private:
    float circleSize;
    float sizeAcc;
};

