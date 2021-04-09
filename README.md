I created the <a href="https://discord.gg/3hd4G6TkmA">Material Foundry</a> Discord server to discuss this and other hardware-based Foundry modules. Feel free to join if you'd like to be updated on this module.<br>
<br>
<b>Both the module and the Arduino firmware are very much outdated since I've been focusing on developing new hardware, but this will change soon (April 2021)</b>

<b>This module requires external hardware that you probably don't have lying around, which means that you have to spend (at least) $40 on getting this module to work. The module is still in development, and probably contains bugs. Make sure that you're willing to risk spending money on something that might not work as intended.<br>
The hardware is currently in the process of getting an upgrade. I'll probably keep supporting the current version, but I can't promise anything.<br>
If you're uncomfortable with this, please wait until the project has been developed a bit further.</b>

### Pre-Build Kits
It is possible to build the required hardware yourself, but there might be people interested in buying a pre-build kit, consisting of a sensor module and some IR bases. I currently do not sell anything, but that will change in the future. I'm also thinking about starting a kickstarter campaign, which would allow much higher quality hardware and at a larger scale than what I could build in my tiny workshop.<br>
<br>
<b>I'm currently working on new and improved hardware for the pre-build kit. Unless you really want to use Material Plane right now, I'd suggest you wait a bit. Updates can be found on the Material Foundry Discord server, and a summary can be found here:</b><br>
### <a href="https://github.com/CDeenen/MaterialPlane/wiki/Current-State-of-Material-Plane">Current state of Material Plane</a>

# Material Plane
Material Plane is a <a href="https://foundryvtt.com/">Foundry VTT</a> module that allows physical minis to be tracked by Foundry when using a horizontally mounted TV. This allows you to bring the joy of physical minis into Foundry.<br>
<br>
The system consists of an IR sensor, and IR enabled mini bases. These bases contain IR LEDs that are tracked by the sensor. The sensor then relays this information to foundry over WiFi, where the information is interpreted as token movement.<br>
<br>
You can use any TV, monitor or projector for this.

[![Youtube Video](https://github.com/CDeenen/MaterialPlane/blob/master/Module/img/YoutubeVid.png)](https://youtu.be/y_IouB-SDnk "FoundryVTT IR Mini Control")

# Instructions and More Info
Instructions and more info can be found in the <a href="https://github.com/CDeenen/MaterialPlane/wiki">wiki</a> (still a work in progress).

## Software Versions & Module Incompatibilities
<b>Foundry VTT:</b> Tested on 0.6.6<br>
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
