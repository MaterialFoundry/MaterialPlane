# Material Plane
Material Plane is a <a href="https://foundryvtt.com/">Foundry VTT</a> module that allows physical minis to be tracked by Foundry when using a horizontally mounted TV. This allows you to bring the joy of physical minis into Foundry.<br>
<br>
The system consists of an IR sensor, and IR enabled mini bases. These bases contain IR LEDs that are tracked by the sensor. The sensor then relays this information to foundry over WiFi, where the information is interpreted as token movement

[![Youtube Video](https://github.com/CDeenen/MaterialPlane/blob/master/Module/img/YoutubeVid.png)](https://youtu.be/y_IouB-SDnk "FoundryVTT IR Mini Control")

## Requirements
You need the following for this module to work:
<ul>
<li><b>Horizontally mounted TV</b></li>
<li><b>IR Sensor Module</b></li>
<li><b>Mount</b></li>
<li><b>IR Mini Bases</b></li>
</ul>
Currently you'll have to source everything yourself. I might consider selling parts or complete kits if there's enough demand (let me know if you'd be interested).

### IR Sensor Module
I recommend building the <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#full-sensor">full sensor unit</a>. But the module will work fine with just using a generic ESP32 and DFRobot IR sensor.<br>
See the above link for a full BOM and building instructions for the full sensor unit.

#### DFRobot SEN0158
The DFRobot SEN0158 is basically the camera from a WiiMote. You can get it from DFRobot themselves, or through various other retailers:<br><br>
DFRobot: https://www.dfrobot.com/product-1088.html <br>
Robotshop: https://www.robotshop.com/en/ir-tracking-camera.html <br>
Mouser: https://eu.mouser.com/ProductDetail/DFRobot/SEN0158?qs=lqAf%2FiVYw9hCccCG%252BpzjbQ%3D%3D <br>
DigiKey: https://www.digikey.nl/product-detail/nl/dfrobot/SEN0158/1738-1250-ND/7087147 <br>
TME: https://www.tme.eu/nl/details/df-sen0158/cameramodules/dfrobot/sen0158/ <br>
Gotronic: https://www.gotronic.fr/art-camera-ir-de-positionnement-sen0158-22705.htm <br>

#### ESP32
The ESP32 is a WiFi enabled microcontroller. It's a very capable chip, more than fast enough for our application.<br>
There are many different ESP32 variations available, most of them should work. We only need 4 pins:<br>
<ul>
<li><b>3.3V</b> - Should be available on all ESP32 boards</li>
<li><b>Gnd</b> - Should be available on all ESP32 boards</li>
<li><b>GPIO 21</b> - SDA pin, is available on most boards</li>
<li><b>GPIO 22</b> - SDL pin, is available on most boards</li>
</ul>
If you want to use the <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models/Sensor%20Enclosure">enclosure</a>, you will need an Adafruit TinyPICO. Sources:<br>
Adafruit: https://www.adafruit.com/product/4335 <br>
Core Electronics: https://www.adafruit.com/product/4335 <br>
Tinytronics: https://www.tinytronics.nl/shop/nl/communicatie/bluetooth/tinypico-esp32-pico-d4-wifi-en-bluetooth-board <br>

If you're not planning to use the enclosure, you can choose between many different modules. If you're unsure on what to get, get a TinyPICO, Node32 or Wemos LOLIN32.<br>

### Mount and Mini Bases
You'll need some way to mount the IR sensor above the TV. You could attach it to the ceiling, or use a microphone stand.<br>
In the <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models">3D models section</a> you can find 3D models for both an enclosure (encloses the sensor and ESP32) and a simple sensor-only mount. Both made for use with a microphone stand.<br>
In that same section, you can also find 3D models of the mini bases.<br>
<br>
Instructions can be found in the <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#ir-bases">readme</a> within the 3D models section.

# Theory of Operation
TLDR: You press a switch on the mini's base, the corresponding token moves.<br>
<br>
Minis are placed on top of 3D printed bases that contain IR LEDs. These LEDs are powered by a CR2032 battery that's located in the base, and the LED is switched on using a small switch on the side of the base. An IR sensor (DFRobot SEN0158), which is basically a stand-alone WiiMote camera, interfaces with an ESP32 microcontroller using I2C, and gives the coordinates and intensity of up to 4 IR points.<br>
To move a token, the switch on the base is pressed, turning on the LED, which is then tracked by the IR sensor. The sensor gives coordinates relative to the sensor's field of view, and are inaccurate due to perspective (the sensor won't be exactly above the TV), so the microcontroller performs a homography transform to project these points on a flat plane (it requires a calibration procedure to find the edge of the screen, by measuring 4 points). Using this calibration, you can place the sensor anywhere, and at any angle, as long as the sensor can see the whole screen.<br>
The calibrated coordinates can then be mirrored or rotated to correspond with the on-screen coordinate system. So in the end, the microcontroller sends out X and Y coordinates between 0 and 1023, relative to the screen, and an intensity value (0-255) over a websocket to Foundry.<br>
Foundry then searches for tokens that are close enough to these coordinates, selects the right token, and moves the token so it follows the physical mini.

# Usage

Please make sure you've done the following:<br>
<ul>
<li>Got all the components for the sensor module: <a href="https://github.com/CDeenen/MaterialPlane#ir-sensor-module">minimal</a> or <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#full-sensor">full sensor</a></li>
<li>Build the enclosure, or some other way to mount the sensor: <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#sensor-mount">minimal</a> or <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#build-instructions-1">full sensor</a></li>
<li>Installed the <a href="https://github.com/CDeenen/MaterialPlane/tree/master/Arduino#arduino-code">Arduino code</a></li>
<li>Made one or more <a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#ir-bases">IR bases</a></li>
<li>Installed the Foundry module</li>
</ul>

Once everything has been set up in foundry (see below), the module is simple to use.<br>
For each mini that you want to track, you need an IR base. Simple place the mini on top, making sure that the LED is always oriented in the same way (the same way you did when calibrating, see below). Simply press the switch on the base, move the mini to its new location, and release the switch.

## Module Settings
In the module settings screen, you can find the following settings:
<ul>
<li><b>Enable Module</b> - Enables the module</li>
<li><b>Movement Method</b> - You can select between two different movement methods. The first (<b>Default</b>), will behave identical to the default Foundry movement: you drag the token, and vision is only updated after releasing the token. The second method (<b>Step-by-Step</b>) will divide the movement into steps of 1 gridsize, which means that the movement and vision is updated constantly</li>
<li><b>Deselect Token After Drop</b> - Automatically deselects the token once you release the switch. Works great in combination with the 'Hot Seat' module, because it will default to the shared view</li>
<li><b>Non-Owned Movement</b> - Allows the movement of non-owned tokens, without being able to see their vision. Useful if NPC minis are being tracked</li>
<li><b>Target Name</b> - Player name of the client that has the TV connected. Is set to 'Observer' by default, just as the 'Hot Seat' module</li>
<li><b>Hide Display Elements</b> - Hides all display elements on the target client to give a clean view</li>
<li><b>Sensor Module IP</b> - IP address of the sensor module. More information <a href="https://github.com/CDeenen/MaterialPlane/tree/master/Arduino/IRsensor">here</a></li>
</ul>

![moduleSettings](https://github.com/CDeenen/MaterialPlane/blob/master/Module/img/ModuleSettings2.png)

[![Youtube Video2](https://github.com/CDeenen/MaterialPlane/blob/master/Module/img/SettingsVid.png)](https://youtu.be/sQxz6mdJcq8 "Settings Video")

## Calibration Menu
Before the module can be used, it has to be calibrated. The calibration values are stored, so a recalibration is only necessary when either the sensor, or the TV has been moved.<br>
<br>
You can access the calibration menu from the game settings on the right of the GM's screen. There should be a new button.<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/Module/img/CalibrationButton.png" width="250">

<br>
The calibration menu has 3 sections: Coordinates, Settings, and Calibration

### Coordinates
This section gives an overview of what the sensor can see (in the calibrated state).<br>
On the left, you can see a table with shows the coordinates and intensity of all 4 IR dots that can be tracked, and on the right you can see a box in which these dots are displayed.<br>
Both are updated in real-time, and can therefore be used to position the sensor relative to the TV.<br>
Once you have mounted the sensor, you should use one of your IR bases to test if all corners of the TV are within the sensor's range. Please make sure that you have disabled the previous calibration (see below).

### Settings
Here you can change the settings of the sensor. <br>
You can mirror in both X and Y direction, rotate the data (switch X and Y), and change the sensitivity of the sensor.<br>
Use the data in the 'Coordinates' section above to determine how you should set these settings. When you move the IR base right, the dot in the square should also move right (otherwise click 'Mirror X'), when you move the IR base up, the dot should also move up (otherwise click 'Mirror Y'), and when you move up, but the dot moves left or right, click 'rotate' (you might have to redo the mirror settings).<br>
Based on the 'intensity' value you can increase or decrease the sensitivity. You might have to try different settings, because the sensitivity response is a bit strange at the moment.

### Calibration
You use this section to actually calibrate the sensor.<br>
You can see a small dot, which indicates whether the sensor is currently calibrated (might be an old calibration, though). On the right you can find the 'Disable Calibration' button, which disables the calibration.<br>
On the bottom you can find the calibration method. You can select between 'Single Point' and 'Multipoint' calibration:
<ul>
<li><b>Single Point Calibration</b> - You calibrate all four corners of the TV, on point at a time. You place the IR base exactly on one of the corners (the center of the base should align with the corner), press the button, and repeat this process for all 4 corners. There's an on-screen box to show you how many points you're calibrated, so you can see whether each measurement was succesful</li>
<li><b>Multipoint Calibration</b> - With multipoint calibration, you don't have to calibrate all four points every time you move either the sensor or the TV. In order to use this method, you'll need permanently mounted IR LED's near each corner of the TV (doesn't have to be exactly on each corner, but fairly close). You will need to do a single point calibration the very first time you use this (make sure you've switched the 4 LEDs off), and once you're done that, the sensor will know the position of the screen, compared to the 4 LEDs, so it only needs the 4 LEDs to do a full calibration. You simply switch the LEDs on, press 'calibrate', and you're done.</li>
</ul>

<b>Note: </b>When calibrating, you need to have the IR bases oriented in the same way for all calibration points, and for the use afterwards. Using the bases downloaded from this page, you'll probably want the switch on the right, so the LED will be in the top right. You have to keep this orientation always, so do not rotate the base, or the sensor's measurement will be off!

![calibrationMenu](https://github.com/CDeenen/MaterialPlane/blob/master/Module/img/CalibrationMenu.png)

# Suggested Other Modules
Foundry is made for digital play, but there are some modules available that might enhance your experience when using physical minis:
<br>
<br>
<a href="https://github.com/Zzarek/FoundryHotSeatObserver">Hot Seat Observer</a><br> - Mainly useful to hide icons<br>
<br>
<a href="https://github.com/CDeenen/LockView">Lock View</a><br> - Gives the GM full control over panning and zooming of connected clients, including disabling panning and zooming. Since you're using a TV with minis on top, you probably don't want to accidentally zoom and pan, because then your minis no longer correspond with what's on the TV.

## Software Versions & Module Incompatibilities
<b>Foundry VTT:</b> Tested on 0.6.6<br>
<b>Module Incompatibilities:</b> When moving tokens, Foundry's click and drag system is bypassed. So modules that depend on that functionality might not work.<br>

## Feedback
If you have any suggestions or bugs to report, feel free to contact me on Discord (Cris#6864), or send me an email: cdeenen@outlook.com.

## Credits
<b>Author:</b> Cristian Deenen (Cris#6864 on Discord)<br>