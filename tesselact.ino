#include "Adafruit_LSM303_Accel.h"
#include "Adafruit_Sensor.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include "Wire.h"
#include "coap-simple.h"
#include "ssnover-wifi-credentials.h"

const lsm303_accel_range_t ACCELEROMETER_RANGE{LSM303_RANGE_4G};
const lsm303_accel_mode_t ACCELEROMETER_MODE{LSM303_MODE_LOW_POWER};
const IPAddress COAP_SERVER_IP_ADDRESS{192, 168, 1, 16};
const IPAddress COAP_SERVER_PORT{5683};
const uint16_t COAP_TRANSPORT_BUFFER_SIZE{256};
const char * COAP_TOPIC_NAME = {"event"};

void setup()
{
}

void loop()
{
    char coapTransferBuffer[COAP_TRANSPORT_BUFFER_SIZE];
    WiFiUDP udp;
    Coap coapClient{udp};

    Serial.begin(115200);
    Serial.println("Info: Booting up Tesselact Cube...");

    // The parameter is some kind of unique ID for this sensor?
    Adafruit_LSM303_Accel_Unified accelerometer{54321};

    bool accelerometerInitialized{accelerometer.begin()};
    if (!accelerometerInitialized)
    {
        Serial.println("Error: Could not initialize the accelerometer");
        while (true)
            ;
    }
    accelerometer.setRange(ACCELEROMETER_RANGE);
    accelerometer.setMode(ACCELEROMETER_MODE);
    Serial.println("Info: Initialized accelerometer");

    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Warning: Waiting to connect to access point...");
    }
    Serial.println("Info: Successfully connected to access point");

    while (true)
    {
        delay(1000);
        sensors_event_t event;
        accelerometer.getEvent(&event);

        sprintf(coapTransferBuffer, "%.1f,%.1f,%.1f", event.acceleration.x,
                event.acceleration.y, event.acceleration.z);
        auto messageId{coapClient.put(COAP_SERVER_IP_ADDRESS, COAP_SERVER_PORT,
                                      COAP_TOPIC_NAME, coapTransferBuffer)};
        Serial.print("x: ");
        Serial.print(event.acceleration.x);
        Serial.print(", y: ");
        Serial.print(event.acceleration.y);
        Serial.print(", z: ");
        Serial.println(event.acceleration.z);
    }
}
