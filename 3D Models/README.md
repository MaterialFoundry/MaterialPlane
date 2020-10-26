# 3D Models
These are the 3D models that you can use for your setup.<br>
<br>
<b>Instructions:</b><br>
<a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#ir-bases">IR bases</a><br>
<a href="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/README.md#full-sensor">Full sensor</a><br>
<a href="https://github.com/CDeenen/MaterialPlane/tree/master/3D%20Models#sensor-mount">Simple sensor mount</a><br>

# IR Bases
This is a collection of bases onto which you can place or glue your minis. They use a CR2032 battery, a microswitch and a 3mm IR LED.<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/Bases.jpg" width="500">

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/MiniWithBase.jpg" width="500">

### BOM
1x Base<br>
1x 3mm IR LED<br>
1x CR2032 battery<br>
1x Microswitch<br>
1x Felt that's big enough to cover the bottom of the base<br>
Soldering iron<br>
Solder<br>
Wire cutter<br>
Superglue<br>

All components should be easy to find, except for the microswitch. Unfortunately I do now know the manufacturer or part number, because I bought it off eBay. If you search for 'switch 3x6x5', you should be able to find it. Just make sure it looks like the one in the photo below. You should be able to get them really cheap (approx. $0.10 each).

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/Switches.jpg" width="500">

### Build Instructions
Currently, the only available bases are ones designed to be printed with a resin printer. The features around the LED are very thin, making it difficult to print using FDM, though with a small nozzle, it might be possible. If you do not own a 3D printer, and you do not know anyone who does, you could try 3D printing services like <a href="https://https://www.3dhubs.com">3D Hubs</a>, or try a 3D printing Facebook group. I might consider selling bases in the future, please let me know if you'd be interested.<br>
<br>
-Glue the switch in place. Try to push it as far to the outside as possible, and make sure the top is flush with the printed part<br>
-LEDs have a positive (anode) and negative (cathode) connection. They can be distinguished by the length of the leads, because the positive one is longer. Looking from the bottom, with the LED hole at the top, push the LED in the hole, with the negative (shorter) lead on the right side<br>
-Bend the negative lead so it fits in the groove, and cut it to length, so it's about as long as the groove<br>
-Bend the positive lead so the lead touches the nearest contact on the switch. Cut the lead to size, so it can just touch the switch's lead<br>
-Solder the positive lead to the switch contact<br>
-Use the excess of the lead you just cut off, and solder it to the other contact of the switch<br>
-Bend the excess through the channel, in such a way that the lead ends up in the center area, bent upwards<br>
-Insert the CR2032 battery, positive side facing up<br>
-Attach the felt, and cut to size<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/BaseBottom.jpg" width="500">
<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/BaseBottomBattery.jpg" width="500">

# Full Sensor

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/FullSensor.jpg" width="500">

A basic (ESP32 + IR sensor) sensor will work fine in practise, but you could add some extra's by using the full sensor.<br>
Additional features: <br>
<ul>
<li>Battery powered</li>
<li>Connection status led</li>
<li>Battery charging state LED/low battery waarning LED</li>
<Li>Full enclosure</li>
</ul>

The full sensor has 1 switch and 2 status LEDs.<br>

#### Switch
The switch switches the battery on, or off (the sensor is always on if it's powered by USB).<br>

#### Battery status indicator (left LED)
If on battery power:<br>
<b>Green</b> - Battery OK<br>
<b>Red</b> - Low battery<br>
<br>
If on USB power:<br>
<b>Off</b> - No battery connected/battery switched off<br>
<b>Blinking red</b> - Battery charging<br>
<b>Green</b> - Battery fully charged<br>
<br>
Using a 2000mAh, the low battery warning switched on after around 21 hours, with another 2.5 hours of battery life left.

#### Connection status indicator (right LED)
<b>Green</b> - Connected to at least 1 client<br>
<b>Red</b> - No connection<br>

## BOM
<ul>
<li>3D printed parts</li>
<li>1x DFRobot SEN0158</li>
<li>1x TinyPICO</li>
<li>2x 5mm Red/Green common cathode LED</li>
<li>2x 180 ohm resistor</li>
<li>1x 12K resistor</li>
<li>1x 22K resistor</li>
<li>1x switch</li>
<li>1x Li-Po battery (max size: 35x53x11mm)</li>
<li>9x M3x8mm countersunk bolts</li>
<li>1x M5x22mm bolt</li>
<li>1x M5 nut</li>
</li>

## Sourcing parts
<b>DFRobot SEN0158</b><br>
DFRobot: https://www.dfrobot.com/product-1088.html <br>
Robotshop: https://www.robotshop.com/en/ir-tracking-camera.html <br>
Mouser: https://eu.mouser.com/ProductDetail/DFRobot/SEN0158?qs=lqAf%2FiVYw9hCccCG%252BpzjbQ%3D%3D <br>
DigiKey: https://www.digikey.nl/product-detail/nl/dfrobot/SEN0158/1738-1250-ND/7087147 <br>
TME: https://www.tme.eu/nl/details/df-sen0158/cameramodules/dfrobot/sen0158/ <br>
Gotronic: https://www.gotronic.fr/art-camera-ir-de-positionnement-sen0158-22705.htm <br>
<br>
<b>TinyPICO</b><br>
Adafruit: https://www.adafruit.com/product/4335 <br>
Core Electronics: https://core-electronics.com.au/tinypico-esp32-development-board.html <br>
Tinytronics: https://www.tinytronics.nl/shop/en/communication/bluetooth/tinypico-esp32-pico-d4-wifi-and-bluetooth-board <br>
<br>
<b>Battery</b><br>
Must be 35x53x11mm or smaller. You can get batteries with capacities of up to 2000mAh within that size, such as:<br>
https://www.tinytronics.nl/shop/en/batteries/li-po/li-po-accu-3.7v-2000mah-jst-ph <br>
<br>
Unfortunately, the sensor isn't able to fully deplete the battery on use, because the TinyPICO has no boost circuitry, so it is considered empty when the voltage drops to around 3.7V. However, after doing an endurance test, the 2000mAh battery I used lasted for around 23:30 hours, so you could probably get away with a 1000 to 1500mAh battery even for the longest gaming sessions.<br>

<br>
<b>Switch</b><br>
Unfortunately I don't have a manufacturer or parts number for these switches, because I bought them on eBay. If you search for "spdt miniature slide switch black" on eBay, and match the picture with the one below, you should be fine.<br>
<br>
<b>Other pars</b><br>
The other parts can be generic. Here is what I used:<br>
LED: https://www.tinytronics.nl/shop/en/lighting/led/rg-led-5mm-green-en-red-diffuse-common-cathode <br>
Resistors: Normal wired 1/4W resistors, can be found at any electronic component supplier<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/Switches2.jpg" width="500">


## Build Instructions

<b>1.</b> Clean the enclosure, and make sure all components fit. Especially the IR sensor and the TinyPICO might be a tight fit (see the images below for the proper placement and positioning). If necessary, cut away small parts of the enclosure with a sharp knife, to make room for the components. You might have to drill out the LED holes with a 5mm drill, if they do not fit.<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/EmptyEnclosure.jpg" width="500">

<b>2.</b> Grab an M3 bolt, and screw it into all the holes, to form the thread. It should give some resistance (and the bolt will get hot, so you might have to let it cool down between holes), but it should be possible without too much problems.<br>
<br>
<b>3.</b> Cut the length of the cable of the IR sensor to around 5 cm, and remove the outer sleeve.<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/SensorCutWires.jpg" width="500">

<b>4.</b> (Optional) Remove the LED inside the IR sensor by prying open the top, removing the circuit board, and desoldering the LED. This will reduce the power consumption by around 20 mA, increasing battery life. When done, insert the circuit board and wrap some tape around the end of the sensor to prevent the circuit board from falling out<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/RemoveLED1.jpg" width="500">
<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/RemoveLED2.jpg" width="500">
<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/RemoveLED3.jpg" width="500">

<b>5.</b> Solder the 4 wires from the IR sensor to the TinyPICO:<br>
Red to 3.3V<br>
Black to GND (next to RST)<br>
Green to pin 22<br>
Yellow to pin 21<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/SensorWiring.jpg" width="500">

<b>6.</b> Take the two LEDs and two 180 ohm resistors. Bend the 3 legs of each LED at a 90 degree angle. Cut the center pin (common cathode) pin to a length of around 5 mm, and do the same with one end of each resistor. Then solder the resistor to the center pin of the LED. Take 2 red and 2 green wires (cut them from the remaining IR sensor wire), and cut them to a length of around 8 cm. Solder the green wires to the leg of the LED that's connected to the green LED (check the datasheet), and do the same for the red wires and the red LED's leg.<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/LEDWiring.jpg" width="500">

<b>7.</b> Solder the red and green wires to the TinyPICO:<br>
LED1 red wire to pin 26<br>
LED1 green wire to pin 25<br>
LED2 red wire to pin 15<br>
LED2 green wire to pin 27<br>
<b>Note:</b> In the image below I switched the red and green wires around, due to a wiring mistake. Please use the pin numbers above.<br>
<br>
<b>8.</b> Solder one leg of the 12K and 22K resistors together. Solder the other leg of the 22K resistor to GND (next to 5V), and the other leg of the 12K resistor to 5V. Cut a wire to around 4 cm (I used green in the image below), and solder that wire to the connection between the two resistors, and pin 32.<br>
<br>
<b>9.</b> Solder the positive (red) wire of the battery to BAT, and the solder a 8 cm long black wire to GND (solder it to the leg of the 22K resistor).<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/TinyPICOWiring.jpg" width="500">

<b>10.</b> Carefully glue to switch to the enclosure (see below for position). You can use superglue, or similar. Be careful to only glue the sides, you don't want any glue in the switch, or it might not work anymore.<br>

<b>11.</b> Push the two LEDs into the holes close to the switch (LED1 to the left in the image, LED2 to the right). It should be a friction fit, but if they are loose, you can glue them. Make sure to push them as far as they will go.<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/LEDsNextToSwitch.jpg" width="500">

<b>12.</b> Solder the two resistors to the center lug of the switch, and solder the black wire connected to GND on the TinyPICO to the same lug. Solder the negative (black) wire of the battery to the top lug of the switch as seen in the image (wiring not shown in image below, but look at the orientation).<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/SwitchWired.jpg" width="500">

<b>13.</b> Slide the IR sensor into its cavity (from the inside) until it sticks out the front, place the TinyPICO in its spot. Clamp the TinyPICO down with the 'ControllerBracket' (don't overtighten), and loosely screw the 'SensorBracket' down. The sensor should still be able to rotate.<br>

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/Brackets.jpg" width="500">

<b>14.</b> Connect the USB cable to the TinyPICO and upload the Arduino code (<a href="https://github.com/CDeenen/MaterialPlane/tree/master/Arduino">instructions here</a>).
<br>

<b>15.</b> Install and enable the Foundry module, go to the module settings, tick "Enable module" and fill in the IP address that you got in the previous step. The sensor should now connect to Foundry (you should get a notification in Foundry, and the right LED should turn green, if not, please try refreshing or check the IP address).
<br>

<b>16.</b> Go into the calibration menu (in the game settings menu on the right), make sure you've deselected 'Mirror X', 'Mirror Y' and 'Rotation'. Use some IR source (could be an IR base, or a remote control) and point it at the sensor, and you should see a red dot appear. Play around with the sensitivity settings until you get a single stable dot.<br>
<br>
<b>17.</b> Make sure the enclosure is laying flat, and move the IR source horizontally. Rotate the sensor inside the enclosure until the dot in the calibration screen also moves horizontally. Then screw it down properly.<br>
<br>
<b>18.</b> Insert the battery inside the enclosure, screw down the lid, and use an M5 bolt and nut to attach the mount.

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/Battery.jpg" width="500">

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/Lid.jpg" width="500">

# Sensor Mount
This is a simple sensor mount, that can be screwed on a microphone stand, and holds the sensor. It consists of 2 parts, held together with an M5x22mm bolt. Can be printed with either a FDM or resin printer.

<img src="https://github.com/CDeenen/MaterialPlane/blob/master/3D%20Models/img/SensorMount.jpg" width="500">

### BOM
1x Micstand Mount<br>
1x Sensor Mount<br>
1x M5x22mm bolt<br>
1x M5 nut<br>
