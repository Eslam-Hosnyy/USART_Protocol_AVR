/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : MUSART				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 1, 2022	*/
/*	Last Edit : N/A					*/
/************************************/
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MUSART_confg.h"
#include "MUSART_private.h"
#include "MUSART_interface.h"

void(*MUSART_pvoidfuserFunctionRXCIE)(void) = NULL;
void(*MUSART_pvoidfuserFunctionTXCIE)(void) = NULL;
void(*MUSART_pvoidfuserFunctionUDRIE)(void) = NULL;

void MUSART_voidINT(u32 ARG_u32Baud, u8 ARG_u8DataBits, u8 ARG_u8Parity, u8 ARG_u8StopBits)
{
	/* Calculate The Baud_Rate */
	u16 UBRR=(F_CPU/(16*ARG_u32Baud))-1;
	UBRRRL = (u8)UBRR;
	UBRRRH = (u8)((UBRR>>8)&0b01111111);

	/* Check The Data Bits (Character Size)*/
	switch(ARG_u8DataBits)
	{
	case MUSART_DATABITS_5:
	{
		CLEAR_BIT(UCSRB,UCSZ2);
		UCSRC &= 0b11111001;
		break;
	}
	case MUSART_DATABITS_6:
	{
		CLEAR_BIT(UCSRB,UCSZ2);
		UCSRC &= 0b11111001;
		UCSRC |= 0b10000010;
		break;
	}
	case MUSART_DATABITS_7:
	{
		CLEAR_BIT(UCSRB,UCSZ2);
		UCSRC &= 0b11111001;
		UCSRC |= 0b10000100;
		break;
	}
	case MUSART_DATABITS_8:
	{
		CLEAR_BIT(UCSRB,UCSZ2);
		UCSRC &= 0b11111001;
		UCSRC |= 0b10000110;
		break;
	}
	case MUSART_DATABITS_9:
	{
		SET_BIT(UCSRB,UCSZ2);
		UCSRC |= 0b10000110;
		break;
	}

	}

	/* SET The Parity_Bits */
	UCSRC &= 0b11001111;
	UCSRC |= ((0b10000000|ARG_u8Parity)<<4);
	/* SET The Stop_Bits */
	UCSRC &= 0b11110111;
	UCSRC |= ((0b10000000|ARG_u8StopBits)<<3);

}

void MUSART_voidEnableTX(void)
{
	SET_BIT(UCSRB,TXEN);
}

void MUSART_voidDisableTX(void)
{
	CLEAR_BIT(UCSRB,TXEN);
}

void MUSART_voidEnableRX(void)
{
	SET_BIT(UCSRB,RXEN);
}

void MUSART_voidDisableRX(void)
{
	CLEAR_BIT(UCSRB,RXEN);
}

void MUSART_voidSendChar(char ARG_CharData)
{
	/* Polling Until The UDR_Rigister Finish Sending*/
	while(!GET_BIT(UCSRA,UDRE));
	/* Send The Character To UDR */
	UDR = ARG_CharData;
}

void MUSART_voidSendString(const char *ARG_StringData)
{
	u32 i =0;
	do
	{
		/* Send The String Charcter by Character */
		MUSART_voidSendChar(ARG_StringData[i]);
		i++;
	}while(ARG_StringData[i] != '\0');  // LOOP Until The End Of The String.
}

u8 MUSART_u8RecieveChar(char *ARG_charDATA)
{
	u8 L_u8Error=0;
	/* Polling Until The UDR_Rigister Finish Reciveing*/
	while(!GET_BIT(UCSRA,RXC));
	/* Return Back with The UDR_Value */
	if(!(GET_BIT(UCSRA,FE)) && !(GET_BIT(UCSRA,PE)) && !(GET_BIT(UCSRA,DOR)))
	{
		*ARG_charDATA = UDR;
	}
	else
	{
		L_u8Error =1;
	}

	return L_u8Error;
}

void MUSART_voidReciveStringUntil(char *ARG_StringData, char ARG_charTreminator)
{
	u32 i =0;
	do
	{
		/* Recieve The String Charcter by Character And Store It in ARG_StringData*/
		MUSART_u8RecieveChar(&ARG_StringData[i]);
		i++;
	}while(ARG_StringData[i-1] != ARG_charTreminator);// LOOP Until Reaching To The Terminator.
	/* Replace The End Of The String (Terminator) by '\0' */
	ARG_StringData[i-1]='\0';
}

void MUSART_voidEnableInterrupt(u8 ARG_u8InterruptSource)
{

	SET_BIT(UCSRB, ARG_u8InterruptSource);
}

void MUSART_voidDisableInterrupt(u8 ARG_u8InterruptSource)
{
	CLEAR_BIT(UCSRB, ARG_u8InterruptSource);
}


void MUSART_voidSetCallBack(u8 ARG_u8InterruptSource, void(*ARG_pvoidfUserFunction)(void))
{
	switch(ARG_u8InterruptSource)
	{
	case MUSART_INTERRUPT_RXCIE:
	{
		MUSART_pvoidfuserFunctionRXCIE = ARG_pvoidfUserFunction;
		break;
	}
	case MUSART_INTERRUPT_TXCIE:
	{
		MUSART_pvoidfuserFunctionTXCIE = ARG_pvoidfUserFunction;
		break;
	}
	case MUSART_INTERRUPT_UDRIE:
	{
		MUSART_pvoidfuserFunctionUDRIE = ARG_pvoidfUserFunction;
		break;
	}
	default:
		break; //report an error
	}
}


void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{

	(*MUSART_pvoidfuserFunctionRXCIE)();

}

void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	(*MUSART_pvoidfuserFunctionUDRIE)();
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	(*MUSART_pvoidfuserFunctionTXCIE)();
}

/*
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{

}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{

}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{

}*/

