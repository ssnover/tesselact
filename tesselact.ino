#include "Adafruit_LSM303_Accel.h"
#include "Adafruit_Sensor.h"
#include "Wire.h"

const lsm303_accel_range_t ACCELEROMETER_RANGE{LSM303_RANGE_4G};
const lsm303_accel_mode_t ACCELEROMETER_MODE{LSM303_MODE_LOW_POWER};

void setup()
{
}

void loop()
{
    Serial.begin(115200);
    Serial.println("Booting up Tesselact Cube...");

    // The parameter is some kind of unique ID for this sensor?
    Adafruit_LSM303_Accel_Unified accelerometer{54321};

    bool accelerometer_initialized{accelerometer.begin()};
    if (!accelerometer_initialized)
    {
        Serial.println("Could not initialize the accelerometer.");
        while (true)
            ;
    }

    accelerometer.setRange(ACCELEROMETER_RANGE);
    accelerometer.setMode(ACCELEROMETER_MODE);

    while (true)
    {
        sensors_event_t event;
        accelerometer.getEvent(&event);

        Serial.print("x: ");
        Serial.print(event.acceleration.x);
        Serial.print(", y: ");
        Serial.print(event.acceleration.y);
        Serial.print(", z: ");
        Serial.println(event.acceleration.z);

        delay(1000);
    }
}
