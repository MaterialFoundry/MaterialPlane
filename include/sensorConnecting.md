To use the Material Plane sensor, there needs to be communication between the sensor and the VTT.<br>
There are 2 ways to do this:

* <b>WiFi:</b> The sensor connects to your (2.4GHz) WiFi network. The VTT can connect directly to it, and you can access the [webserver](webserver.md) for configuration. Multiple VTT clients (for example, both the display and gm clients) can connect to the sensor.
* <b>USB:</b> The sensor connects over USB. WiFi setup is not required, but [Material Companion](https://github.com/MaterialFoundry/MaterialCompanion) is required for the connection. Only 1 VTT client can connect to the sensor (this should be the display client).

Connecting over WiFi is the most convenient, but might not be possible for your situation.

This page will only explain how to connect the sensor to a WiFi network. For connecting a VTT to the sensor, either using WiFi or USB, please check the 'VTT Configuration' section.

## Connecting to WiFi Network
To connect to a WiFi network, the sensor needs to know the SSID (network name) and password of the network. There are 3 ways to do this:

### Connect to WiFi Using Material Companion
You will need to [install Material Companion](https://github.com/MaterialFoundry/MaterialCompanion/wiki/Installation).

1. Connect the sensor to your computer using a USB-C cable
2. Open Material Companion and navigate to the 'Sensor' sub-tab in the 'Material Plane' tab
3. At the top, select the correct 'Sensor USB Port'.
    * The production sensor will show up as 'COM## (Sensor)' or 'COM## (Sensor - Update) If it doesn't show up, try refreshing the USB ports.<br>If it shows up as 'COM## (Sensor - Update)' press the 'reset' button. After refreshing the USB ports it should show up as 'COM## (Sensor)'.
    * The DIY sensor will show up as 'COM##'. There may be multiple 'COM##' ports, see [here](#finding-the-correct-usb-port) if you are unsure which one is the correct one.
4. In the 'Configuration' section, press the 'Read' button at the bottom and wait a few seconds. If the connection is successful all the configuration fields should be filled in.
5. Press the 'Connect' button, which will open a popup.
6. You can scan for nearby WiFi networks by pressing the 'Scan' button, this might take a while.
7. Select the network you want the sensor to connect to, which will fill in the 'SSID' field with the SSID of the network. Alternatively, you can skip the scanning and directly fill in the SSID.
8. Fill in the password of the network.
9. Press 'Connect', the sensor will now restart and attempt to connect to the network.

### Connect to WiFi Using the Webserver
If the sensor is not able to connect to a WiFi network, it will host its own network. By default it will be called 'materialsensor', however, if you have checked the name of the device the name might be different.<br>
![Screenshot](../../img/webserver/Webserver_AccessPoints.png){align=right width=33%}

1. Connect to the sensor's access point, the password is 'Material Foundry'. Wait for the connection to complete (this might take a while).
2. In a browser, navigate to <a href="http://192.168.4.1">http://192.168.4.1</a>.
3. Once the webserver has loaded, navigate to the 'Network' tab.
4. In the 'Access Points' section, you can scan for nearby WiFi networks by pressing the 'Scan' button, this might take a while.
5. Select the network you want the sensor to connect to, which will fill in the 'SSID' field with the SSID of the network. Alternatively, you can skip the scanning and directly fill in the SSID.
6. Fill in the password of the network.
7. Press 'Connect', the sensor will now restart and attempt to connect to the network.

### Connect to WiFi Using USB
You can connect to the sensor over the USB port, and send and receive data over serial.<br>
You could use the built-in [Arduino](https://www.arduino.cc/) serial monitor (open the app, the serial monitor is the button at the top-righ with magnifyng lens icon) or a generic terminal emulator like [YAT](https://sourceforge.net/projects/y-a-terminal/).

See the table below for the correct settings:

|                       | Arduino Serial Monitor    | Generic Terminal Emulator     |
|---                    |---                        |---                            |
| Baud Rate             | 115200                    | 115200                        |
| Termination Character | Both NL & CR              | NL & CR or <CR\><LF\> or \n\r |
| Data Bits             | -                         | 8                             |
| Parity                | -                         | None                          |
| Stop Bits             | -                         | 1                             |
| Flow Control          | -                         | None                          |

If the connection is succesfull, the sensor should output continuous data, for example:<br>
`{"status":"ping","source":"main"}`<br>
Which is transmitted every half second.<br>
You might notice a very rapid output like the following:<br>
`{"status":"IR data","detectedPoints":1,"id":0,"command":0, ...}`<br>
This means that the sensor is detecting some infrared point. It would be helpful to make sure the sensor cannot see any infrared light, so either point it in another direction, or cover the front window.

To scan for WiFi Networks, send `SCAN WIFI`, after a few seconds a list of access points should show up, similar to the image below.

To connect to an access point, send:<br>
`CONNECT WIFI "[SSID]" "[password]"`<br>
Replace `[SSID]` and `[password]` with the actual SSID and password. Do not include the square brackets, but do include the quotation marks.

For example, to connect to an SSID named `My SSID` with password `Password` send:<br>
`CONNECT WIFI "My SSID" "Password"`

![Screenshot](../../img/misc/Serial_Scan_Wifi.png){}

### Sensor Address
To connect the sensor to the VTT, or to access the webserver you need to know the (IP) address of the sensor.<br>
The sensor will have an IP address of the form `x.x.x.x` (for example: `192.168.1.10`), and a DNS name which is the device name with `.local` appended (for example: `materialsensor.local`).

By default, the device name is `materialsensor`, but this can be changed in the [network](webserver.md#network-tab) tab of the webserver, where you can also find the IP address.

Another way to find the device name and IP address is using Material Companion. Read the sensor configuration as described [here](#connect-to-wifi-using-material-companion) (follow it up until point 4) and you can find the IP address and the name in the configuration fields.

Lastly, you can get the data using a terminal emulator. Configure the terminal emulator as described [here](#connect-to-wifi-using-usb).<br>
When you send `STATUS`, a long list of settings is printed. Under the 'WiFi' section, look for 'IP Address' and 'Device Name'.

{% include 'findingComPort.md' %}