/*
    Servo Controller for SainSmart Humanoid Robot Kit
    ------
    Goals:
    04/19/2020: base system implemented
    06/26/2020: updating comments. need to fix the move degrees functions so they will acceratelly move in degrees for any servo regardless of range
    ------
    A (start from small)™ program based off what dad taught me
    ------
    modified Jun 26 2020
    by Steven Liao (with dad)
*/

// Easy to read names for the servos. Also lets us know which one is on which port
#define HEAD            1
#define L_ARM_ELBOW     2
#define L_ARM_OUTWARD   3
#define L_ARM_FORWARD   4

#define L_LEG_PELVIS    8
#define L_LEG_THIGH     9
#define L_LEG_KNEE      10
#define L_LEG_ANKLE     11
#define L_LEG_FOOT      12

#define R_LEG_FOOT      21
#define R_LEG_ANKLE     22
#define R_LEG_KNEE      23
#define R_LEG_THIGH     24
#define R_LEG_PELVIS    25

#define R_ARM_ELBOW     29
#define R_ARM_OUTWARD   30
#define R_ARM_FORWARD   31

// array 1 4/8/2020 14:48
// 4/13/2020 18:05 S11 tuned to 1480, S10 tuned to 1480
// 4/14/2020 15:05 S11 to 1500, S10 to 1490, S12 to 1470, S22 to 1500
// 4/21/2020 17:58 S9 to 1580, S10 to 1500
// 4/23/2020 21:58 S21 to 1480, S11 to 1470, S9 to 1570, S8 to 990, S10 to 1510, S24 to 1550
// 6/04/2020 23:59 S11 to 1490, S22 to 1510
// 6/05/2020 11:50 S12 to 1420. S8 to 995
// 6/19/2020 13:15 S9 to 1600 (-950/+950), S10 to 1500, S11 to 1475, S22 to 1525, S24 to 1450 (-950/+950)
// 6/21/2020 18:50 S24 to 1420 (-1000/+1000), S23 to 1500 (-1000/+1000), S22 to 1520 (-1000/+1000)

// Store servo status only
// Id, default pos, min (value), max (value), min (generated), max (generated)
int servosInfo[][6]
{
    0,  -1, -1, -1, -1, -1,         // Does not exist
    1,  1500, 950, 950, -1, -1,     // Head (Not connected at the moment)
    2,  1470, 950, 950, -1, -1,     // Left arm elbow
    3,  530, 50, 2000, -1, -1,      // Left arm shoulder out
    4,  2500, 2000, 50, -1, -1,     // Left arm shoulder forward
    5,  -1, -1, -1, -1, -1,
    6,  -1, -1, -1, -1, -1,
    7,  -1, -1, -1, -1, -1,
    8,  995, 300, 1200, -1, -1,     // Left leg pelvis
    9,  1600, 950, 950, -1, -1,     // Left leg thigh
    10, 1500, 950, 950, -1, -1,     // Left leg knee
    11, 1475, 950, 950, -1, -1,     // Left leg ankle
    12, 1420, 300, 500, -1, -1,     // Left leg foot
    13, -1, -1, -1, -1, -1,
    14, -1, -1, -1, -1, -1,
    15, -1, -1, -1, -1, -1,
    16, -1, -1, -1, -1, -1,
    17, -1, -1, -1, -1, -1,
    18, -1, -1, -1, -1, -1,
    19, -1, -1, -1, -1, -1,
    20, -1, -1, -1, -1, -1,
    21, 1480, 500, 300, -1, -1,     // Right leg foot
    22, 1520, 1000, 1000, -1, -1,   // Right leg ankle
    23, 1500, 1000, 1000, -1, -1,   // Right leg knee
    24, 1420, 1000, 1000, -1, -1,   // Right leg thigh
    25, 2000, 1200, 300, -1, -1,    // Right leg pelvis
    26, -1, -1, -1, -1, -1,
    27, -1, -1, -1, -1, -1,
    28, -1, -1, -1, -1, -1,
    29, 1530, 950, 950, -1, -1,     // Right arm elbow
    30, 530, 50, 2000, -1, -1,      // Right arm shoulder out
    31, 500, 50, 2000, -1, -1,      // Right arm shoulder forward
    32, -1, -1, -1, -1, -1
};


// 2D array. 4/8/2020 1:17
// Stores servo sUpdates only
// Id, last sUpdated pos
int servosUpdatedPos[][2]
{
    0, -1,  // Does not exist
    1, -1,  // Head (Not connected at the moment)
    2, -1,  // Left arm elbow
    3, -1,  // Left arm shoulder out
    4, -1,  // Left arm shoulder forward
    5, -1,
    6, -1,
    7, -1,
    8, -1,  // Left leg pelvis
    9, -1,  // Left leg thigh
    10, -1, // Left leg knee
    11, -1, // Left leg ankle
    12, -1, // Left leg foot
    13, -1,
    14, -1,
    15, -1,
    16, -1,
    17, -1,
    18, -1,
    19, -1,
    20, -1,
    21, -1, // Right leg foot
    22, -1, // Right leg ankle
    23, -1, // Right leg knee
    24, -1, // Right leg thigh
    25, -1, // Right leg pelvis
    26, -1,
    27, -1,
    28, -1,
    29, -1, // Right arm elbow
    30, -1, // Right arm shoulder out
    31, -1, // Right arm shoulder forward
    32, -1
};


// Side, elbow, shoulder out, shoulder forward
// 0 is left, 1 is right
int arms[][4]
{
    0, 2, 3, 4,
    1, 29, 30, 31
};

// Side, foot, ankle, knee, thigh, pelvis
// First line is left side, second line is right side
int mirroredLegs[2][5]
{
    12, 11, 10, 9, 8,
    21, -22, -23, -24, 25
};

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetDefaultPos > Returns servo's default pos. arg(int servo), returns int
    ------------------------------------------------------------------------------------------------------*/
int sGetDefaultPos(int servo)
{
    return (servosInfo[servo][SERVO_DEFAULT_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetRelMinPos > Returns servo's relative min pos. arg(int servo), returns int
    ------------------------------------------------------------------------------------------------------*/
int sGetRelMinPos(int servo)
{
    return (servosInfo[servo][SERVO_REL_MIN_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetRelMaxPos > Returns servo's relative max pos. arg(int servo), returns int
    ------------------------------------------------------------------------------------------------------*/
int sGetRelMaxPos(int servo)
{
    return (servosInfo[servo][SERVO_REL_MAX_POS]); // Returns servo's relative min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetAbsMinPos > Returns servo's absolute min pos. arg(int servo), returns int
    ------------------------------------------------------------------------------------------------------*/
int sGetAbsMinPos(int servo)
{
    return (servosInfo[servo][SERVO_ABS_MIN_POS]); // Returns servo's absolute min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sGetAbsMaxPos > Returns servo's absolute max pos. arg(int servo), returns int
    ------------------------------------------------------------------------------------------------------*/
int sGetAbsMaxPos(int servo)
{
    return (servosInfo[servo][SERVO_ABS_MAX_POS]); // Returns servo's absolute min pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sCheckPos > Returns last updated pos of servo. arg(int servo), returns int
    ------------------------------------------------------------------------------------------------------*/
int sCheckLastPos(int servo)
{
    return (servosUpdatedPos[servo][SERVO_LAST_POS]); // Returns servo's last updated pos
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sUpdatePos > Updates position of servo args(int servo, int sUpdatedPos), returns int
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
    [4/8/2020] sInit > Initates servos and populates abs min and max. Only called during setup()
    ------------------------------------------------------------------------------------------------------*/
int sInit()
{
    Serial2.begin(SERVO_BAUDRATE);
    int ok = 0;
    if (DEBUG)  // If debugging is turned on...
    {
        Serial.println(F("Initiating servos"));
        Serial.println(F("sInit: START"));
    }

    for (int i = 0; i < MAX_SERVOS_POSSIBLE; i++) // Loops MAX_SERVOS_POSSIBLE times (it's one extra time because servo id starts from 1 and array starts from 0)
    {
        int defaultPos, sUpdatedAbsMinPos, sUpdatedAbsMaxPos;   // Make some vars
        defaultPos = sGetDefaultPos(i);     // Returns servo's default pos
        sUpdatedAbsMinPos = defaultPos - sGetRelMinPos(i);  // Default pos minus the lowest range possible
        sUpdatedAbsMaxPos = defaultPos + sGetRelMaxPos(i);  // Default pos plus the highest range possible
        servosInfo[i][SERVO_ABS_MIN_POS] = sUpdatedAbsMinPos;   // Updates min abs pos
        servosInfo[i][SERVO_ABS_MAX_POS] = sUpdatedAbsMaxPos;   // Updates max abs pos
        if (DEBUG)  // If debugging is turned on...
        {
            Serial.print(i);
            Serial.print(F(" "));
            Serial.println(defaultPos);
        }

    }
    if (DEBUG)  // If debugging is turned on...
    {
        Serial.print(F("servosInit - result: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sCheckIfErrorAbsPos > Checks if abs pos is in range. args(int servo, int sCheckedAbsPos)
    ------------------------------------------------------------------------------------------------------*/
int sCheckIfErrorAbsPos(int servo, int sCheckedAbsPos)
{
    int ok = -1; // Used for debugging
    int lastPos = sCheckLastPos(servo);

    // If the wanted pos of servo is in the allowed range of the servo, we past ok
    if ((sCheckedAbsPos <= sGetAbsMaxPos(servo)) && (sCheckedAbsPos >= sGetAbsMinPos(servo)))
    {
        ok = 0;
    }
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sCheckIfErrorAbsPos - servo: "));
        Serial.print(servo);
        Serial.print(F(" | sCheckedAbsPos: "));
        Serial.print(sCheckedAbsPos);
        Serial.print(F(" | lastPos: "));
        Serial.print(lastPos);
        Serial.print(F(" | result: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/02/2020] sDelay > Servo delay "T###" args(int timeToPos)
    ------------------------------------------------------------------------------------------------------*/
void sDelay(int timeToPos)
{

    Serial2.print(F("T"));  // Sends timeToPos to the SSC
    Serial2.println(timeToPos); // Sends timeToPos to the SSC

    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sDelay: "));
        Serial.println(timeToPos);
    }

    //vTaskDelay( timeToPos / portTICK_PERIOD_MS ); // Use this if this function is called by a RTOS thread
    delay(timeToPos + 10);  // Delays the program because we need to wait for the SSC to finish
}

/*  ------------------------------------------------------------------------------------------------------
    [4/8/2020] sSubmitAbsPos > Submits abs pos to servo. args(int servo, int pos, int timeToPos)
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
    int sMoveToPos = sGetDefaultPos(servo) + pos;   // Adds the wanted pos on top of the default pos
    ok = sMoveAbsMS(servo, sMoveToPos, timeToPos);
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
int sMoveRelDEG(int servo, float Angle, int timeToPos)
{
    int ok = -1;    // Used for debugging
    int sMoveToPos = (Angle / .09) + sGetDefaultPos(servo);
    ok = sMoveAbsMS(servo, sMoveToPos, timeToPos);
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sMoveRelDEG - returns: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

/*  ------------------------------------------------------------------------------------------------------
    [6/26/2020] sMoveAbsDEG > Moves servo to degree, assuming 0 is servo's default pos
    ------------------------------------------------------------------------------------------------------*/
int sMoveAbsDEG(int servo, float Angle, int timeToPos)
{
    int ok = -1;    // Used for debugging
    int sMoveToPos = (Angle / .09) + sGetDefaultPos(servo);
    ok = sMoveAbsMS(servo, sMoveToPos, timeToPos);
    if (DEBUG)  // If debugging is turned on...
    {
        // Debug
        Serial.print(F("sMoveRelDEG - returns: "));
        Serial.println(ok);
    }
    return (ok);    // Returns ok value to the previous function
}

///*  ------------------------------------------------------------------------------------------------------
//    [6/21/2020] sMoveDegAbsToDefault > Moves an servo to a degree (??? to ???) NEED TO EDIT TO DO ACTUALLY DO DEGREES FOR ALL SERVOS
//    ------------------------------------------------------------------------------------------------------*/
//int sMoveDegAbsToDefault(int servo, float Angle, float min_ms, float max_ms, float min_angle, float max_angle, int timeToPos)
//{
//    int ok = -1;    // Used for debugging
//    int sMoveToPos = (((max_ms - min_ms) / (max_angle - min_angle)) * (Angle - min_angle)) + min_ms;    // This reassigns the range from min_ms/max_ms to min_angle/max_angle
//    // Int sMoveToPos = sGetDefaultPos(servo) + pos;
//    if (sCheckIfErrorAbsPos(servo, sMoveToPos) == 0)    // If value is within acceptable range
//    {
//        sSubmitAbsPos(servo, sMoveToPos, timeToPos);    // Move the servo!
//        ok = sUpdatePos(servo, sMoveToPos); // Get result from sUpdatePos
//    }
//    if (DEBUG)  // If debugging is turned on...
//    {
//        // Debug
//        Serial.print(F("sMoveRelToDefault - returns: "));
//        Serial.println(ok);
//    }
//    return (ok);    // Returns ok value to the previous function
//}

/*  ------------------------------------------------------------------------------------------------------
    [6/21/2020] sMoveDeg180 > Moves servo to a degree (0 to 180) NEED TO EDIT TO DO ACTUALLY DO DEGREES FOR ALL SERVOS
    ------------------------------------------------------------------------------------------------------*/
int sMoveDeg180(int servo, float Angle, int timeToPos)
{
    return sMoveDegAbsToDefault(servo, Angle, sGetAbsMinPos(servo), sGetAbsMaxPos(servo), 0, 180, timeToPos);   // A shortcut way to move a servo from 0 to 180
}

/*  ------------------------------------------------------------------------------------------------------
    [6/21/2020] sMoveDeg90 > Moves servo to a degree (-90 to 90)  NEED TO EDIT TO DO ACTUALLY DO DEGREES FOR ALL SERVOS
    ------------------------------------------------------------------------------------------------------*/
int sMoveDeg90(int servo, float Angle, int timeToPos)
{
    return sMoveDegAbsToDefault(servo, Angle, sGetAbsMinPos(servo), sGetAbsMaxPos(servo), -90, 90, timeToPos);  // A shortcut way to move a servo from -90 to 90
}


/*  ------------------------------------------------------------------------------------------------------
    [4/11/2020] sMoveToDefault > Moves all servos to default position.
    ------------------------------------------------------------------------------------------------------*/
int sMoveToDefault()
{
    int ok = -1; // Used for debugging
    for (int i = 1; i < MAX_SERVOS_POSSIBLE; i++)
    {
        int defaultPos = sGetDefaultPos(i);
        if (defaultPos >= 0)
        {
            ok = sMoveAbsMS(i, defaultPos, 200);
            if (ok < 0)
            {
                return (ok); // Returns ok value to the previous function
            }
        }
    }
    if (DEBUG)  // If debugging is turned on...
    {
        Serial.print(F("Default - returns: "));
        Serial.println(ok);
    }
    return (ok); // Returns ok value to the previous function
}
