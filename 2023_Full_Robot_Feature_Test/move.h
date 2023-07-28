bool isInMotion()
{
    bool isServoMoving = false;
    for (int i = 0; i < PCA9685_MAX_CHANNELS; ++i)
    {
        isServoMoving += ServoEasing::ServoEasingArray[i]->isMoving();
    }
    if (IS_DEBUGGING_ENABLED)
    {
        Serial.println(F("IS IN MOTION"));
    }
    return isServoMoving;
}

void actionR(int moveTime)
{
    if (!rIsError)
    {
        if (IS_DEBUGGING_ENABLED)
        {
            Serial.print(F("R_LEG:"));
            Serial.print(R_Y_HIP_deg);
            Serial.print(F(", "));
            Serial.print(R_R_HIP_deg);
            Serial.print(F(", "));
            Serial.print(R_P_HIP_deg);
            Serial.print(F(", "));
            Serial.print(R_P_KNE_deg);
            Serial.print(F(", "));
            Serial.print(R_P_ANK_deg);
            Serial.print(F(", "));
            Serial.print(R_R_ANK_deg);
            Serial.println();
        }
        ServoEasing::ServoEasingArray[R_Y_HIP]->startEaseToD((int)R_Y_HIP_deg, moveTime);
        ServoEasing::ServoEasingArray[R_R_HIP]->startEaseToD((int)R_R_HIP_deg, moveTime);
        ServoEasing::ServoEasingArray[R_P_HIP]->startEaseToD((int)R_P_HIP_deg, moveTime);
        ServoEasing::ServoEasingArray[R_P_KNE]->startEaseToD((int)R_P_KNE_deg, moveTime);
        ServoEasing::ServoEasingArray[R_P_ANK]->startEaseToD((int)R_P_ANK_deg, moveTime);
        ServoEasing::ServoEasingArray[R_R_ANK]->startEaseToD((int)R_R_ANK_deg, moveTime);
    }
    else
    {
        if (IS_DEBUGGING_ENABLED)
        {
            Serial.println(F("Check robot status!"));
        }
    }
}

void actionL(int moveTime)
{
    if (!rIsError)
    {
        if (IS_DEBUGGING_ENABLED)
        {
            Serial.print(F("L_LEG:"));
            Serial.print(L_Y_HIP_deg);
            Serial.print(F(", "));
            Serial.print(L_R_HIP_deg);
            Serial.print(F(", "));
            Serial.print(L_P_HIP_deg);
            Serial.print(F(", "));
            Serial.print(L_P_KNE_deg);
            Serial.print(F(", "));
            Serial.print(L_P_ANK_deg);
            Serial.print(F(", "));
            Serial.print(L_R_ANK_deg);
            Serial.println();
        }
        ServoEasing::ServoEasingArray[L_Y_HIP]->startEaseToD((int)L_Y_HIP_deg, moveTime);
        ServoEasing::ServoEasingArray[L_R_HIP]->startEaseToD((int)L_R_HIP_deg, moveTime);
        ServoEasing::ServoEasingArray[L_P_HIP]->startEaseToD((int)L_P_HIP_deg, moveTime);
        ServoEasing::ServoEasingArray[L_P_KNE]->startEaseToD((int)L_P_KNE_deg, moveTime);
        ServoEasing::ServoEasingArray[L_P_ANK]->startEaseToD((int)L_P_ANK_deg, moveTime);
        ServoEasing::ServoEasingArray[L_R_ANK]->startEaseToD((int)L_R_ANK_deg, moveTime);
    }
    else
    {
        if (IS_DEBUGGING_ENABLED)
        {
            Serial.println(F("Check robot status!"));
        }
    }
}

void actionALL(int moveTime)
{
    actionL(moveTime);
    actionR(moveTime);
}

void actionDelayALL(int moveTime)
{
    actionALL(moveTime);
    vDelay(moveTime);
}

void servoReset(bool stabilize)
{
    Serial.println(F("legs reset!"));
    //reset
    R_Y_HIP_deg = S_CENTER[R_Y_HIP];
    R_R_HIP_deg = S_CENTER[R_R_HIP];
    R_P_HIP_deg = S_CENTER[R_P_HIP];
    R_P_KNE_deg = S_CENTER[R_P_KNE] + ((stabilize) ? +legCalibrateTilt : 0);
    R_P_ANK_deg = S_CENTER[R_P_ANK] + ((stabilize) ? -legCalibrateTilt : 0);
    R_R_ANK_deg = S_CENTER[R_R_ANK];
    //reset
    L_Y_HIP_deg = S_CENTER[L_Y_HIP];
    L_R_HIP_deg = S_CENTER[L_R_HIP];
    L_P_HIP_deg = S_CENTER[L_P_HIP];
    L_P_KNE_deg = S_CENTER[L_P_KNE] + ((stabilize) ? +legCalibrateTilt : 0);
    L_P_ANK_deg = S_CENTER[L_P_ANK] + ((stabilize) ? -legCalibrateTilt : 0);
    L_R_ANK_deg = S_CENTER[L_R_ANK];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//old moving, merging with new stuff!
//////////////////////////////////////////////////////////////////////////////
////////////////////// Ready (Normal + Lift)
void legBend(char leg, int angleOfKnee, bool stabilize)
{
    if ((angleOfKnee <= 120) && (angleOfKnee >= 0))
    {
        if (IS_DEBUGGING_ENABLED)
        {
            Serial.print(toupper(leg));
            Serial.print(F(" leg squat: "));
            Serial.println(angleOfKnee);
        }
        //bend down
        if (leg == 'r')
        {
            R_P_HIP_deg = S_CENTER[R_P_HIP] + (angleOfKnee / 2);
            R_P_KNE_deg = S_CENTER[R_P_KNE] - angleOfKnee + ((stabilize) ? +legCalibrateTilt : 0);
            R_P_ANK_deg = S_CENTER[R_P_ANK] - (angleOfKnee / 2) + ((stabilize) ? -legCalibrateTilt : 0);
        }
        else if (leg == 'l')
        {
            L_P_HIP_deg = S_CENTER[L_P_HIP] + (angleOfKnee / 2);
            L_P_KNE_deg = S_CENTER[L_P_KNE] - angleOfKnee + ((stabilize) ? +legCalibrateTilt : 0);
            L_P_ANK_deg = S_CENTER[L_P_ANK] - (angleOfKnee / 2) + ((stabilize) ? -legCalibrateTilt : 0);
        }
    }
    else
    {
        if (IS_DEBUGGING_ENABLED)
        {
            Serial.print(F("ERROR legs squat: "));
            Serial.println(angleOfKnee);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Forward (Normal + Lift)
void legFwd(char leg, int angleOfKnee, bool stabilize)
{
    //int angleOfKnee = 20;
    if (leg == 'r')
    {
        R_P_HIP_deg = S_CENTER[R_P_HIP] + (angleOfKnee * 0.7);
        R_P_KNE_deg = S_CENTER[R_P_KNE] - angleOfKnee + ((stabilize) ? +legCalibrateTilt : 0);
        R_P_ANK_deg = S_CENTER[R_P_ANK] - (angleOfKnee * 0.3) + ((stabilize) ? -legCalibrateTilt : 0);
    }
    else if (leg == 'l')
    {
        L_P_HIP_deg = S_CENTER[L_P_HIP] + (angleOfKnee * 0.7);
        L_P_KNE_deg = S_CENTER[L_P_KNE] - angleOfKnee + ((stabilize) ? +legCalibrateTilt : 0);
        L_P_ANK_deg = S_CENTER[L_P_ANK] - (angleOfKnee * 0.3) + ((stabilize) ? -legCalibrateTilt : 0);
    }
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Backward (Normal + Lift)
void legBack(char leg, int angleOfKnee, bool stabilize)
{
    //int angleOfKnee = 20;
    if (leg == 'r')
    {
        R_P_HIP_deg = S_CENTER[R_P_HIP] + (angleOfKnee * 0.3);
        R_P_KNE_deg = S_CENTER[R_P_KNE] - angleOfKnee + ((stabilize) ? +legCalibrateTilt : 0);
        R_P_ANK_deg = S_CENTER[R_P_ANK] - (angleOfKnee * 0.7) + ((stabilize) ? -legCalibrateTilt : 0);
    }
    else if (leg == 'l')
    {
        L_P_HIP_deg = S_CENTER[L_P_HIP] + (angleOfKnee * 0.3);
        L_P_KNE_deg = S_CENTER[L_P_KNE] - angleOfKnee + ((stabilize) ? +legCalibrateTilt : 0);
        L_P_ANK_deg = S_CENTER[L_P_ANK] - (angleOfKnee * 0.7) + ((stabilize) ? -legCalibrateTilt : 0);
    }
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Lean (Right + Left)
void legLean(char leg, int leanDeg)
{
    if (leg == 'r')
    {
        R_R_HIP_deg = S_CENTER[R_R_HIP] + (leanDeg * 0.45);
        R_R_ANK_deg = S_CENTER[R_R_ANK] + (leanDeg * 0.55);
    }
    else if (leg == 'l')
    {
        L_R_HIP_deg = S_CENTER[L_R_HIP] + (leanDeg * 0.45);
        L_R_ANK_deg = S_CENTER[L_R_ANK] + (leanDeg * 0.55);
    }
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Balance (Right + Left)
void legBalance(char leg, int leanDeg)
{
    if (leg == 'r')
    {
        R_R_HIP_deg = S_CENTER[R_R_HIP] + (leanDeg * 0.35);
        R_R_ANK_deg = S_CENTER[R_R_ANK] + (leanDeg * 0.65);
    }
    else if (leg == 'l')
    {
        L_R_HIP_deg = S_CENTER[L_R_HIP] + (leanDeg * 0.35);
        L_R_ANK_deg = S_CENTER[L_R_ANK] + (leanDeg * 0.65);
    }
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Twist (Right + Left)
void legTwist(char leg, int twistDeg)
{
    if (leg == 'r')
    {
        R_Y_HIP_deg = S_CENTER[R_Y_HIP] + twistDeg;
    }
    else if (leg == 'l')
    {
        L_Y_HIP_deg = S_CENTER[L_Y_HIP] + twistDeg;
    }
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Compiled
void bendReady()
{
    legBend('r', READY_ANGLE, true);
    legBend('l', READY_ANGLE, true);
}

void twistReady()
{
    legTwist('r', 0);
    legTwist('l', 0);
}

void leanReady()
{
    legLean('r', 0);
    legLean('l', 0);
}

void leanRight()
{
    legLean('r', -20);
    legLean('l', 25);
}

void leanLeft()
{
    legLean('r', 25);
    legLean('l', -20);
}

void balanceRight()
{
    legBalance('r', -20);
    legLean('l', 20);
}

void balanceLeft()
{
    legLean('r', 20);
    legBalance('l', -20);
}

void readyToWalk()
{
    bendReady();
    twistReady();
    leanReady();
}

/*  ------------------------------------------------------------------------------------------------------
    [2022.08.29] walkingV10 > testing out new walking gait
    ------------------------------------------------------------------------------------------------------*/
void walkingV10(int steps, double walkSpeed)
{
    tftMsg("start");
    // Get ready
    readyToWalk();
    legBend('r', BEND_ANGLE, true);
    legBend('l', BEND_ANGLE, true);
    actionDelayALL(MOVE_DEFAULT_TIME);
    for (int i = 0; i < steps; i++)
    {
        ///////////////////////////////////////////////////
        /////////// Left step
        tftMsg("L STEP - lean R");
        leanRight();
        actionDelayALL(walkSpeed * (MOVE_DEFAULT_TIME * 2.5));
        tftMsg("L STEP - lift L");
        legBend('l', LIFT_ANGLE, false);
        actionDelayALL(walkSpeed * (MOVE_DEFAULT_TIME * 0.75));
        tftMsg("L STEP - down forward L, center R, back R");
        legBalance('l', 35);
        legFwd('l', LIFT_ANGLE, false);
        legBend('r', BEND_ANGLE, true);
        actionR(walkSpeed * (MOVE_DEFAULT_TIME + 500));
        actionL(walkSpeed * (MOVE_DEFAULT_TIME));
        vDelay(walkSpeed * (MOVE_DEFAULT_TIME));
        legBack('r', BEND_ANGLE, true);
        actionDelayALL(walkSpeed * (MOVE_DEFAULT_TIME));
        ///////////////////////////////////////////////////
        /////////// Right step
        tftMsg("R STEP - lean L");
        leanLeft();
        actionDelayALL(walkSpeed * (MOVE_DEFAULT_TIME * 2.5));
        tftMsg("R STEP - lift R");
        legBend('r', LIFT_ANGLE, false);
        actionDelayALL(walkSpeed * (MOVE_DEFAULT_TIME * 0.75));
        tftMsg("R STEP - down forward R, center L, back L");
        legBalance('r', 35);
        legFwd('r', LIFT_ANGLE, false);
        legBend('l', BEND_ANGLE, true);
        actionR(walkSpeed * (MOVE_DEFAULT_TIME + 500));
        actionL(walkSpeed * (MOVE_DEFAULT_TIME));
        vDelay(walkSpeed * (MOVE_DEFAULT_TIME));
        legBack('l', BEND_ANGLE, true);
        actionDelayALL(walkSpeed * (MOVE_DEFAULT_TIME));
    }
    tftMsg("end");
    ///////////////////////////////////////////////////
    /////////// To end on left step
    readyToWalk();
    actionDelayALL(MOVE_DEFAULT_TIME + 200);
}

// Taken from BASE.001_PCA9685_Expander_demo, the project I made for testing out the robot's servos.
void rSquatTest()
{
    //reset
    servoReset(true);
    actionALL(2000);
    delay(2100);

    //bend down
    R_P_HIP_deg = S_CENTER[R_P_HIP] + 45;
    R_P_KNE_deg = S_CENTER[R_P_KNE] - 90;
    R_P_ANK_deg = S_CENTER[R_P_ANK] - 45;
    L_P_HIP_deg = S_CENTER[L_P_HIP] + 45;
    L_P_KNE_deg = S_CENTER[L_P_KNE] - 90;
    L_P_ANK_deg = S_CENTER[L_P_ANK] - 45;
    actionALL(2000);
    delay(2100);

    //reset
    servoReset(true);
    actionALL(2000);
    delay(2100);

    //bend down low
    R_P_HIP_deg = S_CENTER[R_P_HIP] + 60;
    R_P_KNE_deg = S_CENTER[R_P_KNE] - 120;
    R_P_ANK_deg = S_CENTER[R_P_ANK] - 60;
    L_P_HIP_deg = S_CENTER[L_P_HIP] + 60;
    L_P_KNE_deg = S_CENTER[L_P_KNE] - 120;
    L_P_ANK_deg = S_CENTER[L_P_ANK] - 60;
    actionALL(2000);
    delay(2100);

    //tilt right
    R_Y_HIP_deg = S_CENTER[R_Y_HIP] + 20;
    R_R_HIP_deg = S_CENTER[R_R_HIP] + 25;
    R_R_ANK_deg = S_CENTER[R_R_ANK] + 25;
    L_Y_HIP_deg = S_CENTER[L_Y_HIP] - 20;
    L_R_HIP_deg = S_CENTER[L_R_HIP] - 25;
    L_R_ANK_deg = S_CENTER[L_R_ANK] - 25;
    actionALL(2000);
    delay(2100);

    //tilt left
    R_Y_HIP_deg = S_CENTER[R_Y_HIP] - 20;
    R_R_HIP_deg = S_CENTER[R_R_HIP] - 25;
    R_R_ANK_deg = S_CENTER[R_R_ANK] - 25;
    L_Y_HIP_deg = S_CENTER[L_Y_HIP] + 20;
    L_R_HIP_deg = S_CENTER[L_R_HIP] + 25;
    L_R_ANK_deg = S_CENTER[L_R_ANK] + 25;
    actionALL(2000);
    delay(2100);

    //reset
    servoReset(true);
    actionALL(2000);
    delay(2100);
}

/*  ------------------------------------------------------------------------------------------------------
    [2023.07.25] walkingV13 > Copy MiniPlanV6 walking. seems to be working, ish.
    ------------------------------------------------------------------------------------------------------*/
void walkingV13(int loops)
{
    int local_bend_angle = 70;
    int local_ready_angle = 50;
    tftMsg("start walkingV13");
    // Get ready

    // step 1
    readyToWalk();
    actionDelayALL(MOVE_DEFAULT_TIME);

    // step 2
    legBend('r', local_bend_angle, true);
    legBend('l', local_ready_angle, true);
    legBalance('r', 25);
    legBalance('l', -20);
    actionDelayALL(400);


    for (int i = 0; i < loops; i++)
    {
        // step 3
        tftMsg("step3");
        legFwd('r', local_bend_angle, true);
        legBalance('r', 30);
        legBalance('l', -20);
        actionDelayALL(300);

        // step 4
        tftMsg("step4");
        legFwd('r', local_ready_angle, true);
        legBend('l', local_ready_angle, true);
        legBalance('l', 30);
        legBalance('r', -20);
        actionDelayALL(500);

        // step 5
        tftMsg("step5");
        legBend('r', local_ready_angle, true);
        legBend('l', local_bend_angle, true);
        legBalance('l', 30);
        legBalance('r', -20);
        actionDelayALL(300);

        // step 6
        tftMsg("step6");
        legFwd('l', local_bend_angle, true);
        legBalance('l', 30);
        legBalance('r', -20);
        actionDelayALL(300);

        // step 7
        tftMsg("step7");
        legFwd('l', local_ready_angle, true);
        legBend('r', local_ready_angle, true);
        legBalance('r', 30);
        legBalance('l', -20);
        actionDelayALL(500);

        // step 8
        tftMsg("step8");
        legBend('r', local_bend_angle, true);
        legBend('l', local_ready_angle, true);
        legBalance('r', 30);
        legBalance('l', -20);
        actionDelayALL(300);
    }

    tftMsg("end walkingV13");

    // step 9 (step 1 again) to end
    readyToWalk();
    actionDelayALL(MOVE_DEFAULT_TIME);
}
