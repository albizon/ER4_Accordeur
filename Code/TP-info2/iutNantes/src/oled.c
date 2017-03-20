#include <stdbool.h>
#include "sam.h"
#include "oled.h"

int __oledCurseurX; //colonne en pixels;
int __oledCurseurY; //ligne en pixels

//****************************************************************************
//fonctions pour utiliser l'afficheur OLED dans les TP Info2
//IUT de Nantes, dept GEII.
//toutes ces fonctions commencent par 'OLED'
//****************************************************************************
//taile des carateres: largeur 6, hauteur 7
void OLEDInit(unsigned char withLogo)
{
	gfx_mono_init();
	if(withLogo)
	{
		//logo IUT!
		gfx_mono_generic_put_bitmap(&logoIUT,0,0);
		gfx_mono_draw_string("IUT de Nantes",43,2,&sysfont);
		gfx_mono_draw_string("Dept GEII",53,19,&sysfont);
		gfx_mono_draw_horizontal_line(63,29,34,GFX_PIXEL_SET);
	}
}

void OLEDSetLine(int line)
{
	if(line > 3) return; //valeur entre 0 et 3.
	__oledCurseurY = line*8;
	__oledCurseurX = 0;
}

void OLEDSetTextCursor(int pos,int line)
{
	if((pos < (128-SYSFONT_WIDTH)) && (line<4))
	{
		__oledCurseurY = line*8;
		__oledCurseurX = pos;
	}
}

void OLEDPrintChar(char car)
{
	if(car == '\n') {
		//passage à la ligne
		__oledCurseurX = 0;
		__oledCurseurY = (__oledCurseurY+8)%32;
	} else {
		gfx_mono_draw_char(car,__oledCurseurX,__oledCurseurY,&sysfont);
		__oledCurseurX += SYSFONT_WIDTH;
		if(__oledCurseurX >= 128) 
		{
			//passage à la ligne.
			__oledCurseurX = 0;
			__oledCurseurY = (__oledCurseurY+8)%32;
		}
	}
}

void OLEDPrintString(char *str)
{
	while(*str)
	{
		OLEDPrintChar(*str);
		str++;
	}
}

void OLEDClear()
{
	int page, column;
	for (page = 0; page < 4; page++) {
		for (column = 0; column < 128; column++) {
			gfx_mono_ssd1306_put_byte(page, column, 0x00, true);
		}
	}
	__oledCurseurX = 0;
	__oledCurseurY = 0;
}

void OLEDClearLine(char line)
{
	int column;
	for (column = 0; column < 128; column++) {
		gfx_mono_ssd1306_put_byte(line, column, 0x00, true);
	}
	__oledCurseurX = 0;
	__oledCurseurY = 0;
}

void OLEDDrawLine(struct point point1, struct point point2, enum gfx_mono_color color)
{
	if(point1.x == point2.x) {
		//ligne verticale
		int length;
		int yMin;
		if(point1.y < point2.y) {
			length = point2.y - point1.y;
			yMin = point1.y;
		} else {
			length = point1.y - point2.y;
			yMin = point2.y;
		}
		gfx_mono_draw_vertical_line(point1.x, yMin, length, color);
	 } else if(point1.y == point2.y) {
		 //ligne horizontale
		int length;
		int xMin;
		if(point1.x < point2.x) {
			length = point2.x - point1.x;
			xMin = point1.x;
		} else {
			length = point1.x - point2.x;
			xMin = point2.x;
		}
		gfx_mono_draw_horizontal_line(xMin, point1.y, length, color);
	 } else { //cas general
		 gfx_mono_draw_line(point1.x, point1.y, point2.x, point2.y,color);
	 }	
}


//****************************************************************************
// le logo de l'IUT!
//****************************************************************************
gfx_mono_color_t PROGMEM_T img[] = {
	0xf8, 0x04, 0x18, 0xfc, 0x0e, 0x02, 0x02, 0x02, 0x02, 0x03, 0x66, 0x0e, 0xf0, 0x00, 0x00, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 
	0x00, 0x00, 0x00, 0x01, 0x03, 0x2e, 0x3c, 0x5a, 0x50, 0xf4, 0xd6, 0xc2, 0x48, 0x20, 0x24, 0x11, 
	0xf8, 0xfe, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 
	0xff, 0xff, 0xff, 0xf0, 0xf0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x7f, 
	0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x7f, 0x7f, 0x70, 0x78, 0x7c, 0x3f, 0x7f, 0x7f, 
	0x78, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0x7f, 0x78, 0x20, 0x00 
};
struct gfx_mono_bitmap logoIUT = { 35 , 32 ,GFX_MONO_BITMAP_PROGMEM,{progmem: img}};
//****************************************************************************

//****************************************************************************
//connexion a l'afficheur OLED SSD1306 en SPI sur le port d'extension 3 de la 
//carte SAMD21 XPlained Pro
//Le driver de bas niveau n'utilise pas le framework ASF, il en reprend
//certaines partie de l'API pour pouvoir utiliser les fonts (texte).
//Ces fonctions de bas niveaux sont utilisée par la bibliothèque gfx 
//fournie par Atmel dans son framework ASF.
//****************************************************************************
#include "pinAccess.h"
#include "pinMux.h"
#define CONFIG_SSD1306_FRAMEBUFFER
//connexion SSD1306
//  broche      == connecteur EXT3 == signal
//SPI_MOSI      => 16              => PB.22 (SERCOM 5 pad 2)
//SPI_CLK       => 18              => PB.23 (SERCOM 5 pad 3)
//DATA_CMD_SEL  =>  5              => PB.30
//DISPLAY_SS    => 15              => PB.17 (SERCOM 5 pad 1)
//DISPLAY_RESET => 10              => PA.27

#define OLED_RESET_PIN PORTA,27
#define OLED_CMD_PIN   PORTB,30
#define OLED_SS_PIN    PORTB,17
#define OLED_CLK_PIN   PORTB,23
#define OLED_MOSI_PIN  PORTB,22

void oledWait10us()
{
	for(volatile int i = 0; i < 1000;i++); //10us min TODO, check
}

void ssd1306_hard_reset()
{
	pinMode(OLED_RESET_PIN,OUTPUT);
	digitalWrite(OLED_RESET_PIN,0);
	oledWait10us();
	digitalWrite(OLED_RESET_PIN,1);
	oledWait10us();
}

void OLEDSpiInit()
{
	//broches accès SPI
	pinMux(OLED_SS_PIN,CONFIG_C);   //config C => SERCOM5 - pad 1 
	pinMux(OLED_MOSI_PIN,CONFIG_D); //config D => SERCOM5 - pad 2
	pinMux(OLED_CLK_PIN,CONFIG_D);  //config D => SERCOM5 - pad 3

	//Power Management.
	PM->APBCMASK.reg |= 1<<7; //sercom5
	
	//horloge: generateur 3 (8MHz)
	GCLK->CLKCTRL.reg = 1 <<14 | //enable
						3 << 8 | //generator 3 => 8MHz
						0x19;	 //SERCOM5
	//config SPI:
	SERCOM5->SPI.CTRLA.bit.SWRST = 1;
	while ( SERCOM5->SPI.CTRLA.bit.SWRST || SERCOM5->SPI.SYNCBUSY.bit.SWRST );
	SERCOM5->SPI.CTRLA.reg =	1 << 16 |	//DOPO = 1 => pad1=SS - pad2=DO - pad3=SCK
								1 << 7	|	//RUNSTDBY
								3 << 2  ;	//Mode Master
	SERCOM5->SPI.CTRLB.reg =    1 << 17 |	//RXEN
								1 << 13 |	//MSSEN (hardware SS).
								1 << 9  ;	//SSDE
	SERCOM5->SPI.BAUD.reg = 3; // p.427 (synchronous) => Fbaud=Fref(2*(baud+1)) => Fref=8MHz => FBaud = 1MHz
	//validation spi
	SERCOM5->SPI.CTRLA.reg |= 0x02;
}

void ssd1306_write_first_command(uint8_t command)
{
	digitalWrite(OLED_CMD_PIN,0);
	SERCOM5->SPI.DATA.reg = (command); //note: hardware SS
}

void ssd1306_write_command(uint8_t command)
{
	while(! (SERCOM5->SPI.INTFLAG.bit.TXC));  //attente fin transmission précédente
	//il faut un peu d'attente entre 2 transaction (trop rapide pour ssd1306 sinon)
	PORT->Group[PORTB].OUTCLR.reg = 1 << 30; //OLED_CMD_PIN = 0 (+rapide que digitalWrite)
	SERCOM5->SPI.DATA.reg = (command); //note: hardware SS
}

void ssd1306_write_data(uint8_t data)
{
	while(! (SERCOM5->SPI.INTFLAG.bit.TXC));  //attente fin transmission précédente
	//il faut un peu d'attente entre 2 transaction (trop rapide pour ssd1306 sinon)
	PORT->Group[PORTB].OUTSET.reg = 1 << 30; //OLED_CMD_PIN = 1 (+rapide que digitalWrite)
	SERCOM5->SPI.DATA.reg = (data); //note: hardware SS
}

void ssd1306_init()
{
	pinMode(OLED_CMD_PIN,OUTPUT);	
	ssd1306_hard_reset();

	OLEDSpiInit();

	//suite init reprise des fichiers ASF.

	// 1/32 Duty (0x0F~0x3F)
	ssd1306_write_first_command(SSD1306_CMD_SET_MULTIPLEX_RATIO); //first command (sans attente TX precedent)
	ssd1306_write_command(0x1F);

	// Shift Mapping RAM Counter (0x00~0x3F)
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_OFFSET);
	ssd1306_write_command(0x00);

	// Set Mapping RAM Display Start Line (0x00~0x3F)
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_START_LINE(0x00));

	// Set Column Address 0 Mapped to SEG0
	ssd1306_write_command(SSD1306_CMD_SET_SEGMENT_RE_MAP_COL127_SEG0);

	// Set COM/Row Scan Scan from COM63 to 0
	ssd1306_write_command(SSD1306_CMD_SET_COM_OUTPUT_SCAN_DOWN);

	// Set COM Pins hardware configuration
	ssd1306_write_command(SSD1306_CMD_SET_COM_PINS);
	ssd1306_write_command(0x02);

	ssd1306_set_contrast(0x8F);

	// Disable Entire display On
	ssd1306_write_command(SSD1306_CMD_ENTIRE_DISPLAY_AND_GDDRAM_ON);

	ssd1306_display_invert_disable();

	// Set Display Clock Divide Ratio / Oscillator Frequency (Default => 0x80)
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_CLOCK_DIVIDE_RATIO);
	ssd1306_write_command(0x80);

	// Enable charge pump regulator
	ssd1306_write_command(SSD1306_CMD_SET_CHARGE_PUMP_SETTING);
	ssd1306_write_command(0x14);

	// Set VCOMH Deselect Level
	ssd1306_write_command(SSD1306_CMD_SET_VCOMH_DESELECT_LEVEL);
	ssd1306_write_command(0x40); // Default => 0x20 (0.77*VCC)

	// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	ssd1306_write_command(SSD1306_CMD_SET_PRE_CHARGE_PERIOD);
	ssd1306_write_command(0xF1);

	ssd1306_display_on();	
}

//****************************************************************************
// la suite du code correspond au fonctions de haut niveau 
// Elles sont basée sur la bibliothèque graphique monochrome gfx
// fournie par Atmel dans sont Framework ASF.
//****************************************************************************
// d'abord, la licence ASF:
/* Copyright (c) 2011-2014 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */ 



//****************************************************************************

//from ASF file sysfont.c
// Use macro from conf_sysfont.h to define font glyph data.
SYSFONT_DEFINE_GLYPHS;

/**
 * \brief Initialize a basic system font
 *
 * This initializes a basic system font globally usable by the application.
 */
struct font sysfont = {
	.type           = FONT_LOC_PROGMEM,
	.width          = SYSFONT_WIDTH,
	.height         = SYSFONT_HEIGHT,
	.first_char     = SYSFONT_FIRSTCHAR,
	.last_char      = SYSFONT_LASTCHAR,
	.data           = {
		.progmem        = sysfont_glyphs,
	},
};


//from ASF file gfx_mono_frame_buffer.c

/* Pointer to the framebuffer; updated by the gfx_mono_set_framebuffer function */
static uint8_t *fbpointer;
void gfx_mono_set_framebuffer(uint8_t *framebuffer)
{
	fbpointer = framebuffer;
}

/**
 * \brief Put a page from RAM to the framebuffer
 *
 * \param[in] data Pointer to data to be written
 * \param[in] page Page address
 * \param[in] column Offset into page (x coordinate)
 * \param[in] width Number of bytes to be written.
 *
 * The following example will write 32 bytes from data_buf to the page 0,
 * column 10 (byte 10 to 42 in the framebuffer).
 * \code
	gfx_mono_framebuffer_put_page(data_buf, 0, 10, 32);
\endcode
 */
void gfx_mono_framebuffer_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t column, gfx_coord_t width)
{
	gfx_mono_color_t *data_pt = data;
	gfx_coord_t *framebuffer_pt = fbpointer +
			((page * GFX_MONO_LCD_WIDTH) + column);

	do {
		*framebuffer_pt++ = *data_pt++;
	} while (--width > 0);
}

/**
 * \brief Read a page from the framebuffer
 *
 * \param[in] data   Pointer where to store the read data
 * \param[in] page   Page address
 * \param[in] column Offset into page (x coordinate)
 * \param[in] width  Number of bytes to be read
 *
 * The following example will read back the first 128 bytes (first page) from
 * the framebuffer:
 * \code
	gfx_mono_framebuffer_get_page(read_buffer, 0, 0, 128);
\endcode
 */
void gfx_mono_framebuffer_get_page(gfx_mono_color_t *data, gfx_coord_t page, \
		gfx_coord_t column, gfx_coord_t width)
{
	gfx_coord_t *framebuffer_pt = fbpointer +
			((page * GFX_MONO_LCD_WIDTH) + column);
	do {
		*data++ = *framebuffer_pt++;
	} while (--width > 0);
}

/**
 * \brief Draw pixel to framebuffer
 *
 * \param[in] x         X coordinate of the pixel
 * \param[in] y         Y coordinate of the pixel
 * \param[in] color     Pixel operation
 *
 */
void gfx_mono_framebuffer_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color)
{
	uint8_t page;
	uint8_t pixel_mask;
	uint8_t pixel_value;

	/* Discard pixels drawn outside the screen */
	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	/*
	 * Read the page containing the pixel in interest, then perform the
	 * requested action on this pixel before writing the page back to the
	 * display.
	 */
	pixel_value = gfx_mono_framebuffer_get_byte(page, x);

	switch (color) {
	case GFX_PIXEL_SET:
		pixel_value |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		pixel_value &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		pixel_value ^= pixel_mask;
		break;

	default:
		break;
	}

	gfx_mono_framebuffer_put_byte(page, x, pixel_value);
}

/**
 * \brief Get the pixel value at x,y in framebuffer
 *
 * \param[in] x      X coordinate of pixel
 * \param[in] y      Y coordinate of pixel
 * \return Non zero value if pixel is set.
 *
 */
uint8_t gfx_mono_framebuffer_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
	uint8_t page;
	uint8_t pixel_mask;

	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return 0;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	return gfx_mono_framebuffer_get_byte(page, x) & pixel_mask;
}

/**
 * \brief Put a byte to the framebuffer
 *
 * \param[in] page   Page address
 * \param[in] column Page offset (x coordinate)
 * \param[in] data   Data to be written
 *
 * This example will put the value 0xFF to the first byte in the framebuffer
 * \code
	gfx_mono_framebuffer_put_byte(0, 0, 0xFF);
\endcode
 */
void gfx_mono_framebuffer_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data)
{
	*(fbpointer + (page * GFX_MONO_LCD_WIDTH) + column) = data;
}

/**
 * \brief Get a byte from the framebuffer
 *
 * \param[in] page   Page address
 * \param[in] column Page offset (x coordinate)
 * \return       data from LCD controller or framebuffer.
 *
 * The following code will read the first byte of the framebuffer
 * \code
	data = gfx_mono_framebuffer_get_byte(0, 0);
\endcode
 */
uint8_t gfx_mono_framebuffer_get_byte(gfx_coord_t page, gfx_coord_t column)
{
	return *(fbpointer + (page * GFX_MONO_LCD_WIDTH) + column);
}

/**
 * \brief Read/Modify/Write a byte in the framebuffer
 *
 * This function will read the byte from the framebuffer and
 * do a mask operation on the byte according to the pixel operation selected
 * by the color argument and the pixel mask provided.
 *
 * \param[in] page       Page address
 * \param[in] column     Page offset (x coordinate)
 * \param[in] pixel_mask Mask for pixel operation
 * \param[in] color      Pixel operation
 *
 * A small example that will XOR the first byte of the framebuffer with 0xAA
 * \code
	gfx_mono_framebuffer_mask_byte(0,0,0xAA,GFX_PIXEL_XOR);
\endcode
 */
void gfx_mono_framebuffer_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color)
{
	gfx_mono_color_t temp;

	temp = gfx_mono_get_byte(page, column);

	switch (color) {
	case GFX_PIXEL_SET:
		temp |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		temp &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		temp ^= pixel_mask;
		break;
	}

	gfx_mono_put_byte(page, column, temp);
}

//from ASF file gfx_mono_generic.c

/**
 * \brief Draw a horizontal line, one pixel wide (generic implementation)
 *
 * \note This function does a very simple bounds checking that does not
 * check if the line is placed outside the screen. If you supply an
 * x- or y-coordinate outside the display the behaviour is undefined,
 * and you risk overwriting portions of internal SRAM.
 *
 * \param[in]  x          X coordinate of leftmost pixel.
 * \param[in]  y          Y coordinate of the line.
 * \param[in]  length     Length of the line in pixels.
 * \param[in]  color      Pixel operation of the line.
 */
void gfx_mono_generic_draw_horizontal_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color)
{
	uint8_t page;
	uint8_t pixelmask;
	uint8_t temp;

	/* Clip line length if too long */
	if (x + length > GFX_MONO_LCD_WIDTH) {
		length = GFX_MONO_LCD_WIDTH - x;
	}

	page = y / 8;
	pixelmask = (1 << (y - (page * 8)));

	if (length == 0) {
		/* Nothing to do. Move along. */
		return;
	}

	switch (color) {
	case GFX_PIXEL_SET:
		while (length-- > 0) {
			temp = gfx_mono_get_byte(page, x + length);
			temp |= pixelmask;
			gfx_mono_put_byte(page, x + length, temp);
		}
		break;

	case GFX_PIXEL_CLR:
		while (length-- > 0) {
			temp = gfx_mono_get_byte(page, x + length);
			temp &= ~pixelmask;
			gfx_mono_put_byte(page, x + length, temp);
		}
		break;

	case GFX_PIXEL_XOR:
		while (length-- > 0) {
			temp = gfx_mono_get_byte(page, x + length);
			temp ^= pixelmask;
			gfx_mono_put_byte(page, x + length, temp);
		}
		break;

	default:
		break;
	}
}

/**
 * \brief Draw a vertical line, one pixel wide (generic implementation)
 *
 * \note This function does a very simple bounds checking that does not
 * check if the line is placed outside the screen. If you supply an
 * x- or y-coordinate outside the display the behaviour is undefined,
 * and you risk overwriting portions of internal SRAM.
 *
 * \param[in]  x          X coordinate of the line.
 * \param[in]  y          Y coordinate of the topmost pixel.
 * \param[in]  length     Length of the line in pixels.
 * \param[in]  color      Pixel operation of the line.
 */
void gfx_mono_generic_draw_vertical_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color)
{
	if (length == 0) {
		return;
	}

	gfx_coord_t y2 = y + length - 1;

	if (y == y2) {
		gfx_mono_draw_pixel(x, y, color);
		return;
	}

	if (y2 >= GFX_MONO_LCD_HEIGHT - 1) {
		y2 = GFX_MONO_LCD_HEIGHT - 1;
	}

	gfx_coord_t y1page = y / 8;
	gfx_coord_t y2page = y2 / 8;

	uint8_t y1bitpos = y & 0x07;
	uint8_t y2bitpos = y2 & 0x07;

	uint8_t y1pixelmask = 0xFF << y1bitpos;
	uint8_t y2pixelmask = 0xFF >> (7 - y2bitpos);

	/* The pixels are on the same page; combine masks */
	if (y1page == y2page) {
		uint8_t pixelmask = y1pixelmask & y2pixelmask;
		gfx_mono_mask_byte(y1page, x, pixelmask, color);
	} else {
		gfx_mono_mask_byte(y1page, x, y1pixelmask, color);

		while (++y1page < y2page) {
			gfx_mono_mask_byte(y1page, x, 0xFF, color);
		}

		gfx_mono_mask_byte(y2page, x, y2pixelmask, color);
	}
}

/**
 * \brief Draw a line between two arbitrary points (generic implementation).
 *
 * \param[in]  x1          Start X coordinate.
 * \param[in]  y1          Start Y coordinate.
 * \param[in]  x2          End X coordinate.
 * \param[in]  y2          End Y coordinate.
 * \param[in]  color       Pixel operation of the line.
 */
void gfx_mono_generic_draw_line(gfx_coord_t x1, gfx_coord_t y1,
		gfx_coord_t x2, gfx_coord_t y2,
		enum gfx_mono_color color)
{
	uint8_t i;
	uint8_t x;
	uint8_t y;
	int8_t xinc;
	int8_t yinc;
	int8_t dx;
	int8_t dy;
	int8_t e;

	/* swap x1,y1  with x2,y2 */
	if (x1 > x2) {
		dx = x1;
		x1 = x2;
		x2 = dx;
		dy = y1;
		y1 = y2;
		y2 = dy;
	}

	dx = x2 - x1;
	dy = y2 - y1;

	x = x1;
	y = y1;

	if (dx < 0) {
		xinc = -1;
		dx = -dx;
	} else {
		xinc = 1;
	}

	if (dy < 0) {
		yinc = -1;
		dy = -dy;
	} else {
		yinc = 1;
	}

	if (dx > dy) {
		e = dy - dx;
		for (i = 0; i <= dx; i++) {
			gfx_mono_draw_pixel(x, y, color);
			if (e >= 0) {
				e -= dx;
				y += yinc;
			}

			e += dy;
			x += xinc;
		}
	} else {
		e = dx - dy;
		for (i = 0; i <= dy; i++) {
			gfx_mono_draw_pixel(x, y, color);
			if (e >= 0) {
				e -= dy;
				x += xinc;
			}

			e += dx;
			y += yinc;
		}
	}
}

/**
 * \brief Draw an outline of a rectangle (generic implementation).
 *
 * \param[in]  x           X coordinate of the left side.
 * \param[in]  y           Y coordinate of the top side.
 * \param[in]  width       Width of the rectangle.
 * \param[in]  height      Height of the rectangle.
 * \param[in] color       Pixel operation of the line.
 */
void gfx_mono_generic_draw_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color)
{
	gfx_mono_draw_horizontal_line(x, y, width, color);
	gfx_mono_draw_horizontal_line(x, y + height - 1, width, color);

	gfx_mono_draw_vertical_line(x, y, height, color);
	gfx_mono_draw_vertical_line(x + width - 1, y, height, color);
}

/**
 * \brief Draw a filled rectangle (generic implementation).
 *
 * \param[in]  x           X coordinate of the left side.
 * \param[in]  y           Y coordinate of the top side.
 * \param[in]  width       Width of the rectangle.
 * \param[in]  height      Height of the rectangle.
 * \param[in]  color       Pixel operation of the line
 */
void gfx_mono_generic_draw_filled_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color)
{
	if (height == 0) {
		/* Nothing to do. Move along. */
		return;
	}

	while (height-- > 0) {
		gfx_mono_draw_horizontal_line(x, y + height, width, color);
	}
}

/**
 * \brief Draw an outline of a circle or arc (generic implementation).
 *
 * The radius is the distance from the center to the circumference,
 * which means that the total width or height of a circle will be
 * (radius*2+1).
 *
 * The octant_mask parameter is a bitmask that decides which octants of
 * the circle to draw. Use the GFX_OCTANTn, GFX_QUADRANTn, GFX_xHALF and
 * GFX_WHOLE constants and OR them together if required. Radius equal to
 * zero gives a single pixel.
 *
 * \param[in]  x           X coordinate of center.
 * \param[in]  y           Y coordinate of center.
 * \param[in]  radius      Circle radius in pixels.
 * \param[in]  color       Pixel operation.
 * \param[in]  octant_mask Bitmask indicating which octants to draw.
 */
void gfx_mono_generic_draw_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t octant_mask)
{
	gfx_coord_t offset_x;
	gfx_coord_t offset_y;
	int16_t error;

	/* Draw only a pixel if radius is zero. */
	if (radius == 0) {
		gfx_mono_draw_pixel(x, y, color);
		return;
	}

	/* Set up start iterators. */
	offset_x = 0;
	offset_y = radius;
	error = 3 - 2 * radius;

	/* Iterate offsetX from 0 to radius. */
	while (offset_x <= offset_y) {
		/* Draw one pixel for each octant enabled in octant_mask. */
		if (octant_mask & GFX_OCTANT0) {
			gfx_mono_draw_pixel(x + offset_y, y - offset_x, color);
		}

		if (octant_mask & GFX_OCTANT1) {
			gfx_mono_draw_pixel(x + offset_x, y - offset_y, color);
		}

		if (octant_mask & GFX_OCTANT2) {
			gfx_mono_draw_pixel(x - offset_x, y - offset_y, color);
		}

		if (octant_mask & GFX_OCTANT3) {
			gfx_mono_draw_pixel(x - offset_y, y - offset_x, color);
		}

		if (octant_mask & GFX_OCTANT4) {
			gfx_mono_draw_pixel(x - offset_y, y + offset_x, color);
		}

		if (octant_mask & GFX_OCTANT5) {
			gfx_mono_draw_pixel(x - offset_x, y + offset_y, color);
		}

		if (octant_mask & GFX_OCTANT6) {
			gfx_mono_draw_pixel(x + offset_x, y + offset_y, color);
		}

		if (octant_mask & GFX_OCTANT7) {
			gfx_mono_draw_pixel(x + offset_y, y + offset_x, color);
		}

		/* Update error value and step offset_y when required. */
		if (error < 0) {
			error += ((offset_x << 2) + 6);
		} else {
			error += (((offset_x - offset_y) << 2) + 10);
			--offset_y;
		}

		/* Next X. */
		++offset_x;
	}
}

/**
 * \brief Draw a filled circle or sector (generic implementation).
 *
 * The radius is the distance from the center to the circumference,
 * which means that the total width or height of a circle will be
 * (radius*2+1).
 *
 * The quadrant_mask parameter is a bitmask that decides which quadrants
 * of the circle to draw. Use the GFX_QUADRANTn, GFX_xHALF and
 * GFX_WHOLE constants and OR them together if required. Radius equal to
 * zero gives a single pixel.
 *
 * \note This function only supports quadrants while gfx_draw_circle()
 *       supports octants. This is to improve performance on drawing
 *       filled circles.
 *
 * \param[in]  x           X coordinate of center.
 * \param[in]  y           Y coordinate of center.
 * \param[in]  radius      Circle radius in pixels.
 * \param[in]  color       Pixel operation.
 * \param[in]  quadrant_mask Bitmask indicating which quadrants to draw.
 */
void gfx_mono_generic_draw_filled_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t quadrant_mask)
{
	gfx_coord_t offset_x;
	gfx_coord_t offset_y;
	int16_t error;

	/* Draw only a pixel if radius is zero. */
	if (radius == 0) {
		gfx_mono_draw_pixel(x, y, color);
		return;
	}

	/* Set up start iterators. */
	offset_x = 0;
	offset_y = radius;
	error = 3 - 2 * radius;

	/* Iterate offset_x from 0 to radius. */
	while (offset_x <= offset_y) {
		/* Draw vertical lines tracking each quadrant. */
		if (quadrant_mask & GFX_QUADRANT0) {
			gfx_mono_draw_vertical_line(x + offset_y,
					y - offset_x, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x + offset_x,
					y - offset_y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT1) {
			gfx_mono_draw_vertical_line(x - offset_y,
					y - offset_x, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x - offset_x,
					y - offset_y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT2) {
			gfx_mono_draw_vertical_line(x - offset_y,
					y, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x - offset_x,
					y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT3) {
			gfx_mono_draw_vertical_line(x + offset_y,
					y, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x + offset_x,
					y, offset_y + 1, color);
		}

		/* Update error value and step offset_y when required. */
		if (error < 0) {
			error += ((offset_x << 2) + 6);
		} else {
			error += (((offset_x - offset_y) << 2) + 10);
			--offset_y;
		}

		/* Next X. */
		++offset_x;
	}
}

/**
 * \brief Put bitmap from FLASH or RAM to display
 *
 * This function will output bitmap data from FLASH or RAM.
 * The bitmap y-coordinate will be aligned with display pages, rounded down.
 * Ie: placing a bitmap at x=10, y=5 will put the bitmap at x = 10,y = 0 and
 * placing a bitmap at x = 10, y = 10 will put the bitmap at x = 10, y = 8
 *
 */
void gfx_mono_generic_put_bitmap(struct gfx_mono_bitmap *bitmap, gfx_coord_t x,
		gfx_coord_t y)
{
	gfx_coord_t num_pages = bitmap->height / 8;
	gfx_coord_t page = y / 8;
	gfx_coord_t column;
	gfx_coord_t i;
	gfx_mono_color_t temp;

	switch (bitmap->type) {
	case GFX_MONO_BITMAP_PROGMEM:
		for (i = 0; i < num_pages; i++) {
			for (column = 0; column < bitmap->width; column++) {
				temp = PROGMEM_READ_BYTE(bitmap->data.progmem
						+ (i * bitmap->width)
						+ column);
				gfx_mono_put_byte(i + page, column + x, temp);
			}
		}
		break;

	case GFX_MONO_BITMAP_RAM:
		for (i = 0; i < num_pages; i++) {
			gfx_mono_put_page(bitmap->data.pixmap
					+ (i * bitmap->width), page + i, x,
					bitmap->width);
		}
		break;

	default:
		break;
	}
}

//from ASF file gfx_mono_text.c
#include "stddef.h"
#include "assert.h"

#ifndef CONFIG_FONT_PIXELS_PER_BYTE
# define CONFIG_FONT_PIXELS_PER_BYTE    8
#endif

#define EXTMEM_BUF_SIZE                 20
/**
 * \internal
 * \brief Helper function that draws a character from a font in progmem
 *        to the display
 *
 * This function will first calculate the start offset in the font character
 * data before iterating over the specific character data.
 *
 * Only pixels in the character that should be enabled are done so, the caller
 * is required to prepare the drawing area before printing a character to it.
 * This is done by the gfx_mono_draw_string() and
 * gfx_mono_draw_progmem_string() functions.
 *
 * \param[in] ch       Character to be drawn
 * \param[in] x        X coordinate on screen.
 * \param[in] y        Y coordinate on screen.
 * \param[in] font     Font to draw character in
 */
static void gfx_mono_draw_char_progmem(const char ch, const gfx_coord_t x,
		const gfx_coord_t y, const struct font *font)
{
	uint8_t PROGMEM_PTR_T glyph_data;
	uint16_t glyph_data_offset;
	uint8_t char_row_size;
	uint8_t rows_left;
	uint8_t i;

	/* Sanity check on parameters, assert if font is NULL. */
	if(font == NULL) return;

	gfx_coord_t inc_x = x;
	gfx_coord_t inc_y = y;

	char_row_size = font->width / CONFIG_FONT_PIXELS_PER_BYTE;
	if (font->width % CONFIG_FONT_PIXELS_PER_BYTE) {
		char_row_size++;
	}

	glyph_data_offset = char_row_size * font->height *
			((uint8_t)ch - font->first_char);
	glyph_data = font->data.progmem + glyph_data_offset;
	rows_left = font->height;

	do {
		uint8_t glyph_byte = 0;
		uint8_t pixelsToDraw = font->width;

		for (i = 0; i < pixelsToDraw; i++) {
			if (i % CONFIG_FONT_PIXELS_PER_BYTE == 0) {
				glyph_byte = PROGMEM_READ_BYTE(glyph_data);
				glyph_data++;
			}

			if ((glyph_byte & 0x80)) {
				gfx_mono_draw_pixel(inc_x, inc_y,
						GFX_PIXEL_SET);
			}

			inc_x += 1;
			glyph_byte <<= 1;
		}

		inc_y += 1;
		inc_x = x;
		rows_left--;
	} while (rows_left > 0);
}

/**
 * \brief Draws a character to the display
 *
 * \param[in] c        Character to be drawn
 * \param[in] x        X coordinate on screen.
 * \param[in] y        Y coordinate on screen.
 * \param[in] font     Font to draw character in
 */
void gfx_mono_draw_char(const char c, const gfx_coord_t x, const gfx_coord_t y,
		const struct font *font)
{
	gfx_mono_draw_filled_rect(x, y, font->width, font->height,
			GFX_PIXEL_CLR);

	switch (font->type) {
	case FONT_LOC_PROGMEM:
		gfx_mono_draw_char_progmem(c, x, y, font);
		break;

	default:
		/* Unsupported mode, call assert */
		return;
		break;
	}
}

/**
 * \brief Draws a string to the display
 *
 * This function will draw a string located in memory to the display.
 *
 * \param[in] str       Pointer to string
 * \param[in] x         X coordinate on screen.
 * \param[in] y         Y coordinate on screen.
 * \param[in] font      Font to draw string in
 */
void gfx_mono_draw_string(const char *str, gfx_coord_t x, gfx_coord_t y,
		const struct font *font)
{
	/* Save X in order to know where to return to on CR. */
	const gfx_coord_t start_of_string_position_x = x;

	/* Sanity check on parameters, assert if str or font is NULL. */
	if(str == NULL) return;
	if(font == NULL) return;

	/* Draw characters until trailing null byte */
	do {
		/* Handle '\n' as newline, draw normal characters. */
		if (*str == '\n') {
			x = start_of_string_position_x;
			y += font->height + 1;
		} else if (*str == '\r') {
			/* Skip '\r' characters. */
		} else {
			gfx_mono_draw_char(*str, x, y, font);
			x += font->width;
		}
	} while (*(++str));
}

/**
 * \brief Draws a string located in program memory to the display
 *
 * This function will draw a string located in program memory to the display,
 * this differs from gfx_mono_draw_string() by using constant string data from
 * the program memory instead of string data in RAM.
 *
 * Using program memory for constant strings will reduce the applications need
 * for RAM, and thus lower the overall size footprint.
 *
 * \param[in] str       Pointer to string located in program memory
 * \param[in] x         X coordinate on screen.
 * \param[in] y         Y coordinate on screen.
 * \param[in] font      Font to draw string in
 */
void gfx_mono_draw_progmem_string(char PROGMEM_PTR_T str, gfx_coord_t x,
		gfx_coord_t y, const struct font *font)
{
	char temp_char;

	/* Sanity check on parameters, assert if str or font is NULL. */
	if(str == NULL) return;
	if(font == NULL) return;

	/* Save X in order to know where to return to on CR. */
	const gfx_coord_t start_of_string_position_x = x;

	/* Draw characters until trailing null byte */
	temp_char = PROGMEM_READ_BYTE((uint8_t PROGMEM_PTR_T)str);

	while (temp_char) {
		/* Handle '\n' as newline, draw normal characters. */
		if (temp_char == '\n') {
			x = start_of_string_position_x;
			y += font->height + 1;
		} else if (temp_char == '\r') {
			/* Skip '\r' characters. */
		} else {
			gfx_mono_draw_char(temp_char, x, y, font);
			x += font->width;
		}

		temp_char = PROGMEM_READ_BYTE((uint8_t PROGMEM_PTR_T)(++str));
	}
}

/**
 * \brief Computes the bounding box of a string
 *
 * \note If string is empty the returned width will be 1 pixel and the height
 * equal to the font height.
 *
 * \param[in] str      String to calculate bounding box for
 * \param[in] font     Font used
 * \param[in] width    Pointer to width result
 * \param[in] height   Pointer to height result
 */
void gfx_mono_get_string_bounding_box(const char *str, const struct font *font,
		gfx_coord_t *width, gfx_coord_t *height)
{
	gfx_coord_t font_width = font->width;
	gfx_coord_t font_height = font->height;

	gfx_coord_t max_width = 1;
	gfx_coord_t max_height = font_height;
	gfx_coord_t x = 0;

	/* Sanity check on parameters, assert if str or font is NULL. */
	if(str == NULL) return;
	if(font == NULL) return;

	/* Handle each character until trailing null byte */
	do {
		/* Handle '\n' as newline, draw normal characters. */
		if (*str == '\n') {
			x = 0;
			max_height += font_height;
		} else if (*str == '\r') {
			/* Skip '\r' characters. */
		} else {
			x += font_width;
			if (x > max_width) {
				max_width = x;
			}
		}
	} while (*(++str));

	/* Return values through references */
	*width = max_width;
	*height = max_height;
}

/**
 * \brief Computes the bounding box of a string located in program memory
 *
 * \note If string is empty the returned width will be 1 pixel and the height
 * equal to the font height.
 *
 * \param[in] str      String in program memory to calculate bounding box for
 * \param[in] font     Font used
 * \param[in] width    Pointer to width result
 * \param[in] height   Pointer to height result
 */
void gfx_mono_get_progmem_string_bounding_box(char PROGMEM_PTR_T str,
		const struct font *font, gfx_coord_t *width,
		gfx_coord_t *height)
{
	gfx_coord_t font_width = font->width;
	gfx_coord_t font_height = font->height;

	char temp_char;
	gfx_coord_t max_width = 1;
	gfx_coord_t max_height = font_height;
	gfx_coord_t x = 0;

	/* Sanity check on parameters, assert if str or font is NULL. */
	if(str == NULL) return;
	if(font == NULL) return;

	/* Handle each character until trailing null byte */
	temp_char = PROGMEM_READ_BYTE((uint8_t PROGMEM_PTR_T)str);

	while (temp_char) {
		/* Handle '\n' as newline, draw normal characters. */
		if (temp_char == '\n') {
			x = 0;
			max_height += font_height;
		} else if (*str == '\r') {
			/* Skip '\r' characters. */
		} else {
			x += font_width;
			if (x > max_width) {
				max_width = x;
			}
		}

		temp_char = PROGMEM_READ_BYTE((uint8_t PROGMEM_PTR_T)(++str));
	}

	/* Return values through references */
	*width = max_width;
	*height = max_height;
}

//from ASF file gfx_mono_ug2832hsweg04.c
//
/* If we are using a serial interface without readback, use framebuffer */

#ifdef CONFIG_SSD1306_FRAMEBUFFER
static uint8_t framebuffer[GFX_MONO_LCD_FRAMEBUFFER_SIZE];
#endif

/**
 * \brief Initialize SSD1306 controller and LCD display.
 * It will also write the graphic controller RAM to all zeroes.
 *
 * \note This function will clear the contents of the display.
 */
void gfx_mono_ssd1306_init(void)
{
	uint8_t page;
	uint8_t column;

#ifdef CONFIG_SSD1306_FRAMEBUFFER
	gfx_mono_set_framebuffer(framebuffer);
#endif

	/* Initialize the low-level display controller. */
	ssd1306_init();

	/* Set display to output data from line 0 */
	ssd1306_set_display_start_line_address(0);

	/* Clear the contents of the display.
	 * If using a framebuffer (SPI interface) it will both clear the
	 * controller memory and the framebuffer.
	 */
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		for (column = 0; column < GFX_MONO_LCD_WIDTH; column++) {
			gfx_mono_ssd1306_put_byte(page, column, 0x00, true);
		}
	}
}

#ifdef CONFIG_SSD1306_FRAMEBUFFER
/**
 * \brief Put framebuffer to LCD controller
 *
 * This function will output the complete framebuffer from RAM to the
 * LCD controller.
 *
 * \note This is done automatically if using the graphic primitives. Only
 * needed if you are manipulating the framebuffer directly in your code.
 */
void gfx_mono_ssd1306_put_framebuffer(void)
{
	uint8_t page;

	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		ssd1306_set_page_address(page);
		ssd1306_set_column_address(0);
		gfx_mono_ssd1306_put_page(framebuffer
				+ (page * GFX_MONO_LCD_WIDTH), page, 0,
				GFX_MONO_LCD_WIDTH);
	}
}
#endif

/**
 * \brief Draw pixel to screen
 *
 * \param[in] x         X coordinate of the pixel
 * \param[in] y         Y coordinate of the pixel
 * \param[in] color     Pixel operation
 *
 * The following will set the pixel at x=10,y=10:
 * \code
	gfx_mono_ssd1306_draw_pixel(10, 10, GFX_PIXEL_SET);
\endcode
 * The following example will clear the pixel at x=10,y=10:
 * \code
	gfx_mono_ssd1306_draw_pixel(10, 10, GFX_PIXEL_CLR);
\endcode
 * And the following will toggle the pixel at x=10,y=10:
 * \code
	gfx_mono_ssd1306_draw_pixel(10, 10, GFX_PIXEL_XOR);
\endcode
 */
void gfx_mono_ssd1306_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t color)
{
	uint8_t page;
	uint8_t pixel_mask;
	uint8_t pixel_value;

	/* Discard pixels drawn outside the screen */
	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	/*
	 * Read the page containing the pixel in interest, then perform the
	 * requested action on this pixel before writing the page back to the
	 * display.
	 */
	pixel_value = gfx_mono_get_byte(page, x);

	switch (color) {
	case GFX_PIXEL_SET:
		pixel_value |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		pixel_value &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		pixel_value ^= pixel_mask;
		break;

	default:
		break;
	}

	gfx_mono_put_byte(page, x, pixel_value);
}

/**
 * \brief Get the pixel value at x,y
 *
 * \param[in] x      X coordinate of pixel
 * \param[in] y      Y coordinate of pixel
 * \return Non zero value if pixel is set.
 *
 * The following example will read the pixel value from x=10,y=10:
 * \code
	pixelval = gfx_mono_ssd1306_get_pixel(10,10);
\endcode
 */
uint8_t gfx_mono_ssd1306_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
	uint8_t page;
	uint8_t pixel_mask;

	if ((x > GFX_MONO_LCD_WIDTH - 1) || (y > GFX_MONO_LCD_HEIGHT - 1)) {
		return 0;
	}

	page = y / GFX_MONO_LCD_PIXELS_PER_BYTE;
	pixel_mask = (1 << (y - (page * 8)));

	return gfx_mono_get_byte(page, x) & pixel_mask;
}

/**
 * \brief Put a page from RAM to display controller.
 *
 * If the controller is accessed by the SPI interface, we can not read
 * back data from the LCD controller RAM. Because of this all data that is
 * written to the LCD controller in this mode is also written to a framebuffer
 * in MCU RAM.
 *
 * \param[in] data Pointer to data to be written
 * \param[in] page Page address
 * \param[in] column Offset into page (x coordinate)
 * \param[in] width Number of bytes to be written.
 *
 * The following example will write 32 bytes from data_buf to the page 0,
 * column 10. This will place data_buf in the rectangle x1=10,y1=0,x2=42,y2=8
 * (10 pixels from the upper left corner of the screen):
 * \code
	gfx_mono_ssd1306_put_page(data_buf, 0, 10, 32);
\endcode
 */
void gfx_mono_ssd1306_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t column, gfx_coord_t width)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	gfx_mono_framebuffer_put_page(data, page, column, width);
#endif
	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	do {
		ssd1306_write_data(*data++);
	} while (--width);
}

/**
 * \brief Read a page from the LCD controller
 *
 * If the LCD controller is accessed by the SPI interface we cannot read
 * data directly from the controller. In that case we will read the data from
 * the local framebuffer instead.
 *
 * \param[in] data   Pointer where to store the read data
 * \param[in] page   Page address
 * \param[in] column Offset into page (x coordinate)
 * \param[in] width  Number of bytes to be read
 *
 * The following example will read back the first 128 bytes (first page) from
 * the display memory:
 * \code
	gfx_mono_ssd1306_get_page(read_buffer, 0, 0, 128);
\endcode
 */
void gfx_mono_ssd1306_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t column, gfx_coord_t width)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	gfx_mono_framebuffer_get_page(data, page, column, width);
#else
	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	do {
		*data++ = ssd1306_read_data();
	} while (--width);
#endif
}

/**
 * \brief Put a byte to the display controller RAM
 *
 * If the LCD controller is accessed by the SPI interface we will also put the
 * data to the local framebuffer.
 *
 * \param[in] page Page address
 * \param[in] column Page offset (x coordinate)
 * \param[in] data Data to be written
 * \param[in] force Forces the write
 *
 * This example will put the value 0xFF to the first byte in the display memory
 * setting a 8 pixel high column of pixels in the upper left corner of the
 * display.
 * \code
	gfx_mono_ssd1306_put_byte(0, 0, 0xFF, false);
\endcode
  */
 void gfx_mono_ssd1306_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data, unsigned char force)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	if (!force && data == gfx_mono_framebuffer_get_byte(page, column)) {
		return;
	}
	gfx_mono_framebuffer_put_byte(page, column, data);
#endif

	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	ssd1306_write_data(data);
}

/**
 * \brief Get a byte from the display controller RAM
 *
 * If the LCD controller is accessed by the SPI interface we cannot read the
 * data. In this case return the data from the local framebuffer instead.
 *
 * \param[in] page Page address
 * \param[in] column Page offset (x coordinate)
 * \return data from LCD controller or framebuffer.
 *
 * The following code will read the first byte from the display memory or the
 * local framebuffer if direct read is not possible. The data represents the
 * pixels from x = 0 and y = 0 to y = 7.
 * \code
	data = gfx_mono_ssd1306_get_byte(0, 0);
\endcode
 */
uint8_t gfx_mono_ssd1306_get_byte(gfx_coord_t page, gfx_coord_t column)
{
#ifdef CONFIG_SSD1306_FRAMEBUFFER
	return gfx_mono_framebuffer_get_byte(page, column);

#else
	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);

	return ssd1306_read_data();

#endif
}

/**
 * \brief Read/Modify/Write a byte on the display controller
 *
 * This function will read the byte from the display controller (or the
 * framebuffer if we cannot read directly from the controller) and
 * do a mask operation on the byte according to the pixel operation selected
 * by the color argument and the pixel mask provided.
 *
 * \param[in] page Page address
 * \param[in] column Page offset (x coordinate)
 * \param[in] pixel_mask Mask for pixel operation
 * \param[in] color Pixel operation
 *
 * A small example that will XOR the first byte of display memory with 0xAA
 * \code
	gfx_mono_ssd1306_mask_byte(0,0,0xAA,GFX_PIXEL_XOR);
\endcode
 */
void gfx_mono_ssd1306_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color)
{
	gfx_mono_color_t temp = gfx_mono_get_byte(page, column);

	switch (color) {
	case GFX_PIXEL_SET:
		temp |= pixel_mask;
		break;

	case GFX_PIXEL_CLR:
		temp &= ~pixel_mask;
		break;

	case GFX_PIXEL_XOR:
		temp ^= pixel_mask;
		break;

	default:
		break;
	}

	gfx_mono_put_byte(page, column, temp);
}


