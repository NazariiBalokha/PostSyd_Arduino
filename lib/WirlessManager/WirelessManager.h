#ifndef WIRELESS_MANAGER_H
#define WIRELESS_MANAGER_H

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <MqttClient.h>

class WirelessManager
{
private:
    EthernetClient ethernetClient;
    MqttClient mqttClient;

    const char* broker;
    int port;
public:
    WirelessManager(byte mac[], const char broker[], int port);

    void setupEthernet();

    void setupMqtt();
    void onMqttMessage(int messageSize);

    void publish(const char* topic, const char* message);
    void subscribe(const char* topic);
    void pool();
};

#endif // WIRELESS_MANAGER_H