#include <stdio.h>
#include <ctype.h>

#include "serial.h"
#include "clock.h"
#include "sam.h"

#define RX 23
#define TX 22

//on redéfinit le pointeur vers SERCOM3, pour éviter
//les cast vers le type SercomUsart à chaque fois.
SercomUsart *uart = (SercomUsart *)SERCOM3;
void SERIALInit()
{
	//PA22 => TXd
	PORT->Group[0].DIRSET.reg = 1<<TX;
	PORT->Group[0].PINCFG[TX].reg = 0x1;
	//PA23 => RXd (nécessaire de mettre en entrée?)
	PORT->Group[0].PINCFG[RX].reg = 0x7; 
	//SERCOM sur lignes 22 et 23 (peripheral func C => 0x2)
	PORT->Group[0].PMUX[11].reg = 0x22;

	//Power Management for SerCom3
	PM->APBCMASK.reg |= 0x20;
	
	//horloge: generateur 3 (8MHz)
	const int generator = F8MHZ;
	GCLK->CLKCTRL.reg = 1 <<14 | //enable
						generator << 8 | //generator
						0x17;	 //GCLK_uart_CORE

	// configure uart 115200 8N1
	// 
	uart->CTRLA.bit.MODE = 0x01; //USART mode avec horloge interne
	uart->CTRLA.bit.DORD = 1;    //LSB first
	uart->CTRLA.bit.CMODE = 0x0; //asynchrone (pas d'horloge en plus)
	uart->CTRLA.bit.RXPO = 1;    //PAD[1] for RX
	uart->CTRLA.bit.TXPO = 0;    //PAD[0] for TX
	
	uart->CTRLB.bit.CHSIZE = 0;  //8 bits
	uart->CTRLB.bit.TXEN = 1;    //TX enable
	uart->CTRLB.bit.RXEN = 1;	 //RX enable
	uart->CTRLB.bit.SBMODE = 0;	 //1 Stop bit.
	//formule p.427:
	//Fref = 16M
	//S=16 (nb samples per bit)
	//FBaud = 115200
	//FBaud = Fref/S*(1-baud/65536)
	uart->BAUD.reg = 50436;
	
	//enable uart => registres de config protégés en ecriture.
	uart->CTRLA.reg |= 0x02;
}

void SERIALPutchar(char txd)
{
	if(txd == '\n') SERIALPutchar('\r');
	while(!(uart->INTFLAG.bit.DRE));
	uart->DATA.reg = (unsigned int) (txd & 0xFF);
	while(!(uart->INTFLAG.bit.TXC));
}

void SERIALPutString(char *str)
{
	char *ptr = str;
	while(*ptr) SERIALPutchar(*ptr++);
}

