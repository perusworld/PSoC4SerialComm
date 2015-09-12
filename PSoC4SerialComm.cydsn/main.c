/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

#include <serial_comm.h>

CY_ISR(MS_ISR_CALLBACK) 
{
    MilliSecondsTimerPing();
}

void OnMessage(uint32* data, uint32 len) {
//    uint32 buf[2];
//    buf[0] = data[0];
//    buf[1] = len;
//    SerialSend(buf, 2);
    SerialDataBegin();
    SerialSendString("got your message data");
    SerialSendBytes(data, len);
    SerialDataEnd();
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


int main()
{
    
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    MS_TIMER_Start();
    MS_ISR_StartEx(MS_ISR_CALLBACK);
    SERIAL_Start();
    SerialInit(OnMessage);
    
    for(;;)
    {
        SerialReadIncoming();
    }
}

/* [] END OF FILE */
