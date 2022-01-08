/*  ------------------------------------------------------------------------------------------------------
    [2021.08.27] heartbeat > Heartbeat coroutine
    ------------------------------------------------------------------------------------------------------  */
COROUTINE(heartbeat)
{
    COROUTINE_LOOP()
    {
        digitalWrite(LED_BUILTIN, LED_ON);
        digitalWrite(D0, LED_ON);
        COROUTINE_DELAY(hbIntervalON);
        digitalWrite(LED_BUILTIN, LED_OFF);
        digitalWrite(D0, LED_OFF);
        COROUTINE_DELAY(hbIntervalOFF);
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [2022.01.03] serialRead > Serial coroutine
    ------------------------------------------------------------------------------------------------------  */
COROUTINE(serialRead)
{
    COROUTINE_LOOP()
    {
        if (sfSerialReader.read())
        {
            sfSerialReader.toLowerCase();
            if (sfSerialReader == "start")
            {
                //handleStartCmd();
            }
            else if (sfSerialReader == "stop" || sfSerialReader == "kill")
            {
                handleStopCmd();
            } // else ignore unrecognized command
            else    // If none of the ifs above were true
            {
                Serial << "Not Recognized: " << sfSerialReader;
            }
            Serial << endl;
            COROUTINE_DELAY(1);
        } // else no delimited command yet
        COROUTINE_DELAY(1);
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [2022.01.02] serialReadConroutine > Coroutine for reading serial data
    ------------------------------------------------------------------------------------------------------  */
class serialReadConroutine: public Coroutine
{
    public:
        int runCoroutine() override
        {
            COROUTINE_LOOP()
            {
                COROUTINE_AWAIT(Serial.available() > 0);
                char c = Serial.read();
                if (c == '\n' || c == '\r')
                {
                    const char* receivedChars = lineBuffer.getLine();
                    Serial << "Received: " << receivedChars << endl;
                    if (strcmp(receivedChars, "ok") == 0)           // Sets robot status to ok
                    {
                        Serial << "---------- ROBOT STATUS FORCED OK ----------" << endl;
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////
                    // Stuff here


                    //////////////////////////////////////////////////////////////////////////////////////////////////////
                    else if (strncmp(receivedChars, "send.", 5 ) == 0 )  // Direct control of servos (EXAMPLE: "send.#21P1500T200")
                    {
                        const char *sub_command = &receivedChars[5];
                        SerialServo << sub_command << endl;
                        Serial << SerialServo << endl;
                    }
                    //////////////////////////////////////////////////////////////////////////////////////////////////////
                    ////////////////////// -------------------- STOP ALL SERVO -------------------- //////////////////////
                    else if ((strcmp(receivedChars, "STOP") == 0) || (strcmp(receivedChars, "stop") == 0) || (strcmp(receivedChars, "KILL") == 0) || (strcmp(receivedChars, "kill") == 0))  // KILL SWITCH
                    {
                        Serial << "---------- KILL SWITCH ACTIVATED ----------" << endl;
                        SerialServo << "#STOP" << endl;
                    }
                    ////////////////////// -------------------- STOP ALL SERVO -------------------- //////////////////////
                    //////////////////////////////////////////////////////////////////////////////////////////////////////
                    else    // If none of the ifs above were true
                    {
                        Serial << "Not Recognized" << endl;
                    }
                    Serial << "- done -" << endl;
                    lineBuffer.clear();
                }
                else
                {
                    lineBuffer.append(c);
                }
            }
        }
    private:
        LineBuffer lineBuffer;  // Creates the linebuffer object for processing the serial data
};
