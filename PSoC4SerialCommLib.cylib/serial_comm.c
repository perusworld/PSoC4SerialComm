#include "serial_comm.h"

ON_MSG onMsgPtr;
unsigned long in_sync = FALSE;
unsigned short ms_count = 0;

#ifdef COMM_MODE_BYTE
    
    unsigned long buf[COMM_BUF_LEN];
    unsigned long buf_cmd = 0u;
    unsigned long buf_prev = 0u;
    unsigned long buf_curr = 0u;
    unsigned long buf_len = 0;

    void SerialReadIncoming()
    {
        unsigned long ch;
        ch = SerialReadChar();
        
        if (0u != ch) 
        {
            buf_prev = buf_curr;
            buf_curr = ch;
            buf[buf_len++] = ch;
            if (COMM_EOM_FIRST == buf_prev && COMM_EOM_SECOND == buf_curr) {
                if (NULL != onMsgPtr) {
                    if (COMM_PING_IN == buf[0]) {
                        SerialPingOut();
                    } else if (COMM_DATA == buf[0]) {
                        onMsgPtr(buf, buf_len);
                    }
                }
                buf_len = 0;
            }
        }
    }

    void SerialSend(unsigned long* data, unsigned long len) 
    {
        SerialDataBegin();
        SerialSendBytes(data, len);
        SerialDataEnd();
    }

#endif 

void MilliSecondsTimerPing() 
{
    ms_count++;
    if(ms_count == 1000) { // 1 second
        ms_count = 0;
        SecondsTimerPing();
    }
}

void SecondsTimerPing() 
{
    if (FALSE == in_sync) {
        SerialPingIn();
    }
}

void SerialInit(ON_MSG onMessage)
{
    onMsgPtr = onMessage;
}

void SerialDataBegin()
{
    SerialWriteChar(COMM_DATA);
}

void SerialDataEnd()
{
    SerialWriteChar(COMM_EOM_FIRST);
    SerialWriteChar(COMM_EOM_SECOND);
}

void SerialSendBytes(unsigned long* data, unsigned long len)
{
    if (0 < len) {
        unsigned long index;
        index = 0u;
        while(index < len)
        {
            SerialWriteChar(data[index]);
            index++;
        }
    }
}

void SerialSendString(const char data[])
{
    SerialWriteString(data);
}

void SerialPingOut() 
{
    in_sync = TRUE;
    SerialWriteChar(COMM_PING_OUT);
    SerialDataEnd();
}

void SerialPingIn()
{
    SerialWriteChar(COMM_PING_IN);
    SerialDataEnd();
}


