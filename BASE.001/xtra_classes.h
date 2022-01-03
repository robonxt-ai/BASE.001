/*  ------------------------------------------------------------------------------------------------------
    [2021.06.16] LineBuffer > Class to process single character into a string
    ------------------------------------------------------------------------------------------------------  */
class LineBuffer
{
    public:
        void append(char c)
        {
            if (mPos >= kBufferSize - 1) return;
            mBuffer[mPos] = c;
            mPos++;
        }

        const char* getLine()
        {
            mBuffer[mPos] = '\0';
            mPos++;
            return mBuffer;
        }

        void clear()
        {
            mPos = 0;
        }

    private:
        static const byte kBufferSize = 50;
        char mBuffer[kBufferSize];
        byte mPos = 0;
};
