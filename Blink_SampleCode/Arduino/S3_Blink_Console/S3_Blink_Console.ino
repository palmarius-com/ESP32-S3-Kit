/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink

  Update by 'palmarius' DEZ2022
  - added Streaming for easier Output an the Console 
    (Mikal Hart) http://arduiniana.org/libraries/streaming/
    https://github.com/geneReeves/ArduinoStreaming
  - added ConsoleInput for more interactivity and testing capability
    https://forum.arduino.cc/t/serial-input-basics-updated/382007




  -DF_CPU=240000000L -DARDUINO=10819 -DARDUINO_PROS3 -DARDUINO_ARCH_ESP32 "-DARDUINO_BOARD=\"PROS3\"" "-DARDUINO_VARIANT=\"um_pros3\"" 
  -DARDUINO_PARTITION_default_16MB -DESP32 -DCORE_DEBUG_LEVEL=0 -DARDUINO_RUNNING_CORE=1 -DARDUINO_EVENT_RUNNING_CORE=1 
  -DBOARD_HAS_PSRAM -DARDUINO_USB_MODE=1 -DARDUINO_USB_CDC_ON_BOOT=0 -DARDUINO_USB_MSC_ON_BOOT=0 -DARDUINO_USB_DFU_ON_BOOT=0
*/

//#define LED_Test 

#include "Streaming.h"

int pinNumber = 100;

// Console.ino
boolean newConsoleData = false;
void handleConsoleInput();

int idle = 0;

enum Options {
  opNone,
  opBlink,
  opLeft,
  opRight
  };

Options option = opNone;
bool startUp = true;

int sequence = 0;

//
void SetAll(uint8_t state);
void ExcuteBlink(int pNum, bool longOn);
void RunLeft();
void RunRight();

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
 
  delay(500);
  Serial << endl;
  
  option = opNone;
  startUp = true;

  delay(250);
  SetAll(LOW);
  delay(250);
  SetAll(HIGH);
  
  Serial << "Setup done !" << endl;
} // setup

// the loop function runs over and over again forever
void loop() {
  handleConsoleInput();

  switch(pinNumber)
  {
    case  0:    case  1:    case  2:    case  3:    case  4:    case  5:    case  6:    case  7:    case  8:    case  9:
    case 10:    case 11:    case 12:    case 13:    case 14:    case 15:    case 16:    case 17:    case 18:    case 21:
    case 35:    case 36:    case 37:    case 38:    case 39:    case 40:    case 41:    case 42:
    case 45:    case 46:    case 47:    case 48:
      option = opBlink;
      break;
    case 19:    case 20:
      Serial << "GPIO_'" << pinNumber << "' is used for USB-only!!" <<endl;
      option = opNone;
      break;
    case 43:    case 44:
      Serial << "GPIO_'" << pinNumber << "' is used for UART only!!" <<endl;
      option = opNone;
      break;
    case 77: option = opLeft;  break; // Run Left
    case 99: option = opRight; break; // Run Right
    default:
      if(!(pinNumber == 100 && startUp == true))
      {
        Serial << "GPIO_'" << pinNumber << "' does not exist!!" <<endl;
      }
      option = opNone;
      break;
  }

  switch(option)
  {
    case opNone:  sequence = 0; break;
    case opBlink: sequence = 0; startUp = false; break;
    case opLeft:  case opRight: startUp = false; break;
  }
  
  switch(option)
  {
    case opNone:
      Serial << "idle " << idle++ << endl;
      if(idle > 9) idle = 0;
      delay(300);
      break;
    case opBlink: ExcuteBlink(pinNumber, false);  break;
    case opLeft:  RunLeft();  break;
    case opRight: RunRight(); break;
  }
} // loop()


void ExcuteBlink(int pNum, bool longOn)
{
  // pinMode(pNum, OUTPUT);
  Serial << "Switching LOW: '" << pNum << "'" <<endl;
  digitalWrite(pNum, LOW);   // turn the LED on (LOW because other side of LED is connected to VCC)
  
  if(longOn) delay(1000);
  else delay(100);

  Serial << "Switching  HIGH: '" << pNum << "'" <<endl;
  digitalWrite(pNum, HIGH); // turn the LED off by making the voltage HIGH
  
  if(longOn) delay(100);
  else delay(300);
} 

void SetAll(uint8_t state)
{
  // GAP  GND ##########################               
  // GAP  EN  ########################## 
  pinMode( 5, OUTPUT);
  pinMode( 7, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(18, OUTPUT);
  // GAP  19 ###########################
  pinMode( 3, OUTPUT);
  pinMode( 9, OUTPUT);
  pinMode(12, OUTPUT);
  // GAP  NC-Pin #######################
  // GAP  3v3 ##########################               
  pinMode( 4, OUTPUT);
  pinMode( 6, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode( 8, OUTPUT);
  // GAP  20 ###########################
  pinMode(46, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  // other side ########################
  // GAP  GND ########################## 
  // GAP  TX  ########################## 
  // GAP  RX  ########################## 
  pinMode(41, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(14, OUTPUT);
  // GAP  NC-Pin #######################
  pinMode( 1, OUTPUT);
  pinMode( 2, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode( 0, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(13, OUTPUT);
  //------------------------------------
  // GAP  GND ##########################               
  // GAP  EN  ########################## 
  digitalWrite( 5, state);
  digitalWrite( 7, state);
  digitalWrite(16, state);
  digitalWrite(18, state);
  // GAP  19 ###########################
  digitalWrite( 3, state);
  digitalWrite( 9, state);
  digitalWrite(12, state);
  // GAP  NC-Pin #######################
  // GAP  3v3 ##########################               
  digitalWrite( 4, state);
  digitalWrite( 6, state);
  digitalWrite(15, state);
  digitalWrite(17, state);
  digitalWrite( 8, state);
  // GAP  20 ###########################
  digitalWrite(46, state);
  digitalWrite(10, state);
  digitalWrite(11, state);
  // other side ########################
  // GAP  GND ########################## 
  // GAP  TX  ########################## 
  // GAP  RX  ########################## 
  digitalWrite(41, state);
  digitalWrite(39, state);
  digitalWrite(37, state);
  digitalWrite(35, state);
  digitalWrite(45, state);
  digitalWrite(47, state);
  digitalWrite(14, state);
  // GAP  NC-Pin #######################
  digitalWrite( 1, state);
  digitalWrite( 2, state);
  digitalWrite(42, state);
  digitalWrite(40, state);
  digitalWrite(38, state);
  digitalWrite(36, state);
  digitalWrite( 0, state);
  digitalWrite(48, state);
  digitalWrite(21, state);
  digitalWrite(13, state);
}

void RunLeft()  // #####################   L E F T   #####################
{
  switch(sequence)
  {
    // GAP  GND ##########################               
    // GAP  EN  ########################## 
    case  0: ExcuteBlink( 5, true); break;
    case  1: ExcuteBlink( 7, true); break;
    case  2: ExcuteBlink(16, true); break;
    case  3: ExcuteBlink(18, true); break;
    // GAP  19 ###########################
    case  4: ExcuteBlink( 3, true); break;
    case  5: ExcuteBlink( 9, true); break;
    case  6: ExcuteBlink(12, true); break;
    // GAP  NC-Pin #######################
    // GAP  3v3 ##########################               
    case  7: ExcuteBlink( 4, true); break;
    case  8: ExcuteBlink( 6, true); break;
    case  9: ExcuteBlink(15, true); break;
    case 10: ExcuteBlink(17, true); break;
    case 11: ExcuteBlink( 8, true); break;
    // GAP  20 ###########################
    case 12: ExcuteBlink(46, true); break;
    case 13: ExcuteBlink(10, true); break;
    case 14: ExcuteBlink(11, true); break;
    default: sequence = -1;         break;
  }
  sequence++;
}

void RunRight() // #####################   R I G H T   ###################
{
  switch(sequence)
  {
    // GAP  GND ########################## 
    // GAP  TX  ########################## 
    // GAP  RX  ########################## 
    case  0: ExcuteBlink(41, true); break;
    case  1: ExcuteBlink(39, true); break;
    case  2: ExcuteBlink(37, true); break;
    case  3: ExcuteBlink(35, true); break;
    case  4: ExcuteBlink(45, true); break;
    case  5: ExcuteBlink(47, true); break;
    case  6: ExcuteBlink(14, true); break;
    // GAP  NC-Pin #######################
    case  7: ExcuteBlink( 1, true); break;
    case  8: ExcuteBlink( 2, true); break;
    case  9: ExcuteBlink(42, true); break;
    case 10: ExcuteBlink(40, true); break;
    case 11: ExcuteBlink(38, true); break;
    case 12: ExcuteBlink(36, true); break;
    case 13: ExcuteBlink( 0, true); break;
    case 14: ExcuteBlink(48, true); break;
    case 15: ExcuteBlink(21, true); break;
    case 16: ExcuteBlink(13, true); break;
    default: sequence = -1;         break;
  }
  sequence++;
}
