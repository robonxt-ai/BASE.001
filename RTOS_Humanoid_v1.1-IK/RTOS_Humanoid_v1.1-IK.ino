/*
    RTOS for SainSmart Humanoid Robot Kit
    ------
    Goals:
    06/01/2020: RTOS implemented
    06/02/2020: Servo controller implemented
    06/04/2020: switching to MEGA because UNO cannot control both serials at the same time
    06/19/2020: v1.1-IK will include Inverse Kinemetics, but for now will update Bluetooth connection (EDIT: Bluetooth connection is in a new project.)
    06/20/2020: not done yet. ADD A FUNCTION TO CONTROL SERVOS IN DEGREES!!! THEN USE IK!
    06/20/2020: removed bluetooth and rtos. this version is focusing on IK only!
    ------
    A (start from small)™ program based off what dad taught me
    ------
    modified Jun 26 2020
    by Steven Liao
*/

// Include Fabrik2D library
#include <FABRIK2D.h>

// Include RAMP library
#include <Ramp.h>

int fabrik_lengths[] = {58, 58, 55};    // 3DOF arm with values for shoulder to elbow, elbow to wrist and wrist to end effector.
Fabrik2D fabrik2D(4, fabrik_lengths);   // This arm has 4 joints; one in the origin, the elbow, the wrist and the end effector.

rampFloat a_zero;
rampFloat a_one;
rampFloat a_two;

float fabrik_x = -50;
float fabrik_y = 130;

float angleOfTool = .45;

// STUFF TO TEST
int zero_mid = 1425;
int one_mid = 1475;
int two_mid = 1540;

int steps = 1024;

int zero_low = zero_mid - steps;
int zero_high = zero_mid + steps;

int one_low = one_mid - steps;
int one_high = one_mid + steps;

int two_low = two_mid - steps;
int two_high = two_mid + steps;
// STUFF TO TEST

bool DEBUG = true;

/*  ------------------------------------------------------------------------------------------------------*/

// Default baudrates for each serial port (servo, serial, bluetooth) MUST BE INT
#define SERVO_BAUDRATE 9600
#define SERIAL_BAUDRATE 9600

// Define Servo default positions and stuff
#define FACTORY_DEFAULT_POS 1500    // Range of board is ~500-2500ms, half is 1500ms
#define SERVO_ID 0                  // Self-explanatory
#define SERVO_LAST_POS 1            // Last updated pos
#define SERVO_DEFAULT_POS 1         // Calibrated default 
#define SERVO_REL_MIN_POS 2         // Relative min pos > depends on default pos of servo
#define SERVO_REL_MAX_POS 3         // Relative max pos > depends on default pos of servo
#define SERVO_ABS_MIN_POS 4         // Absolute min pos > depends on default pos of servo
#define SERVO_ABS_MAX_POS 5         // Absolute max pos > depends on default pos of servo
#define MAX_SERVOS_POSSIBLE 33      // Remember that code starts from 0 , but only have servos 1-32
#define SERVOS_IN_LEG 5             // Number of servos per leg
#define MOVE_DEFAULT_TIME 550       // Default time of delay for servos


// Easy to read names for the servos. Also lets us know which one is on which port
#define HEAD_YAW        1

#define L_HIP_ROLL      8
#define L_HIP_PITCH     9
#define L_KNEE_PITCH    10
#define L_ANKLE_PITCH   11
#define L_ANKLE_ROLL    12

#define R_ANKLE_ROLL    21
#define R_ANKLE_PITCH   22
#define R_KNEE_PITCH    23
#define R_HIP_PITCH     24
#define R_HIP_ROLL      25


/*  ------------------------------------------------------------------------------------------------------
    [6/??/2020] setup > MUST HAVE
    ------------------------------------------------------------------------------------------------------*/
void setup()  // Put your setup code here, to run once:
{
    // Begin Serial
    Serial.begin(SERIAL_BAUDRATE);

    // Initiate servos
    sInit();


    // TESTING
    //sMoveToDefault();
    //    sMoveAbsDEG(R_HIP_ROLL, 0, 2000);
    //    sMoveAbsDEG(R_HIP_PITCH, 0, 2000);
    //    sMoveAbsDEG(R_KNEE_PITCH, 0, 2000);
    //    sMoveAbsDEG(R_ANKLE_ROLL, 0, 2000);
    //    sMoveAbsDEG(R_ANKLE_PITCH, 0, 2000);
    //delay(2000);
    //sMoveAbsDEG(R_HIP_ROLL, 45, 2000);
    //sMoveAbsDEG(R_HIP_PITCH, 45, 2000);
    //sMoveAbsDEG(R_KNEE_PITCH, 45, 2000);
    //sMoveAbsDEG(R_ANKLE_PITCH, 45, 2000);
//    sMoveAbsDEG(R_ANKLE_ROLL, 70, 0);
//    sMoveAbsDEG(L_ANKLE_ROLL, 70, 2000);
//    sMoveAbsDEG(R_ANKLE_ROLL, 0, 0);
//    sMoveAbsDEG(L_ANKLE_ROLL, 0, 2000);
//    sMoveAbsDEG(R_ANKLE_ROLL, 70, 0);
//    sMoveAbsDEG(L_ANKLE_ROLL, 0, 2000);
//    sMoveAbsDEG(R_ANKLE_ROLL, 0, 0);
//    sMoveAbsDEG(L_ANKLE_ROLL, 70, 2000);
//    sMoveAbsDEG(R_ANKLE_ROLL, 40, 0);
//    sMoveAbsDEG(L_ANKLE_ROLL, 40, 2000);
    
    sMoveRelDEG(R_ANKLE_ROLL, 0, 0);
    sMoveRelDEG(L_ANKLE_ROLL, 0, 2000);
    sMoveRelDEG(R_ANKLE_ROLL, 20, 0);
    sMoveRelDEG(L_ANKLE_ROLL, 20, 2000);
    sMoveRelDEG(R_ANKLE_ROLL, -20, 0);
    sMoveRelDEG(L_ANKLE_ROLL, -20, 2000);
    sMoveRelDEG(R_ANKLE_ROLL, 10, 0);
    sMoveRelDEG(L_ANKLE_ROLL, 10, 100);
    sMoveRelDEG(R_ANKLE_ROLL, -10, 0);
    sMoveRelDEG(L_ANKLE_ROLL, -10, 100);
    sMoveRelDEG(R_ANKLE_ROLL, 0, 0);
    sMoveRelDEG(L_ANKLE_ROLL, 0, 2000);
    // TESTING
}

/*  ------------------------------------------------------------------------------------------------------
    [6/??/2020] loop > MUST HAVE
    ------------------------------------------------------------------------------------------------------*/
void loop()
{
    // Empty. Things are done in Tasks.
}
