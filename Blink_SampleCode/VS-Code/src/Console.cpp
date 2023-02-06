//
//
//

#include "Streaming.h"

boolean newConsoleData = false;
int pinNumber;

const uint8_t numChars = 20;
char receivedChars[numChars]; // an array to store the received data

String inString = "";  // inString.toInt()

//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Read Characters   //////
//////////////////////////////////////////////////////////////////////////////////////////////
void recvWithEndMarker() 
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
 
  while (Serial.available() > 0 && newConsoleData == false) 
  {
    rc = Serial.read();
    
    if (rc != endMarker) 
    {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) 
      {
        ndx = numChars - 1;
      }
    }
    else 
    {
      receivedChars[ndx] = '\0'; // terminate the string
      inString = receivedChars;
      ndx = 0;
      newConsoleData = true;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////                                                        Console Handle Inputs     //////
//////////////////////////////////////////////////////////////////////////////////////////////
void handleConsoleInput() // running in main-loop !!
{
  recvWithEndMarker();
  if (newConsoleData == true) 
  {
    Serial << "received String: '" << inString << "'" << endl;
    pinNumber = inString.toInt();
    newConsoleData = false;
  }
}
