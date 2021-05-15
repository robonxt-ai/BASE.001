/*
    testing code for BASE.001: SainSmart Humanoid Robot Kit
    ------
    Milestones:
    02/01/2021: Implementing degrees and IK.
    ------
    A (start from small)™ program based off what dad taught me
    ------
    modified 02/01/2021
    by robonxt
*/




// borrowed from https://www.instructables.com/Arduino-Controlled-Robotic-Biped/ and combined with the kinematics library

#define l1 6.3      // Length (in cm) of leg from HIP_PITCH to KNEE_PITCH
#define l2 5        // Length (in cm) of leg from KNEE_PITCH to ANKLE_PITCH
#define stepClearance 1
#define stepHeight 10.7

void setupKinematics()
{
    Kinematics kinL(l1, l2);
    Position pos;
    Angle ang;
    kinL.getPositions();
    kinL.getAngles();
    if (DEBUG)
    {
        kinL.printPositions();
        kinL.printAngles();
    }
    //kinL.moveToPosition(0, 0, 10);
    //updateLegsPos()
}


void BORROWED_calibrateServos()
{
    //#define stepClearance 1
    //#define stepHeight 10
    //#define hipLOffset 105
    //#define kneeLOffset 155
    //#define ankleLOffset 85
    //#define hipROffset 82
    //#define kneeROffset 25
    //#define ankleROffset 85
}


void standup()
{
    // PHASE 1
    // straighten roll in legs
    sMoveDEG(R_HIP_ROLL,  90, 0);
    sMoveDEG(R_ANKLE_ROLL,  90, 0);
    sMoveDEG(L_HIP_ROLL,  90, 0);
    sMoveDEG(L_ANKLE_ROLL,  90, 0);

    // straighten ankles ser.#22P1500#11P1500T1000
    sMoveDEG(R_ANKLE_PITCH,  90, 0);
    sMoveDEG(L_ANKLE_PITCH,  90, 0);

    // straighten knee ser.#23P1500#10P1500T1000
    sMoveDEG(R_KNEE_PITCH,  90, 0);
    sMoveDEG(L_KNEE_PITCH,  90, 0);

    // straighten hip ser.#24P1500#9P1500T1000
    sMoveDEG(R_HIP_PITCH,  90, 0);
    sMoveDEG(L_HIP_PITCH,  90, 0);

    // straighten right arm ser.#29P1500#30P1500#31P1500T1000
    sMoveDEG(R_ARM_ROLL,  90, 0);
    sMoveDEG(R_SHOULD_ROLL,  0, 0);
    sMoveDEG(R_SHOULD_PITCH,  90, 0);

    // straighten left arm ser.#2P1500#3P1500#4P1500T1000
    sMoveDEG(L_ARM_ROLL,  90, 0);
    sMoveDEG(L_SHOULD_ROLL,  180, 0);
    sMoveDEG(L_SHOULD_PITCH,  90, 2000);
}

void getup(int side)
{
    // PHASE 1
    // straighten roll in legs
    sMoveDEG(R_HIP_ROLL, (side * 0)  + 90, 0);
    sMoveDEG(R_ANKLE_ROLL, (side * 0)  + 90, 0);
    sMoveDEG(L_HIP_ROLL, (-side * 0)  + 90, 0);
    sMoveDEG(L_ANKLE_ROLL, (-side * 0)  + 90, 0);

    // straighten ankles ser.#22P1500#11P1500T1000
    sMoveDEG(R_ANKLE_PITCH, (side * 0)  + 90, 0);
    sMoveDEG(L_ANKLE_PITCH, (-side * 0)  + 90, 0);

    // straighten knee ser.#23P1500#10P1500T1000
    sMoveDEG(R_KNEE_PITCH, (side * 0)  + 90, 0);
    sMoveDEG(L_KNEE_PITCH, (-side * 0)  + 90, 0);

    // straighten hip ser.#24P1500#9P1500T1000
    sMoveDEG(R_HIP_PITCH, (side * 0)  + 90, 0);
    sMoveDEG(L_HIP_PITCH, (-side * 0)  + 90, 0);

    // straighten right arm ser.#29P1500#30P1500#31P1500T1000
    sMoveDEG(R_ARM_ROLL, (side * 0)  + 90, 0);
    sMoveDEG(R_SHOULD_ROLL, (side * 0)  + 90, 0);
    sMoveDEG(R_SHOULD_PITCH, (side * 0)  + 90, 0);

    // straighten left arm ser.#2P1500#3P1500#4P1500T1000
    sMoveDEG(L_ARM_ROLL, (-side * 0)  + 90, 0);
    sMoveDEG(L_SHOULD_ROLL, (-side * 0)  + 90, 0);
    sMoveDEG(L_SHOULD_PITCH, (-side * 0)  + 90, 3000);


    // PHASE 2


    // straighten right arm ser.#29P1500#30P1500#31P1500T1000
    sMoveDEG(R_ARM_ROLL, (-90)  + 90, 0);
    sMoveDEG(R_SHOULD_ROLL, (-60) + 90, 0);
    sMoveDEG(R_SHOULD_PITCH, (side * -90)  + 90, 0);

    // straighten left arm ser.#2P1500#3P1500#4P1500T1000
    sMoveDEG(L_ARM_ROLL, (90)  + 90, 0);
    sMoveDEG(L_SHOULD_ROLL, (60) + 90, 0);
    sMoveDEG(L_SHOULD_PITCH, (-side * -90)  + 90, 2000);

    
    // straighten ankles ser.#22P1500#11P1500T1000
    sMoveDEG(R_ANKLE_PITCH, (side * -45)  + 90, 0);
    sMoveDEG(L_ANKLE_PITCH, (-side * -45)  + 90, 0);

    // straighten knee ser.#23P1500#10P1500T1000
    sMoveDEG(R_KNEE_PITCH, (side * -90)  + 90, 0);
    sMoveDEG(L_KNEE_PITCH, (-side * -90)  + 90, 0);

    // straighten hip ser.#24P1500#9P1500T1000
    sMoveDEG(R_HIP_PITCH, (side * -90)  + 90, 0);
    sMoveDEG(L_HIP_PITCH, (-side * -90)  + 90, 1000);



    // PHASE 3
    // straighten ankles ser.#22P1500#11P1500T1000
    sMoveDEG(R_ANKLE_PITCH, (side * 90)  + 90, 0);
    sMoveDEG(L_ANKLE_PITCH, (-side * 90)  + 90, 0);

    // straighten knee ser.#23P1500#10P1500T1000
    sMoveDEG(R_KNEE_PITCH, (side * -90)  + 90, 0);
    sMoveDEG(L_KNEE_PITCH, (-side * -90)  + 90, 0);

    // straighten hip ser.#24P1500#9P1500T1000
    sMoveDEG(R_HIP_PITCH, (side * 90)  + 90, 0);
    sMoveDEG(L_HIP_PITCH, (-side * 90)  + 90, 0);

    // straighten right arm ser.#29P1500#30P1500#31P1500T1000
    sMoveDEG(R_ARM_ROLL, (side * 0)  + 90, 0);
    sMoveDEG(R_SHOULD_ROLL, (-90)  + 90, 0);
    sMoveDEG(R_SHOULD_PITCH, (side * -90)  + 90, 0);

    // straighten left arm ser.#2P1500#3P1500#4P1500T1000
    sMoveDEG(L_ARM_ROLL, (-side * 0)  + 90, 0);
    sMoveDEG(L_SHOULD_ROLL, (90) + 90, 0);
    sMoveDEG(L_SHOULD_PITCH, (-side * -90)  + 90, 2000);

    
    // PHASE 4
    // straighten ankles ser.#22P1500#11P1500T1000
    sMoveDEG(R_ANKLE_PITCH, (side * 55)  + 90, 0);
    sMoveDEG(L_ANKLE_PITCH, (-side * 55)  + 90, 0);

    // straighten knee ser.#23P1500#10P1500T1000
    sMoveDEG(R_KNEE_PITCH, (side * -55)  + 90, 0);
    sMoveDEG(L_KNEE_PITCH, (-side * -55)  + 90, 0);

    // straighten hip ser.#24P1500#9P1500T1000
    sMoveDEG(R_HIP_PITCH, (side * 5)  + 90, 0);
    sMoveDEG(L_HIP_PITCH, (-side * 5)  + 90, 2000);

    standup();
}

void BORROWED_updateServoPos(int target1, int target2, int target3, char leg)
{
    if (leg == 'l')
    {
        sMoveDEG(L_HIP_PITCH, 90 + target1, 0);        //hipL.write(hipLOffset - target1);
        sMoveDEG(L_KNEE_PITCH, 90 + target2, 0);      //kneeL.write(kneeLOffset - target2);
        sMoveDEG(L_ANKLE_PITCH, target3, 100);    //ankleL.write(2 * ankleLOffset - target3);
    }
    else if (leg == 'r')
    {
        sMoveDEG(R_HIP_PITCH, 90 - target1, 0);       //hipR.write(hipROffset + target1);
        sMoveDEG(R_KNEE_PITCH, 90 - target2, 0);       //kneeR.write(kneeROffset + target2);
        sMoveDEG(R_ANKLE_PITCH, 2 * 90 - target3, 0); //ankleR.write(target3);
    }
}

void BORROWED_pos(float x, float z, char leg)
{
    float hipRad2 = atan(x / z);
    float hipDeg2 = hipRad2 * (180 / PI);

    float z2 = z / cos(hipRad2);

    float hipRad1 = acos((sq(l1) + sq(z2) - sq(l2)) / (2 * l1 * z2));
    float hipDeg1 = hipRad1 * (180 / PI);

    float kneeRad = PI - acos((sq(l1) + sq(l2) - sq(z2)) / (2 * l1 * l2));

    float ankleRad = PI / 2 + hipRad2 - acos((sq(l2) + sq(z2) - sq(l1)) / (2 * l2 * z2));

    float hipDeg = hipDeg1 + hipDeg2;
    float kneeDeg = kneeRad * (180 / PI);
    float ankleDeg = ankleRad * (180 / PI);

    //Serial.print(hipDeg);
    //Serial.print("\t");
    //Serial.print(kneeDeg);
    //Serial.print("\t");
    //Serial.println(ankleDeg);

    BORROWED_updateServoPos(hipDeg, kneeDeg, ankleDeg, leg);
}

void BORROWED_takeStep(float stepLength, int stepVelocity)
{
    sMoveDEG(R_HIP_ROLL, 90 + 7, 0);
    sMoveDEG(R_ANKLE_ROLL, 90 + 7, 0);
    sMoveDEG(L_HIP_ROLL, 90 + 10, 0);
    sMoveDEG(L_ANKLE_ROLL, 90 + 7, 500);
    for (float i = stepLength; i >= -stepLength; i -= 1)
    {
        BORROWED_pos(i, stepHeight, 'r');
        BORROWED_pos(-i, stepHeight - stepClearance, 'l');
        //sDelay(stepVelocity);
    }
    sMoveDEG(R_HIP_ROLL, 90 - 7, 0);
    sMoveDEG(R_ANKLE_ROLL, 90 - 7, 0);
    sMoveDEG(L_HIP_ROLL, 90 - 7, 0);
    sMoveDEG(L_ANKLE_ROLL, 90 - 10, 500);
    for (float i = stepLength; i >= -stepLength; i -= 1)
    {
        BORROWED_pos(-i, stepHeight - stepClearance, 'r');
        BORROWED_pos(i, stepHeight, 'l');
        //sDelay(stepVelocity);
    }
}

void BORROWED_initialize()
{
    for (float i = (l1 + l2); i >= stepHeight; i -= 0.1)
    {
        BORROWED_pos(0, i, 'r');
        BORROWED_pos(0, i, 'l');
        //sDelay(100);
    }
}
