#ifndef _ADSR_CONTROLABLE_H_
#define _ADSR_CONTROLABLE_H_

class ADSRControlable
{
public:
    virtual void setAttack(float milliseconds) = 0;
    virtual void setDecay(float milliseconds) = 0;
    virtual void setSustain(float level) = 0;
    virtual void setRelease(float milliseconds) = 0;

    virtual float getAttack() = 0;
    virtual float getDecay() = 0;
    virtual float getSustain() = 0;
    virtual float getRelease() = 0;
};

#endif