//////////////////////////////////////////////////////////////////////////////////////////////////////
void handleSendCmd(SafeString& strIn)
{
    ssSerialOutput << "sending " << ssSerialReader << " to board" << endl;
    ssServoOutput << ssSerialReader << endl;
}
void handleOkCmd()
{
    ssSerialOutput << "---------- ROBOT STATUS SET TO OK ----------" << endl;
    rIsError = false;
}
void handleKILLCmd()
{
    ssSerialOutput << "---------- KILL SWITCH ACTIVATED ----------" << endl;
    ssServoOutput << "#STOP" << endl;
    rIsError = true;
}
void handleRESTARTCmd()
{
    ssSerialOutput << "---------- SYSTEM RESTARTING NOW ----------" << endl;
    delay(100);
    ESP.restart();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////



//void k()
//{
//
//    // Stuff here
//
//    else if (strcmp(receivedChars, "box") == 0)           // Sets robot status to ok
//    {
//        //move_BOX();
//    }
//    else if (strcmp(receivedChars, "r") == 0)           // Sets robot status to ok
//    {
//        //rReset(5000);
//    }
//    else if (strcmp(receivedChars, "ready") == 0)           // Sets robot status to ok
//    {
//        //readyToWalk();
//    }
//    else if (strcmp(receivedChars, "w") == 0)           // Sets robot status to ok
//    {
//        //walkingV8(2, 1);
//    }
//    else if (strcmp(receivedChars, "w2") == 0)           // Sets robot status to ok
//    {
//        //walkingV9(2, 1);
//    }
//    else if (strcmp(receivedChars, "gS") == 0)           // Sets robot status to ok
//    {
//        //getupSUPINE();
//    }
//
//    else if (strcmp(receivedChars, "selfright") == 0)           // Sets robot status to ok
//    {
//        //isSelfRight = !isSelfRight;
//        //ssSerialOutput << "isSelfRight is now: " << isSelfRight << endl;
//    }
//}
