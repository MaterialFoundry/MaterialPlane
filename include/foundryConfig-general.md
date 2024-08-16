You can access the module configuration by opening the 'Game Settings' sidebar tab (on the right of the screen, cog icon), and clicking the 'Material Plane Configuration' button.

![Screenshot](../../img/foundry/Foundry_Module_Config_Btn.png)

The configuration consists of multiple tabs:

## General
{% if variant != 'touch' %}
![Screenshot](../../img/foundry/Foundry_Module_General.png){align=right width=50%}
{% else %}
![Screenshot](../../img/foundry/Foundry_Module_General_Touch.png){align=right width=50%}
{% endif %}
This tab is used for general settings for the module.

* <b>Active User:</b> Sets the active user for the module. This user will be the one displayed on the display.
* <b>Device:</b> Sets the kind of device that is used for token tracking, either the 'Material Plane Sensor' or a 'Touch Screen'
{% if variant != 'touch' %}
* <b>Low Battery Notifications:</b> Will pop up notifications if the battery of the sensor, base or pen is low
{% endif %}
* <b>Hide Display Elements:</b> Will hide all display elements (sidebar, buttons, scenes, etc). This can be toggles using the 'Ctrl' key
* <b>Block Interactions:</b> Will block canvas interactions if the Material Plane Configuration window is open. This will, for example, prevent tokens from being moved while adjusting sensor settings

