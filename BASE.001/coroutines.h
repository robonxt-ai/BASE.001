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
    [2022.01.03] serialRead > Coroutine for reading serial data, V2
    ------------------------------------------------------------------------------------------------------  */
COROUTINE(serialRead)
{
    COROUTINE_LOOP()
    {
        if (ssSerialReader.read())
        {
            ssSerialReader.toLowerCase();
            if (ssSerialReader == "ok")
            {
                handleOkCmd();
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////// -------------------- STOP ALL SERVO -------------------- //////////////////////
            else if (ssSerialReader == "stop" || ssSerialReader == "kill")
            {
                handleKILLCmd();
            }
            else if (ssSerialReader == "restart")
            {
                handleRESTARTCmd();
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////
            else    // If none of the ifs above were true
            {
                ssSerialOutput << "Not Recognized: " << ssSerialReader << endl;
            }
            ssSerialOutput << endl;
            COROUTINE_DELAY(5);
        }
        COROUTINE_DELAY(5);
    }
}

/*  ------------------------------------------------------------------------------------------------------
    [2022.01.08] servoSend > Coroutine for moving servos
    ------------------------------------------------------------------------------------------------------  */
COROUTINE(servoSend)
{
    COROUTINE_LOOP()
    {
        if (!rIsError)
        {
            // Do stuff here
            /*
                if (something queue has stuff)
                {
                    //we parse it and send to servos. Also let the brain know!
                    ssServoOutput << "#11P1000T200" << endl;
                    ssSerialOutput << "#11P1000T200" << endl;
                    COROUTINE_DELAY(2000);
                    ssServoOutput << "#11P1500T200" << endl;
                    ssSerialOutput << "#11P1000T200" << endl;
                    COROUTINE_DELAY(2000);
                }
            */

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
