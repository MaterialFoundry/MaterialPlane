# Arduino Code
This is the Arduino code that has to be uploaded to the ESP32. In order to upload the code, please follow the following steps:<br>
<ol>
<li>Download the latest version of <a href="https://www.arduino.cc/">Arduino</a></li>
<li>Download the <a href="https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers">USB drivers</a></li>
<li>Add the ESP32 boards to Arduino. To do so, follow <a href="https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md">this</a> guide</li>
<li>Download the latest files from <a href="https://github.com/CDeenen/MaterialPlane/releases/tag/ArduinoIRsensor">here</a> and extract the .zip file</li>
<li>Open IRsensor.ino, and at '#define SSID "your_ssid"' and '#define PASS "your_password"' fill in your WiFi router's SSID and password</li>
<li>If you're using the full sensor, leave "#define FULL_SENSOR" as is, otherwise comment it out: "//#define FULL_SENSOR"
<li>Click 'Tools', 'Board', 'ESP32 Arduino', and then select your board. In my case it was 'TinyPICO'</li>
<li>Again under 'Tools', click 'Port', and select the correct serial port</li>
<li>You should now be able to upload the code to the ESP32, by pressing the 'Upload' button (top-left, the arrow pointing to the right)</li>
</ol>

Once it's done uploading, you should be able to open the Serial Monitor ('Tools', 'Serial Monitor'), set the baud rate to 115200 (bottom right) and you should see text appearing.<br>
If all went well, you after a few seconds you should get the message:<br>
<br>
"Done initializing<br>
Connected to: {your ssid} with IP: {your IP}"<br>
<br>
Please remember this IP address, because you will need it during setup in Foundry