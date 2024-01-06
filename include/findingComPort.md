## Finding the Correct USB Port
For updates over USB, you will need to find the correct USB port over which the update can take place.<br>
Some devices, such as the production sensor and dock may show up as named devices in Material Companion or the Arduino IDE, but other will not. To figure out the correct port, you can try one of these methods:

<b>Using Material Companion</b><br>

1. Open Material Companion and navigate to either the 'Sensor', 'Base' or 'Pen' sub-tab in the 'Material Plane' tab
2. Make sure the device is disconnected, then press the 'refresh' button next to 'Sensor/Dock USB Port'
3. Take note of which ports are currently selectable
4. Connect the device, wait a few seconds, and press the 'refresh' button again
5. A new port should show up, this is the port you're looking for

<b>Using the Arduino IDE</b><br>

1. Open the Arduino IDE
2. Make sure the device is disconnected, navigate to 'Tools' and take note of which ports are available under 'Port: xxx'
3. Connect the device, wait a few seconds, and navigate to 'Tools' again (this won't work if you stay in the 'Tools' menu while connecting the device)
5. A new port should show up, this is the port you're looking for

<b>Using Device Manager (Windows)</b><br>

1. Open the start menu and search for 'Device Manager'
2. Make sure the device is disconnected, navigate to 'Ports (COM & LPT)' and take note of which COM ports are available
3. Connect the device, wait a few seconds, and Device Manager should update and show a new COM port, this is the port you're looking for