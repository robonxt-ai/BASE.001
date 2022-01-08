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
    ------
    Goals:
    code abides by C++ rules?
*/
#define VERSION "2022.01.05 8:50PM" // Version
/*  ------------------------------------------------------------------------------------------------------  */
// Default baudrates for each serial port (servo, serial, bluetooth) MUST BE INT
#define SERVOC_BAUDRATE 115200      // SERVOC = Servo Controller
#define SERIAL_BAUDRATE 115200      // SERIAL = Serial communication

// Defines SoftwareSerial ports
const byte PIN_SERVO_RX = D5;       // RX pin for the servo board
const byte PIN_SERVO_TX = D6;       // TX pin for the servo board

// For heartbeat
const int LED_ON = LOW;             // Because LOW turns on the esp8266 built-in led
const int LED_OFF = HIGH;           // Because HIGH turns off the esp8266 built-in led
const int hbIntervalON = 70;        // How long to stay on?
const int hbIntervalOFF = 1750;     // How long to stay off?
bool hbSTATE = false;               // For heartbeat STATES

// For startup settings
bool isECHO = true;                 // Echo commands through serial?
/*  ------------------------------------------------------------------------------------------------------  */
// For AceRoutine (coroutines)
#include <AceRoutine.h>
using namespace ace_routine;

// For Streaming (iostream)
#include <Streaming.h>

// For software serial ports
#include <SoftwareSerial.h>
SoftwareSerial  SerialServo(PIN_SERVO_RX, PIN_SERVO_TX);

// For SafeString
#include "SafeStringReader.h"
createSafeStringReader(sfSerialReader, 50, " ,\r\n");
createSafeStringReader(sfServoReader, 50, " ,\r\n");

#include "BufferedOutput.h"
createBufferedOutput(output, 66, DROP_UNTIL_EMPTY); // modes are DROP_UNTIL_EMPTY, DROP_IF_FULL or BLOCK_IF_FULL


/*  ------------------------------------------------------------------------------------------------------  */
// Include needed files (This should be just before the setup!)
#include "xtra_classes.h"       // This includes the LineBuffer class
#include "command_handlers.h"       // This includes the LineBuffer class
#include "coroutines.h"         // This includes coroutines

/*  ------------------------------------------------------------------------------------------------------  */
// Objects
//LineBuffer lineBuffer;  // Creates the linebuffer object for processing the serial data
//serialReadConroutine serialRead;

/*  ------------------------------------------------------------------------------------------------------  */

/*  ------------------------------------------------------------------------------------------------------
    [2022.01.02] setup > MUST HAVE
    ------------------------------------------------------------------------------------------------------  */
void setup() // Put your setup code here, to run once:
{
    // Begin Serial setup
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(D0, OUTPUT);

    Serial.begin(SERIAL_BAUDRATE);
    SerialServo.begin(SERVOC_BAUDRATE);
    delay(200);
    Serial << " " << endl << " " << endl;
    SerialServo << " " << endl << " " << endl;
    delay(10);
    SafeString::setOutput(Serial);  // enable error messages and SafeString.debug() output to be sent to Serial
    sfSerialReader.connect(Serial); // where SafeStringReader will read from
    //sfServoReader.connect(Serial);  // where SafeStringReader will read from
    if (isECHO)
    {
        sfSerialReader.echoOn();          // echo back all input, by default echo is off
    }
    Serial << "VERSION: " << VERSION << endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // End Serial setup
    //
    // Begin program setup
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    Serial << "---------- Setup START ----------" << endl;



    Serial << "----------- Setup END -----------" << endl;
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // End program setup
    //
    // Begin single run programs
    //////////////////////////////////////////////////////////////////////////////////////////////////////
}

/*  ------------------------------------------------------------------------------------------------------
    [2021.06.16] loop > MUST HAVE
    ------------------------------------------------------------------------------------------------------  */
void loop()
{
    //
    // Code for background services here
    heartbeat.runCoroutine();       // Heartbeat
    serialRead.runCoroutine();      // Read serial
    //
    // Code for normal program here
}
