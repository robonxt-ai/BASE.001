/*  ------------------------------------------------------------------------------------------------------
    [2021.08.27] heartbeat > Heartbeat coroutine loop
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
    [2022.01.03] serialRead > Coroutine loop for reading serial data, V2
    ------------------------------------------------------------------------------------------------------  */
COROUTINE(serialRead)
{
    COROUTINE_LOOP()
    {
        if (ssSerialReader.read())
        {
            ssSerialReader.toUpperCase();   //change all inputs to caps
            if (ssSerialReader.startsWith("VERS") || ssSerialReader.startsWith("INFO"))
            {
                handleINFOCmd();
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            else if (ssSerialReader.startsWith('#'))
            {
                handleSendCmd(ssSerialReader);
                //updateServoPosition(convertSSToPosition(ssSerialReader)); // make this before queues!
            }
            else if (ssSerialReader == "OK")
            {
                handleOkCmd();
            }
            ////////////////////// -------------------- STOP ALL SERVO -------------------- //////////////////////
            else if (ssSerialReader == "STOP" || ssSerialReader == "KILL")
            {
                handleKILLCmd();
            }
            else if (ssSerialReader == "RESTART")
            {
                handleRESTARTCmd();
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            else    // If none of the ifs above were true
            {
                ssSerialOutput << "Not Recognized: " << ssSerialReader << endl;
            }
            //ssSerialOutput << endl;
            COROUTINE_DELAY(10);
        }
        COROUTINE_DELAY(10);
    }
}



//    2022.01.25: process:    when sending data (string) from serial: hold it in buffer until ends with Time; process string to store servo positions. 
//                            when sending data (int) from brain: convert to string; hold in buffer until ends with Time; process string to store servo positions.
//                            so we need: int > string (easy); string > int (hard); string > buffer (???)
//void process_servo_data(SafeString& inputLine, int* s, int* p, int* t)
//{
//    createSafeString(field, 6); // for the field strings. Should have capacity > largest field length
//    const char delimiters[] = "#PT"; // List of delimiters
//    int nextIdx = 0; // index into inputLine
//    size_t fieldNumber = 0;
//    bool returnEmptyFields = false; // ,, returns an empty field
//
//    //inputLine = F("#2P2500#3P1500#8P1550#9P1200");
//    ssSerialOutput << F("The input is ") << inputLine << endl;
//    nextIdx = 0; // getting tokens start from front of inputLine
//    fieldNumber = 0; // no fields yet
//    int index = 0;
//    int receiveList[][2];
//
//    while (nextIdx >= 0)   // still finding tokens
//    {
//        nextIdx = inputLine.stoken(field, nextIdx, delimiters, returnEmptyFields); // steps over previous delimiter // returns -1 if none found
//        field.debug(F("   inputLine.stoken => "));
//        fieldNumber++;
//        int data;
//        if (field.toInt(data))
//        {
//            ssSerialOutput << F("Field ") << fieldNumber << F(": ") << data << endl;
//            if (fieldNumber % 2 == 1)
//            {
//                receiveList[index][0] = data;
//                index++;
//            }
//            else
//            {
//                receiveList[index][1] = data;
//            }
//        }
//        else
//        {
//            SafeString::Output.print(F("   ,")); SafeString::Output.print(field); SafeString::Output.println(F(", is not a number"));
//        }
//    }
//    if ((fieldNumber % 2) == 1)
//    {
//        // means we have a time field
//        *t = receiveList[fieldNumber];
//    }
//    else
//    {
//        // means we don't have a time field
//        *t = 0;
//    }
//}



/*  ------------------------------------------------------------------------------------------------------
    [2022.01.19] servoRead > Coroutine loop for reading servo serial data (might do something with it later?)
    ------------------------------------------------------------------------------------------------------  */
COROUTINE(servoRead)
{
    COROUTINE_LOOP()
    {
        if (ssServoReader.read())
        {
            ssSerialOutput << "get: " << ssServoReader << endl;
            COROUTINE_DELAY(10);
        }
        COROUTINE_DELAY(10);
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [2022.01.08] servoSend > Coroutine loop for moving servos
    ------------------------------------------------------------------------------------------------------  */
COROUTINE(servoSend)
{

    COROUTINE_LOOP()
    {
        if (!rIsError)
        {
            // Do stuff here

//            if (qServoData.itemCount() > 0)
//            {
//                int qS = 0, qP = 0, qT = 0;
//                char* huhuhuhuh = qServoData.getHead();
//                createSafeStringFromCharPtr(data, huhuhuhuh);
//
//                process_servo_data(data, &qS, &qP, &qT);
//
//                //we parse it and send to servos. Also let the brain know!
//                //process data with qServoData.front() and put them into three ints: qS, qP, and qT
//
//                ssSerialOutput << "sending " << data;
//
//                ssServoOutput << data;
//                if (qT >= 0)
//                {
//                    ssServoOutput << endl;
//                }
//                qServoData.dequeue();
//                COROUTINE_DELAY(qT + 5);
//            }

            COROUTINE_DELAY(20);
        }
        // don't do stuff here
        COROUTINE_DELAY(20);
    }
}




///*  ------------------------------------------------------------------------------------------------------
//    [2021.09.04] servoMove > Coroutine for moving servos
//    ------------------------------------------------------------------------------------------------------  */
//COROUTINE(servoMove)
//{
//    COROUTINE_LOOP()
//    {
//        // Code stuff down here
//        if (rIsError == false)
//        {
//            if ((qS.isEmpty()) == false)
//            {
//                //bool is_there_duration = false;     // Since we didn't do anything yet
//
//                //char data[15];
//                const int ser = qS.dequeue();
//                const int pos = qP.dequeue();
//                const int dur = qD.dequeue();
//
//                // Update servo pos data
//                servosUpdatedPos[ser][SERVO_PRE_UPD_POS] = pos; // Update last pos of servo with new pos
//
//                // SEND DATA!
//                char data[16];
//                if (dur < SERVO_MIN_DURATION)
//                {
//                    sprintf (data, "#%dP%d", ser, pos);     // Don't change this to <<! we need to keep it as one string so we can safely pass it to the SSC32
//
//                    //Serial << data;
//                    SerialServo.print(data);
//                }
//                else
//                {
//                    sprintf (data, "#%dP%dT%d", ser, pos, dur);     // Don't change this to <<! we need to keep it as one string so we can safely pass it to the SSC32
//
//                    Serial << data << endl;
//                    SerialServo.println(data);
//
//                    Serial << "After command: qS=" << qS.itemCount() << " qP=" << qP.itemCount() << " qD=" << qD.itemCount() << endl;
//                    COROUTINE_DELAY(dur + 5);
//                }
//
//                //COROUTINE_DELAY(1);
//            }   // End of sending data
//
//            //COROUTINE_DELAY(1);
//        }   // End of error checking
//
//        COROUTINE_DELAY(1);
//    }// End of coroutine
//};
