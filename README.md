# DemoEsp2Ard_ESP32_tembed

[Esp2Ard](https://github.com/blake5634/ESP2Ard) is a related package that supports serial communication between ESP32 and Arduino.

[DemoEsp2Ard_ESP32_tembed](https://github.com/blake5634/DemoESP2Ard_ESP32_tembed) (this repo) is a demo of ESP2Ard which has been developed for the [Lilygo T-embed](https://www.lilygo.cc/products/t-embed) ESP32-based user I/O kit. I'm aiming for a nice way to add a UI for configuring an Arduino app without reflashing.

This code is set up to build on IDF. IDF is a professional grade tool chain for building and flashing ESP32s.   As of 10/23 ESP2Ard  does not yet support ESP32 on the Arduino IDE.

Here is a linux-oriented step-by-step for getting this to run.

1) This demo is based on the [LilyGo T-Embed repository](https://github.com/Xinyuan-LilyGO/T-Embed/tree/main)

2) First install ESP-IDF using [these instructions from Espressif](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/).

3) Follow their documentation and build, flash, and test the "hello world" example.  This will make sure you get the details such as correct USB tty  device for uploading code to ESP32. 1

4) Then, navigate to the [example](https://github.com/Xinyuan-LilyGO/T-Embed/tree/main/example/esp-idf-v5.0) of an `idf.py` project which includes nice graphics and UI elements.

5) Get that example (esp-idf-v5.0) working on your T-embed hardware (see AliExpress or Amazon). Observe UI elements change on its screen when you move the scroll wheel etc.

6) Now navigate to your clone of this repo.   ESP2Ard is already included but may not be the latest version.  The next two steps might not be needed but it would be better to get the latest version:

7) go into `main` and clone [Esp2Ard](https://github.com/blake5634/ESP2Ard).

8) Copy `ESP2Ard.c` and `ESP2Ard.h` back up in to `main` (do not copy the `.cpp` version per note below).

9) go back to the project level (`DemoEsp2Ard_ESP32_tembed`) and initialize the idf.py environment with `>get_idf` (I find you have to do this again sometimes if your computer goes to sleep and you wake it up).  Probably also a good idea to do `>idf.py fullclean` to start fresh.

7) try to build it! (`> idf.py build`). In case of build problems see Espressif's documentation and ask ChatGPT.

8) try to flash it into your T-embed.

9) T-embed App guide for this code:

1. should see three buttons.  You can move a highlight outline to select one.
2. Move to `Set Name' and turn the wheel. Names should change in the bottom row.
5. Turn the wheel until "HH:MM" is selected in a red outline.
7. Press the button - the outline turns green
9. Turn the wheel and the time changes from 06:30 as you turn the wheel
11. Press the button again and you go back to red outline for button select.

#### THIS IS WHEN THE SERIAL DATA IS SENT OUT ON YOUR PORT (the new time value is sent)

##### Suggested hardware setup (works for me).

   - soldered 20-AWG wires into pin holes 16, 17 and GND on the T-embed (see [pinout](https://github.com/Xinyuan-LilyGO/T-Embed/blob/main/image/T-Embed1.png))
   - plug them in to pins 2,3,GND respectively on Arduino Uno.

##### The [Esp2Ard](https://github.com/blake5634/ESP2Ard) repo includes a .ino file to run on the Arduino for receiving this data and echoing it on the USB back to your PC.


#### Note on naming:

##### Code files ESP2Ard.c / ESP2Ard.cpp
You must use the ".c" name for building in ESP32 IDF environment and the ".cpp" name for building in the Arduino environment (at least for software serial).

