You'll need a TV, or some other display (monitor/projector) onto which the virtual tabletop is displayed.

{% if variant != 'touch' %}
For the Material Plane hardware (both DIY and production) you do have to consider the size of your TV, due to the limited detection angle of the sensor, see [Display-Sensor Distance section](requirements.md#display-sensor-distance) below.
Virtually any display will work, however, some older models (especially plasma and LCD displays with CCFL backlight) can emit infrared noise which might interfere with the sensor. To remedy this, you could add infrared-blocking foil to the display. Modern displays should not cause any issues.
{% endif %}

{% if variant == 'touch' %}
If the display has touch capabilities built-in there are no further requirements. Otherwise, make sure that your infrared touch frame or capacitive touch foil is the correct size and mounted correctly.
{% endif %}