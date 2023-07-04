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
    2022.01.19: Sending data to servo works now. Servo sends back data as well.
    2022.01.22: Thinking about using LittleFS to save config files, but not implementing that until I finish other things.
    2022.01.24: Trying to get some processing done. QList does not work on ESP boards, switching over to ArduinoQueue.
    2022.01.25: process:    when sending data (string) from serial: hold it in buffer until ends with Time; process string to store servo positions.
                            when sending data (int) from brain: convert to string; hold in buffer until ends with Time; process string to store servo positions.
                            so we need: int > string (easy); string > int (hard); string > buffer (???)
    2022.01.30: working on int > string (easy);
    ------
    Goals:
    code abides by C++ rules?
*/
#define PROJECT "BASE.001"          // PROJECT
#define CREATOR "robonxt"           // CREATOR
#define VERSION "2022.01.25 1:57AM" // VERSION
#define TESTING true                // TESTING

/*  ------------------------------------------------------------------------------------------------------  */
// Default baudrates for each serial port (servo, serial, bluetooth) MUST BE INT
#define SERVOC_BAUDRATE 115200      // SERVOC = Servo Controller
#define SERIAL_BAUDRATE 115200      // SERIAL = Serial communication
#define MAX_SERIAL_LENGTH 512       // Maximum length of serial commands

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
bool isDebug = true;                // Echo commands through serial?
bool isECHO = true;                 // Echo commands through serial?
/*  ------------------------------------------------------------------------------------------------------  */
// For LittleFS
//#include <FS.h>   // future use
//#include <LittleFS.h>  // future use

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
#include "BufferedOutput.h"
createSafeStringReader(ssSerialReader, MAX_SERIAL_LENGTH, " ,\r\n");
createSafeStringReader(ssServoReader, MAX_SERIAL_LENGTH, " ,\r\n");
createBufferedOutput(ssSerialOutput, MAX_SERIAL_LENGTH, DROP_UNTIL_EMPTY); // modes are DROP_UNTIL_EMPTY, DROP_IF_FULL or BLOCK_IF_FULL
createBufferedOutput(ssServoOutput, MAX_SERIAL_LENGTH, DROP_UNTIL_EMPTY); // modes are DROP_UNTIL_EMPTY, DROP_IF_FULL or BLOCK_IF_FULL

// For ArduinoQueue (since QList doesn't work on ESP boards)
#include <ArduinoQueue.h>
const int MAX_ITEMS_IN_QUEUE = 512;
ArduinoQueue<char*> qServoData(MAX_ITEMS_IN_QUEUE);

// For QList (QList doesn't work on ESP boards)
//#include <QList.h>
//QList<String> qServoData;

/*  ------------------------------------------------------------------------------------------------------  */
// Include needed files (This should be just before the setup!)
#include "servo_data.h"         // This includes all servo data
#include "command_handlers.h"   // This includes all the commands handled by serialRead
#include "coroutines.h"         // This includes coroutines
#include "testing_strings.h"    // TESTING


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
    ssServoOutput.connect(SerialServo, SERVOC_BAUDRATE);    // where ssServoOutput will send
    if (isECHO)
    {
        ssSerialReader.echoOn();            // echo back all input, by default echo is off
    }
    handleINFOCmd();    // Sends info to serial
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // End Serial setup
    //
    // Begin program setup
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    ssSerialOutput << "---------- Setup START ----------" << endl;

    qServoData.enqueue("#2P2500");
    qServoData.enqueue("#4P1500T1000");
    qServoData.enqueue("#2P500T7000");
    qServoData.enqueue("#4P500");

    qServoData.enqueue("#2P1500T5000");
    qServoData.enqueue("#4P2500T1000");

    qServoData.enqueue("#2P500T500");
    qServoData.enqueue("#4P500T100");
    qServoData.enqueue("#2P2500T500");


    //test();
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
    //serialRead.runCoroutine();      // Read serial
    servoRead.runCoroutine();       // Read servo serial
    //servoSend.runCoroutine();       // Send servo data
    //
    // Code for normal program here
//    if (qServoData.itemCount() > 0)
//    {
//        test();
//    }
    //
    // Code for more background services here
    // hi
}
