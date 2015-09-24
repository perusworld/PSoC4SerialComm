#if !defined(serial_comm_H)
    #define serial_comm_H
        
    #include "serial_options.h"

    #define COMM_MODE_BYTE
    //#define COMM_MODE_CHAR
    //#define COMM_MODE_JSON

    #define COMM_BUF_LEN        (256)
    #define COMM_PING_IN        (0XCC)
    #define COMM_PING_OUT       (0XDD)
    #define COMM_DATA           (0XEE)
    #define COMM_EOM_FIRST      (0XFE)
    #define COMM_EOM_SECOND     (0XFF)
    #define COMM_ZERO_BYTE      (0XFD)

    #ifdef COMM_MODE_BYTE
        typedef void (*ON_MSG)(unsigned long*, unsigned long);
        void SerialSend(unsigned long* data, unsigned long len);
    #endif

    #ifdef COMM_MODE_CHAR
        typedef void (*ON_MSG)(char*, uint8);
    #endif

    #ifdef COMM_MODE_JSON
        typedef void (*ON_MSG)(char*, uint8);
    #endif
    
    unsigned long SerialReadChar();
    void SerialWriteChar(unsigned long ch);
    void SerialWriteString(const char str[]);

    void SerialInit(ON_MSG onMessage);
    void SerialPingOut();
    void SerialPingIn();
    void SerialDataBegin();
    void SerialDataEnd();
    void SerialSendDataByte(unsigned long data);
    void SerialSendData(unsigned long* data, unsigned long len);
    void SerialSendBytes(unsigned long* data, unsigned long len);
    void SerialSendString(const char data[]);
    void SerialReadIncoming();

unsigned short ms_count = 0;
unsigned long in_sync = FALSE;
ON_MSG onMsgPtr;


void SerialSecondsTimerPing() 
{
    if (FALSE == in_sync) {
        SerialPingIn();
    }
}

void SerialMilliSecondsTimerPing() 
{
    ms_count++;
    if(ms_count == 1000) { // 1 second
        ms_count = 0;
        SerialSecondsTimerPing();
    }
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

void SerialSendDataByte(unsigned long data) 
{
    SerialDataBegin();
    SerialWriteChar(data);
    SerialDataEnd();
}

void SerialSendData(unsigned long* data, unsigned long len)
{
    SerialDataBegin();
    SerialSendBytes(data, len);
    SerialDataEnd();
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

void SerialInit(ON_MSG onMessage)
{
    onMsgPtr = onMessage;
}

#ifdef COMM_MODE_BYTE
    
    unsigned long buf[COMM_BUF_LEN];
    unsigned long buf_cmd = 0u;
    unsigned long buf_prev = 0u;
    unsigned long buf_curr = 0u;
    unsigned long buf_len = 0;
    unsigned long data[COMM_BUF_LEN];

    void SerialReadIncoming()
    {
        unsigned long ch;
        unsigned long index = 0;
        ch = SerialReadChar();
        
        if (0u != ch) 
        {
            if (COMM_ZERO_BYTE == ch) {
                ch = 0;
            }
            buf_prev = buf_curr;
            buf_curr = ch;
            buf[buf_len++] = ch;
            if (COMM_EOM_FIRST == buf_prev && COMM_EOM_SECOND == buf_curr) {
                if (NULL != onMsgPtr) {
                    if (COMM_PING_IN == buf[0]) {
                        SerialPingOut();
                    } else if (COMM_DATA == buf[0]) {
                        for(index=1;index < buf_len-2;index++) {
                            data[index-1] = buf[index];
                        }
                        onMsgPtr(data, buf_len - 3);
                    }
                }
                buf_len = 0;
            }
        }
    }

#endif 

#endif /* serial_comm_H */
