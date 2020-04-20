/*****************************************************************************
* File Name		: main.h
* Version		: 1.0 
*
* Description:
*  This file contains the function prototypes and constants used in
*  main.c
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
#ifndef __MAIN_H
	#define __MAIN_H
	
	#include <project.h>

	/*****************************************************************************
	* MACRO Definitions
	*****************************************************************************/   
	/* Constants used to enable/disable tuner */
	#define ENABLED                     (1)
	#define DISABLED                    (0)    
	#define TUNER_ENABLE                (DISABLED)

	/* Tuner type selection macro
		The I2C block is shared between the buttons (CSD0) and proximity (CSD1) tuner interface
		Hence only one of the tuner interface can be active at a time.
		The TUNER_TYPE macro selects the active tuner interface when tuner is enabled */
	#define TUNER_TYPE_BUTTONS			0
	#define TUNER_TYPE_PROXIMITY		1
	#define TUNER_TYPE					TUNER_TYPE_BUTTONS

	/* Constants indicating CapSense scan completion on CSD0/CSD1 */
	#define CAPSENSE_BUTTON_SCAN_COMPLETE		1 /* CSD0 scan completion mask */
	#define CAPSENSE_PROX_SCAN_COMPLETE			2 /* CSD1 scan completion mask */
	/* CSD0 and CSD1 combined scan complete mask */
	#define CAPSENSE_SCAN_COMPLETE				(CAPSENSE_BUTTON_SCAN_COMPLETE|CAPSENSE_PROX_SCAN_COMPLETE) 

	/* Boolean constants */
	#define TRUE								1
	#define FALSE								0
	#define ON									TRUE
	#define OFF									FALSE
	#define SET									ON
	#define CLEAR								OFF

	/* Constants for color selection */
	#define COLOR_RED							1
	#define COLOR_GREEN							2
	#define COLOR_BLUE							3

	/* Maximum compare value of the PRS modulator */
	#define PRSM_MAX_COMPARE					32767

	/* Constants for brightness control */
	#define BRIGHTNESS_MIN						1
	#define BRIGHTNESS_MAX						6
	/* Maximum brightness step size */
	#define BRIGHTNESS_STEP_MAX					(PRSM_MAX_COMPARE/(BRIGHTNESS_MAX - BRIGHTNESS_MIN + 1))
	/* Minimum brightness step size */
	#define BRIGHTNESS_STEP_MIN					100

	/* Constants for transforming proximity signal to brightness scaling factor */
	#define PROXIMITY_SIGNAL_SHIFT_FACTOR		1

	/* Macros to find rising and falling edge on the data passed */
	#define RISING_EDGE_DET(curr, prev)			((curr ^ prev) & curr)
	#define FALLING_EDGE_DET(curr, prev)		((curr ^ prev) & prev)

	/* Button mask registers */
	#define LEFT_BUTTON_MASK					(0x01<<CapSense_Buttons_SENSOR_LEFT__BTN)
	#define RIGHT_BUTTON_MASK					(0x01<<CapSense_Buttons_SENSOR_RIGHT__BTN)
	#define UP_BUTTON_MASK						(0x01<<CapSense_Buttons_SENSOR_UP__BTN)
	#define DOWN_BUTTON_MASK					(0x01<<CapSense_Buttons_SENSOR_DOWN__BTN)
	#define CENTRE_BUTTON_MASK					(0x01<<CapSense_Buttons_SENSOR_CENTRE__BTN)
	
	#define IsPowerOfTwo(x)						(((x) & (-x)) == x)
	#define IsNotPowerOfTwo(x)					(((x) & (-x)) != x)
	
	/*****************************************************************************
	* Function Prototypes
	*****************************************************************************/ 
	uint32 CapSense_ValidateButtons(uint32 prevButtonStatus);
#endif
/* [] END OF FILE */
