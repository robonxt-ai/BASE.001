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

//    sMoveDeg90(24, 0.0, 2000);
//    sMoveDeg90(23, 0.0, 2000);
//    sMoveDeg90(22, 0.0, 2000);
//    delay(2000);
//    sMoveDeg90(24, -90.0, 0);
//    sMoveDeg90(23, 90.0, 0);
//    sMoveDeg90(22, -90.0, 2000);
//    delay(2000);
//    sMoveDeg90(24, 90.0, 0);
//    sMoveDeg90(23, -90.0, 0);
//    sMoveDeg90(22, 90.0, 2000);


/*  ------------------------------------------------------------------------------------------------------
    [6/??/2020] mapFloat > like map(), but supports floats
    ------------------------------------------------------------------------------------------------------*/

int mapFloat (float Angle, float min_ms, float max_ms, float min_angle, float max_angle)
{
    return (((max_ms - min_ms) / (max_angle - min_angle)) * (Angle - min_angle)) + min_ms;
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
            ok = sMoveAbsMS(i, defaultPos, 100);
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

///*  ------------------------------------------------------------------------------------------------------
//    [6/21/2020] sMoveDeg180 > Moves servo to a degree (0 to 180) NEED TO EDIT TO DO ACTUALLY DO DEGREES FOR ALL SERVOS
//    ------------------------------------------------------------------------------------------------------*/
//int sMoveDeg180(int servo, float Angle, int timeToPos)
//{
//    return sMoveDegAbsToDefault(servo, Angle, sGetAbsMinPos(servo), sGetAbsMaxPos(servo), 0, 180, timeToPos);   // A shortcut way to move a servo from 0 to 180
//}
//
///*  ------------------------------------------------------------------------------------------------------
//    [6/21/2020] sMoveDeg90 > Moves servo to a degree (-90 to 90)  NEED TO EDIT TO DO ACTUALLY DO DEGREES FOR ALL SERVOS
//    ------------------------------------------------------------------------------------------------------*/
//int sMoveDeg90(int servo, float Angle, int timeToPos)
//{
//    return sMoveDegAbsToDefault(servo, Angle, sGetAbsMinPos(servo), sGetAbsMaxPos(servo), -90, 90, timeToPos);  // A shortcut way to move a servo from -90 to 90
//}
