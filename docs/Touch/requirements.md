{%set variant = 'touch' %}

# Requirements
The requirements for using Material Plane using touch can be divided into 3 parts:

* [Touch-related hardware](#touch-related-hardware)
* [Compatible Minis](#compatible-minis)
* [Virtual Tabletop](#virtual-tabletop)
* [Horizontally mounted display](#horizontally-mounted-display)

# Touch-Related Hardware
Some kind of hardware is required that can detect touches. While there are more options, the following 3 will be the most commong:

* <b>Integrated capacitive touch:</b> A display with integrated touch layer. These tend to be very expensive, but are a good choice due to their accuracy, easy of use, and number of touch points.
* <b>Infrared Touch Frame:</b> Touch frames work by sending a beam of IR light across the surface of the TV. If this light is interrupted, the location is calculated and registered as a touch point. Infrared touch frames are relatively inexpensive and easy to mount to an existing display.
* <b>Capacitive Touch Foil:</b> This is a foil that is attached to a non-touch display to give it capacitive touch. Can have similar advantages to integrated touch screens, but can be difficult to apply properly (without bubbles).

# Compatible Minis
<b>Infrared Touch Frames:</b><br>
There are 2 challenges related to infrared touch frames:

* The IR beam is located slightly above the surface of the TV (probably a few millimeters)
* Small objects might not be detected This means that the touch frame might have trouble detecting certain minis. If the base of the mini is thin, it's possible that the IR beam is at the height of the legs of that mini, which might be undetectable.<br>
The easiest way to solve this, would be to increase the height of the base, by, for example, glueing some object to the bottom of the base.

<b>Capacitive Screens:</b><br>
In simple terms, a capacitive screen works by sensing a change in capacitance caused by touch. For this to function for minis (or other objects), the mini must be conductive, or at least, there must be a conductive path from your finger to the touch screen. Below are 2 methods to achieve this.

* Copper Tape<br>
Buy copper (or other conductive) tape, cut of a piece (try around 3 or 4 cm), and place it on the bottom of the base in such a way that a part of the tape extends past the base. Fold the extending part up (towards the top of the mini). Optionally, you can fold the extending part of the tape double, so it sticks to itself, and not to the mini (or to your finger). When you want to move the mini, you will have to continuously touch the copper tape.
* Conductive Paint<br>
This may or may not work, but it is possible to buy (transparent) conductive paint. Spray this across the whole mini, including the bottom of the base. You might need multiple coats to achieve a low enough resistance.

## Virtual Tabletop
{% include 'requirements-vtt.md' %}

## Horizontally Mounted Display
{% include 'requirements-display.md' %}