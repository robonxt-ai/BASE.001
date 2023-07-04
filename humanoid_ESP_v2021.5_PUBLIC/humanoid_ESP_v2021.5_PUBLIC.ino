/*
    PUBLIC Main code for BASE.001
    ------
    A (start from small)™ program
    ------
    Designed for version: humanoid_ESP_v2022_PUBLIC.ino
    Last modified: 2022.03.04
    Programmer: robonxt
    ------
    NOTES:
    getup function may be have weird results. You have been warned. It is a semi-working concept.
    misuse of it may cause the robot to destroy itself.
    ------
    Changelogs:
    2021.05.14: Initial commit of working(?) latest code. Disabled Blynk.
    2022.03.04: Removed all Blynk features.

*/

/*  ------------------------------------------------------------------------------------------------------  */
// Is debugging messages enabled?
bool DEBUG = false;

// Default baudrates for each serial port (servo, serial, bluetooth) MUST BE INT
#define SERVOC_BAUDRATE 115200 // SERVOC = Servo Controller
#define SERIAL_BAUDRATE 115200 // SERIAL = Serial communication

// Defines SoftwareSerial ports
const byte PIN_SERVO_RX = D5; // RX pin for the servo board
const byte PIN_SERVO_TX = D6; // TX pin for the servo board

// For heartbeat
const int hbIntervalON = 50;    // How long to stay on?
const int hbIntervalOFF = 2000; // Between heartbeats
bool hbSTATE = 0;               // For heartbeat STATES

// For gyro
const int guDelay = 100; // Delay between gyro updates
const int gpDelay = 500; // Delay between gyro prints
bool gSTATE = 0;         // For gyro STATES

// For robot states and actions
//bool rIsRightedWhenIdle = false; // Is robot righted (when starting up or when not doing actions)
//char *rCurrActionState[] = "NONE";      // What is the robot currently doing? What state is it in?
bool rIsBusy = true;                // Is the robot IDLE?
const int rThresholdToRight = 70;   // What's the threshold when the robot is considered "Not righted"?
const int getupDelay = 5000;        // Delay between checking if robot has tipped over
bool rIsError = false;

// For Qlist
int previousDuration = 0;

/*  ------------------------------------------------------------------------------------------------------  */
// For MPU
//#include <Arduino.h> // Including this seems to cause the program to break for ESP
#include <TinyMPU6050.h>
MPU6050 mpu(Wire);

// For QList
#include <QList.h>
QList<int> qServo;
QList<int> qPosition;
QList<int> qDuration;

// For software serial ports
#include <SoftwareSerial.h>
SoftwareSerial SerialServo(PIN_SERVO_RX, PIN_SERVO_TX);

// For non-blocking delays
#include <elapsedMillis.h>
elapsedMillis hbMillis; // For heartbeat

elapsedMillis guMillis; // For gyro
elapsedMillis gpMillis; // For gyro print

elapsedMillis getupMillis; // For getup

elapsedMillis servoDelay; // For non-blocking servo controller

// For kinematics
#include <Kinematics.h>
//#include <FABRIK2D.h>

// For debugging use only
#include "Arduino_DebugUtils.h"

/*  ------------------------------------------------------------------------------------------------------  */
// Include needed files (This should be just before the setup!)
#include "servo_controller2.h"  // Testing!
#include "MPU.h"

#include "command_receiver2.h" // Place this the last one in the list!

/*  ------------------------------------------------------------------------------------------------------
    [2021/04/15] isBusy > set status to idle or not
    ------------------------------------------------------------------------------------------------------*/
void isBusy(bool truth)
{
    rIsBusy = truth;
}

/*  ------------------------------------------------------------------------------------------------------
    [11/09/2020] heartbeat > Heartbeat
    ------------------------------------------------------------------------------------------------------*/
void heartbeat()
{
    if (hbMillis >= (hbIntervalOFF + hbIntervalON)) // Turns off LED
    {
        digitalWrite(LED_BUILTIN, HIGH); // Remember that LOW turns on the Built in LED for ESP boards!
        hbSTATE = 0;
        hbMillis = 0;
        //Debug.print(DBG_VERBOSE, F("heartbeat"));
    }
    else if ((hbMillis >= hbIntervalOFF) && (hbSTATE == 0)) // Turns on LED
    {
        digitalWrite(LED_BUILTIN, LOW); // Remember that LOW turns on the Built in LED for ESP boards!
        hbSTATE = 1;
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [01/25/2021] setup > MUST HAVE
    ------------------------------------------------------------------------------------------------------  */
void setup() // Put your setup code here, to run once:
{
    // SET DEBUG MODES
    // DBG_NONE - no debug output is shown
    // DBG_ERROR - critical errors
    // DBG_WARNING - non-critical errors
    // DBG_INFO - information
    // DBG_DEBUG - more information
    // DBG_VERBOSE - most information
    //Debug.setDebugLevel(DBG_INFO);
    //Debug.timestampOn();

    // Begin Serial
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(SERIAL_BAUDRATE);
    delay(50);
    for (int i = 0; i < 10; i++)
    {
        Serial.println(" ");
        delay(20);
    }
    //rCurrActionState = "SETUP";
    //
    // Code for setups
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    Serial.println("---------- Setup START ----------");
    // Initiate servos
    sInit();

    //setupKinematics();
    //BORROWED_initialize();

    setupMPU();
    Serial.println("---------- Setup DONE ----------");
    //rCurrActionState = "IDLE";
    isBusy(false);
}


/*  ------------------------------------------------------------------------------------------------------
    [2021/04/22] gyroUpdate > Updates data from gyro and sends it to serial
    ------------------------------------------------------------------------------------------------------*/
void gyroUpdate()
{
    if (gpMillis >= (gpDelay)) // If gpDelay is passed, then we print gyro values
    {
        //Debug.print(DBG_VERBOSE, F("gyro print"));
        //gSTATE = 2;
        mpu.Execute();
        //MPU_print();
        gpMillis = 0;
    }
    else
    {
        // Nothing
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [2021/04/15] humanoidStateCheck > If robot is tipped over, right itself back up
    ------------------------------------------------------------------------------------------------------*/
void humanoidStateCheck()
{
    if (getupMillis >= getupDelay) // If it's time to check if robot has tipped over
    {
        if (rIsBusy == false)
        {
            Serial.println("checking if robot has tipped over");
            if (abs(mpu.GetAngY()) >= rThresholdToRight)
            {
                //rCurrActionState = "RIGHTING";
                isBusy(true);
                if (mpu.GetAngY() >= rThresholdToRight) // If it's tipped backward
                {
                    getup(-1);
                }
                else if (mpu.GetAngY() <= -rThresholdToRight) // If it's tipped forward
                {
                    getup(1);
                }
            }
            getupMillis = 0;

        }
        else
        {
            
        }
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [01/25/2021] loop > MUST HAVE
    ------------------------------------------------------------------------------------------------------  */
void loop()
{
    gyroUpdate(); // Gyro
    heartbeat();  // Heartbeat
    //
    // Code for normal program

    // Code for sending data to outputs (non-blocking)
    servoReceiver();
    serialControl();
    humanoidStateCheck();
}
