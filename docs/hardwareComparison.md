# Hardware Comparison
There are a few options when it comes down to the tracking of physical miniatures. This page will give an overview of these options, and a comparison between them.

## Options

### Material Plane DIY Hardware

The first option would be to use a Material Plane sensor. The setup consists of 2 parts:

1. A sensor, which is mounted above the TV, and basically functions like an IR camera
2. Mini bases, which are placed underneath the mini and contain an IR LED which can be tracked by the sensor

There are 2 variants, the DIY variant and the production variant. The DIY variant has to be assembled by the user, while the production variant comes pre-assembled, and is available at the [Material Foundry webshop](https://www.materialfoundry.nl/).<br>
The main differences between the two variants can be found in the comparison below.<br>
The Material Plane sensor can be used on any display, for example a normal TV, or a projector.<br>
Because the minis are only detected when they are moved, there is no limit the the amount of minis you can have on the table. There is, however, a limit to the amount of minis that can be moved at the same time: 4 for the DIY sensor and 16 for the production sensor.<br>
Other forms of interaction (besides moving minis) is not possible for the DIY sensor, while the production sensor supports a special pen that can be used like a mouse to open doors, draw shapes, place templates, etc.<br>
Because the sensor is mounted above the TV, contact with the TV while moving minis is not required, unlike other setups. This means that minis can be raised up into the air in order for them to be moved over other minis.

### IR Touch Screen
<b>Material Plane support for IR touch screens is currently experimental. It is not yet clear how well it actually works, so it is currently not advisable to purchase one specifically for this purpose.</b><br>
An IR touch screen uses IR LEDs on 2 sides of the screen, and sensors on the other 2 sides. By placing a finger (or mini) on top of the screen, a shadow is cast on the sensors, because the IR light cannot pass through your finger. This is then converted to a position, which is interpreted as a touch by the computer.<br>
These touch screens can generally detect up to 10 touch points, however, these are not completely independent. Because the touch points cast a shadow, blind spots (where no touch is detected) are possible, and touches on one side of the display can influence the detected position of other touch points.<br>
Because the IR LEDs and sensors are slightly above the TV, it might be necessary to place the minis on a small platform to ensure that they are detected by the sensors.<br>
A non-touch display can quite easily be converted to an IR touch display through an IR touch frame. They can be easily found on, for example, Amazon for around $150 to $300 (depending on size and vendor).<br>
Other forms of interaction (besides moving minis) is possible, but is limited by the algoritm that distinguishes minis from other touches.

### Capacitive Touch Screen
<b>Material Plane support for capacitive touch screens is currently experimental. It is not yet clear how well it actually works, so it is currently not advisable to purchase one specifically for this purpose.</b><br>
A capacitive touch screen uses capacitive sensing to detect touches. I will not go into detail on how this works, for more information, take a look on [Wikipedia](https://en.wikipedia.org/wiki/Capacitive_sensing). The most important things are that capacitive touch screens only detect certain objects, such as fingers, while other objects are not detectable. This requires some modification to each mini that has to be detected, to basically create electrical contact between the screen and a hand through the mini. This could be done by, for example, applying copper tape to the bottom of the mini, with a piece of that tape extending up, so that it can be touched when the mini is moved.<br>
Unlike an IR touch screen, the touch points of a capacitive touch screen are independent. The number of detectable touch points is generally 10, but this can be higher or lower, depending on the display. Depending on how the minis are detected, this limit might not be important. In the above case (using copper tape), the mini is only detected when the mini is touched, therefore you could add as many minis as you like, as long as you only touch up to 10 at the same time.<br>
Big displays with built-in capacitive touch screens are hard to find and expensive. Capacitive touch can be added to existing non-touch displays (search for 'touch foil'), but these are more difficult to find than IR touch frames.<br>
Other forms of interaction (besides moving minis) is possible, but is limited by the algoritm that distinguishes minis from other touches.<br>

## Comparison
| |DIY MP|Production MP|IR Touch|Capacitive Touch|
|-|-|-|-|-|
|Max nr of minis on TV|Unlimited|Unlimited|10<sup>1</sup>|Unlimited<sup>2</sup>|
|Max nr of simultaneously moved minis<sup>3</sup>|4|16|10<sup>1</sup>|10|
|Other interaction methods<sup>4</sup>|No|Yes (through pen)|Yes (potentially limited)|Yes (potentially limited)|
|Required hardware|Sensor + Bases|Sensor + Bases|Screen and Touch Frame<sup>5</sup>|Just the screen<sup>6</sup>|
|Detection limitations|Line of sight required<sup>7</sup>|Line of sight required<sup>7</sup>|Touch points are not independent, contact with TV must be maintained|Contact with TV must be maintained|
|Display limitations|Can work on any display, but with size limitation<sup>8</sup>|Can work on any display, but with size limitation<sup>8</sup>|Requires either built-in touch, or a fitting touch frame|Requires either built-in touch, or a fitting touch foil|
|Mini movement method|Button press on base|Touch sensors on left and right side of the base|Raise a mini and then place it down again before moving the mini|Touching the conductive part of the mini<sup>2</sup>|
|Mini identification<sup>9</sup>|Location based|ID based|Location based|Location based|
|Portability|Can be easily transported somewhere else, to be used on a different display|Can be easily transported somewhere else, to be used on a different display|Requires the display (or touch frame) to be transported|Requires the display to be transported|
|Availablility|Must be built by yourself, some parts can be difficult to get|[Webshop](https://www.materialfoundry.nl/)|Touch frames are easy to find online|TVs with built-in capacitive touch are expensive and difficult to find, touch foil is difficult to find (price unknown)|
|Price (excluding display)|$50 - $100|$150-$300|$150 - $300|Unknown, but probably high|
|Current state|Functional|Functional|Experimental|Experimental|

<sup>1</sup> This is a theoretical limit, issues might occur before them due to the shadow effect, as described above<br>
<sup>2</sup> Depends on how the minis are detected, see above<br>
<sup>3</sup> This is a theoretical limit, your computer might not be able to process more than a few minis at the same time<br>
<sup>4</sup> This includes things like opening doors, placing templates, using measurement tools, etc<br>
<sup>5</sup> It might be necessary to place something underneath the mini to raise them, see above<br>
<sup>6</sup> Minis might require modification to add a conductive part, see above<br>
<sup>7</sup> Line of sight is required between the IR LED in the base and the sensor, care must be taken in how to hold a mini, and how to position minis on the base<br>
<sup>8</sup> The MP sensor is basically an IR camera, this means that any kind of display (TV, projector, etc) is compatible, as long as it's not too big. The maximum size depends on the distance between the sensor and the display, more info [here](https://github.com/CDeenen/MaterialPlane/wiki/Requirements#horizontally-mounted-tv).<br>
<sup>9</sup> Identification in this case means the method that is used to identify which mini is moved, and how this is related to the digital tokens. Location based means that it will link the token that's nearest to the mini, while ID based means that it is always known which mini is moved though a unique ID, regardless of the mini's location relative to its digital token.