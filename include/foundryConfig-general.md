You can access the module configuration by opening the 'Game Settings' sidebar tab (on the right of the screen, cog icon), and clicking the 'Material Plane Configuration' button.

![Screenshot](../../img/foundry/Foundry_Module_Config_Btn.png)

The configuration consists of multiple tabs:

## General
![Screenshot](../../img/foundry/Foundry_Module_General.png){align=right width=50%}
This tab is used for general settings for the module.

* <b>Active User:</b> Sets the active user for the module. This user will be the one displayed on the display.
* <b>Device:</b> Sets the kind of device that is used for token tracking, either the 'Material Plane Sensor' or a 'Touch Screen'
* <b>Movement Method:</b> Material Plane offers 3 different movement methods:
    * <i>Live:</i> When a token is being moved, its vision is updated constantly
    * <i>Foundry Default:</i> When a token is being moved, its vision is only updated after the token is dropped/released
    * <i>Step-By-Step:</i> When a token is being moved, it will update its position and vision every time it is moved onto a new grid space
* <b>Deselect Token After Drop:</b> Will deselect the token after it has been dropped/released
* <b>Draw Movement Marker:</b> Will draw a square on the grid to indicate where the token will end up if dropped/released. This marker will be green if this grid space is allowed, or it will turn red if the token cannot move there (for example, if it is blocked by a wall)
* <b>Non-Owned Movement:</b> Allows non-owned tokens to be moved. Vision of non-owned tokens will not be shown
* <b>Token Collision Prevention:</b> Whenever a token is dropped/released onto a grid space that is already occupied, the module will attempt to move the token to the nearest empty grid space along its movement path
* <b>Hide Display Elements:</b> Will hide all display elements (sidebar, buttons, scenes, etc). This can be toggles using the 'Ctrl' key
* <b>Block Interactions:</b> Will block canvas interactions if the Material Plane Configuration window is open. This will, for example, prevent tokens from being moved while adjusting sensor settings

