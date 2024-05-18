#ifndef NODE_CONFIG_H
#define NODE_CONFIG_H

const uint8_t NODE_ID = 10;
const unsigned long PROCESSING_TIME_INTERVAL   = 600000;  // 10 mins
const unsigned long TRANSMISSION_TIME_INTERVAL = 1000;
const unsigned long BUTTON_UP_TIME = 1000;  // 1 sec
const uint16_t MY_NETWORK_ID = 0xACDC;

#define MSG_SNR "snr"
#define MSG_RSSI "rssi"

#endif 