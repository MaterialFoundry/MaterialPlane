## Control
{% if variant != 'touch' %}
![Screenshot](../../img/foundry/Foundry_Module_Control.png){align=right width=50%}
{% else %}
![Screenshot](../../img/foundry/Foundry_Module_Control_Touch.png){align=right width=50%}
{% endif %}

This tab is used for settings related to controlling tokens.

* <b>Movement Method:</b> Material Plane offers 3 different movement methods:
    * <i>Live:</i> When a token is being moved, its vision is updated constantly
    * <i>Foundry Default:</i> When a token is being moved, its vision is only updated after the token is dropped/released
    * <i>Step-By-Step:</i> When a token is being moved, it will update its position and vision every time it is moved onto a new grid space
{% if variant != 'touch' %}
* <b>Base Orientation:</b> (Only relevant for base adapters or bases bigger than 1x1) Set the orientation of the bases, relative to the display. This allows the module to compensate for the center location of bigger tokens.
{% endif %}
* <b>Deselect Token After Drop:</b> Will deselect the token after it has been dropped/released
* <b>Draw Movement Marker:</b> Will draw a square on the grid to indicate where the token will end up if dropped/released. This marker will be green if this grid space is allowed, or it will turn red if the token cannot move there (for example, if it is blocked by a wall)
* <b>Non-Owned Movement:</b> Allows non-owned tokens to be moved. Vision of non-owned tokens will not be shown
* <b>Token Collision Prevention:</b> Whenever a token is dropped/released onto a grid space that is already occupied, the module will attempt to move the token to the nearest empty grid space along its movement path
* <b>Ruler Mode:</b> If enabled, the module will draw a ruler from the token's movement starting position to its current position. 4 modes are available:
    * <i>Disabled:</i> Disable the ruler
    * <i>Straight Line:</i> Draws a straight ruler from the token's starting position to its current position
    * <i>Follow Movement:</i> Draws a ruler that (approximately) follows the token's path
    * <i>Pathfinding:</i> Finds the shortest distance between the token's starting position and its current position. Requires [routinglib](https://foundryvtt.com/packages/routinglib) to be installed and enabled
* <b>Pathfinding Distance:</b> ('Pathfinding' ruler mode only) Pathfinding is enabled for the last ruler segments to distances up to this value (in grid spaces). Segments at further distances will be locked. This prevents the pathfinding from always finding the shortest path, no matter how the token was previously moved. Set to 0 to disable.
* <b>Clear Ruler:</b> Sets when to clear the drawn ruler:
    * <i>On Token Drop:</i> Clears the ruler when the token is dropped/released
    * <i>On New Movement:</i> Ruler will stay visible after dropping a token. Clears the ruler when new movement is initiated

