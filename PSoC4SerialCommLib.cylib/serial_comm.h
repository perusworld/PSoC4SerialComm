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
    
    void SerialMilliSecondsTimerPing();
    unsigned long SerialReadChar();
    void SerialWriteChar(unsigned long ch);
    void SerialWriteString(const char str[]);

    void SerialSecondsTimerPing();
    void SerialInit(ON_MSG onMessage);
    void SerialPingOut();
    void SerialPingIn();
    void SerialDataBegin();
    void SerialDataEnd();
    void SerialSendBytes(unsigned long* data, unsigned long len);
    void SerialSendString(const char data[]);
    void SerialReadIncoming();

#endif /* serial_comm_H */
