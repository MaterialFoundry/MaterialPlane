<b>This module requires external hardware that you probably don't have lying around, which means that you have to spend (at least) $40 on getting this module to work. The module is still in development, and probably contains bugs. Make sure that you're willing to risk spending money on something that might not work as intended.<br></b>
<br>
You can currently place a pre-order for pre-build hardware from my webshop: <a href="https://www.materialfoundry.nl/">https://www.materialfoundry.nl/</a><br>

### [Documentation](https://materialfoundry.github.io/MaterialPlane/)

# Material Plane
Material Plane is a <a href="https://foundryvtt.com/">Foundry VTT</a> module that allows physical minis to be tracked by Foundry when using a horizontally mounted TV. This allows you to bring the joy of physical minis into Foundry.<br>
<br>
There are currently 2 ways to track minis:<br>

## Material Plane sensor
The system consists of an IR sensor, and IR enabled mini bases. These bases contain IR LEDs that are tracked by the sensor. The sensor then relays this information to foundry over WiFi, where the information is interpreted as token movement.<br>
You can use any TV, monitor or projector for this.<br>
There is a pre-assembled and advanced version of the hardware for sale on the [Material Foundry webshop](https://www.materialfoundry.nl/), or it is possible to build DIY hardware.

## Touch Screen
There is currently experimental support for touch screen devices (broken in Foundry v11, though). Either capacitive touch screens or normal TVs with an IR touch frame can work.<br>
<br>
Please take a look at [this](https://materialfoundry.github.io/MaterialPlane/hardwareComparison/) page for a comparison between the Material Plane sensor and touch screen.<br>

## Trailer
<a href="https://www.youtube.com/watch?v=VVTjNrCfUwM">
<img border="0" alt="trailer" src="img/Trailer Thumbnail.png" width="100%">
</a>

# Important Links
* [Documentation](https://materialfoundry.github.io/MaterialPlane/)
* [Issues/Feature requests](https://github.com/MaterialFoundry/MaterialPlane/issues)
* [Main repository](https://github.com/materialfoundry/materialplane)
* [Foundry module](https://github.com/MaterialFoundry/MaterialPlane_Foundry) ([Releases](https://github.com/MaterialFoundry/MaterialPlane_Foundry/releases))
* [Sensor firmware](https://github.com/MaterialFoundry/MaterialPlane_Sensor) ([Releases](https://github.com/MaterialFoundry/MaterialPlane_Sensor/releases))
* [Base firmware](https://github.com/MaterialFoundry/MaterialPlane_Base) ([Releases](https://github.com/MaterialFoundry/MaterialPlane_Base/releases))
* [Pen firmware](https://github.com/MaterialFoundry/MaterialPlane_Pen) ([Releases](https://github.com/MaterialFoundry/MaterialPlane_Pen/releases))
* [Material Companion](https://github.com/MaterialFoundry/MaterialCompanion) ([Releases](https://github.com/MaterialFoundry/MaterialCompanion/releases))
* [Arduino core](https://github.com/MaterialFoundry/MaterialFoundry_Arduino) ([Releases](https://github.com/MaterialFoundry/MaterialFoundry_Arduino/releases))
* [3D models](https://github.com/MaterialFoundry/MaterialPlane_Models)
* [Discord server](https://discord.gg/3hd4G6TkmA)
* [Patreon](https://www.patreon.com/materialfoundry)

## Software Versions & Module Incompatibilities
<b>Foundry VTT:</b> v10 & v11<br>
<b>Module Incompatibilities:</b> When moving tokens, Foundry's click and drag system is bypassed. So modules that depend on that functionality might not work.<br>

## Feedback
If you have any suggestions or bugs to report, feel free to contact me on Discord (Cris#6864), or send me an email: cdeenen@outlook.com.

## Credits
<b>Author:</b> Cristian Deenen (Cris#6864 on Discord)<br>
<br>
Please consider supporting me on <a href="https://www.patreon.com/materialfoundry">Patreon</a>, and feel free to join the Material Foundry <a href="https://discord.gg/3hd4G6TkmA">Discord</a> server.

## Abandonment
Abandoned modules are a (potential) problem for Foundry, because users and/or other modules might rely on abandoned modules, which might break in future Foundry updates.<br>
I consider this module abandoned if all of the below cases apply:
<ul>
  <li>This module/github page has not received any updates in at least 3 months</li>
  <li>I have not posted anything on "the Foundry" and "the League of Extraordinary Foundry VTT Developers" Discord servers in at least 3 months</li>
  <li>I have not responded to emails or PMs on Discord in at least 1 month</li>
  <li>I have not announced a temporary break from development, unless the announced end date of this break has been passed by at least 3 months</li>
</ul>
If the above cases apply (as judged by the "League of Extraordinary Foundry VTT Developers" admins), I give permission to the "League of Extraordinary Foundry VTT Developers" admins to assign one or more developers to take over this module, including requesting the Foundry team to reassign the module to the new developer(s).<br>
I require the "League of Extraordinary Foundry VTT Developers" admins to send me an email 2 weeks before the reassignment takes place, to give me one last chance to prevent the reassignment.<br>
I require to be credited for my work in all future releases.
