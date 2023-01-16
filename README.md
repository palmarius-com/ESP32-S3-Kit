# ESP32-S3-Kit
https://www.tindie.com/products/palmarius/esp32-s3-devboard-modular/

#### What is it?
The kit contains a super compact  ESP32-S3-WROOM-1-N16R8, a Breadboard-Adapter to test before using it in a Project, a Programmer that can be toggled via a switch to provide 5V or 3.3 Volts, two USB-C Ports that can also be used independently. Datasheet is a 3D-PDF: download and use free AdabeAcrobat Reader-DC (https://get.adobe.com/de/reader/)

#### Why did you make it?
Because I could not find anything like this on the market.
This is the ESP32-Setup that I would have loved to receive when I first started with Arduino-Electronis.
Being able to put this on the breadboard with two spare rows next to each pin is a dream come true.
All other DevBoards I had over time fit on a breadboard but cover all pins with no spare to actually put a jumper-wire.

#### What makes it special?
The ESP has the smallest Footpring imaginable. All Pins are exposed for maximum capabilities, without increasing the size of the Footprint.
Together with the Breadboard Adapter, the ESP can be tested and firmware can be uploaded.
After finishing your project, you can just unplug the ESP and use it in your setup with no space wasted at all. Every Pin has a neighboring space on a 100mil pcb-grid, so even though the footprint is tiny, all pins are accessible and no SMD soldering is required to get the ESP into your projects.

The base is equipped with a locking switch to allow the boot/program mode and normal operation.
I just never liked the idea of pulling jumpers (and lose them...)
A green LED indicates the normal operation of the ESP, and a red one indicates the boot mode.
Both LEDs are in a separate circuit so they don't drain the power of the programming pins or influence the behavior in any way.

All parts can be used independently. 
I already spoke about the ESP (check out the 3D-PDF), the Programmer fits on the ESP-Base but can also be used for other projects. The complete board can toggle between 5 and 3.3Volts, so also the RX-TX Lines are toggled. I even added a UPDI pin to program AVR controllers.

The USB-C exposes all pins required for USB-PD and is Breadboard compatible for other uses.
