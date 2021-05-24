# StatusLight
Simple ESP8266 project to turn beacon lights into status lights

This project is based on the ESP8266 Web GPIO example from https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/

The circuit is dead simple, so anyone with some electronics knowledge should be able to modify it.

Two resistors and a button is added if the board does not reset correctly when power is connected.

![IMG1621852591](https://user-images.githubusercontent.com/11834016/119335457-5d042a80-bcc7-11eb-8bdd-8ecce2ca2d9c.png)

The button is optional, but saves you a hassle if you mount this in a case thus cannot reach the on-board reset button easily. (Note: you can simply connect a button between RST and GND. The circuit was originally designed for Normally Closed switch because that's what I had at the moment.)
