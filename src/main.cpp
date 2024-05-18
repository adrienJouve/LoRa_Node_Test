#include <Arduino.h>
#include <LoRa.h>
#include <LoRaHomeNode.h>
#include <SPI.h>
#include "sensors.h"

#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(x) Serial.println(F(x))
#define DEBUG_MSG_VAR(x) Serial.println(x)
#else
#define DEBUG_MSG(x) // define empty, so macro does nothing
#endif

// Objects instentiation
Sensors mNode;
LoRaHomeNode mLoRaHome(mNode.getNodeId());

// sampling management
unsigned long nextProcessTime;      // Next processing time
unsigned long nextSendTime;         // Next send time
unsigned long nextSendRetryTime;    // Next send retry time
bool forceProcessing;
JsonDocument receivedMessage;

void setup()
{

  //initialize Serial Monitor
#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial)
    ;
#endif
  DEBUG_MSG("initializing LoRa Node");
  // initialize LoRa    
  mLoRaHome.setup();

  // Update Data before start
  forceProcessing = true;
}

/**
* Main loop of the LoRa Node
* Constantly try to receive JSON LoRa message
* Every transmissionTimeInterval send JSON LoRa messages
*/
void loop()
{
  unsigned long tick = millis();

  // Application processing Task
  if (tick  >= nextProcessTime
    || forceProcessing) {
    DEBUG_MSG("Processing Task");
    forceProcessing = mNode.appProcessing();

    nextProcessTime = millis() + mNode.getProcessingTimeInterval();
  }

  // Send Task
  if ((tick >= nextSendTime)
    || (true == mNode.getTransmissionNowFlag())) {
    DEBUG_MSG("Send Task");
    mNode.setTransmissionNowFlag(false);
    mLoRaHome.sendToGateway(mNode.getJsonTxPayload(), mNode.getTxCounter());
    mNode.incrementTxCounter();

    nextSendTime = millis() + mNode.getTransmissionTimeInterval();
    nextSendRetryTime = millis() + mLoRaHome.getRetrySendMessageInterval();
  }

  // Retry message not received by the gateway
  if ((tick >= nextSendRetryTime) && (mLoRaHome.isWaitingForAck())) {
    DEBUG_MSG("Retry Send Task");
    mLoRaHome.sendToGateway(mNode.getJsonTxPayload(), mNode.getTxCounter());

    nextSendRetryTime = millis() + mLoRaHome.getRetrySendMessageInterval();
  }

  // Receive Task
  bool messageReceived = mLoRaHome.receiveLoraMessage(receivedMessage);
  if(messageReceived){
    DEBUG_MSG("Receive Task");
    mNode.parseJsonRxPayload(receivedMessage);
    forceProcessing = true;
  }
}
