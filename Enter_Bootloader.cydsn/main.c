#include <project.h>

CY_ISR_PROTO(bootSwitchISR);
CY_ISR_PROTO(bootSwitchTimerISR);

int main()
{
    BootSwitchISR_StartEx(bootSwitchISR);
    BootSwitchTimerISR_StartEx(bootSwitchTimerISR);
    
    CyGlobalIntEnable;
    
    for(;;)
    {
    }
}

CY_ISR(bootSwitchISR)
{
    BootSwitch_ClearInterrupt();
    
    if (!BootSwitch_Read())
    {
        BootSwitchTimer_WriteCounter(0);
        BootSwitchTimer_Start();
    }
    else
    {
        BootSwitchTimer_Stop();
    }
}

CY_ISR(bootSwitchTimerISR)
{
    BootSwitchTimer_ClearInterrupt(BootSwitchTimer__INTR_MASK_TC);
    
    Bootloadable_Load();
}