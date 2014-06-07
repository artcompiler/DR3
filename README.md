DR3
===

USAGE

After loading DR3 with the code in dr3.ino, place the bot on whatever surface you want to be marked.

Then follow the following instructions to control the bot from an iOS device that supports Bluetooth 4.0.

1. Download Bluetooth testing software LightBlue for iOS (https://itunes.apple.com/us/app/lightblue-bluetooth-low-energy/id557428110?mt=8)
2. Start LightBlue and turn on bot.
3. Select the "Peripherial" named "ZeroBeacon"
4. Select "Characteristic 1" (bottom of screen)
5. Select "Write new value"
6. Type a bytecode command (see source code. e.g. '03' will draw a circle)
7. Select "Done". (the bot should start moving)

Bytecode commands can be chained together. (e.g. '020909090901' puts the pen down and moves forward a bit and lifts the pen up.). Just make sure the commands are each two digit (byte) format.
