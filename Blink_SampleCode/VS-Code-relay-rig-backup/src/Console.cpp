//
//
//

//#include "Streaming.h"
#include <Streaming.h>

int pinNumber0;
int pinNumber1;


// Console.ino
boolean newConsoleData0 = false;
boolean newConsoleData1 = false;

const byte numChars0 = 50;
char receivedChars0[numChars0]; // an array to store the received data
String inString0 = "";  // inString.toInt()

const byte numChars1 = 50;
char receivedChars1[numChars1]; // an array to store the received data
String inString1 = "";  // inString.toInt()

//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Read Characters   //////
//////////////////////////////////////////////////////////////////////////////////////////////
void recvWithEndMarker0() 
{
  static byte ndx0 = 0;
  char endMarker0 = '\n';
  char rc0;
 
  while (Serial.available() > 0 && newConsoleData0 == false) 
  {
    rc0 = Serial.read();
    
    if (rc0 != endMarker0) 
    {
      receivedChars0[ndx0] = rc0;
      ndx0++;
      if (ndx0 >= numChars0) 
      {
        ndx0 = numChars0 - 1;
      }
    }
    else 
    {
      receivedChars0[ndx0] = '\0'; // terminate the string
      inString0 = receivedChars0;
      ndx0 = 0;
      newConsoleData0 = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Handle Inputs     //////
//////////////////////////////////////////////////////////////////////////////////////////////
void handleConsoleInput0() // running in main-loop !!
{
  recvWithEndMarker0();
  if (newConsoleData0 == true) 
  {
    Serial << "received String0: '" << inString0 << "'" << endl;
    pinNumber0 = inString0.toInt();
    newConsoleData0 = false;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Read Characters   //////
//////////////////////////////////////////////////////////////////////////////////////////////
void recvWithEndMarker1() 
{
  static byte ndx1 = 0;
  char endMarker1 = '\n';
  char rc1;
 
  while (Serial1.available() > 0 && newConsoleData1 == false) 
  {
    rc1 = Serial1.read();
    
    if (rc1 != endMarker1) 
    {
      receivedChars1[ndx1] = rc1;
      ndx1++;
      if (ndx1 >= numChars1) 
      {
        ndx1 = numChars1 - 1;
      }
    }
    else 
    {
      receivedChars1[ndx1] = '\0'; // terminate the string
      inString1 = receivedChars1;
      ndx1 = 0;
      newConsoleData1 = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Handle Inputs     //////
//////////////////////////////////////////////////////////////////////////////////////////////
void handleConsoleInput1() // running in main-loop !!
{
  recvWithEndMarker1();
  if (newConsoleData1 == true) 
  {
    Serial << "received String1: '" << inString1 << "'" << endl;
    pinNumber1 = inString1.toInt();
    newConsoleData1 = false;
  }
}
