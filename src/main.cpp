#include <Arduino.h>
#include <Servo.h>
#include "Ultrasonic.h"
#include <ArduinoMqttClient.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "ServoManager.h"
#include "StepperManager.h"

byte mac[] = {
  0xA0, 0x61, 0x0A, 0xAE, 0x94, 0xE2
};

EthernetClient ethernetClient;
MqttClient mqttClient(ethernetClient);

const char broker[] = "10.130.56.30";
int port = 1883;

Ultrasonic ultrasonic(6);

#define OUTPUT1   5                // Connected to the Blue coloured wire
#define OUTPUT2   8                // Connected to the Pink coloured wire
#define OUTPUT3   9                // Connected to the Yellow coloured wire
#define OUTPUT4   10               // Connected to the Orange coloured wire
#define DELAY 2                    // delay after every step


StepperManager stepperManager(OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, DELAY);

ServoManager ServoManager0;
ServoManager ServoManager1;
ServoManager ServoManager2(true);

ServoManager servos[] = {
  ServoManager0,
  ServoManager1,
  ServoManager2
};

long RangeInCentimeters;
bool messageReceived = false;

int testTing;

const char responseTopic[]  = "sorter/chute";
const char scannerTopic[]  = "sorter/package/ready";

void onMqttMessage(int messageSize);
void spinMotor();
void setupEthernet();
void setupMqtt();

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up...");
  pinMode(OUTPUT1, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(OUTPUT4, OUTPUT);

  setupEthernet();
  setupMqtt();

  servos[1].attach(7);
  servos[2].attach(3);

  servos[1].manualControl(0);
  servos[2].manualControl(160);

  Serial.println("Servo test started...");
  servos[1].testServo();
  delay(1000);
  Serial.println("Testing 2nd servo...");
  servos[2].testServo();

  Serial.println("Servo test complete.");

}
void loop() {
spinMotor();
mqttClient.poll();

}

void spinMotor(){
	RangeInCentimeters = ultrasonic.MeasureInCentimeters();
  Serial.print("Distance: ");
  Serial.println(RangeInCentimeters);

  if (RangeInCentimeters < 7) {
    Serial.println("Object detected, stopping motor.");
    messageReceived = false;
    mqttClient.beginMessage(scannerTopic);
    mqttClient.print("");
    mqttClient.endMessage();    
    while (!messageReceived) {

      delay(100);
      mqttClient.poll();
    }
  }

  stepperManager.spinMotor(128);
}


void setupEthernet() {
Ethernet.begin(mac);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  delay(500);
}

void setupMqtt(){
  Serial.println("Connecting to MQTT broker...");
  Serial.print("Broker: ");
  Serial.println(broker);
  Serial.print("Port: ");
  Serial.println(port);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  mqttClient.onMessage(onMqttMessage);
  mqttClient.subscribe(responseTopic); 
}


void onMqttMessage(int messageSize) {
  if (mqttClient.available()) {
  
    String topic = mqttClient.messageTopic();
    String message = "";
    

    while (mqttClient.available()) {
      char c = (char)mqttClient.read();
      message += c;
    }
  
    Serial.print("Received on topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    Serial.println(message);

    messageReceived = true;
    
    if (topic == responseTopic) {
      Serial.print("Chute: ");
      Serial.println(message.toInt());

      servos[message.toInt()].openGate();
      stepperManager.spinMotor(1024);
      servos[message.toInt()].closeGate();

      Serial.println("Servo control complete.");
      messageReceived = true;
    }
  }

  Serial.println();
}