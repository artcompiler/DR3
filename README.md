DR3
===

USAGE

After loading DR3 with the code in dr3.ino, place the bot on whatever surface you want to be marked.

Then following the following instructions to control the bot from an iOS device that supports Bluetooth 4.0.

1. Download Bluetooth testing software LightBlue for iOS (https://itunes.apple.com/us/app/lightblue-bluetooth-low-energy/id557428110?mt=8)
2. Start LightBlue and turn on bot.
3. Select "Periphrial" named "ZeroBeacon"
4. Select "Characteristic 1" (bottom of screen)
5. Select "Write new value"
6. Type bytecode command (see source code. e.g. '03' will draw a circle)
7. Select "Done". (the bot should start moving)
