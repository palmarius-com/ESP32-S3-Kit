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
*/

//#define LED_Test 

#include "Streaming.h"

// Prototyes
void RunLeft();
void RunRight();
void ExcuteBlink(int pNum, bool longOn);

// Console.ino
extern boolean newConsoleData;
extern int pinNumber;
void handleConsoleInput();

// other file

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

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  newConsoleData = false;
  pinNumber = 100;
  // initialize digital pin LED_BUILTIN as an output.

  delay(500);
  Serial << endl;
  
  option = opNone;
  startUp = true;
  
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
      delay(500);
      break;
    case opBlink: ExcuteBlink(pinNumber, false);  break;
    case opLeft:  RunLeft();  break;
    case opRight: RunRight(); break;
  }
} // loop()


void ExcuteBlink(int pNum, bool longOn)
{
  pinMode(pNum, OUTPUT);
  Serial << "Switching HIGH: '" << pNum << "'" <<endl;
#ifdef LED_Test
  if(pNum == 4) digitalWrite(pNum, LOW); 
  else 
#endif
  digitalWrite(pNum, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  if(longOn) delay(1000);
  else delay(100);
  Serial << "Switching  LOW: '" << pNum << "'" <<endl;
#ifdef LED_Test
  if(pNum == 4) digitalWrite(pNum, HIGH);
  else
#endif
  digitalWrite(pNum, LOW); // turn the LED off by making the voltage LOW
  
  if(longOn) delay(100);
  else delay(300);
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
