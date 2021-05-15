/*
    User command receiver code for BASE.001
    ------
    A (start from small)™ program
    ------
    Designed for version: humanoid_ESP_v2021.4.2.ino
    Last modified: 2021.04.26
    Programmer: robonxt
    ------
    Changelogs:
    2021.01.25: Initial commit.
    2021.04.26: Merging with reentrantcodetest2
*/

const byte maxDataLength = 30;          //Max length of string
char receivedChars[maxDataLength + 1];  //string (the +1 is for the null char)

/*  ------------------------------------------------------------------------------------------------------
    [2021.01.25] receiveSerial > Reading received data using Serial.read
    ------------------------------------------------------------------------------------------------------  */
uint8_t receiveSerial(char* buff, uint8_t sizevar)
{
    static uint8_t ctr = 0; // store the current position in the buff array
    uint8_t ch; // store the last character received
    if (Serial.available() > 0) // true when characters in serial input buffer
    {
        ch = Serial.read(); // store character from buffer in ch
        if (ctr < sizevar)   // if the ctr is less than your buffer yet
        {
            buff[ctr++] = ch; // add it to your buffer
        }
        if (ch == '\r') // if that character is a carriage return
        {
            buff[ctr - 1] = 0; // replace '\r' with '\0' (string termination)
            ctr = 0; // reset the pointer
            Debug.print(DBG_INFO, F("Command: %s"), buff); // Prints received command
            return 1;
        }
        else
        {
            return 0;
        }
    }   //end serial was available
    return 0;
}

/*  ------------------------------------------------------------------------------------------------------
    [2021.04.22] serialControl > List of commands that the robot will respond to
    ------------------------------------------------------------------------------------------------------  */
void serialControl()
{
    if (receiveSerial(receivedChars, sizeof(receivedChars)))
    {
        if (strcmp(receivedChars, "ok") == 0)
        {
            // Do stuff here
            rIsError = false;
            rIsBusy = false;
        }
        else if (strcmp(receivedChars, "box") == 0)
        {
            // Upper body
            sMoveDEG(R_ARM_ROLL, 90, 0);
            sMoveDEG(L_ARM_ROLL, 90, 0);
            sMoveDEG(R_SHOULD_ROLL, 0, 0);
            sMoveDEG(L_SHOULD_ROLL, 180, 0);
            sMoveDEG(R_SHOULD_PITCH, 90, 0);
            sMoveDEG(L_SHOULD_PITCH, 90, 1000);
            // Lower body
            sMoveDEG(R_ANKLE_PITCH, 180, 0);
            sMoveDEG(L_ANKLE_PITCH, 0, 0);
            sMoveDEG(R_KNEE_PITCH, 0, 0);
            sMoveDEG(L_KNEE_PITCH, 180, 0);
            sMoveDEG(R_HIP_PITCH, 180, 0);
            sMoveDEG(L_HIP_PITCH, 0, 0);
            sMoveDEG(R_HIP_ROLL, 90, 0);
            sMoveDEG(L_HIP_ROLL, 90, 0);
            sMoveDEG(R_ANKLE_ROLL, 90, 0);
            sMoveDEG(L_ANKLE_ROLL, 90, 2000);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strncmp(receivedChars, "ser.", 4 ) == 0 )  // Direct control of servos (EXAMPLE: "ser.#21P1500T200")
        {
            char *sub_command = &receivedChars[4];
            SerialServo.println(sub_command);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////// -------------------- STOP ALL SERVO -------------------- //////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        else if ((strcmp(receivedChars, "STOP") == 0) || (strcmp(receivedChars, "stop") == 0) || (strcmp(receivedChars, "KILL") == 0) || (strcmp(receivedChars, "kill") == 0))  // KILL SWITCH
        {
            Serial.println("---------- KILL SWITCH ACTIVATED ----------");
            rIsError = true;
            rIsBusy = true;
            SerialServo.println("#STOP");
        }
        else    // If none of the ifs above were true
        {
            Serial.print(F("Not Recognized: "));
            Serial.println(receivedChars);
        }
        Serial.println(F(" done"));
    }
}
