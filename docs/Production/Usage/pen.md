## Pen Activation
The pen is activated whenever one of its buttons are pressed, and it will stay activated for a set amount of time after all buttons have been released. By default this timeout is 10 seconds, but this can be configured using Material Companion as explained [here](../basePenConfig.md).

## Holding the Pen
![Screenshot](../../img/hardware/production/Pen_Holding.png){align=right width=33%}

To use the pen, the side with the LEDs must be facing up, towards the sensor. The side of the pen with the buttons is the front. For the A, C and D buttons, only the front LED needs to be exposed. When pressing the B button both the front and rear LED need to be exposed.

In general, it's best to hold the pen like a normal writing pen: the thumb and index finger hold the pen close to the buttons, with the rear of the pen resing on the part of the hand connecting the thumb and index finger, see the top image on the right.

Alternatively, the pen would be held as shown in the lower image on the right. While this can be more comfortable in some situations, you will not be able to use the function assigned to the B button, since the rear LED is blocked by the hand.

## B Button
The B button is special, because it enables both the front and rear LEDs. This means that the orientation of the pen can be determined.<br>
This is used for rotating things. For example, when using the 'Token' function, you can press B and rotate the pen to rotate a token.

## C Button
The C button is reserved for interacting with the pen menu. Pressing that button will always open the menu, regardless of the mode.

## Pen Menu
By pressing the C button the pen menu will open, it will automatically close when the pen is no longer used. Here, you can select the function of the pen. You select the function using either the C or D button. You can move the menu around by pressing and holding the center (Material Foundry logo) using the C or D button.

You can enable an info display by pressing the info button in the pen menu. This info display displays the current mode and the function of each button.

### Inner circle
The inner circle of the pen menu sets the mode of the pen. The 'Drawings', 'Templates' and 'Macros' modes will open a secondary ring of options.<br>
The following table gives a summary of all options of the pen menu. 

| Mode          | Icon                                                                                  | A Button          | B Button          | D Button          |
|------         |----------                                                                             |----------         |----------         |----------         |
| Canvas        | ![arrow-pointer-solid](../../img/hardware/production/penMenu/arrow-pointer-solid.svg)    | Pan canvas        | Zoom canvas       | Click canvas      |   
| Token         | ![user-solid](../../img/hardware/production/penMenu/user-solid.svg)                      | Deselect token    | Rotate token      | Move token        |
| Ruler         | ![ruler-solid](../../img/hardware/production/penMenu/ruler-solid.svg)                    | Undo last segment | Clear ruler       | Start ruler/new segment |
| Target        | ![bullseye-solid](../../img/hardware/production/penMenu/bullseye-solid.svg)              | Remove all targets| -                 | Target token      |
| Drawings      | ![pencil-alt-solid](../../img/hardware/production/penMenu/pencil-solid.svg)              | Move drawing      | Rotate drawing    | Draw shape        |
| Templates     | ![ruler-combined-solid](../../img/hardware/production/penMenu/ruler-combined-solid.svg)  | Move tempalate    | Rotate template   | Draw template     |
| Macros        | ![arrow-pointer-solid](../../img/hardware/production/penMenu/ruler-combined-solid.svg)   | User configurable | User configurable | User configurable |
| Info          | ![circle-info-solid](../../img/hardware/production/penMenu/circle-info-solid.svg)        | -                 | -                 | -                 |

### Canvas
The canvas mode allows some basic interaction with the canvas, such as panning or zooming the canvas with the A and B buttons, respecivetly.<br>
The D button will click on the canvas and can be used for things like opening doors.

| A Button          | B Button          | D Button          |
|----------         |----------         |----------         |
| Pan canvas        | Zoom canvas       | Click canvas      |   


### Token
The token mode will manipulate tokens.<br>
Tokens can be moved by pressing and holding the D button. They can be rotated by pressing the B button and rotating the pen, and tokens can be deselected with the A button.

| A Button          | B Button          | D Button          |
|----------         |----------         |----------         |
| Deselect token    | Rotate token      | Move token        | 

### Ruler
Distances can be measured using the ruler mode.<br>
Start a measurement by pressing the D button. Using the D button a new ruler segment is created, the A button removes the last segment, and using the B button you can clear the ruler.

| A Button          | B Button          | D Button          |
|----------         |----------         |----------         |
| Undo last segment | Clear the ruler   | Start ruler/new segment | 

### Target
Press the D button to target a token and the A button to remove all targets.

| A Button          | B Button          | D Button          |
|----------         |----------         |----------         |
| Remove all targets| -                 | Target token      | 

### Drawings
![Screenshot](../../img/foundry/Foundry_Pen_Drawing.png){align=right width=33%}
With the drawings mode you can place or edit drawings on the canvas.<br>
On the left of the pen menu there are 2 sets of colors. The top-left quadrant sets the fill color of the drawing, while the bottom-left quadrant sets the line color of the drawing.

A pencil icon will be drawn for each drawing on the canvas, this is to indicate the 'target' point for each drawing when trying to edit it using the 'Select' mode.

| Mode      | Icon                                                                              | A Button          | B Button          | D Button          |
|------     |----------                                                                         |----------         |----------         |----------         |
| Select    | ![expand-solid](../../img/hardware/production/penMenu/expand-solid.svg)              | Move drawing      | Rotate drawing    | Resize drawing      |   
| Rectangle/Ellipse/Freehand | ![square-solid](../../img/hardware/production/penMenu/square-solid.svg)/![circle-solid](../../img/hardware/production/penMenu/circle-solid.svg)/![signature-solid](../../img/hardware/production/penMenu/signature-solid.svg)                                            | -                 | -                 | Draw shape        |
| Polygon   | ![draw-polygon-solid](../../img/hardware/production/penMenu/draw-polygon-solid.svg)  | -                 | Undo last segment | Place new segment |
| Clear     | ![trash-solid](../../img/hardware/production/penMenu/trash-solid.svg)                | -                 | -                 | Remove drawing    |

### Templates
![Screenshot](../../img/foundry/Foundry_Pen_Template.png){align=right width=33%}
With the template mode you can place or edit templates on the canvas.<br>

| Mode      | Icon                                                                              | A Button          | B Button          | D Button          |
|------     |----------                                                                         |----------         |----------         |----------         |
| Select    | ![expand-solid](../../img/hardware/production/penMenu/expand-solid.svg)              | Move template      | Rotate template    | Resize template      |   
| Circle/Cone/Rectangle/Ray | ![circle-solid](../../img/hardware/production/penMenu/circle-solid.svg)/![angle-left-solid](../../img/hardware/production/penMenu/angle-left-solid.svg)/![square-regular](../../img/hardware/production/penMenu/square-regular.svg)/![arrows-left-right-solid](../../img/hardware/production/penMenu/arrows-left-right-solid.svg)                                       | -                 | -                 | Draw template        |
| Clear     | ![trash-solid](../../img/hardware/production/penMenu/trash-solid.svg)                | -                 | -                 | Remove template    |

### Macros
![Screenshot](../../img/foundry/Foundry_Pen_Macro.png){align=right width=33%}
The macro mode allows for customized and more complex pen behavior.<br>
<br>
You can have up to 8 groups of macros (M1 - M8), where each macro group can have one or more macros assigned to each button and button  mode (press/release/hold).<br>
Macros can be assigned to buttons and button modes from the '[Pen Setup](../Foundry/foundryConfig.md#pen-setup)' tab in the module configuration.<br>
<br>
Macros have access to the following variables:

| Variable | Description |
|---        |---    |
|scope.button           | Button that is being pressed  |
|scope.buttonMode       | Mode of the button that is being pressed (press/release/hold) |
|scope.coordinates      | X and Y coordinates of the pen (e.g. scope.coordinates.x) |
|scope.coordinates2     | X and Y coordinates of the second infrared LED of the pen when the B button is pressed |
|scope.angle            | Angle (in degrees) of the pen when the B button is pressed |
|scope.length           | Apparent length (in pixels) of the pen when the B button is pressed. This is essentially the distance between scope.coordinates and scope.coordinates2. |
|scope.id               | Id of the pen |
|scope.raw              | Raw data of the pen point(s), see below |

Raw data:
```js 
scope.raw = [
    {
        //point 0
        number: 0; //number of the point
        area: 11; //area of the point
        avgBrightness: 221; //average brightness of the point
        maxBrightness: 253; //maximum brightness of the point
        x: 1135.542; //unscaled x-coordinate of the point
        y: 1723.461; //unscaled y-coordinate of the point
    },{
        //point 1
    }  
]
```