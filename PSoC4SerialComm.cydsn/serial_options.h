#if !defined(serial_options_H)
    #define serial_options_H

    #include <project.h>
    #include <serial_comm.h>

    CY_ISR(MS_ISR_CALLBACK) 
    {
        SerialMilliSecondsTimerPing();
    }
    
    void OnMessage(uint32* data, uint32 len) {
        SerialDataBegin();
        SerialSendString("got your message data");
        SerialSendBytes(data, len);
        SerialDataEnd();
    }

    void SerialCommInit()
    {
        MS_TIMER_Start();
        MS_ISR_StartEx(MS_ISR_CALLBACK);
        SERIAL_Start();
        SerialInit(OnMessage);
    }

    unsigned long SerialReadChar()
    {
        return SERIAL_UartGetChar();
    }

    void SerialWriteChar(unsigned long ch)
    {
        SERIAL_UartPutChar(ch);
    }

    void SerialWriteString(const char str[])
    {
        SERIAL_UartPutString(str);
    }

#endif /* serial_options_H */
