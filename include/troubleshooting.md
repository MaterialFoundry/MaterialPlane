## How to use
Below you will find multiple tables covering different topics related to Material Plane.<br>
For easy navigation, each table can be found in the table of contents on the left.<br>
Pick the table that best corresponds with your issue, if you cannot find your issue there, make sure it's not located somewhere else.<br>
If your issue is nowhere to be found, or you found a solution that isn't mentioned here, please contact me.

Issues can have multiple causes or multiple solutions.<br>
If you find a row that does not mention an issue, it relates to the issue in the row above it.<br>
Similarly, if you find a row that does not mention a possible cause, it relates to the issue and possible cause of the row above it.

## Sensor
| Issue                                             | Possible cause                        | Possible solution                         | More info                                                 |
|---------------------------------------------------|---------------------------------------|-------------------------------------------|-----------------------------------------------------------|
| Sensor can't detect base/pen                      | Sensor sensitivity set incorrectly    | Properly configure the sensor             | [link](SensorConfiguration/sensorSettings.md#exposure)    |
| Sensor can't detect base/pen at edge of display   | Sensor sensitivity set incorrectly    | Properly configure the sensor             | [link](SensorConfiguration/sensorSettings.md#exposure)    |
|                                                   | Sensor too close to the display       | Properly configure the sensor             | [link](SensorConfiguration/sensorSettings.md#exposure)    |                                              
| Sensor detects a lot of noise                     | Minimum brightness set too low        | Increase minimum brightness               | [link](SensorConfiguration/sensorSettings.md#exposure)
|                                                   | Too much infrared noise in room       | Switch all infrared sources off, such as: <br>-Wii sensor bar<br>-VR stations/receivers
|                                                   |                                       | Prevent direct sunlight on the sensor/display/table
|                                                   |                                       | Make sure there are no lights shining/reflecting directly into the sensor
| Sensor can't detect complete display              | Sensor too close to the display       | Move sensor further back                  | [link](SensorPositioning/sensorDistance.md)               |
{% if variant == 'production' %}|                                                   |                                       | Install a wide-angle lens                 | [link](SensorConfiguration/sensorLens.md)                 |
{% endif %}| Sensor won't charge                               | Sensor is not getting (enough) power  | Connect USB cable to power adapter        |
|                                                   |                                       | Try a different power adapter             |
|                                                   | Broken cable                          | Replace cable                             |
| Sensor can't connect to WiFi                      | Wrong credentials                     | Enter correct credentials                 |
|                                                   | No 2.4GHz WiFi available              | Make sure there's 2.4GHz WiFi available   |
|                                                   | Router too far away                   | Move router or sensor closer, or get a WiFi extender    |
| Detected points move in wrong direction           | Mirroring and/or rotation not configured properly | Properly configure mirroring and/or rotation  | [link](SensorConfiguration/sensorSettings.md#transform)
{% if variant == 'production' %}| Incorrect battery readings  | Battery has been replaced             | Reset battery configuration                           | [link](SensorConfiguration/webserver.md#status-tab)   
|                                                   | Bug                                   | Reset battery configuration                           | [link](SensorConfiguration/webserver.md#status-tab)   
{% elif variant == 'diy' %}| Incorrect battery readings    | Battery reading is only a very rough estimate | No solution
| No battery readings during charging               | This is on purpose: During charging, the battery voltage is read much too high, making the voltage reading useless | No solution{% endif %}

{% if variant == 'production' %}
## Base
| Issue                                         | Possible cause                                    | Possible solution                                             | More info                                                 |
|-----------------------------------------------|---------------------------------------------------|---------------------------------------------------------------|-----------------------------------------------------------|
| Base won't update                             | Both the pen and base are connected to the dock   | Remove one of them                                            | [link](Updating/basePenUpdating.md#base--pen)    |
|                                               | Faulty USB-C cable or USB port                    | Try a different cable or USB port
|                                               | Incorrect or no USB drivers installed             | Install the drivers                                           | [link](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all#drivers-if-you-need-them) |
| Base won't charge                             | Dock is not getting power                         | Apply power to the dock                                       | 
|                                               | Dock is getting insufficient power                | Try a different power adapter that can supply enough power    | [link](HardwareOverview/dock.md#power-supply-requirements)    |
|                                               | Too many dock expansions stacked                  | Try removing dock expansions                                  | [link](HardwareOverview/dock.md#expansion-stacking-limitations)  |
|                                               | Base not seated correctly                         | Try reseating it                                              | [link](HardwareOverview/dock.md#base-charging)  |
| Base won't detect touch                       | Base switched off                                 | Switch base on                                                | [link](Usage/bases.md#switching-a-base-on-or-off)
|                                               | Touch sensitivity set too low                     | Increase touch sensitivity                                    | [link](basePenConfig.md#configuration-options)
|                                               | Wrong (pen?) firmware installed                   | Install the correct firmware                                  | [link](Updating/basePenUpdating.md)
| Base won't go into standby (LED always on)    | Base is in 'Always On Mode'                       | Switch base back to 'Normal' mode                             | [link](Usage/bases.md#base-modes)
|                                               | Touch sensitivity set too high                    | Decrease touch sensitivity                                    | [link](basePenConfig.md#configuration-options)
| Base becomes active when placed on display    | Touch sensitivity set too high                    | Decrease touch sensitivity                                    | [link](basePenConfig.md#configuration-options)

## Pen
| Issue                 | Possible cause                                    | Possible solution                                             | More info                                             |
|-----------------------|---------------------------------------------------|---------------------------------------------------------------|-----------------------------------------------------|
| Pen won't update      | Both the pen and base are connected to the dock   | Remove one of them                                            | [link](Updating/basePenUpdating.md#base--pen)    |
|                       | Faulty USB-C cable or USB port                    | Try a different cable or USB port                             |
|                       | Incorrect or no USB drivers installed             | Install the drivers                                           | [link](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all#drivers-if-you-need-them) |
| Pen/ won't charge     | Dock is not getting power                         | Apply power to the dock                                       |   
|                       | Dock is getting insufficient power                | Try a different power adapter that can supply enough power    | [link](HardwareOverview/dock.md#power-supply-requirements) |
|                       | Too many dock expansions stacked                  | Try removing dock expansions                                  | [link](HardwareOverview/dock.md#expansion-stacking-limitations)  |
|                       | Pen not seated correctly                          | Try reseating it                                              | [link](HardwareOverview/dock.md#base-charging)  |
{% endif %}

## Calibration
| Issue                                     | Possible cause    | Possible solution      | More info |
|-------------------------------------------|-------------------|------------------------|-----------|
| Can't perform/complete calibration        | Active user not configured correctly              | Configure active user                         | [link](Foundry/foundryConfig.md#general)
|                                           | Active user not connected to Foundry              | Connect active user
|                                           | Sensor not connected                              | See [above](#sensor)
|                                           | Sensor sensitivity not set correctly              | Configure sensor                              | [link](SensorConfiguration/sensorSettings.md#exposure)
|                                           | Base not enabled                                  | Switch on base
|                                           | Sensor can't see entire display                   | See [above](#sensor)
| Tokens don't stay directly below base     | No calibration performed                          | Perform calibration                           | [link](calibration.md)
|                                           | Calibration disabled                              | Enable calibration                            | [link](calibration.md)
|                                           | Calibration not done correctly                    | Perform calibration, make sure you check [Base Orientation](calibration.md#base-orientation) | [link](calibration.md)
|                                           | Sensor offset and/or scaling set incorrectly      | Correctly configure offset and/or scaling     | [link](SensorConfiguration/sensorSettings.md#transform)
| Detected points move in wrong direction   | Mirroring and/or rotation not configured properly | Properly configure mirroring and/or rotation  | [link](SensorConfiguration/sensorSettings.md#transform)

## Foundry VTT
| Issue                                         | Possible cause                                    | Possible solution                                             | More info |
|-----------------------------------------------|---------------------------------------------------|---------------------------------------------------------------|-----------|
| Can't see module in Foundry's module page     | No internet connection                            | Make sure you are connected to the internet                   |
|                                               | Foundry server down                               | Wait until the server is up again                             |
|                                               | Incompatible Foundry version                      | Upgrade/downgrade to a compatible version                     |
|                                               | Bug in the module                                 | Report it to me                                               |
|                                               | Bug in Foundry                                    | Report it to the Foundry team                                 |
| Can't install module                          | Bug in the module                                 | Report it to me                                               |
|                                               | Bug in Foundry                                    | Report it to the Foundry team                                 |
| Can't update module                           | No internet connection                            | Make sure you are connected to the internet                   |
|                                               | Incompatible Foundry version                      | Upgrade/downgrade to a compatible version                     |
|                                               | Bug in the module                                 | Report it to me                                               |
|                                               | Bug in Foundry                                    | Report it to the Foundry team                                 |
| Sensor won't connect to module                | Sensor not connected to WiFi                      | Connect sensor to WiFi                                        | [link](SensorConfiguration/sensorConnecting.md)
|                                               | Incorrect 'Connection Mode' selected              | Select correct mode                                           | [link](Foundry/foundryConnection.md)
|                                               | Incorrect 'Sensor Module IP Address' configured   | Configure correct address                                     | [link](Foundry/foundryConnection.md)
|                                               | Foundry server is secured                         | Connect through Material Companion                            | [link](Foundry/foundryConnection.md)
| Tokens don't move                             | Sensor is not connected to WiFi                   | Connect sensor to WiFi                                        | [link](SensorConfiguration/sensorConnecting.md)
|                                               | Sensor is not connected to module                 | Connect sensor to module                                      | [link](Foundry/foundryConnection.md)
|                                               | Sensor is not correctly calibrated                | Perform calibration                                           | [link](calibration.md)
|                                               | Sensor mirroring/rotation not configured correctly| Configure mirroring and/or rotation                           | [link](SensorConfiguration/sensorSettings.md#transform) 
|                                               | Sensor sensitivity is not set correctly           | Configure sensor                                              | [link](SensorConfiguration/sensorSettings.md)     
|                                               | Token is not owned by display user                | Make display user owner of token                              | [link](Foundry/foundrySetup.md)     
|                                               |                                                   | Enable 'Non-Owned Movement'                                   | [link](Foundry/foundryConfig.md)                            
| Wrong tokens are being moved                  | Sensor not correctly calibrated                   | Perform calibration                                           | [link](calibration.md)
|                                               | Sensor mirroring/rotation not configured correctly| Configure mirroring and/or rotation                           | [link](SensorConfiguration/sensorSettings.md#transform) 
| Tokens don't stay directly below base         | Sensor not configured properly                    | Configure sensor                                              | [link](SensorConfiguration/sensorSettings.md) 
| Tokens are not dropped after releasing base   | Module is configured to not drop tokens           | Enable 'Delect Token After Drop'                              | [link](Foundry/foundryConfig.md#general)
| Tokens can move through walls                 | This is a known issue that has been hard to solve | Try to avoid having walls through the middle of a grid space  |
| Detected points move in wrong direction       | Mirroring and/or rotation not configured properly | Properly configure mirroring and/or rotation                  | [link](SensorConfiguration/sensorSettings.md#transform)