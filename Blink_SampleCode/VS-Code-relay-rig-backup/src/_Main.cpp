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
#include "MCP23017.h"
#include "Wire.h"

MCP23017 MCP_L(0x20);
MCP23017 MCP_R(0x21);

//#include "Streaming.h"
#include <Streaming.h>

extern int pinNumber0;
extern int pinNumber1;


// Console.ino
extern boolean newConsoleData0;
extern boolean newConsoleData1;
void handleConsoleInput0();
void handleConsoleInput1();

int idle = 0;

enum Options {
  opNone,
  opBlink,
  opLeft,
  opRight,
  opTest
  };

Options option = opNone;
bool startUp = true;

int sequence = 0;

void SetAll(uint8_t state);
void ExcuteBlink(int pNum, bool longOn);
void ExcuteBlinkMCPonly(int pNum, bool longOn);
void RunLeft();
void RunRight();

void SetRelais(int TestType, int TestStep);
void RunTest();

#define TX_U1PIN 17 // connects to TX on MicroE
#define RX_U1PIN 18 // connects to RX on MicroE

#define I2CSDA 3
#define I2CSCL 4

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200); // Debug Serial Port
  Serial1.begin(9600, SERIAL_8N1, RX_U1PIN, TX_U1PIN); // connection to chroma 19054
//  Serial1.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.

 pinNumber0 = 100;
 pinNumber1 = 100;

  Wire.begin(I2CSDA, I2CSCL);
  MCP_L.begin();
  MCP_R.begin();
  
  delay(500);
  Serial << endl;
  Serial1 << endl;
  
  MCP_L.pinMode16(0x0000);
  MCP_R.pinMode16(0x0000);
  // reset All
  MCP_L.write16(0x0000); // NO
  MCP_R.write16(0x0000); // NC
  
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
 handleConsoleInput0();
  handleConsoleInput1();
  
  switch(pinNumber0)
  {
    case  0:    case  1:    case  2:  /*case  3:    case  4:*/  case  5:    case  6:    case  7:    case  8:    case  9:
    case 10:    case 11:    case 12:    case 13:    case 14:    case 15:    case 16:  /*case 17:    case 18:*/  case 21:
    case 35:    case 36:    case 37:    case 38:    case 39:    case 40:    case 41:    case 42:
    case 45:    case 46:    case 47:    case 48:
      option = opBlink;
      break;
    case 3:    case 4:
      Serial << "GPIO_'" << pinNumber0 << "' is used for I2C only!!" <<endl;
      option = opNone;
      break;
    case 17:    case 18:
      Serial << "GPIO_'" << pinNumber0 << "' is used for UART_1 only!!" <<endl;
      option = opNone;
      break;
    case 19:    case 20:
      Serial << "GPIO_'" << pinNumber0 << "' is used for USB-only!!" <<endl;
      option = opNone;
      break;
    case 43:    case 44:
      Serial << "GPIO_'" << pinNumber0 << "' is used for UART_0 only!!" <<endl;
      option = opNone;
      break;
  
    case 77: option = opLeft;  break; // Run Left
    case 99: option = opRight; break; // Run Right
    case 300: option = opTest; break; // Run Test


    case 101: // l 1, r alle außer 1
    SetRelais(1, 0);
    break;
    case 102: // l 2, r alle außer 2
    SetRelais(1, 1);
    break;
    case 103: // l 3, r alle außer 3
    SetRelais(1, 2);
    break;
    case 104: // l1, r alle außer 1
    SetRelais(1, 3);
    break;
    case 105: // l1, r alle außer 1
    SetRelais(1, 4);
    break;
    case 106: // l1, r alle außer 1
    SetRelais(1, 5);
    break;
    case 107: // l1, r alle außer 1
    SetRelais(1, 6);
    break;
    case 108: // l1, r alle außer 1
    SetRelais(1, 7);
    break;
    case 109: // l1, r alle außer 1
    SetRelais(1, 8);
    break;

    case 201: // l 1, r 1
    SetRelais(2, 0);
    break;
    case 202: // l 2, r 2
    SetRelais(2, 1);
    break;
    case 203: // l1, r alle außer 1
    SetRelais(2, 2);
    break;
    case 204: // l1, r alle außer 1
    SetRelais(2, 3);
    break;
    case 205: // l1, r alle außer 1
    SetRelais(2, 4);
    break;
    case 206: // l1, r alle außer 1
    SetRelais(2, 5);
    break;
    case 207: // l1, r alle außer 1
    SetRelais(2, 6);
    break;
    case 208: // l1, r alle außer 1
    SetRelais(2, 7);
    break;
    case 209: // l1, r alle außer 1
    SetRelais(2, 8);
    break;

    default:
      if(!(pinNumber0 == 100 && startUp == true))
      {
        Serial << "GPIO_'" << pinNumber0 << "' does not exist!!" <<endl;
      }
      option = opNone;
      break;
  }

  switch(option)
  {
    case opNone:  sequence = 0; break;
    case opBlink: sequence = 0; startUp = false; break;
    case opTest: startUp = false; break;
    case opLeft: case opRight: startUp = false; break;
  }
  
  switch(option)
  {
    case opNone:
      Serial << "idle " << idle++ << endl;
      if(idle > 9) idle = 0;
      delay(1000);
      break;
    case opBlink: ExcuteBlink(pinNumber0, false);  break;
    case opLeft:  RunLeft();  break;
    case opRight: RunRight(); break;
    case opTest: RunTest(); break;
  }

  ExcuteBlinkMCPonly(pinNumber1, false);
} // loop()

void SetRelais(int TestType, int TestStep)
{
//  MCP_L.write16(0x0000); // NO
//  MCP_R.write16(0x0000); // NC

//    for(int i=0; i<9; i++)
//    {
//      MCP_L.digitalWrite(i, HIGH);  
//    }
//    MCP_L.digitalWrite(TestStep, LOW);

  for(int iL=0; iL<9; iL++)
  {
    if(iL == TestStep)
    {
      MCP_L.digitalWrite(iL, LOW); // low active
    }
    else  
    {
      MCP_L.digitalWrite(iL, HIGH);
    }
  }

  if(TestType == 1) //  l 1, r alle außer 1
  {
    for(int ir1=0; ir1<9; ir1++)
    {
      if(ir1 == TestStep)
      {
        MCP_R.digitalWrite(ir1, HIGH);  // low active für TT1 ist 1 aus !!
      }
      else
      {
        MCP_R.digitalWrite(ir1, LOW);    // low active
      }
    }
  }
  else if(TestType == 2) //  l 1, r 1
  {
    for(int ir2=0; ir2<9; ir2++)
    {
      if(ir2 == TestStep)
      {
        MCP_R.digitalWrite(ir2, LOW);   // low active
      }
      else
      {
        MCP_R.digitalWrite(ir2, HIGH);  
      }
    }
  }   
}

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

void ExcuteBlinkMCPonly(int pNum, bool longOn)
{
  if(!(pNum > 0 && pNum < 17)) return;
    
  // pinMode(pNum, OUTPUT);
  Serial1<< "Serial 1  LOW: '" << pNum << "'" <<endl;

  MCP_L.digitalWrite(pNum-1, HIGH);
  MCP_R.digitalWrite(pNum-1, HIGH);
  
  if(longOn) delay(1000);
  else delay(100);

  Serial1<< "Serial 1   HIGH: '" << pNum << "'" <<endl;

  MCP_L.digitalWrite(pNum-1, LOW);
  MCP_R.digitalWrite(pNum-1, LOW);
 
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
  //pinMode(18, OUTPUT); // UART_1_RX
  // GAP  19 ###########################
  //pinMode( 3, OUTPUT); // I2C SDA
  pinMode( 9, OUTPUT);
  pinMode(12, OUTPUT);
  // GAP  NC-Pin #######################
  // GAP  3v3 ##########################               
  //pinMode( 4, OUTPUT); // I2C SCL
  pinMode( 6, OUTPUT);
  pinMode(15, OUTPUT);
  //pinMode(17, OUTPUT); // UART_1_TX
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
  //digitalWrite(18, state); // UART_1_RX
  // GAP  19 ###########################
  //digitalWrite( 3, state); // I2C SDA
  digitalWrite( 9, state);
  digitalWrite(12, state);
  // GAP  NC-Pin #######################
  // GAP  3v3 ##########################               
  //digitalWrite( 4, state); // I2C SCL
  digitalWrite( 6, state);
  digitalWrite(15, state);
  //digitalWrite(17, state); // UART_1_TX
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

void RunTest()
{
  delay(500);
  
  switch(sequence)
  {
    case 0 : SetRelais(1, 0); break;
    case 1 : SetRelais(1, 1); break;
    case 2 : SetRelais(1, 2); break;
    case 3 : SetRelais(1, 3); break;
    case 4 : SetRelais(1, 4); break;
    case 5 : SetRelais(1, 5); break;
    case 6 : SetRelais(1, 6); break;
    case 7 : SetRelais(1, 7); break;
    case 8 : SetRelais(1, 8); break;
    case 9 : SetRelais(2, 0); break;
    case 10 : SetRelais(2, 1); break;
    case 11 : SetRelais(2, 2); break;
    case 12 : SetRelais(2, 3); break;
    case 13 : SetRelais(2, 4); break;
    case 14 : SetRelais(2, 5); break;
    case 15 : SetRelais(2, 6); break;
    case 16 : SetRelais(2, 7); break;
    case 17 : SetRelais(2, 8); break;
    default: sequence = -1;         break;
  }
  sequence++;
}
