/*****************************************************************************
* File Name		: LED_Control.h
* Version		: 1.0 
*
* Description:
*  This file contains the function prototypes and constants used in
*  LED_Control.c
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
#if !defined(LED_CONTROL_H) 
#define LED_CONTROL_H 

#include "cytypes.h"

/*****************************************************************************
* MACRO Definition
*****************************************************************************/
#define OFF						    0x00
#define MIN_BRIGHTNESS				500
/*****************************************************************************
* Data Type Definition
*****************************************************************************/


/*****************************************************************************
* Enumerated Data Definition
*****************************************************************************/
typedef enum
{
    DISPLAY_LED_OFF,
    DISPLAY_LED_WHITE,
    DISPLAY_LED_BLUE,
    DISPLAY_LED_GREEN,
    DISPLAY_LED_RED,
    DISPLAY_LED_PREV_COLOR,
    DISPLAY_UP_SWIPE,
    DISPLAY_DOWN_SWIPE
}DISPLAY_COMMAND;  

typedef enum
{
    LED_COLOR_WHITE,
    LED_COLOR_BLUE,
    LED_COLOR_GREEN,
    LED_COLOR_RED
}LED_COLOR;  

/*****************************************************************************
* Data Structure Definition
*****************************************************************************/


/*****************************************************************************
* Global Variable Declaration
*****************************************************************************/


/*****************************************************************************
* Function Prototypes
*****************************************************************************/
void ShowPrevLEDColor(void);
void DisplayLEDOutput(DISPLAY_COMMAND command);

/*****************************************************************************
* External Function Prototypes
*****************************************************************************/
	
	
#endif /* LED_CONTROL_H */

/* [] END OF FILE */
