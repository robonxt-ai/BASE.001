void handleStopCmd()
{
    Serial << "---------- KILL SWITCH ACTIVATED ----------" << endl;
    SerialServo << "#STOP" << endl;
}
