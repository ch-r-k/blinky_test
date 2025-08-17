#pragma once

class IGpioPin
{
   public:
    ~IGpioPin() = default;
    virtual void set() = 0;
    virtual void reset() = 0;
    virtual bool get() = 0;
};
