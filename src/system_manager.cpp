#include "system_manager.hpp"

SystemManager::SystemManager()
    : hardwareManager(),
      deviceManager(hardwareManager),
      applicationManager(deviceManager)
{
    static std::uint8_t qs_tx_buf[2 * 1024];  // buffer for QS-TX channel
    QP::QS::initBuf(qs_tx_buf, sizeof(qs_tx_buf));

    static std::uint8_t qs_rx_buf[100];  // buffer for QS-RX channel
    QP::QS::rxInitBuf(qs_rx_buf, sizeof(qs_rx_buf));
}

SystemManager::~SystemManager() {}

void SystemManager::run() { applicationManager.start(); }
