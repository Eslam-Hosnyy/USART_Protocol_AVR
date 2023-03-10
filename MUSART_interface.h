/************************************/
/*	Author	  :	ESLAM_HOSNY			*/
/*	SWC		  : MUSART				*/
/*  Layer	  : MCAL				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December 1, 2022	*/
/*	Last Edit : N/A					*/
/************************************/

#ifndef _MUSART_INTERFACE_
#define _MUSART_INTERFACE_

#ifndef F_CPU
#define	F_CPU	1000000UL
#endif

#define MUSART_DATABITS_5				5
#define MUSART_DATABITS_6				6
#define MUSART_DATABITS_7				7
#define MUSART_DATABITS_8				8
#define MUSART_DATABITS_9				9

#define MUSART_PARITY_NONE				0
#define MUSART_PARITY_EVEN				2
#define MUSART_PARITY_ODD				3

#define MUSART_STOPBITS_1				0
#define MUSART_STOPBITS_2				1

#define MUSART_INTERRUPT_RXCIE			7
#define MUSART_INTERRUPT_TXCIE			6
#define MUSART_INTERRUPT_UDRIE			5


void MUSART_voidINT(u32 ARG_u32Baud, u8 ARG_u8DataBits, u8 ARG_u8Parity, u8 ARG_u8StopBits);

void MUSART_voidEnableTX(void);

void MUSART_voidDisableTX(void);

void MUSART_voidEnableRX(void);

void MUSART_voidDisableRX(void);

void MUSART_voidSendChar(char ARG_CharData);

void MUSART_voidSendString(const char *ARG_StringData);

u8 MUSART_u8RecieveChar(char *ARG_charDATA);

void MUSART_voidReciveStringUntil(char *ARG_StringData, char ARG_charTreminator);

void MUSART_voidEnableInterrupt(u8 ARG_u8InterruptSource);

void MUSART_voidDisableInterrupt(u8 ARG_u8InterruptSource);

void MUSART_voidSetCallBack(u8 ARG_u8InterruptSource, void(*ARG_pvoidfUserFunction)(void));


#endif
