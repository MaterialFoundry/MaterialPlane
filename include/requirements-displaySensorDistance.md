In order for the sensor to detect minis across the whole display, the sensor needs to be located at a minimum distance above the display. The minimum distance depends on the size of the display, where a bigger display requires a larger distance.

{% if variant == 'production' %}
A [wide-angle lens]({{lensLink}}) can be installed in the production sensor when your display is too big and/or the distance to the ceiling is too small. The lens can either come pre-installed by selecting the option in the sensor product page, or it can be bought separately.
{% endif %}

The table below gives the minimum distance between the display and sensor. Measure the distance between the top of the display and the desired sensor mounting location (ceiling, microphone stand, etc). 

{% if variant == 'production' %}
Look at the row with your display size:

* If the measured distance is smaller than the value in the 'With Lens' column, your setup is incompatible with Material Plane. 
* If the distance is larger than the value in the 'With Lens' column but larger than the 'Without Lens' column, your setup requires the wide-angle lens. 
* If the distance is larger than the value in the 'Without Lens' column, the lens is not required, but can still be used to decrease the distance between sensor and display.
{% else %}
Look at the row with your display size, and if the value in the 'Distance' column is smaller than the measured distance, your setup is incompatible with Material Plane.
{% endif %}

Placing the sensor too far away from the display will result in reduced accuracy and potentially more jittery movement. For optimal results you should place the sensor as close to the minimum distance as possible (with some wiggle room for alignment). If you do not need the wide-angle lens, it's better to not have it installed.

Please note that these are just approximate values, assuming a 16:9 aspect ratio display and perfect sensor positioning while ignoring any manufacturing tolerances. Try to err on the safe side by subtracting a few cm/inches from the measured distance between display and sensor.

{% if variant == 'production' %}
Display Size | Production (No Lens) | Production (Lens) 
-------------|----------------------|-------------------
32" 	     | 109cm/43" 	        | 88cm/35"          
40" 	     | 134cm/53" 	        | 108cm/43"         
43" 	     | 144cm/57" 	        | 116cm/46"         
50" 	     | 166cm/66" 	        | 134cm/53"         
55" 	     | 182cm/72" 	        | 146cm/57"         
60" 	     | 198cm/78" 	        | 159cm/63"         
65" 	     | 214cm/85" 	        | 172cm/68"         
70" 	     | 230cm/91" 	        | 185cm/73"         
75" 	     | 246cm/97" 	        | 198cm/78"         
80" 	     | 278cm/110" 	        | 223cm/88"         
{% else %}
Display Size | Distance
-------------|--------
32" 	     | 120cm/47"
40" 	     | 150cm/59"
43" 	     | 160cm/63"
50" 	     | 187cm/74"
55" 	     | 205cm/81"
60" 	     | 224cm/88"
65" 	     | 243cm/96"
70" 	     | 261cm/103"
75" 	     | 280cm/110"
80" 	     | 289cm/114"
{% endif %}