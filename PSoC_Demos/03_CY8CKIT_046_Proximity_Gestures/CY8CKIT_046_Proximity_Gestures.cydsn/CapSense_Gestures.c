/*****************************************************************************
* File Name		: CapSense_Gestures.c
* Version		: 1.0 
*
* Description:
*  This file defines the function used to detect the proximity gesture made 
*  by an approaching hand.
*
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
#include "CapSense_Gestures.h"
#include "LED_Control.h"
#include "project.h"
#include <stdbool.h>

/*******************************************************************************
* Function Name: DetectGesture
********************************************************************************
* Summary:
*  This function scans the proximity sensors individually and determines if a 
*  valid gesture has been made.
*
* Parameters:
*  void
*
* Return:
*  GESTURE: The gesture detected by the CapSense Gesture Pad.
*
*******************************************************************************/
GESTURE DetectGesture(void)
{
	/* Variables to store proximity states. */
	bool prox0State = false;
	bool prox1State = false;
	
	/* Variable declared static to remember the state machine
	 * state between function calls. */
    static GESTURE_STATE currState = GESTURE_STATE_INACTIVE;
	
	GESTURE gesture = GESTURE_NO_GESTURE;
    GESTURE_ZONE currZone;
	
	/* Get the proximity sensor states. */
	prox0State = CapSense_CheckIsWidgetActive(CapSense_PROXIMITYSENSOR0__PROX);	
	prox1State = CapSense_CheckIsWidgetActive(CapSense_PROXIMITYSENSOR1__PROX);
	
	/* Determine the zone in which hand is currently present
     **************************************************************************
     ******************  Sensor placement and zones   *************************
     *   
     *          GESTURE_ZONE_OUT (Both Prox0 and Prox1 are inactive)
	 *				=============<Prox1 ZONE starts>==============
     *          GESTURE_ZONE_SENSOR_0 (Prox1 is active but Prox0 is inactive)   
     * 				=============<Prox0 ZONE starts>==============
     *          GESTURE_ZONE_SENSOR_0 (Prox1 is active but Prox0 is inactive)
	 *			GESTURE_ZONE_SENSOR_0_1 (Both Prox0 and Prox1 are active)
	 *				=============<Prox1 ZONE ends>==============
     *          GESTURE_ZONE_SENSOR_1 (Prox0 is active but Prox1 is inactive) 				
	 *				===============<Prox0 ZONE ends>==============
     *          GESTURE_ZONE_OUT (Both Prox0 and Prox1 are inactive)
     *
	 * Prox0 is Proximity Sensor 0 (P9[4])
	 * Prox1 is Proximity Sensor 1 (P9[5])
     ***************************************************************************/
    
    currZone = (GESTURE_ZONE)((prox1State << 1)| prox0State);
    
    /* Determine if a gesture is detected by checking the transition between 
	 * different zones
     */
	switch(currState)
	{
	case GESTURE_STATE_INACTIVE:
        switch(currZone)
        {
        case GESTURE_ZONE_SENSOR_0:
            currState = GESTURE_STATE_DOWN_START;
            break;
        case GESTURE_ZONE_SENSOR_1:
            currState = GESTURE_STATE_UP_START;
            break;
        case GESTURE_ZONE_OUT:
            gesture = GESTURE_SENSORS_INACTIVE;
            /* Remain in current state i.e. GESTURE_STATE_INACTIVE */
            break;            
        default:
            /* Remain in current state i.e. GESTURE_STATE_INACTIVE */
            break;
        }
		break;
		
	case GESTURE_STATE_UP_START:
		switch(currZone)
        {
        case GESTURE_ZONE_SENSOR_0:
             /* A complete up swipe gesture has been detected at this 
             * stage
             */
			gesture = GESTURE_UP_SWIPE;
            currState = GESTURE_STATE_INACTIVE;
            break;
        case GESTURE_ZONE_OUT:
            currState = GESTURE_STATE_INACTIVE;
            gesture = GESTURE_SENSORS_INACTIVE;
            break;
        default:
            /* Remain in current state i.e. GESTURE_STATE_UP_START */ 
            break;
        }
  		break;
      	
	case GESTURE_STATE_DOWN_START:
		switch(currZone)
        {
        case GESTURE_ZONE_SENSOR_1:
            /* A complete down swipe gesture has been detected at this 
             * stage
             */
			gesture = GESTURE_DOWN_SWIPE;
			currState = GESTURE_STATE_INACTIVE;
            break;
        case GESTURE_ZONE_OUT:
            currState = GESTURE_STATE_INACTIVE;
            gesture = GESTURE_SENSORS_INACTIVE;
        default:
            /* Remain in current state i.e. GESTURE_STATE_DOWN_START */
            break;   
        }
		break;
        
    default:
        break;
        
	}
    
	return(gesture);
}

/* [] END OF FILE */
