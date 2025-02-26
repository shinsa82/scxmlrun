# MQTT over Websocket

Although web browsers do not support MQTT directly,
they still can process MQTT messages using the following components.

1. JavaScript module, called [`mqttws`](https://github.com/eclipse/paho.mqtt.javascript/tree/master/src/paho-mqtt.js)
   developed by the [Eclipse Paho](https://projects.eclipse.org/projects/technology.paho/) project,
   for receiving/transmitting MQTT messages over Websocket packets.

   The module can be loaded into a html by simply adding a `<script src="...">` line.  
   Refer to [^1] for the detail.

1. MQTT/Websocket bridge functionality of [mosquitto](https://mosquitto.org/).

   It may need to be configured to activate this functionality.
   See the instruction below.  


## Mosquitto configuration

To configure `mosquitto` to work as a bridge between MQTT and Websocket,
you need to take the following steps.

1. create `/etc/mosquitto/conf.d/websockets.conf` with the following lines.

   ```
   listener 1883  
   listener 9001  
   protocol websockets
   ```

1. restart mosquitto

   ```$ service mosquitto restart```

1. check out `mosquitto.log` and
   make sure that `port 9001` is opened for Websocket packets.

   <details>
   <summary>mosquitto log</summary>
   <div>
   <pre>
   $ tail /var/log/mosquitto/mosquitto.log
   1539619797: mosquitto version 1.4.15 (build date Sat, 07 Apr 2018 11:16:43 +0100) starting
   1539619797: Config loaded from /etc/mosquitto/mosquitto.conf.
   1539619797: Opening ipv4 listen socket on port 1883.
   1539619797: Opening ipv6 listen socket on port 1883.
   1539619797: <b>Opening websockets listen socket on port 9001</b>.
   </pre>
   </div>
   </details>


## Caveats

- Safari (v12.0) refuses to load the [MQTT client module](https://github.com/eclipse/paho.mqtt.javascript/tree/master/src/paho-mqtt.js)
  in JavaScript for a security reason.
  It seems "LocalStorage" operations in the module are considered as potential security threats.

- Firefox (v60.2) also refuses to load the module when it is specified as

  ```
  <script src="https://cdnjs.cloudflare.com/ajax/libs/paho-mqtt/1.0.1/mqttws31.min.js"
          type="text/javascript">
  </script>
  ```

  This is perhaps since its certificate (might have) expired. not sure.  
  As a work-around, the module has been copied and is loaded locally.

## References
[^1]:
  [Paho JavaScript client API](http://www.eclipse.org/paho/files/jsdoc/Paho.MQTT.Client.html)

[^2]:
  [Mosquitto configuration](https://mosquitto.org/man/mosquitto-conf-5.html)
