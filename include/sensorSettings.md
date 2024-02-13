This page discusses all settings related to how the sensor detects bases and handles the data related to this.These settings can be accessed through the Foundry [Module Configuration screen](../Foundry/foundryConfig.md#module-configuration) or the [webserver](webserver.md).

The tab is divided into multiple sections which can be expanded or collapsed.

## Coordinates
{% if variant == 'production' %}
![Screenshot](../../img/webserver/Webserver_Coordinates.png){align=right width=33%}
{% else %}
![Screenshot](../../img/webserver/Webserver_Coordinates_DIY.png){align=right width=33%}
{% endif %}

This section displays data of any detected infrared points (such as a base).<br>
A point is a collection of one or more 'pixels' where infrared light was detected. Pixels close to each other will be combined to form a single point.

The top part of this section displays what the sensor can see. Any detected points will be displayed here with each point numbered and given a color.

The middle part gives the data of the first 4 points:

* <b>X/Y:</b> The X and Y coordinates of the point.
{% if variant == 'production' %}
* <b>Average Brightness:</b> The average brightness of all pixels within the point.
* <b>Maximum Brightness:</b> The brightness of the brightest pixel within the point.
{% else %}
* <b>Brightness:</b> The brightness of the point.
{% endif %}
* <b>Area:</b> The size of the point.

{% if variant == 'production' %}
The bottom part gives data transmitted by a detected base or pen (production sensor only):

* <b>ID:</b> The id of the base or pen.
* <b>Command:</b> The transmitted command (for example the buttons pressed on the pen).
* <b>Battery:</b> Approximate battery percentage.
{% endif %}


## Exposure
![Screenshot](../../img/webserver/Webserver_Exposure.png){align=right width=33%}

The exposure section can be used to configure things related to the detection of bases.

There are 2 brightness settings ('Brightness' and 'Minimum Brightness') and an 'Auto Exposure' button.<br>
You should try the auto exposure first:

1. Grab a base and activate it, make sure it stays activated during the auto exposure process. Make sure only one base is visible to the sensor. 
2. Hold the base near the edge of the display
3. Press the 'Auto Exposure' button
4. The sensor will increase the brightness until it detects the base and the brightness is close to 255

{% if variant == 'production' %}
<b>Tip</b>: You can keep the base activated without touching it: Touch the side of the base very short, wait for the red LED to switch off, touch the side of the base again. Repeat this 5 times and the red LED will start blinking. The base is now in 'always on' mode. You can switch it back by either switching the base off and on, or by doing the same procedure again.
{% endif %}

If the auto exposure did not work:

1. Set 'Minimum Brightness' to around 100
2. Slide 'Brightness' all the way down and slowly increase it until the base or pen is detected
3. Keep increasing it until the maximum brightness is between 220 and 255
4. If the base or pen is not detected, try increasing the minimum brightness
5. If the sensor detects more points, increase the minimum brightness
6. In tricky environments (for example with a lot of stray infrared light) you might have to find a balance between the 'Brightness' and 'Minimum Brightness' slider
7. Move the base or pen across your display and make sure that the maximum brightness stays well above 'Minimum Brightness'

<b>Update Rate:</b><br>
The update rate controls how often the sensor sends out position data. Higher update rates will improve responsiveness, but might cause problems for slower systems, because line of sight and lighting calculations will have to be made more often. This can especially become evident when multiple bases are moved at the same time.<br>
Set it as high as you system will allow.

<b>Averaging:</b><br>
Averaging will smooth the position data of the bases. The average count equals how many readings are taken and averaged, where a higher value results in a very smooth but less responsive movement, while lower values result in more jittery but more responsive movement.<br>
Try different values to find one that fits best for you.

## Transform
![Screenshot](../../img/webserver/Webserver_Transform.png){align=right width=33%}
The 'Transform' section allows you to modify the position data.<br>

<b>Mirroring & Rotation</b><br>
When you move a base horizontally, but the point in the configuration screen moves the other direction, enable 'Mirror X'.<br>
When you move a base vertically, but the point moves the other direction, enable 'Mirror Y'.<br>
When you move a base horizontally, but the point moves vertically, enable 'Rotation'.<br>

<b>Offset & Scaling</b><br>
Offset and scaling can be used to fine tune the position data after calibration.<br>
Using the 'Offset X' and 'Offset Y' sliders you can add a horizontal of vertical offset to the position data.<br>
Using the 'Scale X' and 'Scale Y' sliders you can scale the position data, which in essence stretches the data out. 

## Calibration
The 'Calibration' section of the 'Sensor' tab allows you to enable or disable the calibration, and to perform a calibration procedure.

If the 'Calibration Enabled' or 'Calibration Offset Enabled' boxes are checked, then these calibration procedures are being applied. For easy sensor repositioning, it is advisable that you uncheck these boxes.<br>
<b>Please note that ticking these boxes does not perform an actual calibration procedure.</b>

See [this](../calibration.md) page for information on how to perform the calibration procedure.
