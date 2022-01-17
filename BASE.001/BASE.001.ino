/*
    BASE.001
    ------
    A (start from small)™ program
    ------
    Designed for version: BASE.001.ino
    Last modified: SEE VERSION
    Programmer: robonxt
    ------
    2022.01.02: Reversioned to BASE.001. Due to changed servo positions, need to update servo control program
    2022.01.03: Trying out SafeStringReader for reading serial data
    2022.01.07: More testing
    2022.01.10: Thanks to the creator of SafeStrings, I now understand how to make BufferedOutput work with EspSoftwareSerial
    ------
    Goals:
    code abides by C++ rules?
*/
#define VERSION "2022.01.10 01:05AM" // Version
/*  ------------------------------------------------------------------------------------------------------  */
// Default baudrates for each serial port (servo, serial, bluetooth) MUST BE INT
#define SERVOC_BAUDRATE 115200      // SERVOC = Servo Controller
#define SERIAL_BAUDRATE 115200      // SERIAL = Serial communication
#define MAX_SERIAL_LENGTH 256       // Maximum length of serial commands

// Defines SoftwareSerial ports
const byte PIN_SERVO_RX = D5;       // RX pin for the servo board
const byte PIN_SERVO_TX = D6;       // TX pin for the servo board

// For heartbeat
const bool LED_ON = LOW;            // Because LOW turns on the esp8266 built-in led
const bool LED_OFF = HIGH;          // Because HIGH turns off the esp8266 built-in led
const int hbIntervalON = 70;        // How long to stay on?
const int hbIntervalOFF = 1750;     // How long to stay off?

// Robot stuff
bool rIsError = false;              // is Error?
bool rIsStand = false;              // is standing?

// For startup settings
bool isECHO = true;                 // Echo commands through serial?
/*  ------------------------------------------------------------------------------------------------------  */
// For AceRoutine (coroutines)
#include <AceRoutine.h>
using namespace ace_routine;

// For Streaming (iostream)
#include <Streaming.h>

// For software serial ports (uses EspSoftwareSerial)
#include <SoftwareSerial.h>
SoftwareSerial SerialServo(PIN_SERVO_RX, PIN_SERVO_TX);

// For SafeString
#include "SafeStringReader.h"

//createSafeString(serialData, MAX_SERIAL_LENGTH);
//createSafeString(servoData, MAX_SERIAL_LENGTH);
createSafeStringReader(ssSerialReader, MAX_SERIAL_LENGTH, " ,\r\n");
createSafeStringReader(ssServoReader, MAX_SERIAL_LENGTH, " ,\r\n");

#include "BufferedOutput.h"
createBufferedOutput(ssSerialOutput, MAX_SERIAL_LENGTH, DROP_UNTIL_EMPTY); // modes are DROP_UNTIL_EMPTY, DROP_IF_FULL or BLOCK_IF_FULL
createBufferedOutput(ssServoOutput, MAX_SERIAL_LENGTH, DROP_UNTIL_EMPTY); // modes are DROP_UNTIL_EMPTY, DROP_IF_FULL or BLOCK_IF_FULL


/*  ------------------------------------------------------------------------------------------------------  */
// Include needed files (This should be just before the setup!)
#include "command_handlers.h"   // This includes all the commands handled by serialRead
#include "coroutines.h"         // This includes coroutines

/*  ------------------------------------------------------------------------------------------------------  */
// Objects


/*  ------------------------------------------------------------------------------------------------------  */

/*  ------------------------------------------------------------------------------------------------------
    [2022.01.10] setup > MUST HAVE
    ------------------------------------------------------------------------------------------------------  */
void setup() // Put your setup code here, to run once:
{
    // Begin Serial setup
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(D0, OUTPUT);

    Serial.begin(SERIAL_BAUDRATE);
    SerialServo.begin(SERVOC_BAUDRATE);
    delay(250);
    SafeString::setOutput(Serial);          // enable error messages and SafeString.debug() output to be sent to Serial
    ssSerialReader.connect(Serial);         // where ssSerialReader will read from
    ssServoReader.connect(SerialServo);    // where ssServoReader will read from

    ssSerialOutput.connect(Serial, SERIAL_BAUDRATE);        // where ssSerialOutput will send
    ssServoOutput.connect(SerialServo, SERVOC_BAUDRATE);    // where ssServoOutput will send. Need baud rate here because EspSoftwareSerial's availableForWrite() not reliable`
    if (isECHO)
    {
        ssSerialReader.echoOn();            // echo back all input, by default echo is off
        //ssSerialReader.echoOn();          // echo back all input, by default echo is off
    }
    ssSerialOutput << "--------------------------------------------------" << endl;
    ssSerialOutput << "VERSION: " << VERSION << endl;
    ssServoOutput << F("#1P1500T100") << endl << F("OK") << endl;      // Warm up the head servo sends a OK to servo board
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // End Serial setup
    //
    // Begin program setup
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    ssSerialOutput << "---------- Setup START ----------" << endl;


    ssSerialOutput << "---------- Setup END ----------" << endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // End program setup
    //
    // Begin single run programs
    //////////////////////////////////////////////////////////////////////////////////////////////////////
}

/*  ------------------------------------------------------------------------------------------------------
    [2022.01.10] loop > MUST HAVE
    ------------------------------------------------------------------------------------------------------  */
void loop()
{
    //
    // Code for background services here
    ssSerialOutput.nextByteOut();   // Sends remaining data to Serial
    ssServoOutput.nextByteOut();    // Sends remaining data to SerialServo
    heartbeat.runCoroutine();       // Heartbeat
    serialRead.runCoroutine();      // Read serial
    servoSend.runCoroutine();       // Send servo data
    //
    // Code for normal program here

    //
    // Code for more background services here
    // hi
}
