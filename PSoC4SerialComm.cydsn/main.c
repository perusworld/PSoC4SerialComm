#include <project.h>

#include "serial_comm_options.h"

int main()
{
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    SerialCommInit();

    for(;;)
    {
        SerialReadIncoming();
    }
}

/* [] END OF FILE */
