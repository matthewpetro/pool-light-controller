# pool-light-controller
Code to control a Pentair IntelliBrite light by using an [ESP32 microcontroller](https://www.espressif.com/en/products/socs/esp32) with an attached relay.

Pentair IntelliBrite lights can be changed to different preprogrammed colors and scenes by cycling the power. The full list of scenes can be found in the [manual](https://www.pentair.com/content/dam/extranet/nam/pentair-pool/residential/manuals/lighting/intellibrite-5g-white-color-pool-spa-lights-manual-english-french.pdf). This controller code runs on an ESP32 microcontroller such as the [Adafruit HUZZAH32](https://www.adafruit.com/product/3619) and can cycle the power via an attached relay. The code also connects to wifi and implements an HTTP interface that enables the attached IntelliBrite light to be connected to a home automation system.

Also included in this repo is a tool that can save the wifi SSID and password in flash memory on the ESP32. This avoids the need for the wifi credentials to be built into the controller code and makes it significantly less likely that the credentials will accidentally get committed into the repo.
