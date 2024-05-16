#ifndef SENSORS_H
#define SENSORS_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <LoRaNode.h>

class Sensors : public LoRaNode
{
public:
    Sensors();
    virtual ~Sensors() = default;

    void appSetup();
    virtual bool appProcessing() override;
    void addJsonTxPayload(JsonDocument& payload);
    virtual bool parseJsonRxPayload(JsonDocument& payload) override;

private:
    uint32_t mCounter;
};

#endif