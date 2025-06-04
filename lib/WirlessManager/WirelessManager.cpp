#include "WirelessManager.h"

WirelessManager::WirelessManager(byte mac[], const char broker[], int port)
    : broker(broker), port(port), mqttClient(ethernetClient) {
    Ethernet.begin(mac);
}

