The sensor can be updated in 4 ways:

* Using [Material Companion over WiFi](#material-companion-wifi)
* Using [Material Companion with a USB cable](#material-companion-usb)
* Using the [sensor webserver](#webserver)
* Using the [Arduino IDE](#arduino-ide) (USB or WiFi)

{% if variant == 'diy' %}<b>The first time uploading the firmware to the sensor, you must upload using a USB cable (either using Material Companion or the Arduino IDE).</b>{% endif %}

The sensor has 2 different things that require separate updates:

* <b>Firmware:</b> This is the code that is responsible for almost everything the sensor does, except for the webserver
* <b>Webserver:</b> This is the code that is responsible for the webserver

These may or may not receive updates at the same time. Depending on the update method you will either have to update these separately or they can be updated at the same time.

### Finding the Current Version
You can find the versions of the firmware and webserver that are installed on your sensor in one of the following ways:

* <b>Using Material Companion:</b> The versions can be reported in the [Sensor](https://materialfoundry.github.io/MaterialCompanion/materialPlane/#sensor) tab.
* <b>Using the Sensor's Webserver:</b> The versions will be displayed on the [Status](../SensorConfiguration/webserver.md#status-tab) tab.
* <b>Using the Module's Downloads Tab:</b> The versions will be displayed in 'Current' column on the [Downloads](../Foundry/foundryConfig.md#downloads) tab of the Material Plane configuration screen.

### Finding the Latest Version
You can find the latest versions of the firmware and webserver in one of the following ways:

* <b>Using Material Companion:</b> The latest versions are displayed in the 'Update' section in the [Sensor](https://materialfoundry.github.io/MaterialCompanion/materialPlane/#sensor) tab.
* <b>Using the Module's Downloads Tab:</b> The latest versions will be displayed in 'Latest' column on the [Downloads](../Foundry/foundryConfig.md#downloads) tab of the Material Plane configuration screen.
* <b>Using GitHub's Releases Page:</b> The [Releases Page](https://github.com/MaterialFoundry/MaterialPlane_Sensor/releases) on GitHub will list all the latest releases.

## Material Companion (WiFi)

<b>This method requires the firmware of the sensor to be v3.0.4 or later.</b><br>
Material Companion has the option to update the sensor over your WiFi connection. For this to work, you will need to [connect the sensor to your WiFi network](../SensorConfiguration/sensorConnecting.md).<br>
You will need to update the firmware and webserver separately.

![Screenshot](../../img/materialCompanion/MaterialCompanion_Sensor_WiFi_Update.png){width=50%}

1. Open Material Companion and navigate to the 'Sensor' sub-tab within the 'Material Plane' tab.
2. At the bottom 'Update' section, select either 'WiFi - Firmware' or 'WiFi - Webserver' at 'Update Method'
3. At 'Sensor Address' fill in the address of the sensor. By default this is 'materialsensor.local', but this is configurable in the [sensor configuration](../SensorConfiguration/webserver.md#network-tab). You could also fill in the sensor IP address, for example '192.168.1.20'
4. Select the correct hardware variant of your sensor at 'Variant'
5. At 'Firmware Version' and 'Webserver Version', select the version you want to update to the sensor
6. Optionally, you could tick 'Show Pre-Releases' which will allow you to update a pre-release version (not recommended for normal use)
7. Press the 'Update' button
8. A popup will appear that gives the update progress, you can press 'Details' to get more details about the progress.

    ![Screenshot](../../img/materialCompanion/MaterialCompanion_Sensor_Update_Progress.png){align=center}

9. If the update went succesfull the sensor will restart

## Material Companion (USB)

Material Companion has the option to update the sensor over USB.<br>
You can update the firmware, the webserver, or both.

![Screenshot](../../img/materialCompanion/MaterialCompanion_Sensor_USB_Update.png){width=50%}

1. Open Material Companion and navigate to the 'Sensor' sub-tab within the 'Material Plane' tab.
2. At the top, select the correct 'Sensor USB Port'.
    * The production sensor will show up as 'COM## (Sensor)' or 'COM## (Sensor - Update) If it doesn't show up, try refreshing the USB ports.<br>If it shows up as 'COM## (Sensor)' press and hold the 'boot' button, then press the 'reset' button and release the 'boot' button. After refreshing the USB ports it should show up as 'COM## (Sensor - Update)'.
    * The DIY sensor will show up as 'COM##'. There may be multiple 'COM##' ports, see [here](#finding-the-correct-usb-port) if you are unsure which one is the correct one.
3. At the bottom 'Update' section, select 'USB' at 'Update Method'.
4. Select the correct hardware variant of your sensor at 'Variant'.
5. At 'Firmware Version' and 'Webserver Version', select the version you want to update to the sensor. You can set one to 'none' to prevent one from updating.
6. Optionally, you could tick 'Show Pre-Releases' which will allow you to update a pre-release version (not recommended for normal use).
7. Press the 'Update' button.
8. A popup will appear that gives the update progress, you can press 'Details' to get more details about the progress.

    ![Screenshot](../../img/materialCompanion/MaterialCompanion_Sensor_Update_Progress.png){align=center}

9. If the update went succesfull you can restart the sensor.

## Webserver
The firmware or webserver can be updated from the sensor webserver. You will have to update them separate from each other.

1. Download the latest webserver (Webserver.bin) or firmware (Sensor_[variant]_Firmware.bin) from [here](https://github.com/MaterialFoundry/MaterialPlane_Sensor/releases).
2. Navigate to the [sensor webserver](../SensorConfiguration/webserver.md).
3. Press the 'Update' button at the bottom of the 'Status'tab, this will navigate you to the update page.
4. Select either 'Firmware' or 'Webserver', depending on which you want to update.
5. Browse for the firmware or webserver file.
6. The sensor will now be updated and will restart when its done.

![Screenshot](../../img/webserver/Webserver_Update.png){align=center}

## Arduino IDE
The Arduino IDE gives you the option to update the firmware and webserver (separate from each other), and it even gives you the option to make changes to the code.<br>
Steps 1 - 7 will only need to be done once.<br>
You can upload using the Arduino IDE either over the USB cable or over WiFi (requires the firmware of the sensor to be v3.0.4 or later)

1. Download and install the legacy Arduino IDE from [here](https://www.arduino.cc/en/software). Do not download Arduino IDE 2.x.x, you want 1.x.x
2. Download and install the 'esp32fs plugin' from [here](https://github.com/lorol/arduino-esp32fs-plugin)
3. Open the Arduino IDE and navigate to 'File' => 'Preferences'
4. Near the bottom there should be a field for 'Addition Boards Manager URLs', click the button to the right of that field
![Screenshot](../../img/misc/Arduino_Additional_Boards_Btn.png){align=center width=50%}
5. Fill in the following on separate lines<br>
    "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json"<br>
    "https://github.com/MaterialFoundry/MaterialFoundry_Arduino/releases/latest/download/package_materialfoundry_index.json"
    
    ![Screenshot](../../img/misc/Arduino_Additional_Boards.png){align=center width=50%}

6. Restart the IDE, then navigate to 'Tools' => 'Board: xxx' => Boards Manager, which should open a new window
7. Wait for the window to fully load, then search for and install 'esp32' (not 'Arduino ESP32 Boards') and 'Material Foundry'.
![Screenshot](../../img/misc/Arduino_Boards_Manager.png){align=center width=50%}
8. Download and extract the 'Source code' from the [latest sensor release](https://github.com/MaterialFoundry/MaterialPlane_Sensor/releases)
9. Open 'Sensor.ino' in the Arduino IDE
10. Navigate to 'Tools' => 'Board: xxx' and select your harware version/board
    * In most cases you will want to select 'Material Foundry' => 'Material Plane Sensor (xxx)', where you replace 'xxx' with your hardware variant
    * If you use a board that does not fit within the default sensor variants, select your board from the 'ESP32 Arduino' list

    ![Screenshot](../../img/misc/Arduino_Boards.png){align=center width=50%}

11. Navigate to 'Tools' and select the correct 'Port'.
    * To update over WiFi, select 'materialsensor at x.x.x.x' under 'Network Ports'
    * The production sensor will show up as 'COM## (Material Plane Sensor (Production))' or 'COM## (ESP32S3 Dev Module).<br>If it shows up as 'COM## (Material Plane Sensor (Production))' press and hold the 'boot' button, then press the 'reset' button and release the 'boot' button. After refreshing the USB ports it should show up as 'COM## (ESP32S3 Dev Module)'.
    * The DIY sensor can show up with various names. There may be multiple 'COM##' ports, see [here](#finding-the-correct-usb-port) if you are unsure which one is the correct one

    ![Screenshot](../../img/misc/Arduino_Port.png){align=center width=50%}

12. You can now update either the firmware or the webserver:
    * <b>Firmware:</b> Press the 'Upload' button (arrow pointing to the right in the top-left part of the screen). Then wait for the IDE to compile and then upload the firmware
    
    ![Screenshot](../../img/misc/Arduino_Upload.png){align=center}
    
    * <b>Webserver:</b> Navigate to 'Tools' and select 'ESP32 Sketch Data Upload', select 'SPIFFS' and press 'OK'. Then wait for the IDE to upload the webserver

    ![Screenshot](../../img/misc/Arduino_Spiffs.png){align=center}

{% include 'findingComPort.md' %}