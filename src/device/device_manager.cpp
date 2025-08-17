#include "device_manager.hpp"
#include "device/user_input/user_input.hpp"

DeviceManager::DeviceManager(HardwareManager& hardware_manager)
{
    user_indication.setOutputPin(hardware_manager.getLedPin());
    user_input.setInputPin(hardware_manager.getButtonPin());
}

UserIndication& DeviceManager::getUserIndication() { return user_indication; }
UserInput& DeviceManager::getUserInput() { return user_input; }