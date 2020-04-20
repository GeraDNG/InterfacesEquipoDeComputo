/******************************************************************************
* Project Name		: CY8CKIT_046_Deep_Sleep_Blinky
* Version			: 1.0
* Device Used		: CY8C4248BZI-L489     
* Software Used		: PSoC Creator 4.2
* Compiler Used		: ARM GCC 5.4.1
* Related Hardware	: CY8CKIT-046 PSoC 4 L-Series Pioneer Kit 
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* (“Software”), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software (“EULA”).
*
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress’s integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress 
* reserves the right to make changes to the Software without notice. Cypress 
* does not assume any liability arising out of the application or use of the 
* Software or any product or circuit described in the Software. Cypress does 
* not authorize its products for use in any products where a malfunction or 
* failure of the Cypress product may reasonably be expected to result in 
* significant property damage, injury or death (“High Risk Product”). By 
* including Cypress’s product in a High Risk Product, the manufacturer of such 
* system or application assumes all risk of such use and in doing so agrees to 
* indemnify Cypress against all liability.
*******************************************************************************/
/*******************************************************************************
* Theory of Operation: This project demonstrates DeepSleep power mode operation
* of PSoC 4200L device. The PSoC 4200L device is put to DeepSleep power mode 
* and wakes up every 1 second. The PSoC 4200L device wakes up from DeepSleep 
* power mode when the Watchdog Timer0 (WDT0) count reaches the match value. This 
* is configured in the "Clocks" tab of the file CY8CKIT_046_Deep_Sleep_Blinky.cydwr.
* The WDT0 is clocked using the Low Frequency Clock (LFCLK) which in turn is 
* sourced by ILO. The ILO can be inaccurate up to 60%. This project uses the 
* ILO Trim Component to trim the ILO to an accuracy (±10%) using IMO. 
*
* The project also has a pin Component which is connected to the green LED on 
* the PSoC 4 L-Series Pioneer Kit. The PSoC 4200L toggles the state of this pin
* each time the device wakes up from DeepSleep power mode. This blinks the 
* green LED at a frequency of 0.5Hz.
*
* Note: This project sets the "Debug Select" option in the System tab of 
* CY8CKIT_046_Deep_Sleep_Blinky.cydwr file as GPIO instead of SWD. This allows 
* the PSoC 4200L to save more power.
*******************************************************************************/

#include <project.h>

#define ZERO				(0x00)
#define DELAY_MS			(1000)
#define CLOCK_FOR_DELAY		(32*DELAY_MS)

/* 4 ILO periods expressed in microseconds. */
#define ILOX4 				((4 * 1000)/32)

int main()
{
	/* Variables used to trim ILO. */
	uint32 clocksComp = ZERO;
    uint32 currentCounterVal = ZERO;
	
	CyGlobalIntEnable;
	
	/* Start the ILO Trim Component. */
	ILO_Trim_Start();
		
    for(;;)
    {		
		/* Calculate the number of clock cycles required 
		 * to compensate for ILO error for a timer value of 1 second. */
		clocksComp = ILO_Trim_Compensate(CLOCK_FOR_DELAY);
		
		/* Update the Watchdog Timer with the compensated match value. */
        CySysWdtSetMatch(CY_SYS_WDT_COUNTER0, clocksComp - 1);
		
		/* Read the current count value of the WDT. */
        currentCounterVal = CySysWdtGetCount(CY_SYS_WDT_COUNTER0);
		
		/* Reset the counter if the count value is greater than
		 * the match value. */
        if (currentCounterVal > (clocksComp - 1))
        {
            CySysWdtResetCounters(CY_SYS_WDT_COUNTER0_RESET);
        }
		
		/* Provide a delay to allow the changes on WDT register to take 
		 * effect. This is approximately 4 LFCLK cycles. */
		CyDelayUs(ILOX4);
			
		/* Enter DeepSleep power mode. The WDT is set to wakeup the device
		 * every 1s in the "Clock" tab of CY8CKIT_046_Deep_Sleep_Blinky.cydwr
		 * settings for WDT0. */
		CySysPmDeepSleep();	
		
		/* Read the pin state and then set it to the opposite value. */
		Pin_GreenLED_Write(!Pin_GreenLED_Read());
    }
}

/* [] END OF FILE */
