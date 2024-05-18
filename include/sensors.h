#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "loRaOverlay/LoRaNode.h"

class Sensors : public LoRaNode
{
public:
    Sensors();
    virtual ~Sensors() = default;

    virtual bool appProcessing() override;
    virtual JsonDocument getJsonTxPayload() override;
    virtual bool parseJsonRxPayload(JsonDocument& payload) override;

private:
    uint32_t mCounter;
};

#endif