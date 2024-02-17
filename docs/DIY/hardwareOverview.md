For the DIY hardware you will, as the name suggest, do it yourself. This includes sourcing parts, basic soldering, 3D printing (for the Full sensor). You will be responsible for all troubleshooting.<br>

<b>It is your own responsibility to properly build and use the hardware.<br>
Material Foundry cannot be held responsible for any damage, either directly or indirectly caused by Material Foundry or any associated hardware, software or service.<br>
This includes damage caused by incorrect documentation, bugs in the software/firmware or wrong advise.</b>

## Sensor
The sensor is responsible for detecting the location of bases, onto which minis are placed. 
The sensor has a special infrared camera that can track sources of infrared light. 
After calibrating the sensor, the sensor can transmit the exact location of bases to the VTT over (2.4GHz) WiFi or USB, which can then move tokens.

A maximum of 4 minis can be moved at the same time, but you can have as many minis on your display (just don't move more than 4 at the same time).

For the DIY sensor, you have 2 options:

* Basic: The most barebones version, just enough to use Material Plane
* Full: A complete device that adds an enclosure, battery charging and more

See the table below for a comparison, where you should consider everytying to be identical, except for the listed items.

|               | Basic Sensor  | Full Sensor   |
|---------------|---------------|---------------|
| Required materials    | Only microcontroller and infrared tracking sensor | Much big list of [requirements](BuildInstructions/sensorFull.md#requirements)
| Microcontroller   | Basically any ESP32 or ESP32-S3 board<br> Check the [compatible boards](BuildInstructions/sensorBasic.md#compatible-boards) section  | Must use eiter a TinyPICO or TinyS3  |
| Battery           | No battery or battery charging    | With battery and battery charging |
| Indicator LEDs    | None                              | Battery and connection indicator LEDs |
| Enclosure         | None                              | 3D printed
| USB Detection     | None                              | Included

## Base