// do we need a settings menu?
//////////////////////////////////////////////////////////////////////////////////////////////////////
void handleINFOCmd()
{
    ssSerialOutput << "--------------------------------------------------" << endl;
    //ssSerialOutput << "----- DETAILS -----" << endl;
    ssSerialOutput << "PROJECT: " << PROJECT << endl;
    ssSerialOutput << "CREATOR: " << CREATOR << endl;
    ssSerialOutput << "VERSION: " << VERSION << endl;
    ssSerialOutput << "----- SETTINGS -----" << endl;
    ssSerialOutput << "SERVOC_BAUDRATE: " << SERVOC_BAUDRATE << endl;
    ssSerialOutput << "SERIAL_BAUDRATE: " << SERIAL_BAUDRATE << endl;
    ssSerialOutput << "rIsError: " << rIsError << endl;
    ssSerialOutput << "rIsStand: " << rIsStand << endl;
    ssSerialOutput << "isECHO: " << isECHO << endl;
    ssSerialOutput << "--------------------------------------------------" << endl;
}
void handleSendCmd(SafeString& strIn)
{
    ssSerialOutput << "send: " << ssSerialReader << endl;
    //qServoData.enqueue();
    ssServoOutput << ssSerialReader << endl;
}
void handleFORCECmd(SafeString& strIn)
{
    ssSerialOutput << "force: " << ssSerialReader << endl;
    
    ssServoOutput << ssSerialReader << endl;
}
void handleOkCmd()
{
    ssSerialOutput << "---------- ROBOT STATUS SET TO OK ----------" << endl;
    ssServoOutput << "#OK" << endl;
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
