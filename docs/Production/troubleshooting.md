## Sensor
| Issue                                             | Possible cause                        | Possible solution                         | More info                                                 |
|---------------------------------------------------|---------------------------------------|-------------------------------------------|-----------------------------------------------------------|
| Sensor can't detect base/pen                      | Sensor sensitivity set incorrectly    | Properly configure the sensor             | [link](SensorConfiguration/sensorSettings.md#exposure)    |
| Sensor can't detect base/pen at edge of display   | Sensor sensitivity set incorrectly    | See above                                 |  
|                                                   | Sensor too close to the display       | See below                                 |                                               
| Sensor can't detect complete display              | Sensor too close to the display       | Move sensor further back                  | [link](SensorPositioning/sensorDistance.md)               |
|                                                   |                                       | Install a wide-angle lens                 | [link](SensorConfiguration/sensorLens.md)                 |
| Sensor won't charge                               | Sensor is not getting (enough) power  | Connect USB cable to power adapter        |
|                                                   |                                       | Try a different power adapter             |
|                                                   | Broken cable                          | Replace cable                             |
| Sensor can't connect to WiFi                      | Wrong credentials                     | Enter correct credentials                 |
|                                                   | No 2.4GHz WiFi available              | Make sure there's 2.4GHz WiFi available   |
|                                                   | Router too far away                   | Move router or sensor closer, or get WiFi extender    |
| Incorrect battery readings                        | Battery has been replaced             | Reset battery configuration                           | [link](SensorConfiguration/webserver.md#status-tab)   
|                                                   | Bug                                   | Reset battery configuration                           | [link](SensorConfiguration/webserver.md#status-tab)   
| Sensor can't detect base/pen ID                   |
| Sensor can't detect pen                           |

## Base
| Issue                 | Possible cause                                    | Possible solution                                             | More info                                                 |
|-----------------------|---------------------------------------------------|---------------------------------------------------------------|-----------------------------------------------------------|
| Base won't update     | Both the pen and base are connected to the dock   | Remove one of them                                            | [link](Updating/basePenUpdating.md#base--pen)    |
|                       | Faulty USB-C cable or USB port                    | Try a different cable or USB port
|                       | Incorrect or no USB drivers installed             | Install the drivers                                           | [link](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all#drivers-if-you-need-them) |
| Base won't charge     | Dock is not getting power                         | Apply power to the dock                                       | 
|                       | Dock is getting insufficient power                | Try a different power adapter that can supply enough power    | [link](HardwareOverview/dock.md#power-supply-requirements)    |
|                       | Too many dock expansions stacked                  | Try removing dock expansions                                  | [link](HardwareOverview/dock.md#expansion-stacking-limitations)  |
|                       | Base not seated correctly                         | Try reseating it                                              | [link](HardwareOverview/dock.md#base-charging)  |

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

## Calibration
| Issue                                     | Possible cause    | Possible solution      | More info |
|-------------------------------------------|-------------------|------------------------|-----------|
| Can't perform/complete calibration        |
| Tokens don't stay directly below base     |

## Foundry VTT
| Issue                                         | Possible cause                                    | Possible solution                             | More info |
|-----------------------------------------------|---------------------------------------------------|-----------------------------------------------|-----------|
| Can't see module in Foundry's module page     | No internet connection                            | Make sure you are connected to the internet   |
|                                               | Foundry server down                               | Wait until the server is up again             |
|                                               | Incompatible Foundry version                      | Upgrade/downgrade to a compatible version     |
|                                               | Bug in the module                                 | Report it to me                               |
|                                               | Bug in Foundry                                    | Report it to the Foundry team                 |
| Can't install module                          | Bug in the module                                 | Report it to me                               |
|                                               | Bug in Foundry                                    | Report it to the Foundry team                 |
| Can't update module                           | No internet connection                            | Make sure you are connected to the internet   |
|                                               | Incompatible Foundry version                      | Upgrade/downgrade to a compatible version     |
|                                               | Bug in the module                                 | Report it to me                               |
|                                               | Bug in Foundry                                    | Report it to the Foundry team                 |
| Sensor won't connect to module                | Sensor not connected to WiFi                      | See [above](#sensor)                          |
|                                               | Incorrect 'Connection Mode' selected              | Select correct mode                           | [link](Foundry/foundryConnection.md)
|                                               | Incorrect 'Sensor Module IP Address' configured   | Configure correct address                     | [link](Foundry/foundryConnection.md)
|                                               | Foundry server is secured                         | Connect through Material Companion            | [link](Foundry/foundryConnection.md)
| Tokens don't move                             |
| Wrong tokens are being moved                  |
| Tokens don't stay directly below base         |
| Tokens are not dropped after releasing base   |
| Tokens can move through walls                 |

## Material Companion
| Issue                                         | Possible cause    | Possible solution      | More info |
|-----------------------------------------------|-------------------|---------------|-----------|
| Can't start Material Companion                |
| Sensor can't connect to Material Companion    |


## Performance
| Issue                                                     | Possible cause    | Possible solution      | More info |
|-----------------------------------------------------------|-------------------|------------------------|-----------|
| Sensor is updating very slow (in 'Coordinates' section)   |
| Token movement is updated very slow                       |