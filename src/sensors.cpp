#include "sensors.h"
#include "NodeConfig.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x) Serial.println(F(x))
#define DEBUG_MSG_VAR(x) Serial.println(x)
#else
#define DEBUG_MSG(x) // define empty, so macro does nothing
#define DEBUG_MSG_VAR(x)
#endif


/*!********************************************************************
 * @brief Construct a new Node:: Node object
 **********************************************************************/
Sensors::Sensors():
    LoRaNode(NODE_ID, TRANSMISSION_TIME_INTERVAL, PROCESSING_TIME_INTERVAL, true),
    mCounter(0)
{
}

/**
* Add JSON Tx payload messages
* @param payload the JSON payload to be completed as per application needs
*/
JsonDocument Sensors::getJsonTxPayload() {
    JsonDocument payload;
    payload["test"] = mCounter++;
    return payload;
}

/**
* Parse JSON Rx payload
* One should avoid any long processing in this routine. LoraNode::AppProcessing is the one to be used for this purpose
* Limit the processing to parsing the payload and retrieving the expected attributes
* @param payload the JSON payload received by the node
* return true in case of new message received
*/
bool Sensors::parseJsonRxPayload(JsonDocument& payload) {
    DEBUG_MSG("Parsing JSON Rx payload");
    return false;
}

/**
* App processing of the node.
* Invoke every loop of the nodes before Rx and Tx
* ONe should benefit from using processingTimeInterval to avoid overloading the node
*/
bool Sensors::appProcessing() {
    return false;
}