#include "device_manager.hpp"

DeviceManager::DeviceManager(HardwareManager& hardware_manager)
{
    userIndication.setOutputPin(hardware_manager.getLedPin());
}

UserIndication& DeviceManager::getUserIndication() { return userIndication; }