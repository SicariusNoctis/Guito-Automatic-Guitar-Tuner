// Course:      ENSC 100W
// Group:       Kappa
// Authors:     Mateen Ulhaq, 301250828, <mulhaq@sfu.ca>
// Description: Bluetooth communicaion code.
// License:     GPLv3


// #include <MeetAndriod.h>
#include "Arduino.h"
#include "Comm.h"
#include "Motor.h"
#include "Notes.h"


// Called whenever a command is received over the Bluetooth connection
// [flag], [command] for [...]
// 'C',    'X'       for Emergency stop
// 'C',    'P'       for Ping
// 'C',    'N'       for Next string
// 'C',    'S'       for Standard tuning
// 'C',    'D'       for Drop D tuning
// 'C',    'E'       for E flat tuning
void receiveCommand(byte flag, byte numOfValues)
{
  static char command[64] = {'\0'};
  meetAndroid.getString(command);

  switch(command[0])
  {
  case 0:
    // null
    break;

  case 'X':
    // Emergency stop
    // Cut power to system (coast motors)
    rotateMotor(0);
    stopped = true;
    break;

  case 'P':
    // Ping
    meetAndroid.send("Ping received on " + millis());
    break;

  case 'N':
    // Tune next string
    nextString();
    stopped = false;
    break;

  case 'S':
    // Standard tuning
    setFlag(TUNING_STANDARD);
    setString(0);
    stopped = false;
    break;

  case 'D':
    // Drop D
    setFlag(TUNING_DROPD);
    setString(0);
    stopped = false;
    break;

  case 'E':
    // E Flat
    setFlag(TUNING_EFLAT);
    setString(0);
    stopped = false;
    break;

  default:
    meetAndroid.send("Unrecognized command");
    break;
  }
}


// Called whenever a value is received over the Bluetooth connection
void receivePitch(byte flag, byte numOfValues)
{
  frequency = meetAndroid.getInt();
}


