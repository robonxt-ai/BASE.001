/*
    Servo controller code for BASE.001
    ------
    A (start from small)™ program
    ------
    Designed for version: humanoid_ESP_v2021.4.2.ino
    Last modified: 2021.04.26
    Programmer: robonxt
    ------
    Changelogs:
    04/19/2020: Base system implemented
    06/26/2020: Updating comments. need to fix the move degrees functions so they will accuratelly move in degrees for any servo regardless of range
    06/27/2020: Working degrees system. some servos are faulty, replacing...
    01/25/2021: Remaking servo controller program to be cleaner
    01/26/2021: Removed many functions, starting over
    01/28/2021: Added delay to sDelay()
    02/01/2021: Implementing degrees and IK.
    2021.04.26: Merging with reentrantcodetest2

*/


/*  ------------------------------------------------------------------------------------------------------  */
// Servo setting default values and stuff
#define MAX_SERVO_ALLOWED 33        // Remember that code starts from 0 , but only have servos 1-32
#define SERVO_FACTORY_POS 1500      // Range of board is ~500-2500ms, half is 1500ms (for programmer use only)
#define SERVOS_IN_LEG 5             // Number of servos per leg
#define MOVE_DEFAULT_TIME 550       // Default time of delay for servos
#define SERVO_MIN_DURATION 100      // Minimum time that servos can delay (last checked was 100ms)

// Reading from 2D servo position array
#define SERVO_ID 0                  // Self-explanatory (starts from 0)
#define SERVO_PRE_UPD_POS 1         // Previously updated pos (for servosUpdatedPos 2D array)
#define SERVO_DEFAULT_POS 1         // Calibrated default pos (for servosInfo 2D array)
#define SERVO_REL_MIN_POS 2         // Relative min pos > depends on default pos of servo
#define SERVO_REL_MAX_POS 3         // Relative max pos > depends on default pos of servo
#define SERVO_ABS_MIN_POS 4         // Absolute min pos > depends on default pos of servo
#define SERVO_ABS_MAX_POS 5         // Absolute max pos > depends on default pos of servo

// Easy to read names for the servos. Also lets us know which one is connected to which port
#define L_HIP_ROLL      8
#define L_HIP_PITCH     9
#define L_KNEE_PITCH    10
#define L_ANKLE_PITCH   11
#define L_ANKLE_ROLL    12

#define L_ARM_ROLL      2
#define L_SHOULD_ROLL   3
#define L_SHOULD_PITCH  4

#define HEAD_YAW        1

#define R_SHOULD_PITCH  29
#define R_SHOULD_ROLL   30
#define R_ARM_ROLL      31

#define R_ANKLE_ROLL    21
#define R_ANKLE_PITCH   22
#define R_KNEE_PITCH    23
#define R_HIP_PITCH     24
#define R_HIP_ROLL      25

/*  ------------------------------------------------------------------------------------------------------  */
// servoInfo (2D array)
// Stores default (centered) servo positions
// -----
// 04/08/2020: Created array
// 07/16/2020: S12 to 1470
// 01/25/2021: S11 to 1480
// 02/01/2021: S21 to 1500, S25 to 2010
// 02/18/2021: S24 to 1450, S10 to 1500, S23 to 1500, S11 to 1500
// 2021/04/17: S10 to 1510, S11 to 1490, S22 to 1550, S25 to 2040, S8 to 970, S31 to 1550
// -----
// [servo_id (manual) | default (manual) | to_min (manual) | to_max (manual) | abs_min (generated) | abs_max (generated)]
int servosInfo[][6]
{
    0,  -1, -1, -1, -1, -1,         // Does not exist. There is no "Servo 0"
    1,  -1, -1, -1, -1, -1,         // HEAD_YAW
    2,  1500, 1000, 1000, -1, -1,   // L_ARM_ROLL
    3,  1500, 1000, 1000, -1, -1,   // L_SHOULD_ROLL
    4,  1500, 1000, 1000, -1, -1,   // L_SHOULD_PITCH
    5,  -1, -1, -1, -1, -1,
    6,  -1, -1, -1, -1, -1,
    7,  -1, -1, -1, -1, -1,
    8,   970, 300, 1200, -1, -1,    // L_HIP_ROLL
    9,  1530, 1000, 1000, -1, -1,   // L_HIP_PITCH
    10, 1510, 1000, 1000, -1, -1,   // L_KNEE_PITCH
    11, 1490, 1000, 1000, -1, -1,   // L_ANKLE_PITCH
    12, 1460, 280, 520, -1, -1,     // L_ANKLE_ROLL
    13, -1, -1, -1, -1, -1,
    14, -1, -1, -1, -1, -1,
    15, -1, -1, -1, -1, -1,
    16, -1, -1, -1, -1, -1,
    17, -1, -1, -1, -1, -1,
    18, -1, -1, -1, -1, -1,
    19, -1, -1, -1, -1, -1,
    20, -1, -1, -1, -1, -1,
    21, 1480, 520, 280, -1, -1,     // R_ANKLE_ROLL
    22, 1550, 1000, 1000, -1, -1,   // R_ANKLE_PITCH
    23, 1500, 1000, 1000, -1, -1,   // R_KNEE_PITCH
    24, 1450, 1000, 1000, -1, -1,   // R_HIP_PITCH
    25, 2040, 1200, 300, -1, -1,    // R_HIP_ROLL
    26, -1, -1, -1, -1, -1,
    27, -1, -1, -1, -1, -1,
    28, -1, -1, -1, -1, -1,
    29, 1500, 1000, 1000, -1, -1,   // R_SHOULD_PITCH
    30, 1500, 1000, 1000, -1, -1,   // R_SHOULD_ROLL
    31, 1550, 1000, 1000, -1, -1,   // R_ARM_ROLL
    32, -1, -1, -1, -1, -1
};

/*  ------------------------------------------------------------------------------------------------------  */
// servosUpdatedPos (2D array)
// Stores servo sUpdates only
// -----
// 04/08/2020 1:17: Created array
// -----
// [servo_id (manual) | previously_updated_pos (generated)]
int servosUpdatedPos[][2]
{
    0, -1,  // Does not exist. There is no "Servo 0"
    1, -1,  // HEAD_YAW
    2, -1,  //
    3, -1,  //
    4, -1,  //
    5, -1,
    6, -1,
    7, -1,
    8, -1,  // L_HIP_ROLL
    9, -1,  // L_HIP_PITCH
    10, -1, // L_KNEE_PITCH
    11, -1, // L_ANKLE_PITCH
    12, -1, // L_ANKLE_ROLL
    13, -1,
    14, -1,
    15, -1,
    16, -1,
    17, -1,
    18, -1,
    19, -1,
    20, -1,
    21, -1, // R_ANKLE_ROLL
    22, -1, // R_ANKLE_PITCH
    23, -1, // R_KNEE_PITCH
    24, -1, // R_HIP_PITCH
    25, -1, // R_HIP_ROLL
    26, -1,
    27, -1,
    28, -1,
    29, -1, //
    30, -1, //
    31, -1, //
    32, -1
};


/*  ------------------------------------------------------------------------------------------------------
    [2021.04.26] dumpList > DEBUG
    ------------------------------------------------------------------------------------------------------  */
void dumpList(char *where)
{
    Serial.print(where);
    Serial.println(" : dumping list...");

    for (int i = 0; i < qServo.size(); i++)
    {
        Serial.print(i);
        Serial.print(" of sList is: ");
        Serial.print(qServo.get(i));
        Serial.print(" ");
        Serial.print(qPosition.get(i));
        Serial.print(" ");
        Serial.println(qDuration.get(i));
    }
    Serial.println("------ END ------\n");
}


/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetDefaultPos > Returns servo's default pos
    ------------------------------------------------------------------------------------------------------  */
int sGetDefaultPos(int servo)
{
    return (servosInfo[servo][SERVO_DEFAULT_POS]); // Returns servo's default pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetRelMinPos > Returns servo's relative min pos
    ------------------------------------------------------------------------------------------------------  */
int sGetRelMinPos(int servo)
{
    return (servosInfo[servo][SERVO_REL_MIN_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetRelMaxPos > Returns servo's relative max pos
    ------------------------------------------------------------------------------------------------------  */
int sGetRelMaxPos(int servo)
{
    return (servosInfo[servo][SERVO_REL_MAX_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetAbsMinPos > Returns servo's absolute min pos
    ------------------------------------------------------------------------------------------------------  */
int sGetAbsMinPos(int servo)
{
    return (servosInfo[servo][SERVO_ABS_MIN_POS]); // Returns servo's absolute min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetAbsMaxPos > Returns servo's absolute max pos
    ------------------------------------------------------------------------------------------------------  */
int sGetAbsMaxPos(int servo)
{
    return (servosInfo[servo][SERVO_ABS_MAX_POS]); // Returns servo's absolute min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [01/25/2021] sGetPrevPos > Returns servo last updated pos
    ------------------------------------------------------------------------------------------------------  */
int sGetPrevPos(int servo)
{
    return (servosUpdatedPos[servo][SERVO_PRE_UPD_POS]); // Returns servo's last updated pos
}

/*  ------------------------------------------------------------------------------------------------------
    [01/25/2021] sUpdatePos > Updates position of servo
    ------------------------------------------------------------------------------------------------------  */
int sUpdatePos(int servo, int sUpdatedPos)
{
    int ok = -1; // Used for debugging
    if (sGetPrevPos(servo) < 0) // If last position is less then 1 (which means error)
    {
        servosUpdatedPos[servo][SERVO_PRE_UPD_POS] = sUpdatedPos; // Update last pos of servo with sUpdatedPos
        ok = 1;     // Returns 1 since previous pos was an error, but it successfully fixed the error
    }
    else
    {
        servosUpdatedPos[servo][SERVO_PRE_UPD_POS] = sUpdatedPos; // Update last pos of servo with sUpdatedPos
        ok = sUpdatedPos; // Returns with the sUpdatedPos
    }
    Debug.print(DBG_VERBOSE, F("sUpdatePos - id: %d | sUpdatedPos: %d | result: %d"), servo, sUpdatedPos, ok);
    return (ok); // Returns ok value to the previous function
}


/*  ------------------------------------------------------------------------------------------------------
    [2021.04.26] sDelay > Non-blocking sDelay
    ------------------------------------------------------------------------------------------------------  */
int  sDelay(int duration)
{
    SerialServo.print(F("T"));      // Sends duration to the SSC
    SerialServo.println(duration); // Sends duration to the SSC

    if (duration > SERVO_MIN_DURATION)
    {
        SerialServo.print("T");
        SerialServo.println(duration);
        return 1;       // Returns 1 to let previous code know that duration was less than 100 so it was skipped
    }
    return 0;           // Returns 0 if all data is sent.
}


/*  ------------------------------------------------------------------------------------------------------
    [2021.04.26] sSendData > Sends data to board. If duration < 100, skip sending "T" for non-blocking moves
    ------------------------------------------------------------------------------------------------------  */
int sSendData(int servo, int pos, int duration)
{
    Serial.print("send_data: ");
    //Serial.println(data);
    SerialServo.print(F("#"));
    SerialServo.print(servo);
    SerialServo.print(F("P"));
    SerialServo.print(pos);

    return sDelay(duration);     // Returns 0 if all data sent, 1 if duration skipped
}













/*  ------------------------------------------------------------------------------------------------------
    [01/25/2021] sCheckIfError > Checks if position is in range of servo
    ------------------------------------------------------------------------------------------------------  */
int sCheckIfError(int servo, int checkedAbsPos)
{
    int ok = -1; // Used for debugging
    int lastPos = sGetPrevPos(servo);

    // If the wanted pos of servo is in the allowed range of the servo, we pass ok. If not, "ok" stays -1
    if ((checkedAbsPos <= sGetAbsMaxPos(servo)) && (checkedAbsPos >= sGetAbsMinPos(servo)))
    {
        ok = 0;
    }
    //Debug.print(DBG_VERBOSE, F("sCheckIfError - id: %d | sCheckedAbsPos: %d | lastPos: %d | result: %d"), servo, checkedAbsPos, lastPos, ok);
    return (ok);    // Returns ok value to the previous function
}



/*  ------------------------------------------------------------------------------------------------------
    [2021.04.26] sMove > Moves servo to pos in ms (Like sSubmitPos but with error checking)
    ------------------------------------------------------------------------------------------------------  */
void sMove(int servo, int pos, int duration)
{
    int ok = -1;    // Used for debugging
    if (sCheckIfError(servo, pos) == 0)   // If value is within acceptable range
    {
        
        // Sends move data to servo
        qServo.push_back(servo);    // Send it to Queue!
        qPosition.push_back(pos);    // Send it to Queue!
        qDuration.push_back(duration);    // Send it to Queue!

        ok = sUpdatePos(servo, pos);    // Get result from sUpdatePos
    }
    //Debug.print(DBG_DEBUG, F("sMove - id: %d | pos: %d | duration: %d | result: %d"), servo, pos, duration, ok);
    //return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [2021.05.14] sMoveDEG > Moves servo to X degree, assuming 90 (degrees) is servo's default pos
    ------------------------------------------------------------------------------------------------------*/
void sMoveDEG(int servo, float wantedPos, int duration)
{
    //int ok = -1;    // Used for debugging

    // testing!
    int base, whole, MID_OFFSET, ratio, moveTo;
    MID_OFFSET = sGetDefaultPos(servo); // Mid offset (default position, which is middle)
    base = MID_OFFSET - 1000;           // base is mid - 1000 (total range is 180 degrees or 2000ms give or take)
    whole = base + 4000;                // whole is if max range was 360. it's not possible, but it's good to calculate it anyways.
    ratio = (whole - base) / 360;       // ratio = 4000/360, which is 11.11 ms per degree.
    moveTo = base + (wantedPos * ratio);    //


    sMove(servo, moveTo, duration);
    //Debug.print(DBG_DEBUG, F("sMoveDEG - id: %d | moveTo: %d | duration: %d | result: %d"), servo, moveTo, duration, ok);
    //return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [2021.04.22] servoReceiver > Servo command sending but non-blocking. Uses QList
    ------------------------------------------------------------------------------------------------------  */
void servoReceiver()
{
    // collect data about what to do to servo, position, duration.
    // data[20];

    if (servoDelay >= previousDuration)       // If the delay betwen sending commands has passed according to the last sent duration....
    {
        if (qServo.size() > 0 && rIsError != true)
        {
            dumpList("servoReceiver");
            //debugPrint("Sending to servo: ", str);
            //sendServoData(sQueue.get(0));
            int ser = qServo.get(0);
            int pos = qPosition.get(0);
            int dur = qDuration.get(0);
            //debugPrint("List before sending to servo: ", qServo.size());
            SerialServo.print("#");
            SerialServo.print(ser);
            SerialServo.print("P");
            SerialServo.print(pos);

            if (dur > 100)
            {
                SerialServo.print("T");
                SerialServo.println(dur);
            }
            sUpdatePos(ser, pos);    // Get result from sUpdatePos

            //delay(10);
    
            qServo.clear(0);
            qPosition.clear(0);
            qDuration.clear(0);
            //debugPrint("List after sending data: ", qServo.size());
            //Serial.println("");

            //dumpList("sR2");
            previousDuration = dur;
        }
        else
        {
            previousDuration = 0;
        }
        servoDelay = 0;         //last command is to reset the timer!
    }
    else
    {
        // we wait and don't do anything to the queue
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [01/26/2021] sReset > Moves servo to default position as listed in
    ------------------------------------------------------------------------------------------------------  */
void sReset(int servo, int duration)
{
    sMove(servo, sGetDefaultPos(servo), duration);
    //Debug.print(DBG_DEBUG, F("sReset - returns: %d"), ok);
    //return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [01/26/2021] sInit > Initates servos and populates abs min and max values. Only called during setup()
    ------------------------------------------------------------------------------------------------------  */
void sInit()
{
    SerialServo.begin(SERVOC_BAUDRATE);  // SerialServo is connected to the SSC32 serial port
    Debug.print(DBG_INFO, F("sInit: %s"), "START");
    for (int i = 0; i < MAX_SERVO_ALLOWED; i++) // Loops MAX_SERVO_ALLOWED times (it's one extra time because servo id starts from 1 and array starts from 0)
    {
        int defaultPos, updatedAbsMinPos, updatedAbsMaxPos;   // Make some vars
        defaultPos = sGetDefaultPos(i);     // Returns servo's default pos
        updatedAbsMinPos = defaultPos - sGetRelMinPos(i);  // Default pos minus the lowest range possible
        updatedAbsMaxPos = defaultPos + sGetRelMaxPos(i);  // Default pos plus the highest range possible
        servosInfo[i][SERVO_ABS_MIN_POS] = updatedAbsMinPos;   // Updates min abs pos
        servosInfo[i][SERVO_ABS_MAX_POS] = updatedAbsMaxPos;   // Updates max abs pos
        //Debug.print(DBG_DEBUG, F("sInit - id: %d | def: %d | to_min: %d | to_max: %d | abs_min: %d | abs_max: %d"), i, sGetDefaultPos(i), sGetRelMinPos(i), sGetRelMaxPos(i), sGetAbsMinPos(i), sGetAbsMaxPos(i));
        // [servo_id (manual) | default (manual) | to_min (manual) | to_max (manual) | abs_min (generated) | abs_max (generated)]
        //delay(1);  // Delay to prevent crashes?
    }
    Debug.print(DBG_INFO, F("sInit: %s"), "DONE");
}
