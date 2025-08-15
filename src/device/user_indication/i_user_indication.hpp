#pragma once

class IUserIndication
{
   private:
   public:
    virtual void set() = 0;
    virtual void reset() = 0;
};