# Base & Pen Configuration
Both the base and pen have some configuration options.<br>
You will need to [install Material Companion](https://github.com/MaterialFoundry/MaterialCompanion/wiki/Installation).

To read and modify the base or pen configurations, you need to place a base or pen on the dock. The base has to be in the charging slot with 3 pins.<br>
<b>You cannot read or configure a base if the pen is connected to the dock, or vise versa!</b>

## Configuration Options

<b>Firmware</b><br>
This field is read-only and displays the current firmware version of the base or pen.

<b>Id</b><br>
The id of the base or pen. This can be modified, which is mostly useful if you have multiple bases or pens that happen to have the same id. The id is used to [link tokens to a specific base](Usage/bases.md#token-detection), besides that it does not matter if multiple bases or pens share the same id.

<b>Touch Sensitivity (Base Only)</b><br>
The sensitivity of the touch sensors on the side of the base.<br>
If set too low, a touch might be difficult to detect (needing to press hard) or might be completely undetectable.<br>
If set too high, noise might trigger a false touch. This can be from, for example, electrical noise from the display or a hand that moved too close to the base.

<b>Timeout (Pen Only)</b><br>
When a pen is activated by pressing one of its buttons, it will stay active until all buttons are released and some extra time. The timeout option gives the lenght of this extra time.<br>
For example, if the timeout is set to 10 seconds, then the pen will stay active for 10 seconds after all butttons have been released.

## Reading the Current Configuration

1. Open Material Companion and navigate to the 'Base' or 'Pen' sub-tab in the 'Material Plane' tab.<br>
2. At the top, select the correct 'Dock USB Port'. The dock should show up as 'COM## (Dock)'. If it doesn't show up, try refreshing the USB ports or try [finding the correct USB port](#finding-the-correct-usb-port).
3. Press the 'Read' button. After a few seconds the configuration fields should be filled.

## Writing a New Configuration

1. [Read](#reading-the-current-configuration) the current configuration
2. Make any adjustments to the configuration
3. Press the 'Write' button, a popup should show giving the progress.

## Resetting to the Default Configuration

1. [Read](#reading-the-current-configuration) the current configuration
2. Press the 'Reset' button, a popup should show giving the progress.

{% include 'findingComPort.md' %}