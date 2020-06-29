/*
    Movement collection for SainSmart Humanoid Robot Kit
    ------
    Goals:
    06/28/2020: last working version: movement_v2.ino
    06/28/2020: updated for humanoid_v1.1-IK
    ------
    A (start from small)™ program based off what dad taught me
    ------
    modified Jun 28 2020
    by Steven Liao (with dad)
*/


//#define L_HIP_ROLL      8
//#define L_HIP_PITCH     9
//#define L_KNEE_PITCH    10
//#define L_ANKLE_PITCH   11
//#define L_ANKLE_ROLL    12
//
//#define R_ANKLE_ROLL    21
//#define R_ANKLE_PITCH   22
//#define R_KNEE_PITCH    23
//#define R_HIP_PITCH     24
//#define R_HIP_ROLL      25

int leanForward = 10;
int diffOfJoint = 0;

//experimental array sorting for future use.
int leanRightARR[][2] =
{
    L_HIP_ROLL,     70,
    L_ANKLE_ROLL,   80,
    R_ANKLE_ROLL,   125,
    R_HIP_ROLL,     80
};

int ll_readyARR[][2] =
{
    L_HIP_ROLL,     0,
    L_HIP_PITCH,    -350,
    L_KNEE_PITCH,   600,
    L_ANKLE_PITCH,  -350,
    L_ANKLE_ROLL,   0
};

//////////////////////////////////////////////////////////////////////////////
////////////////////// Ready (Normal + Lift)
void leftLegReady()
{
    //Left foot forward
    sMoveRelMS(L_HIP_PITCH, -300 - (leanForward / 2), 0);
    sMoveRelMS(L_KNEE_PITCH,   600, 0);
    sMoveRelMS(L_ANKLE_PITCH, -300 - (leanForward / 2), 0);

}
void rightLegReady()
{
    sMoveRelMS(R_ANKLE_PITCH, 300 + (leanForward / 2), 0);
    sMoveRelMS(R_KNEE_PITCH, -600, 0);
    sMoveRelMS(R_HIP_PITCH, 300 + (leanForward / 2), 0);
}

void leftLegReadyLift()
{
    //Left foot forward
    sMoveRelMS(L_HIP_PITCH, -400 - (leanForward / 2), 0);
    sMoveRelMS(L_KNEE_PITCH,   800, 0);
    sMoveRelMS(L_ANKLE_PITCH, -400 - (leanForward / 2), 0);

}
void rightLegReadyLift()
{
    sMoveRelMS(R_ANKLE_PITCH, 400 + (leanForward / 2), 0);
    sMoveRelMS(R_KNEE_PITCH, -800, 0);
    sMoveRelMS(R_HIP_PITCH, 400 + (leanForward / 2), 0);
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Forward (Normal + Lift)
void leftLegFwd()
{
    //Left foot forward
    sMoveRelMS(L_HIP_PITCH, -500 - (leanForward / 2), 0);
    sMoveRelMS(L_KNEE_PITCH,   600, 0);
    sMoveRelMS(L_ANKLE_PITCH, -100 - (leanForward / 2), 0);

}
void rightLegFwd()
{
    sMoveRelMS(R_ANKLE_PITCH, 100 + (leanForward / 2), 0);
    sMoveRelMS(R_KNEE_PITCH, -600, 0);
    sMoveRelMS(R_HIP_PITCH, 500 + (leanForward / 2), 0);
}

void leftLegFwdLift()
{
    sMoveRelMS(L_HIP_PITCH, -600 - (leanForward / 2), 0);
    sMoveRelMS(L_KNEE_PITCH,   800, 0);
    sMoveRelMS(L_ANKLE_PITCH, -200 - (leanForward / 2), 0);

}
void rightLegFwdLift()
{
    sMoveRelMS(R_ANKLE_PITCH, 200 + (leanForward / 2), 0);
    sMoveRelMS(R_KNEE_PITCH, -800, 0);
    sMoveRelMS(R_HIP_PITCH, 600 + (leanForward / 2), 0);
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Backward (Normal + Lift)
void leftLegBack()
{
    sMoveRelMS(L_HIP_PITCH, -50 - (leanForward / 2) + diffOfJoint, 0);
    sMoveRelMS(L_KNEE_PITCH,   500, 0);
    sMoveRelMS(L_ANKLE_PITCH, -450 - (leanForward / 2), 0);

}
void rightLegBack()
{
    sMoveRelMS(R_ANKLE_PITCH, 450 + (leanForward / 2), 0);
    sMoveRelMS(R_KNEE_PITCH, -500, 0);
    sMoveRelMS(R_HIP_PITCH, 50 + (leanForward / 2) - diffOfJoint, 0);
}

void leftLegBackLift()
{
    sMoveRelMS(L_HIP_PITCH, -250 - (leanForward / 2) + diffOfJoint, 0);
    sMoveRelMS(L_KNEE_PITCH,   900, 0);
    sMoveRelMS(L_ANKLE_PITCH, -650 - (leanForward / 2), 0);

}
void rightLegBackLift()
{
    sMoveRelMS(R_ANKLE_PITCH, 650 + (leanForward / 2), 0);
    sMoveRelMS(R_KNEE_PITCH, -900, 0);
    sMoveRelMS(R_HIP_PITCH, 250 + (leanForward / 2) - diffOfJoint, 0);
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Lean (Ready + Left + Right)
void leftSideReady()
{
    sMoveRelMS(L_HIP_ROLL, 0, 0);
    sMoveRelMS(L_ANKLE_ROLL,   0, 0);
}
void rightSideReady()
{
    sMoveRelMS(R_HIP_ROLL, 0, 0);
    sMoveRelMS(R_ANKLE_ROLL,   0, 0);
}

void leftSideLeanRight()
{
    //    sMoveRelMS(L_HIP_ROLL, 80, 0);
    //    sMoveRelMS(L_ANKLE_ROLL, 85, 0);
    sMoveRelMS(L_HIP_ROLL, 80, 0);
    sMoveRelMS(L_ANKLE_ROLL, 80, 0);
}
void rightSideLeanRight()
{
    //    sMoveRelMS(R_ANKLE_ROLL, 110, 0);
    //    sMoveRelMS(R_HIP_ROLL, 80, 0);
    sMoveRelMS(R_ANKLE_ROLL, 80, 0);
    sMoveRelMS(R_HIP_ROLL, 80, 0);
}

void leftSideLeanLeft()
{
    //    sMoveRelMS(L_ANKLE_ROLL, -110, 0);
    //    sMoveRelMS(L_HIP_ROLL, -80, 0);
    sMoveRelMS(L_ANKLE_ROLL, -80, 0);
    sMoveRelMS(L_HIP_ROLL, -80, 0);
}
void rightSideLeanLeft()
{
    //    sMoveRelMS(R_HIP_ROLL, -80, 0);
    //    sMoveRelMS(R_ANKLE_ROLL, -85, 0);
    sMoveRelMS(R_HIP_ROLL, -80, 0);
    sMoveRelMS(R_ANKLE_ROLL, -80, 0);
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Balance (Left + Right)
void leftSideBalanceLeft()
{
    sMoveRelMS(L_ANKLE_ROLL, -125, 0);
    sMoveRelMS(L_HIP_ROLL, -75, 0);

}
void rightSideBalanceRight()
{
    sMoveRelMS(R_HIP_ROLL, 75, 0);
    sMoveRelMS(R_ANKLE_ROLL, 125, 0);

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
        //vTaskDelay( 100 / portTICK_PERIOD_MS );
        ///////////////////////////////////////////////////


        ///////////////////////////////////////////////////
        /////////// Right step whole
        // Right leg up
        balanceLeft();
        sDelay(MOVE_DEFAULT_TIME);

        rightLegFwd();
        leftLegBack();
        sDelay(MOVE_DEFAULT_TIME + 200);
        //vTaskDelay( 100 / portTICK_PERIOD_MS );
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


/*  ------------------------------------------------------------------------------------------------------
    [6/10/2020] ??? > ???
    ------------------------------------------------------------------------------------------------------*/
void walkingV7(int steps)
{
    // Get ready
    readyToWalk();
    for (int i = 0; i < steps; i++)
    {
        ///////////////////////////////////////////////////
        /////////// Left step whole
        // Left leg up
        balanceRight();
        sDelay(650);
        leftLegReadyLift();
        balanceRight();
        sDelay(250);

        leftLegFwd();
        rightLegReadyLift();
        rightLegBack();
        sDelay(MOVE_DEFAULT_TIME + 200);
        //vTaskDelay( 100 / portTICK_PERIOD_MS );
        ///////////////////////////////////////////////////


        ///////////////////////////////////////////////////
        /////////// Right step whole
        // Right leg up
        balanceLeft();
        sDelay(650);
        rightLegReadyLift();
        balanceLeft();
        sDelay(250);
        rightLegFwd();
        leftLegBack();
        sDelay(MOVE_DEFAULT_TIME + 200);
        //vTaskDelay( 100 / portTICK_PERIOD_MS );
        ///////////////////////////////////////////////////
    }
    ///////////////////////////////////////////////////
    /////////// To end on left step
    balanceRight();
    rightLegReady();
    leftLegReadyLift();
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
