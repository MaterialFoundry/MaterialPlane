It is necessary to establish a connection between the sensor and your Foundry client.

In the very least, the Foundry client that is displayed on the shared display must connect to the sensor.<br>
Optionally, the gamemaster's client can also connect to the sensor. Doing this gives the gamemaster access to the sensor configuration, which might make configuration easier.

You will need to configure the connection for each client separately, and you will need to make sure that the display client is set as the 'Active User' in the [Material Plane Configuration](foundryConfig.md).

The connection between the Foundry client and sensor can be established over WiFi, or through the USB port (currently not functional).

## WiFi Connection to Foundry
Before we continue, it is necessary to properly establish the difference between the Foundry server and any clients that connect to it, and the difference between secured and unsecured servers.

### Client vs Server
Whenever you or your players use Foundry, there will be a single server. This server can take one of multiple forms:

* Part of the Foundry application, this is always the case if one user is running the Foundry application.
* A local server, for example, a computer in your office that runs a dedicated Foundry server.
* A remote server, for example, using [the Forge](https://forge-vtt.com/), [Molten Hosting](https://moltenhosting.com/), or another service that provides servers.

Anyone accessing Foundry, is doing so through a client. There's basically only 2 different client forms:

* Part of the Foundry application (the application is both a server and a client).
* Through a browser

Material Plane never talks directly to your Foundry server, it only connects to one or more clients.<br>
For this reason, it does not matter how or where the server is hosted.

### Secured vs Unsecured Servers
Most websites you visit on the internet are secured using SSL certificates, which allows safe, encrypted communication. Whether or not a website or server is secured can be identified by the lock to the left of your browsers navigation bar.<br>
Most remote Foundry servers (such as servers hosted on the Forge or Molten Hosting) are secured.<br>
Local Foundry servers are, by default, not secured. If yours is, you probably know this already, because you've had to configure it yourself.

For local gaming (so both the server and clients on your home network), there is no reason to secure the server, and to make connecting to the sensor easy, I would recommend that you do not secure it.

The reason this is important, is that the sensor cannot currently provide a secured connection. If your server is secured, the sensor is therefore not allowed (by your browser) to connect to the Foundry client. The result of this is that you will need to connect to the sensor through Material Companion, which can bridge this gap between the sensor and Foundry client.

### Connection options
When connecting the sensor to the VTT over WiFi, you have 2 options:

* <b>Direct Connection:</b> The sensor connects directly to the VTT.
* <b>Through Material Companion:</b> The sensor connects to Material Companion, which then connects to the VTT.

The direct connection is preferable, but not always possible. For example, if your Foundry server is secured (see above).<br>
This is where Material Companion comes into play: it connects to the client from the computer, which is allowed for secured servers. Material Companion can then connect to the sensor and pass all the data through.

#### Direct Connection
![Screenshot](../../img/foundry/Foundry_Module_Connection.png){align=right width=50%}

It is assumed that your sensor is already [connected to your WiFi network](../SensorConfiguration/sensorConnecting.md).

For a direction connection between the sensor and client, you will need to open the [Material Plane Configuration](foundryConfig.md) and head over to the 'Connection' tab. Here, set the 'Connection Mode' to 'Connect Directly to the Sensor'.<br>
Below that, in the 'Sensor Module IP Address', fill in the sensor IP and port. By default, this is 'materialsensor.local:3000'. If this doesn't work, try figuring out the [correct sensor address](../SensorConfiguration/sensorConnecting.md#sensor-address). 

#### Connection Through Material Companion
![Screenshot](../../img/foundry/Foundry_Module_Connection_MC.png){align=right width=50%}

It is assumed that your sensor is already [connected to your WiFi network](../SensorConfiguration/sensorConnecting.md).

Make sure [Material Companion](https://github.com/MaterialFoundry/MaterialCompanion/wiki) is running on the same computer as the client. If both the display client and gamemaster client need to connect to the sensor, make sure Material Companion is running on both computers.

To configure the connection, you will need to open the [Material Plane Configuration](foundryConfig.md) and head over to the 'Connection' tab. Here, set the 'Connection Mode' to 'Connect Through Material Companion'.<br>
Below that, in the 'Material Companion IP Address', fill in the Material Companion IP and port. By default, this is 'localhost:3001'.

## USB Connection to Foundry
<b>Currently unsupported.</b>