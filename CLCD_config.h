/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: CLCD		 		*/
/*	Layer		: HAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 23, 2022	*/
/*	Last Edit 	: N/A				*/
/************************************/

#ifndef _CLCD_CONFIG_H_
#define _CLCD_CONFIG_H_

/* 1 For 4-bit Mode
 * 0 For 8-bit Mode 		*/
#define CLCD_MODE		 1

/* Definition Of The used PORT of DATA and CONTROL
 * */
#define CLCD_DATAPORT	 MDIO_PORTC
#define CLCD_CTRLPORT	 MDIO_PORTC

/* Definition Of the Control-Pins
 * */
#define CLCD_RS_PIN		 PIN6
#define CLCD_RW_PIN		 PIN5
#define CLCD_E_PIN		 PIN4

/*
 * Definition Of the Four-Pins Used (For the 4-bits Mode only)
 * */
#define CLCD_DATAPIN4    PIN0
#define CLCD_DATAPIN5    PIN1
#define CLCD_DATAPIN6    PIN2
#define CLCD_DATAPIN7    PIN3


#endif
