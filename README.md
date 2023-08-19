# pool-light-controller
Code to control a Pentair IntelliBrite light by using an ESP32 microcontroller with an attached relay.

Pentair IntelliBrite lights can be changed to different preprogrammed colors and scenes by cycling the power. The full list of scenes can be found in the [manual](https://www.pentair.com/content/dam/extranet/nam/pentair-pool/residential/manuals/lighting/intellibrite-5g-white-color-pool-spa-lights-manual-english-french.pdf). This controller code runs on an ESP microcontroller and can cycle the power via an attached relay. The code also connects to wifi and implements a REST interface that enables the attached IntelliBrite light to be connected to a home automation system.
