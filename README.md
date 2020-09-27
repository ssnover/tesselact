# tesselact
ESP8266-based sensor which reports motion events of a cube.

## Goal
Build a cube that can detect being moved and on detection report which side is up and whether it was turned, tapped, or shaken. This project is
using a NodeMCU v2 board with an ESP8266. For simplicity I'm using Arduino's build system and libraries, including the Adafruit LSM303 sensor library
and a CoAP client library.

I'll be writing a CoAP server which will be hooked into my ROS system and associate preset scenes for lights, music, etc with different sides and
motions for the cube. When that's live, you'll see a link: here.

## Dependencies
* https://github.com/adafruit/Adafruit_LSM303_Accel
* https://github.com/hirotakaster/CoAP-simple-library
