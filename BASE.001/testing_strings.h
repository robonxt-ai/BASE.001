//    2022.01.25: process:    when sending data (string) from serial: hold it in buffer until ends with Time; process string to store servo positions.
//                            when sending data (int) from brain: convert to string; hold in buffer until ends with Time; process string to store servo positions.
//                            so we need: int > string (easy); string > int (hard); string > buffer (???)

// for testing
#define MAX_SERVO_ALLOWED 33        // Remember that code starts from 0 , but only have servos 1-32
#define SERVO_MIN_DURATION 100      // Minimum time that servos can delay (last checked was 100ms)


// string2intFULL:  converts a string (example: #2P2500#3P1500#8P1550#9P1200T3460) into three arrays of ints: q, p, t.
//              it does not change the original SafeString, but it does erase and add in the three arrays.
int string2intFULL(SafeString& inputLine, int s[], int p[], int t[])
{
    createSafeString(field, 6); // for the field strings. Should have capacity > largest field length
    const char delimiters[] = "#PT"; // List of delimiters
    int nextIdx = 0; // index into inputLine, getting tokens start from front of inputLine
    size_t fieldNumber = 0; // no fields yet
    bool returnEmptyFields = false; // returns an empty field if there's no space between two delimiters

    ssSerialOutput << F("The input is ") << inputLine << endl;
    int sindex = 0;
    int pindex = 0;
    int tindex = 0;

    nextIdx = 0; // reset this, so we getting tokens start from front of inputLine

    while (nextIdx >= 0)   // still finding tokens
    {
        nextIdx = inputLine.stoken(field, nextIdx, delimiters, returnEmptyFields); // steps over previous delimiter // returns -1 if none found
        field.debug(F("   inputLine.stoken => "));
        fieldNumber++;
        int data;
        if (field.toInt(data))
        {
            ssSerialOutput << F("Field ") << fieldNumber << F(": ") << data << endl;
            if ((fieldNumber % 2 == 1) && data <= MAX_SERVO_ALLOWED)    // if odd (1,3,5)
            {
                s[sindex] = data;
                sindex++;
            }
            else // if even (2,4,6)
            {
                p[pindex] = data;
                pindex++;
            }

        }
        else
        {
            SafeString::Output.print(F("   ,")); SafeString::Output.print(field); SafeString::Output.println(F(", is not a number"));
        }
    }
    ssSerialOutput << F("Total fields: ") << fieldNumber << F("in: ") << inputLine << endl;
    if ((fieldNumber % 2) == 1) //after everything was calculated, check if fieldNumber is even or odd
    {
        // if odd, we have a time field

        t[tindex] = s[sindex];
        s[sindex] = -1;
        return 0;
    }
    else
    {
        // if even, we don't have a time field
        t[tindex] = 0;
        return -1;
    }
}

// string2int:  converts a single servo data string (example: #2P2500T3460) into ints: q, p, t.
//              it does not change the original SafeString, but changes the ints.
//              returns 0 if ok, -1 if error, 1 if has time
int string2int(SafeString& inputLine, int &s, int &p, int &t)
{
    createSafeString(field, 10); // for the field strings. Should have capacity > largest field length
    int nextIdx = 0; // index into inputLine, getting tokens start from front of inputLine
    bool returnEmptyFields = false; // returns an empty field if there's no space between two delimiters
    ssSerialOutput << F("The input is ") << inputLine << endl;
    int data = 0;
    int stat = 0;
    int fieldNumber = 0;
    // find #
    while (nextIdx >= 0)   // still finding tokens
    {
        nextIdx = inputLine.stoken(field, nextIdx, "#PT", returnEmptyFields); // steps over previous delimiter // returns -1 if none found
        fieldNumber++;
        field.debug(F("   inputLine.stoken => "));
        if (field.toInt(data))  // make sure it's a number value
        {
            if (fieldNumber == 1)
            {
                s = data;
                stat = 0;
            }
            else if (fieldNumber == 2)
            {
                p = data;
                stat = 0;
            }
            else if (fieldNumber == 3)
            {
                t = data;
                stat = 1;
            }
        }
        else
        {
            SafeString::Output << "error: in fieldNumber " << fieldNumber << ", " << field << " is not a number" << endl;
            stat = -1;
        }
    }
    return stat;
}


// pass 0 for ok, 1 if t > SERVO_MIN_DURATION
int int2string(SafeString& inputLine, int s, int p, int t)
{
    if (t < SERVO_MIN_DURATION)
    {
        //sprintf (data, "#%dP%d", ser, pos);     // Don't change this to <<! we need to keep it as one string so we can safely pass it to the SSC32
        inputLine.concat("#").concat(s).concat("P").concat(p);
        return 0;
    }
    else
    {
        //sprintf (data, "#%dP%dT%d", ser, pos, dur);     // Don't change this to <<! we need to keep it as one string so we can safely pass it to the SSC32
        inputLine.concat("#").concat(s).concat("P").concat(p).concat("T").concat(t);
        return 1;
    }
}


void test()
{
    int qS, qP, qT;
    char* huhuhuhuh = qServoData.getHead();
    createSafeStringFromCharPtr(data, huhuhuhuh);

    string2int(data, qS, qP, qT);

    //we parse it and send to servos. Also let the brain know!
    //process data with qServoData.front() and put them into three ints: qS, qP, and qT

    ssSerialOutput << "sending " << data;
}
