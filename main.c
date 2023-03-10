/************************************/
/*	Author		: Eslam_Hosny		*/
/*	SWC			: N/A				*/
/*	Layer		: N/A				*/
/*	Version   	: 0.0				*/
/*	Date	  	: N/A				*/
/*	Last Edit 	: N/A				*/
/************************************/
#define F_CPU		8000000UL
#include <util/delay.h>
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MDIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "MUSART_interface.h"
#include "MGIE_interface.h"


int main (void)
{

	PORT_voidInit();
	CLCD_voidInit();
	CLCD_voidClear();


	MUSART_voidINT(9600, MUSART_DATABITS_8, MUSART_PARITY_NONE, MUSART_STOPBITS_1);
	MUSART_voidEnableRX();
	MUSART_voidEnableTX();

	while(1)
	{

		MUSART_voidSendString("ESLAM");

		_delay_ms(500);


	}

	return 0;
}
