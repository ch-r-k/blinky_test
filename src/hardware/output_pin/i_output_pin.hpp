#pragma once

class IOutputPin
{
   public:
    virtual void set() = 0;
    virtual void reset() = 0;
};
