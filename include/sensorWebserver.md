{% if variant == 'production' %}
![Screenshot](../../img/webserver/Webserver_Status_Tab.png){align=right width=33%}
{% else %}
![Screenshot](../../img/webserver/Webserver_Status_Tab_DIY.png){align=right width=33%}
{% endif %}

The sensor hosts its own webserver which can be used to check the status of the sensor, update the firmware and configure the sensor.<br>
The webserver is only available if the sensor is connected to WiFi.

To access the webserver, open a browser and navigate to the `http://[sensor address].local` or `http://[sensor IP]`.<br>
You can get info on finding either [here](sensorConnecting.md#sensor-address).

By default, <a href="http://materialsensor.local">http://materialsensor.local</a> should work, if not, make sure the device name is the same or fall back to using the sensor IP address (for example `http://192.168.1.10`).

Make sure the address starts with `http://` not `https://`.

Once the browser has loaded the webserver, it will try to open a websocket connection, please wait a few seconds, after which the webserver should be fully loaded.

## Status Tab
The status tab gives an overview of the sensor status, allows the firmware to be updated, the sensor to be reset to its default values, and the sensor to be restarted.

<b>Status</b><br>
{% if variant == 'production' %}
![Screenshot](../../img/webserver/Webserver_Status.png){align=right width=33%}
{% else %}
![Screenshot](../../img/webserver/Webserver_Status_DIY.png){align=right width=33%}
{% endif %}

* <b>Hardware Variant:</b> The hardware variant of the sensor (for example 'Production' or 'DIY Basic').
* <b>Firmware Version:</b> The current version of the firmware.
* <b>Webserver Version:</b> The current version of the webserver.
* <b>Uptime:</b> The time in hours and minutes the sensor has been on.
* <b>Debug Enable:</b> If enabled, the sensor will output debug data to the [console](#console-tab) or the USB port.
* <b>Serial Output:</b> If enabled, the sensor will output data over the USB port.

<b>Battery</b><br>
{% if variant == 'production' %}
![Screenshot](../../img/webserver/Webserver_Battery.png){align=right width=33%}
{% else %}
![Screenshot](../../img/webserver/Webserver_Battery_DIY.png){align=right width=33%}
{% endif %}

* <b>Charging State:</b> The current charging state.
* <b>Percentage:</b> The estimated remaining battery percentage.
{% if variant == 'production' %}
* <b>Time to Empty:</b> Estimated time in hours and minutes until the battery is empty, see below.
* <b>Time to Full:</b> Estimated time in hours and minutes until the battery is full, see below.
{% endif %}

<b>Battery (Advanced)</b><br>
{% if variant == 'production' %}
There is an advanced battery section that can be expanded by clicking on it.

* <b>Voltage:</b> The battery voltage.
* <b>Current:</b> Current drain of the battery (negative means battery draining, positive means the battery is charging).
* <b>Capacity:</b> Estimated battery capacity (current/maximum).

<b>Time to Empty/Full</b><br>
The sensor can give an estimated time to empty or time to full.<br>
Please note that these values can be way off. The sensor will slowly learn the battery behavior which will improve the estimate, however, when the sensor has just started up, the sensor just started or stopped charging, or when the battery configuration has just been reset (see below), the values will be inaccurate.

{% else %}
The full DIY sensors have an advanced section that can be expanded by clicking on it.

* <b>Voltage:</b> The battery voltage.
{% endif %}

<b>Lower section</b><br>
![Screenshot](../../img/webserver/Webserver_Status_LowerSection.png){align=right width=33%}

* <b>Update:</b> Opens a new window to update the sensor. See [here](../Updating/sensorUpdating.md#webserver) for more info.
* <b>Reset Settings to Default Values:</b> Opens a new window to reset some or all of the sensor settings. See below for more info.
* <b>Restart Sensor:</b> Restarts the sensor.

<b>Resetting Sensor Settings</b><br>
Pressing the 'Reset' button will open a new popup where you can reset sensor settings back to their defaults.

You can choose one or more of the following:
![Screenshot](../../img/webserver/Webserver_Reset.png){align=right width=33%}

* <b>IR Configuration:</b> If ticked, will reset all settings related to the detection of IR points (everything configurable in the 'IR Tracker' tab).
* <b>Battery:</b> If ticked, will reset the battery configuration. The sensor will learn the battery behavior over time to make more accurate estimates. If the battery configuration is reset, it will clear this stored behavior. This is required if a new battery is inserted or if the battery values are very inaccurate.
* <b>Network Settings:</b> If ticked, will reset all settings related to the network, such as the network to connect to. This will disconnect the sensor from the current WiFI network and requires this to be reconfigured.

By pressing 'Ok' the ticked configurations will be reset and the sensor will restart.

## Network Tab

<b>Network Status</b><br>
![Screenshot](../../img/webserver/Webserver_NetworkStatus.png){align=right width=33%}

* <b>Connection Status:</b> Indicates if the sensor is connected to a WiFi network.
* <b>SSID:</b> The network the sensor is connected to, or configured to connect to.
* <b>IP Address:</b> The IP address of the sensor.
* <b>Name:</b> The name of the sensor.

<b>Access Points</b><br>
Here you can scan for and connect to a WiFi network.

Follow the instructions (starting from #4) [here](sensorConnecting.md#connect-to-wifi-using-the-webserver).

<b>Websocket</b><br>
![Screenshot](../../img/webserver/Webserver_Websocket.png){align=right width=33%}

Status of the websocket server that the sensor hosts.<br>
It displays how many clients are connected and their IP addresses. These could be from browsers accessing the webserver or from VTT clients.

## IR Tracker Tab
This tab is used to configure the [sensor settings](sensorSettings.md).

## Console Tab
![Screenshot](../../img/webserver/Webserver_Console.png){align=right width=33%}
The console tab is meant for debugging. If 'debug enable' is ticked in the [status tab](#status-tab), the sensor will send debug messages to the console.

Messages can be sent to the sensor at the bottom, the 'Clear' button clears the console, 'Autoscroll' enabled or disables the automatic scrolling, and 'Show timestamp' will prepend each message with the time it was received.