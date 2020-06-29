/*
    Servo Controller for SainSmart Humanoid Robot Kit
    ------
    Goals:
    04/19/2020: base system implemented
    06/26/2020: updating comments. need to fix the move degrees functions so they will acceratelly move in degrees for any servo regardless of range
    06/27/2020: working degrees system. some servos are faulty, replacing...
    ------
    A (start from small)™ program based off what dad taught me
    ------
    modified Jun 26 2020
    by Steven Liao (with dad)
*/

// array 1 4/8/2020 14:48
// 4/13/2020 18:05 S11 tuned to 1480, S10 tuned to 1480
// 4/14/2020 15:05 S11 to 1500, S10 to 1490, S12 to 1470, S22 to 1500
// 4/21/2020 17:58 S9 to 1580, S10 to 1500
// 4/23/2020 21:58 S21 to 1480, S11 to 1470, S9 to 1570, S8 to 990, S10 to 1510, S24 to 1550
// 6/04/2020 23:59 S11 to 1490, S22 to 1510
// 6/05/2020 11:50 S12 to 1420. S8 to 995
// 6/19/2020 13:15 S9 to 1600 (-950/+950), S10 to 1500, S11 to 1475, S22 to 1525, S24 to 1450 (-950/+950)
// 6/21/2020 18:50 S24 to 1420 (-1000/+1000), S23 to 1500 (-1000/+1000), S22 to 1520 (-1000/+1000)
// 6/26/2020 23:32 S9 to 1530 (-1000/+1000), S10 to 1480 (-1000/+1000), S11 to 1475 (-1000/+1000), S12 to
// 6/27/2020 14:32 S12 to 1410
// 6/28/2020 14:32 S12 to 1500


// Store servo status only
// Id, default pos, min (value), max (value), min (generated), max (generated)
int servosInfo[][6]
{
    0,  -1, -1, -1, -1, -1,         // Does not exist
    1,  -1, -1, -1, -1, -1,         // HEAD_YAW
    2,  -1, -1, -1, -1, -1,         //
    3,  -1, -1, -1, -1, -1,         //
    4,  -1, -1, -1, -1, -1,         //
    5,  -1, -1, -1, -1, -1,
    6,  -1, -1, -1, -1, -1,
    7,  -1, -1, -1, -1, -1,
    8,  995, 300, 1200, -1, -1,     // L_HIP_ROLL
    9,  1530, 1000, 1000, -1, -1,   // L_HIP_PITCH
    10, 1480, 1000, 1000, -1, -1,   // L_KNEE_PITCH
    11, 1475, 1000, 1000, -1, -1,   // L_ANKLE_PITCH
    12, 1500, 280, 520, -1, -1,     // L_ANKLE_ROLL
    13, -1, -1, -1, -1, -1,
    14, -1, -1, -1, -1, -1,
    15, -1, -1, -1, -1, -1,
    16, -1, -1, -1, -1, -1,
    17, -1, -1, -1, -1, -1,
    18, -1, -1, -1, -1, -1,
    19, -1, -1, -1, -1, -1,
    20, -1, -1, -1, -1, -1,
    21, 1480, 520, 280, -1, -1,     // R_ANKLE_ROLL
    22, 1520, 1000, 1000, -1, -1,   // R_ANKLE_PITCH
    23, 1500, 1000, 1000, -1, -1,   // R_KNEE_PITCH
    24, 1420, 1000, 1000, -1, -1,   // R_HIP_PITCH
    25, 2000, 1200, 300, -1, -1,    // R_HIP_ROLL
    26, -1, -1, -1, -1, -1,
    27, -1, -1, -1, -1, -1,
    28, -1, -1, -1, -1, -1,
    29, -1, -1, -1, -1, -1,         //
    30, -1, -1, -1, -1, -1,         //
    31, -1, -1, -1, -1, -1,         //
    32, -1, -1, -1, -1, -1
};


// 2D array. 4/8/2020 1:17
// Stores servo sUpdates only
// Id, last sUpdated pos
int servosUpdatedPos[][2]
{
    0, -1,  // Does not exist
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

// ANKLE_ROLL, ANKLE_PITCH, KNEE_PITCH, R_HIP_PITCH, R_HIP_ROLL
// First line is left side, second line is right side
int mirroredLegs[2][5]
{
    12,     11,     10,     9,      8,
    21,     -22,    -23,    -24,    25
};

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetDefaultPos > Returns servo's default pos
    ------------------------------------------------------------------------------------------------------*/
int sGetDefaultPos(int servo)
{
    return (servosInfo[servo][SERVO_DEFAULT_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetRelMinPos > Returns servo's relative min pos
    ------------------------------------------------------------------------------------------------------*/
int sGetRelMinPos(int servo)
{
    return (servosInfo[servo][SERVO_REL_MIN_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetRelMaxPos > Returns servo's relative max pos
    ------------------------------------------------------------------------------------------------------*/
int sGetRelMaxPos(int servo)
{
    return (servosInfo[servo][SERVO_REL_MAX_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetAbsMinPos > Returns servo's absolute min pos
    ------------------------------------------------------------------------------------------------------*/
int sGetAbsMinPos(int servo)
{
    return (servosInfo[servo][SERVO_ABS_MIN_POS]); // Returns servo's absolute min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetAbsMaxPos > Returns servo's absolute max pos
    ------------------------------------------------------------------------------------------------------*/
int sGetAbsMaxPos(int servo)
{
    return (servosInfo[servo][SERVO_ABS_MAX_POS]); // Returns servo's absolute min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sCheckPos > Returns servo last updated pos
    ------------------------------------------------------------------------------------------------------*/
int sCheckLastPos(int servo)
{
    return (servosUpdatedPos[servo][SERVO_LAST_POS]); // Returns servo's last updated pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sUpdatePos > Updates position of servo
    ------------------------------------------------------------------------------------------------------*/
int sUpdatePos(int servo, int sUpdatedPos)
{
    int ok = -1; // Used for debugging
    if (sCheckLastPos(servo) < 0) // If last position is less then 1 (which means error)
    {
        servosUpdatedPos[servo][SERVO_LAST_POS] = sUpdatedPos; // Update last pos of servo with sUpdatedPos
        ok = 1;     // Returns 1 since previous pos was an error, but it successfully fixed the error
    }
    else
    {
        servosUpdatedPos[servo][SERVO_LAST_POS] = sUpdatedPos; // Update last pos of servo with sUpdatedPos
        ok = sUpdatedPos; // Returns with the sUpdatedPos
    }
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sUpdatePos - servo: "));
        Serial.print(servo);
        Serial.print(F(" | sUpdatedPos: "));
        Serial.print(sUpdatedPos);
        Serial.print(F(" | result: "));
        Serial.println(ok);
    }
    return (ok); // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sCheckIfErrorAbsPos > Checks if abs pos is in range
    ------------------------------------------------------------------------------------------------------*/
int sCheckIfErrorAbsPos(int servo, int checkedAbsPos)
{
    int ok = -1; // Used for debugging
    int lastPos = sCheckLastPos(servo);

    // If the wanted pos of servo is in the allowed range of the servo, we pass ok
    if ((checkedAbsPos <= sGetAbsMaxPos(servo)) && (checkedAbsPos >= sGetAbsMinPos(servo)))
    {
        ok = 0;
    }
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sCheckIfErrorAbsPos - servo: "));
        Serial.print(servo);
        Serial.print(F(" | sCheckedAbsPos: "));
        Serial.print(checkedAbsPos);
        Serial.print(F(" | lastPos: "));
        Serial.print(lastPos);
        Serial.print(F(" | result: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/02/2020] sDelay > Servo delay "T###"
    ------------------------------------------------------------------------------------------------------*/
void sDelay(int timeToPos)
{
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sDelay: "));
        Serial.println(timeToPos);
    }
    Serial2.print(F("T"));  // Sends timeToPos to the SSC
    Serial2.println(timeToPos); // Sends timeToPos to the SSC

    //vTaskDelay( timeToPos / portTICK_PERIOD_MS ); // Use this if this function is called by a RTOS thread
    delay(timeToPos);  // Delays the program because we need to wait for the SSC to finish
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sSubmitAbsPos > Submits abs pos to servo
    ------------------------------------------------------------------------------------------------------*/
int sSubmitAbsPos(int servo, int pos, int timeToPos)
{
    int ok = -1;    // Used for debugging
    // Sends move data to servo
    Serial2.print(F("#"));
    Serial2.print(servo);
    Serial2.print(F("P"));
    Serial2.print(pos);
    ok = 0; // Returns 0 if it doesn't have delay
    if (timeToPos > 0)
    {
        sDelay(timeToPos);
        ok = 1; // Returns 1 if it has delay
    }
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sSubmitAbsPos - servo: "));
        Serial.print(servo);
        Serial.print(F(" | pos: "));
        Serial.print(pos);
        Serial.print(F(" | timeToPos: "));
        Serial.print(timeToPos);
        Serial.print(F(" | result: "));
        Serial.println(ok);
    }
    return (ok); // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/26/2020] sMoveAbsMS > Moves servo to pos in ms
    ------------------------------------------------------------------------------------------------------*/
int sMoveAbsMS(int servo, int pos, int timeToPos)
{
    int ok = -1;    // Used for debugging
    if (sCheckIfErrorAbsPos(servo, pos) == 0)   // If value is within acceptable range
    {
        sSubmitAbsPos(servo, pos, timeToPos);   // Move the servo!
        ok = sUpdatePos(servo, pos);    // Get result from sUpdatePos
    }
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sMoveAbsMS - returns: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/26/2020] sMoveRelMS > Moves servo to pos in ms with servo default value added
    ------------------------------------------------------------------------------------------------------*/
int sMoveRelMS(int servo, int pos, int timeToPos)
{
    int ok = -1; // Used for debugging
    int moveToPos = sGetDefaultPos(servo) + pos;   // Adds the wanted pos on top of the default pos
    ok = sMoveAbsMS(servo, moveToPos, timeToPos);
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sMoveRelMS - returns: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/26/2020] sMoveRelDEG > Moves servo to degree, assuming 0 is servo's default pos
    ------------------------------------------------------------------------------------------------------*/
int sMoveRelDEG(int servo, float angle, int timeToPos)
{
    int ok = -1;    // Used for debugging
    float moveToPos;
    //int moveToPos = (angle / .09) + sGetDefaultPos(servo);
    if (sGetAbsMinPos(servo) > sGetAbsMaxPos(servo))
    {
        // ...the result is the min (which is the higher number) minus the ms value of angle (calculated)
        // The value sent to the servo will be lower than min pos (cause it's bigger than max)
        moveToPos = sGetDefaultPos(servo) - (angle / .09);
    }
    else
    {
        // Else we do normal adding to min pos
        moveToPos = sGetDefaultPos(servo) + (angle / .09);
    }
    ok = sMoveAbsMS(servo, moveToPos, timeToPos);
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sMoveRelDEG - returns: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/27/2020] sMoveAbsDEG > Moves servo to degree, assuming 0 is servo's lowest number
    ------------------------------------------------------------------------------------------------------*/
int sMoveAbsDEG(int servo, float angle, int timeToPos)
{
    int ok = -1;    // Used for debugging
    float moveToPos;
    // If the min pos is higher than the max pos...
    if (sGetAbsMinPos(servo) > sGetAbsMaxPos(servo))
    {
        // ...the result is the min (which is the higher number) minus the ms value of angle (calculated)
        // The value sent to the servo will be lower than min pos (cause it's bigger than max)
        moveToPos = sGetAbsMaxPos(servo) + (angle / .09);
    }
    else
    {
        // Else we do normal adding to min pos
        moveToPos = sGetAbsMinPos(servo) + (angle / .09);
    }
    ok = sMoveAbsMS(servo, moveToPos, timeToPos);
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sMoveAbsDEG - returns: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/27/2020] sMoveAbsDEGOLD > Moves servo to degree, assuming 0 is servo's lowest number
    ------------------------------------------------------------------------------------------------------*/
int sMoveAbsDEGOLD(int servo, float angle, int timeToPos)
{
    int ok = -1;    // Used for debugging
    int moveToPos;
    // If the min pos is higher than the max pos...
    if (sGetAbsMinPos(servo) > sGetAbsMaxPos(servo))
    {
        // ...the result is the min (which is the higher number) minus the ms value of angle (calculated)
        // The value sent to the servo will be lower than min pos (cause it's bigger than max)
        moveToPos = sGetAbsMinPos(servo) - (angle / .09);
    }
    else
    {
        // Else we do normal adding to min pos
        moveToPos = sGetAbsMinPos(servo) + (angle / .09);
    }
    ok = sMoveAbsMS(servo, moveToPos, timeToPos);
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sMoveRelDEG - returns: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/26/2020] sInit > Initates servos and populates abs min and max values. Only called during setup()
    ------------------------------------------------------------------------------------------------------*/
void sInit()
{
    Serial2.begin(SERVO_BAUDRATE);  // Serial2 is connected to the SSC32 serial port
    if (DEBUG)  // If debugging is turned on...
    {
        Serial.println(F("Initiating servos"));
        Serial.println(F("sInit: START"));
    }
    for (int i = 0; i < MAX_SERVOS_POSSIBLE; i++) // Loops MAX_SERVOS_POSSIBLE times (it's one extra time because servo id starts from 1 and array starts from 0)
    {
        int defaultPos, updatedAbsMinPos, updatedAbsMaxPos;   // Make some vars
        defaultPos = sGetDefaultPos(i);     // Returns servo's default pos
        updatedAbsMinPos = defaultPos - sGetRelMinPos(i);  // Default pos minus the lowest range possible
        updatedAbsMaxPos = defaultPos + sGetRelMaxPos(i);  // Default pos plus the highest range possible
        servosInfo[i][SERVO_ABS_MIN_POS] = updatedAbsMinPos;   // Updates min abs pos
        servosInfo[i][SERVO_ABS_MAX_POS] = updatedAbsMaxPos;   // Updates max abs pos
        if (DEBUG)  // If debugging is turned on...
        {
            Serial.print(i);
            Serial.print(F(" = "));
            Serial.println(defaultPos);
        }
    }
    if (DEBUG)  // If debugging is turned on...
    {
        Serial.println(F("sInit: DONE "));
    }
}
