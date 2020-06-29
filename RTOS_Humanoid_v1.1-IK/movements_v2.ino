/*
    Servo Controller for SainSmart Humanoid Robot Kit
    ------
    Goals:
    06/28/2020: last working version: movement_v2.ino
    06/28/2020: updated for humanoid_v1.1-IK
    ------
    A (start from small)™ program based off what dad taught me
    ------
    modified Jun 26 2020
    by Steven Liao (with dad)
*/


//experimental array sorting for future use.
int leanRightARR[][2] =
{
    L_LEG_PELVIS, 70,
    L_LEG_FOOT, 80,
    R_LEG_FOOT, 125,
    R_LEG_PELVIS, 80
};

int ll_readyARR[][2] =
{
    L_LEG_PELVIS, 0,
    L_LEG_THIGH, -350,
    L_LEG_KNEE, 600,
    L_LEG_ANKLE, -350,
    L_LEG_FOOT, 0
};

//////////////////////////////////////////////////////////////////////////////
////////////////////// Ready (Normal + Lift)
void leftLegReady()
{
    //Left foot forward
    sMoveRelToDefault(L_LEG_THIGH, -300 - (leanForward / 2), 0);
    sMoveRelToDefault(L_LEG_KNEE,   600, 0);
    sMoveRelToDefault(L_LEG_ANKLE, -300 - (leanForward / 2), 0);

}
void rightLegReady()
{
    sMoveRelToDefault(R_LEG_ANKLE, 300 + (leanForward / 2), 0);
    sMoveRelToDefault(R_LEG_KNEE, -600, 0);
    sMoveRelToDefault(R_LEG_THIGH, 300 + (leanForward / 2), 0);
}

void leftLegReadyLift()
{
    //Left foot forward
    sMoveRelToDefault(L_LEG_THIGH, -400 - (leanForward / 2), 0);
    sMoveRelToDefault(L_LEG_KNEE,   800, 0);
    sMoveRelToDefault(L_LEG_ANKLE, -400 - (leanForward / 2), 0);

}
void rightLegReadyLift()
{
    sMoveRelToDefault(R_LEG_ANKLE, 400 + (leanForward / 2), 0);
    sMoveRelToDefault(R_LEG_KNEE, -800, 0);
    sMoveRelToDefault(R_LEG_THIGH, 400 + (leanForward / 2), 0);
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Forward (Normal + Lift)
void leftLegFwd()
{
    //Left foot forward
    sMoveRelToDefault(L_LEG_THIGH, -500 - (leanForward / 2), 0);
    sMoveRelToDefault(L_LEG_KNEE,   600, 0);
    sMoveRelToDefault(L_LEG_ANKLE, -100 - (leanForward / 2), 0);

}
void rightLegFwd()
{
    sMoveRelToDefault(R_LEG_ANKLE, 100 + (leanForward / 2), 0);
    sMoveRelToDefault(R_LEG_KNEE, -600, 0);
    sMoveRelToDefault(R_LEG_THIGH, 500 + (leanForward / 2), 0);
}

void leftLegFwdLift()
{
    sMoveRelToDefault(L_LEG_THIGH, -600 - (leanForward / 2), 0);
    sMoveRelToDefault(L_LEG_KNEE,   800, 0);
    sMoveRelToDefault(L_LEG_ANKLE, -200 - (leanForward / 2), 0);

}
void rightLegFwdLift()
{
    sMoveRelToDefault(R_LEG_ANKLE, 200 + (leanForward / 2), 0);
    sMoveRelToDefault(R_LEG_KNEE, -800, 0);
    sMoveRelToDefault(R_LEG_THIGH, 600 + (leanForward / 2), 0);
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Backward (Normal + Lift)
void leftLegBack()
{
    sMoveRelToDefault(L_LEG_THIGH, -50 - (leanForward / 2) + diffOfJoint, 0);
    sMoveRelToDefault(L_LEG_KNEE,   500, 0);
    sMoveRelToDefault(L_LEG_ANKLE, -450 - (leanForward / 2), 0);

}
void rightLegBack()
{
    sMoveRelToDefault(R_LEG_ANKLE, 450 + (leanForward / 2), 0);
    sMoveRelToDefault(R_LEG_KNEE, -500, 0);
    sMoveRelToDefault(R_LEG_THIGH, 50 + (leanForward / 2) - diffOfJoint, 0);
}

void leftLegBackLift()
{
    sMoveRelToDefault(L_LEG_THIGH, -250 - (leanForward / 2) + diffOfJoint, 0);
    sMoveRelToDefault(L_LEG_KNEE,   900, 0);
    sMoveRelToDefault(L_LEG_ANKLE, -650 - (leanForward / 2), 0);

}
void rightLegBackLift()
{
    sMoveRelToDefault(R_LEG_ANKLE, 650 + (leanForward / 2), 0);
    sMoveRelToDefault(R_LEG_KNEE, -900, 0);
    sMoveRelToDefault(R_LEG_THIGH, 250 + (leanForward / 2) - diffOfJoint, 0);
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Lean (Ready + Left + Right)
void leftSideReady()
{
    sMoveRelToDefault(L_LEG_PELVIS, 0, 0);
    sMoveRelToDefault(L_LEG_FOOT,   0, 0);
}
void rightSideReady()
{
    sMoveRelToDefault(R_LEG_PELVIS, 0, 0);
    sMoveRelToDefault(R_LEG_FOOT,   0, 0);
}

void leftSideLeanRight()
{
    //    sMoveRelToDefault(L_LEG_PELVIS, 80, 0);
    //    sMoveRelToDefault(L_LEG_FOOT, 85, 0);
    sMoveRelToDefault(L_LEG_PELVIS, 80, 0);
    sMoveRelToDefault(L_LEG_FOOT, 80, 0);
}
void rightSideLeanRight()
{
    //    sMoveRelToDefault(R_LEG_FOOT, 110, 0);
    //    sMoveRelToDefault(R_LEG_PELVIS, 80, 0);
    sMoveRelToDefault(R_LEG_FOOT, 80, 0);
    sMoveRelToDefault(R_LEG_PELVIS, 80, 0);
}

void leftSideLeanLeft()
{
    //    sMoveRelToDefault(L_LEG_FOOT, -110, 0);
    //    sMoveRelToDefault(L_LEG_PELVIS, -80, 0);
    sMoveRelToDefault(L_LEG_FOOT, -80, 0);
    sMoveRelToDefault(L_LEG_PELVIS, -80, 0);
}
void rightSideLeanLeft()
{
    //    sMoveRelToDefault(R_LEG_PELVIS, -80, 0);
    //    sMoveRelToDefault(R_LEG_FOOT, -85, 0);
    sMoveRelToDefault(R_LEG_PELVIS, -80, 0);
    sMoveRelToDefault(R_LEG_FOOT, -80, 0);
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Balance (Left + Right)
void leftSideBalanceLeft()
{
    sMoveRelToDefault(L_LEG_FOOT, -110, 0);
        sMoveRelToDefault(L_LEG_PELVIS, -80, 0);

}
void rightSideBalanceRight()
{
    sMoveRelToDefault(R_LEG_PELVIS, 80, 0);
    sMoveRelToDefault(R_LEG_FOOT, 110, 0);

}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Compiled
void readyToWalk()
{
    leftLegReady();
    rightLegReady();
    leftSideReady();
    rightSideReady();
    sDelay(MOVE_DEFAULT_TIME);
}

void leanReady()
{
    leftSideReady();
    rightSideReady();
}

void leanLeft()
{
    leftSideLeanLeft();
    rightSideLeanLeft();
}

void leanRight()
{
    leftSideLeanRight();
    rightSideLeanRight();
}

void balanceLeft()
{
    leftSideBalanceLeft();
    rightSideLeanLeft();
}

void balanceRight()
{
    rightSideBalanceRight();
    leftSideLeanRight();
}

///*  ------------------------------------------------------------------------------------------------------
//    [4/??/2020] ??? > ???
//    ------------------------------------------------------------------------------------------------------*/
//void walkingV2(int howManyTimes)
//{
//
//    //sMoveRelToDefault(int servo, int pos, int timeToPos);
//    ////(Forward Hopping v1 (Works but slow. Needs fine tuning)  4/5/2020 23:13) MODDED for new servo pos
//    //#12P+100 #11P-350 #10P+600 #9P-350 #8P+100 #25P+125 #24P+350 #23P-600 #22P+350 #21P+100T300
//    //#11P-450 #10P+400 #9P-25T300
//    //#11P-450 #10P+850 #9P-550T400
//    //#12P-100 #11P-350 #10P+600 #9P-350 #8P-125 #25P-100 #24P+350 #23P-600 #22P+350 #21P-100T300
//    //#24P+25 #23P-400 #22P+450T300
//    //#24P+550 #23P-850 #22P+450T400
//
//    //Or this version (new)
//    //#12P+80#8P+70#25P+80#21P+110T500
//    //#9P-600#10P+750#11P-240#22P+550#23P-600#24P+150T500
//    //#12P-110#8P-80#25P-70#21P-80T500
//    //#9P-150#10P+600#11P-550#22P+240#23P-750#24P+600T500
//    readyToWalk();
//
//    for (int i = 0; i < howManyTimes; i++)
//    {
//        //Lean Right
//        leanRight();
//        sDelay(MOVE_DEFAULT_TIME);
//        //Left foot forward
//        leftLegForward();
//        sDelay(MOVE_DEFAULT_TIME);
//        //Lean left
//        leanLeft();
//        sDelay(MOVE_DEFAULT_TIME);
//        //Right foot forward
//        rightLegForward();
//        sDelay(MOVE_DEFAULT_TIME);
//    }
//    readyToWalk();
//}
//
//void walkingV3(int steps)
//{
//    readyToWalk();
//    for (int i = 0; i < steps; i++)
//    {
//        // Lean left
//        leanLeft();
//        sDelay(MOVE_DEFAULT_TIME);
//
//        // Right foot forward
//        rightLegForward();
//        sDelay(MOVE_DEFAULT_TIME);
//
//        // Get right side ready
//        rightLegReady();
//
//        //Lean right
//        leanRight();
//        sDelay(MOVE_DEFAULT_TIME);
//
//        //Left foot forward
//        leftLegForward();
//        sDelay(MOVE_DEFAULT_TIME);
//
//        // Get left side ready
//        leftLegReady();
//
//
//    }
//
//    readyToWalk();
//
//}
void walkingV4(int steps)
{
    readyToWalk();
    for (int i = 0; i < steps; i++)
    {
        ////////////////////////////
        // From starting position, take right step while moving back left leg before lowering right foot
        leanLeft();
        rightLegReadyLift();
        sDelay(MOVE_DEFAULT_TIME);
        rightLegFwdLift();
        sDelay(MOVE_DEFAULT_TIME);
        // We move both legs at once!
        leftLegBack();
        rightLegFwd();
        sDelay(300);
        leanReady();
        sDelay(MOVE_DEFAULT_TIME);
        ////////////////////////////

        // Bring left leg back to starting position
        leanRight();
    }
    sDelay(MOVE_DEFAULT_TIME);

    readyToWalk();
}

void walkingV5(int steps)
{
    // Get ready
    readyToWalk();

    ///////////////////////////////////////////////////
    /////////// Left step whole
    // Left leg up
    balanceRight();
    leftLegReadyLift();
    sDelay(MOVE_DEFAULT_TIME);

    // Left leg forward lift + right leg back
    leftLegFwdLift();
    rightLegBack();
    sDelay(MOVE_DEFAULT_TIME - 100);

    // Left leg forward down
    leftLegFwd();
    ///////////////////////////////////////////////////


    ///////////////////////////////////////////////////
    /////////// Right step whole
    // Right leg up
    balanceLeft();
    rightLegReadyLift();
    sDelay(MOVE_DEFAULT_TIME);

    // Right leg forward lift + right leg back
    rightLegFwdLift();
    leftLegBack();
    sDelay(MOVE_DEFAULT_TIME - 100);

    // Right leg forward down
    rightLegFwd();
    ///////////////////////////////////////////////////

    for (int i = 0; i < steps; i++)
    {

    }

}

/*  ------------------------------------------------------------------------------------------------------
    [6/10/2020] ??? > ???
    ------------------------------------------------------------------------------------------------------*/
void walkingV6(int steps)
{
    // Get ready
    readyToWalk();
    for (int i = 0; i < steps; i++)
    {
        ///////////////////////////////////////////////////
        /////////// Left step whole
        // Left leg up
        balanceRight();
        sDelay(MOVE_DEFAULT_TIME);

        leftLegFwd();
        rightLegBack();
        sDelay(MOVE_DEFAULT_TIME + 200);
        vTaskDelay( 100 / portTICK_PERIOD_MS );
        ///////////////////////////////////////////////////


        ///////////////////////////////////////////////////
        /////////// Right step whole
        // Right leg up
        balanceLeft();
        sDelay(MOVE_DEFAULT_TIME);

        rightLegFwd();
        leftLegBack();
        sDelay(MOVE_DEFAULT_TIME + 200);
        vTaskDelay( 100 / portTICK_PERIOD_MS );
        ///////////////////////////////////////////////////
    }
    ///////////////////////////////////////////////////
    /////////// To end on left step
    balanceRight();
    rightLegReady();
    sDelay(MOVE_DEFAULT_TIME);

    leftLegReady();
    sDelay(MOVE_DEFAULT_TIME);
    readyToWalk();
}


// leftLegReady();
// rightLegReady();
// leftLegReadyLift();
// rightLegReadyLift();
// leftLegFwd();
// rightLegFwd();

// leftLegFwdLift();
// rightLegFwdLift();

// leftLegBack();
// rightLegBack();

// leftLegBackLift();
// rightLegBackLift();

// leftSideReady();
// rightSideReady();

// leftSideLeanLeft();
// rightSideLeanLeft();

// leftSideLeanRight();
// rightSideLeanRight();

// leftSideBalanceLeft();
// rightSideBalanceRight();

// void balanceLeft();
// void balanceRight();


// readyToWalk();
// leanReady();
// leanLeft();
// leanRight();
