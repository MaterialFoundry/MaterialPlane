![Screenshot](../../img/misc/SensorPlacement.png){align=right width=50%}
Finding a suitable orientation and position of the sensor above the display is essential for optimal performance.<br>
For the sensor to detect bases {% if variant == 'production' %}or the pen{% endif %}, there needs to be line of sight between the sensor and the bases {% if variant == 'production' %} or pen{% endif %}. The relative angle between the base{% if variant == 'production' %}or the pen{% endif %} and sensor can influence this. Take a look at the (exaggerated) example on the right.

If the base is directly below the sensor (center base), the apparent brightness of the infrared LED is at its maximum, as long as no part of the mini is obscuring the line of sight. <br>
The left base gives an example of this: the line of sight between the infrared LED and sensor goes right through the mini, so the sensor cannot see the base.<br>
In case of the right base, the mini does not obscure the line of sight, but due to the angle between the sensor and base, the apparent brightness of the infrared LED is decreased.<br>
This situation is identical in the other axis (pointing out of your screen), so an optimal angle and position of the sensor needs to be found where the chance of the line of sight being obscured, and the relative angle between the sensor and base is minimized.

To do this, we also need to take into account how players will be sitting around the display. Consider the 2 situations in the images below.

The red circle indicates the approximate location of the sensor above the display, with the sensor pointing towards the center of the display. The orientation of the bases during calibration and during play will be as shown in the top-right corner.<br>
Because the sensor is located towards the GM side, the chance of a mini obscuring the infrared LED is reduced. Only when bases are placed on the part of the display closest to the GM this might become an issue.<br>
The apparent brightness of the infrared LEDs will be pretty good across most of the display, but the part of the display opposite the GM might experience reduced apparent brightness. It is a good idea to make sure the sensitivity of the sensor is tuned so the sensor can detect the bases at these parts of the display.<br>
You could consider moving the sensor towards the green circle. This will reduce the chance of minis obscuring the LED (see the left mini in the earlier topmost image on this page), but this will reduce the apparent brightness in the part of the display opposite the circle.

![Screenshot](../../img/misc/Sensor_Placement_Table.png)