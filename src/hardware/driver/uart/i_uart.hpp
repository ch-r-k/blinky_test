#pragma once

#include <span>
#include <cstdint>

namespace hardware_layer
{
class IUart
{
   public:
    virtual ~IUart() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void startWrite(const std::span<std::uint8_t> data) = 0;
    virtual void startRead(const std::span<std::uint8_t> data) = 0;
};

}  // namespace hardware_layer
