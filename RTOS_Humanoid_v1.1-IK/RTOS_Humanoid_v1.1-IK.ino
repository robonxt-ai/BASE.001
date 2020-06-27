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

bool DEBUG = false;

/*  ------------------------------------------------------------------------------------------------------*/

// Default baudrates for each serial port (servo, serial, bluetooth) MUST BE INT
#define SERVO_BAUDRATE 9600
#define SERIAL_BAUDRATE 9600

// Define pins for servo and bluetooth serial ports
#define PIN_SERVO_RX 8          // RX pin for the servo board
#define PIN_SERVO_TX 9          // TX pin for the servo board

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

/*  ------------------------------------------------------------------------------------------------------
    [6/??/2020] setup > MUST HAVE
    ------------------------------------------------------------------------------------------------------*/
void setup()  // Put your setup code here, to run once:
{
    // Begin Serial
    Serial.begin(SERIAL_BAUDRATE);

    // Start Servo setup
    sInit();

    //    Serial.println();
    //    Serial.print("ang0");
    //    Serial.print("\t");
    //    Serial.print("ang1");
    //    Serial.print("\t");
    //    Serial.print("ang2");
    //    Serial.print("\t");
    //    Serial.print("x1");
    //    Serial.print("\t");
    //    Serial.print("y1");
    //    Serial.print("\t");
    //    Serial.print("x2");
    //    Serial.print("\t");
    //    Serial.print("y2");
    //    Serial.print("\t");
    //    Serial.print("x3");
    //    Serial.print("\t");
    //    Serial.println("y3");
    //
    //    // Set tolerance to 0.5mm. If reachable, the end effector will approach
    //    // the target with this tolerance
    //    fabrik2D.setTolerance(0.5);
    //
    //
    //    // Solve inverse kinematics given the coordinates x and y, the desired tool angle and the list of lengths for the arm.
    //    fabrik2D.solve(fabrik_x, fabrik_y, angleOfTool, fabrik_lengths);
    //
    //    // store values in floats
    //
    //    float zero_deg = fabrik2D.getAngle(0) * 57296 / 1000;
    //    float one_deg = fabrik2D.getAngle(1) * 57296 / 1000;
    //    float two_deg = fabrik2D.getAngle(2) * 57296 / 1000;
    //
    //    // Angles are printed in degrees.
    //    // The function calls below shows how easy it is to get the results from the inverse kinematics solution.
    //    Serial.print(zero_deg);
    //    Serial.print("\t");
    //    Serial.print(one_deg);
    //    Serial.print("\t");
    //    Serial.print(two_deg);
    //    Serial.print("\t");
    //    Serial.print(fabrik2D.getX(1));
    //    Serial.print("\t");
    //    Serial.print(fabrik2D.getY(1));
    //    Serial.print("\t");
    //    Serial.print(fabrik2D.getX(2));
    //    Serial.print("\t");
    //    Serial.print(fabrik2D.getY(2));
    //    Serial.print("\t");
    //    Serial.print(fabrik2D.getX(3));
    //    Serial.print("\t");
    //    Serial.print(fabrik2D.getY(3));

    //a_zero.go(fabrik2D.getAngle(0) * 57296 / 1000, 500);
    //a_one.go(fabrik2D.getAngle(0) * 57296 / 1000, 500);
    //a_two.go(fabrik2D.getAngle(0) * 57296 / 1000, 500);

    //    SetJointZero(zero_deg);
    //    SetJointOne(one_deg);
    //    SetJointTwo(two_deg);


    //    SetJointZero(66.24);
    //    SetJointOne(47.51);
    //    SetJointTwo(-23.75);

    sMoveDeg90(24, 0.0, 2000);
    sMoveDeg90(23, 0.0, 2000);
    sMoveDeg90(22, 0.0, 2000);
    delay(2000);
    sMoveDeg90(24, -90.0, 0);
    sMoveDeg90(23, 90.0, 0);
    sMoveDeg90(22, -90.0, 2000);
    delay(2000);
    sMoveDeg90(24, 90.0, 0);
    sMoveDeg90(23, -90.0, 0);
    sMoveDeg90(22, 90.0, 2000);
}

/*  ------------------------------------------------------------------------------------------------------
    [6/??/2020] loop > MUST HAVE
    ------------------------------------------------------------------------------------------------------*/
void loop()
{
    // Empty. Things are done in Tasks.
    sMoveDEG(5, 1500, 1000);

}
