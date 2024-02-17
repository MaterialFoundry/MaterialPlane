# Basic Sensor Build Instructions

{% include 'diyDisclaimer.md' %}

This page discusses the fabrication of the basic DIY sensor. If you are not sure whether you want to build the full or basic sensor, please head over to the [hardware overview](../hardwareOverview.md).<br>
Discussed on this page are the required tools, materials and parts you need and the build instructions.

## Before You Get Started
The basic sensor build requires a compatible ESP32 board. Almost any ESP32 or ESP32-S3 board is compatible. It will need to be dual core (so no ESP32-SOLO based boards) and based on whether you have an ESP32 or ESP32-S3, you will need to make sure that the following pins are available on the board:

| Board     | Pins      |
|-----------|-----------|
| ESP32     | 21 & 22   |
| ESP32-S3  | 8 & 9     |

### Compatible Boards
For Material Plane, there is no noticable difference between an ESP32 or ESP32-S3, so pick the one that you can source or the one that is cheapest.<br>
Below is an incomplete list of boards that <i>should</i> be compatible.

| ESP32                                 | ESP32-S3                          |
|---------------------------------------|-----------------------------------|
| ESP32-DevKitC                         | ESP32-S3-DevKitC                  |
| ESP32-PicoKit                         | Arduino Nano ESP32                |
| Wemos LOLIN32                         | Wemos S3 (also the Mini and Pro)  |
| FireBeetle ESP32                      | LilyGo T7-S3                      |
| <i>And many more</i>                  | <i>And many more</i>              |

### Things to Avoid
When looking through the product listing, make sure you don't see any of the following terms:

* ESP32-S2
* ESP32-Cx (can be C2, C3 or C6)
* ESP32-H2
* ESP-WROOM-02
* ESP8266
* Solo
* Zigbee

## Requirements

### Required Tools

* Soldering iron + solder
* Wire cutter
* Wire stripper

### Bill of Materials

* 3D printed parts
* An ESP32 or ESP32-S3
* DFRobot SEN0158

### Sourcing Parts

<b>Please note that the links below are a suggestion only and there may be mistakes. It is your own responsibility to make sure the part is compatible.<br>
If you find an incompatible part or a dead/incorrect link, please contact me.</b>

| Supplier              | ESP32/ESP32-S3 | DFRobot SEN0158 |
|-----------------------|-----------------|----------------------|
| Mouser (US)           | [ESP32-DevKitC](https://eu.mouser.com/ProductDetail/Espressif-Systems/ESP32-DevKitC-VIB?qs=w%2Fv1CP2dgqqYaiigtkDvQw%3D%3D)<br>[ESP32-S3-DevKitC](https://eu.mouser.com/ProductDetail/Espressif-Systems/ESP32-S3-DevKitC-1U-N8?qs=Li%252BoUPsLEnt6p%252BOu3d2jKw%3D%3D) | [link](https://eu.mouser.com/ProductDetail/DFRobot/SEN0158?qs=lqAf%2FiVYw9hCccCG%252BpzjbQ%3D%3D) |
| Digikey (US)          | [ESP32-PicoKit](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-PICO-KIT-1/21572663) <br> [ESP32-S3-DevKitC](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-S3-DEVKITC-1-N8R2/15199627) | [link](https://www.digikey.com/en/products/detail/dfrobot/SEN0158/7087147?s=N4IgTCBcDaIDoBcAEBlAogOQAwEYCsAHCALoC%2BQA) |
| RobotShop (US)        | [FireBeetle ESP32](https://www.robotshop.com/products/firebeetle-esp32-iot-microcontroller) <br> [Arduino Nano ESP32](https://www.robotshop.com/products/arduino-nano-esp32-with-headers) | [link](https://www.robotshop.com/en/ir-tracking-camera.html) |
| TinyTronics (NL)      | [ESP32 Board](https://www.tinytronics.nl/shop/en/development-boards/microcontroller-boards/with-wi-fi/esp32-wifi-and-bluetooth-board-cp2102) <br> [Wemos LOLIN32](https://www.tinytronics.nl/shop/en/development-boards/microcontroller-boards/with-wi-fi/wemos-lolin32-esp32-cp2104) | [link](https://www.tinytronics.nl/shop/en/sensors/optical/infrared/dfrobot-gravity-ir-positioning-camera) |
| OpenCircuit (NL)      | [FireBeetle ESP32](https://opencircuit.shop/product/firebeetle-esp32-e-iot-microcontroller) <br> [Lilygo T7-S3](https://opencircuit.shop/product/lilygo-t7-s3-esp32-s3-development-board-wifi) | [link](https://opencircuit.shop/product/gravity-ir-positioning-camera-for-arduino) |
| Gotronic (FR)         | [NodeMCU ESP32](https://www.gotronic.fr/art-module-nodemcu-esp32-28407.htm) <br> [Seeed Studio XIAO ESP32S3](https://www.gotronic.fr/art-carte-xiao-esp32s3-36954.htm) | [link](https://www.gotronic.fr/art-camera-ir-de-positionnement-sen0158-22705.htm) |
| Botland (PL)          | [ESP32-DevKitC](https://botland.store/esp32-wifi-and-bt-modules/8893-esp32-wifi-bt-42-platform-with-module-5904422337438.html) <br> [ESP32-S3 DevKit](https://botland.store/esp32-wifi-and-bt-modules/23340-esp32-s3-dev-kit-n8r8-development-board-wifi-bluetooth-without-connectors-waveshare-24363.html) | [link](https://botland.store/arduino-rpi-cameras/19901-gravity-ir-positioning-camera-for-arduino-dfrobot-sen0158--5903351246330.html) |
| DFRobot (CN)          | [FireBeetle ESP32](https://www.dfrobot.com/product-1590.html) <br> [FireBeetle 2 ESP32-S3](https://www.dfrobot.com/product-2676.html) | [link](https://www.dfrobot.com/product-1088.html) |


## Instructions
The instructions for the basic sensor are really simple.<br>
Solder the wires of the DFRobot SEN0158 to the following pins:

| Wire Color    | Function  | ESP32 pin         | ESP32-S3 pin      |
|---------------|-----------|-------------------|-------------------|
| Red           | Power     | 3V3               | 3V3               |
| Black         | Ground    | GND               | GND               |
| Yellow        | SDA       | 21                | 8                 |
| Green         | SCL       | 22                | 9                 |

That's it. Any further additions to the sensor are up to you.