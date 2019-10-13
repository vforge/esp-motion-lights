# esp-motion-lights

ESP3266: Motion Detection + Lights on D1 mini

```yaml
  - platform: mqtt
      state_topic: "ESP-PIR-01/feeds/motion"
      name: PIR Sensor
      payload_on: "ON"
      payload_off: "OFF"
      qos: 0
      device_class: motion
```
