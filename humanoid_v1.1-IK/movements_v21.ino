/*
    Movement collection for SainSmart Humanoid Robot Kit
    ------
    Goals:
    06/28/2020: last working version: movement_v2.ino
    06/28/2020: updated for humanoid_v1.1-IK
    09/17/2020: added squatv1
    09/17/2020: NOTES: NEED TO MAKE 3D MAP OF WHERE ALL LIMBS ARE, MAYBE USE MATHLAB?
    09/19/2020: ???

    ------
    A (start from small)™ program based off what dad taught me
    ------
    modified Sep 17 2020
    by robonxt (with dad)
*/

int leanForward = 100;

//////////////////////////////////////////////////////////////////////////////
////////////////////// Ready (Normal + Lift)
void leftLegReady()
{
    //Left foot forward
    sWalk(L_HIP_PITCH, 0, 0);
    sWalk(L_KNEE_PITCH, 0, 0);
    sWalk(L_ANKLE_PITCH, -0 - (leanForward / 2), 0);

}
void rightLegReady()
{
    sWalk(R_ANKLE_PITCH, 0 + (leanForward / 2), 0);
    sWalk(R_KNEE_PITCH, 0, 0);
    sWalk(R_HIP_PITCH, 0, 0);
}

void leftLegReadyLift()
{
    //Left foot forward
    sWalk(L_HIP_PITCH, 400, 0);
    sWalk(L_KNEE_PITCH,   800, 0);
    sWalk(L_ANKLE_PITCH, -400 - (leanForward / 2), 0);

}
void rightLegReadyLift()
{
    sWalk(R_ANKLE_PITCH, 400 + (leanForward / 2), 0);
    sWalk(R_KNEE_PITCH, -800, 0);
    sWalk(R_HIP_PITCH, -400, 0);
}


void leftLegReadyLiftHigher()
{
    //Left foot forward
    sWalk(L_HIP_PITCH, 500, 0);
    sWalk(L_KNEE_PITCH,   1000, 0);
    sWalk(L_ANKLE_PITCH, -500 - (leanForward / 2), 0);

}
void rightLegReadyLiftHigher()
{
    sWalk(R_ANKLE_PITCH, 500 + (leanForward / 2), 0);
    sWalk(R_KNEE_PITCH, -1000, 0);
    sWalk(R_HIP_PITCH, -500, 0);
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Forward (Normal + Lift)
void leftLegFwd()
{
    //Left foot forward
    sWalk(L_HIP_PITCH, 500, 0);
    sWalk(L_KNEE_PITCH,   600, 0);
    sWalk(L_ANKLE_PITCH, -100 - (leanForward / 2), 0);

}
void rightLegFwd()
{
    sWalk(R_ANKLE_PITCH, 100 + (leanForward / 2), 0);
    sWalk(R_KNEE_PITCH, -600, 0);
    sWalk(R_HIP_PITCH, -500, 0);
}

void leftLegFwdLift()
{
    sWalk(L_HIP_PITCH, 600, 0);
    sWalk(L_KNEE_PITCH,  800, 0);
    sWalk(L_ANKLE_PITCH, -200 - (leanForward / 2), 0);

}
void rightLegFwdLift()
{
    sWalk(R_ANKLE_PITCH, 200 + (leanForward / 2), 0);
    sWalk(R_KNEE_PITCH, -800, 0);
    sWalk(R_HIP_PITCH, -600, 0);
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Backward (Normal + Lift)
void leftLegBack()
{
    sWalk(L_HIP_PITCH, 50, 0);
    sWalk(L_KNEE_PITCH,  500, 0);
    sWalk(L_ANKLE_PITCH, -450 - (leanForward / 2), 0);

}
void rightLegBack()
{
    sWalk(R_ANKLE_PITCH, 450 + (leanForward / 2), 0);
    sWalk(R_KNEE_PITCH, -500, 0);
    sWalk(R_HIP_PITCH, -50, 0);
}

void leftLegBackLift()
{
    sWalk(L_HIP_PITCH, 250, 0);
    sWalk(L_KNEE_PITCH,   900, 0);
    sWalk(L_ANKLE_PITCH, -650 - (leanForward / 2), 0);

}
void rightLegBackLift()
{
    sWalk(R_ANKLE_PITCH, 650 + (leanForward / 2), 0);
    sWalk(R_KNEE_PITCH, -900, 0);
    sWalk(R_HIP_PITCH, -250, 0);
}
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Lean (Ready + Left + Right)
void leftSideReady()
{
    sWalk(L_HIP_ROLL, 0, 0);
    sWalk(L_ANKLE_ROLL, 0, 0);
}
void rightSideReady()
{
    sWalk(R_HIP_ROLL, 0, 0);
    sWalk(R_ANKLE_ROLL, 0, 0);
}

void leftSideLeanRight()
{
    //    sWalk(L_HIP_ROLL, 80, 0);
    //    sWalk(L_ANKLE_ROLL, 85, 0);
    sWalk(L_HIP_ROLL, 80, 0);
    sWalk(L_ANKLE_ROLL, 80, 0);
}
void rightSideLeanRight()
{
    //    sWalk(R_ANKLE_ROLL, 110, 0);
    //    sWalk(R_HIP_ROLL, 80, 0);
    sWalk(R_ANKLE_ROLL, 80, 0);
    sWalk(R_HIP_ROLL, 80, 0);
}

void leftSideLeanLeft()
{
    //    sWalk(L_ANKLE_ROLL, -110, 0);
    //    sWalk(L_HIP_ROLL, -80, 0);
    sWalk(L_ANKLE_ROLL, -80, 0);
    sWalk(L_HIP_ROLL, -80, 0);
}
void rightSideLeanLeft()
{
    //    sWalk(R_HIP_ROLL, -80, 0);
    //    sWalk(R_ANKLE_ROLL, -85, 0);
    sWalk(R_HIP_ROLL, -80, 0);
    sWalk(R_ANKLE_ROLL, -80, 0);
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
////////////////////// Balance (Left + Right)
void leftSideBalanceLeft()
{
    sWalk(L_ANKLE_ROLL, -125, 0);
    sWalk(L_HIP_ROLL, -80, 0);

}
void rightSideBalanceRight()
{
    sWalk(R_HIP_ROLL, 80, 0);
    sWalk(R_ANKLE_ROLL, 125, 0);

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

void squatV1()
{
    leftLegReadyLiftHigher();
    rightLegReadyLiftHigher();
}

/*  ------------------------------------------------------------------------------------------------------
    [6/10/2020] ??? > ???
    ------------------------------------------------------------------------------------------------------*/
void walkingV7(int steps, float walkSpeed)
{
    // Get ready
    readyToWalk();
    for (int i = 0; i < steps; i++)
    {
        //  leanForward = 40;
        ///////////////////////////////////////////////////
        /////////// Left step whole
        // Left leg up
        leanRight();
        sDelay(walkSpeed * 650);
        leftLegReadyLift();
        balanceRight();
        sDelay(walkSpeed * 200);

        leftLegFwd();
        leanRight();
        rightLegReadyLift();
        rightLegBack();
        sDelay(walkSpeed * MOVE_DEFAULT_TIME + 200);
        //vTaskDelay( 100 / portTICK_PERIOD_MS );
        ///////////////////////////////////////////////////


        ///////////////////////////////////////////////////
        /////////// Right step whole
        // Right leg up
        leanLeft();
        sDelay(walkSpeed * 650);
        rightLegReadyLift();
        balanceLeft();
        sDelay(walkSpeed * 200);

        rightLegFwd();
        leanLeft();
        leftLegReadyLift();
        leftLegBack();
        sDelay(walkSpeed * MOVE_DEFAULT_TIME + 200);
        //vTaskDelay( 100 / portTICK_PERIOD_MS );
        ///////////////////////////////////////////////////
    }
    ///////////////////////////////////////////////////
    /////////// To end on left step
    balanceRight();
    sDelay(walkSpeed * MOVE_DEFAULT_TIME);
    rightLegReady();
    leftLegReadyLift();
    leftLegReady();
    sDelay(walkSpeed * MOVE_DEFAULT_TIME);
    readyToWalk();
}


/*  ------------------------------------------------------------------------------------------------------
    [9/19/2020] ??? > works well on ready pos, doesn't work when squatting. should change after IK upgrade
    ------------------------------------------------------------------------------------------------------*/
void turnLeft(int turns)
{
    int kickMovement = 250;
    int kickTimePower = 200;
    int beforeKickPos = sCheckLastPos(R_ANKLE_PITCH);

    for (int x = 0; x < turns; x++)
    {
        leanLeft();
        sDelay(kickTimePower);

        //Serial.print(sGetAbsMinPos(R_ANKLE_PITCH));
        //Serial.println(" WHAT IS THE MIN POS?");
        //Serial.print(beforeKickPos);
        //Serial.println(" IS BEFORE THE KICK");

        if ((beforeKickPos - kickMovement) <= sGetAbsMinPos(R_ANKLE_PITCH))
        {
            sSubmitAbsPos(R_ANKLE_PITCH, sGetAbsMinPos(R_ANKLE_PITCH), kickTimePower);
        }
        else
        {
            sMoveAbsMS(R_ANKLE_PITCH, beforeKickPos - kickMovement, kickTimePower);
        }
        //Serial.print(sCheckLastPos(R_ANKLE_PITCH));
        //Serial.println(" AFTER THE KICK");
        sMoveAbsMS(R_ANKLE_PITCH, beforeKickPos, 0);
        leanReady();
        sDelay(kickTimePower);
    }
}



/*  ------------------------------------------------------------------------------------------------------
    [9/19/2020] ??? > ???
    ------------------------------------------------------------------------------------------------------*/
void walkingV8(int steps, float walkSpeed)
{
    // Get ready
    readyToWalk();
    for (int i = 0; i < steps; i++)
    {
        //  leanForward = 40;
        ///////////////////////////////////////////////////
        /////////// Left step whole
        // Left leg up
        balanceRight();
        sDelay(walkSpeed * 600);
        leftLegReadyLift();
        //balanceRight();
        sDelay(walkSpeed * 600);

        leftLegFwd();
        leanRight();
        rightLegReadyLift();
        rightLegBack();
        sDelay(walkSpeed * 600);
        ///////////////////////////////////////////////////


        ///////////////////////////////////////////////////
        /////////// Right step whole
        // Right leg up
        balanceLeft();
        sDelay(walkSpeed * 600);
        rightLegReadyLift();
        //balanceLeft();
        sDelay(walkSpeed * 600);

        rightLegFwd();
        leanLeft();
        leftLegReadyLift();
        leftLegBack();
        sDelay(walkSpeed * 600);
        ///////////////////////////////////////////////////
    }
    ///////////////////////////////////////////////////
    /////////// To end on left step
    balanceRight();
    sDelay(walkSpeed * 400);
    rightLegReady();
    leftLegReadyLift();
    leftLegReady();
    sDelay(walkSpeed * 400);
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
