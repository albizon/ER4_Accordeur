#ifndef __OLED_H__
#define __OLED_H__

#include <stdint.h>

//****************************************************
//fonctions specifiques IUT de Nantes
//****************************************************

//initialisation de l'afficheur
// si withLogo = 0, pas de logo de démarrage (mais c'est dommage!)
void OLEDInit(unsigned char withLogo);

void OLEDClearLine(char line);

//*** fonctions pour le texte ***

//la taille des caractères est de 
// - 6 pixels de large
// - 7 pixels de haut
// => on peut mettre 4 lignes
//met le curseur en début de ligne
void OLEDSetLine(int line);

//affiche un caractere.
//si le caractère est '\n', on passe à la ligne suivante.
//si on déborde les lignes => on passe à la premiere ligne
//si on deborde les colonnes => on passe à la ligne suivante.
void OLEDPrintChar(char car);

//affiche une chaine de caractere (qui se termine par le caractere \0!).
void OLEDPrintString(char *str);

//efface l'afficheur
void OLEDClear();

//positionne le curseur pour le texte (4 lignes de 21 caractères)
// - pos: position en x en pixel depuis la gauche (chaque caractere fait 6 pixels)
// - line: numéro de ligne (de 0 à 3)
void OLEDSetTextCursor(int pos,int line);

//*** fonctions pour le graphique ***

struct point
{
	int x;
	int y;
};

/** Opération sur les pixels en mode graphique */
enum gfx_mono_color {
	GFX_PIXEL_CLR = 0, //effacement des pixels
	GFX_PIXEL_SET = 1, //affichage des pixels
	GFX_PIXEL_XOR = 2, //inversion des pixels (xor)
};

//faire une ligne (approche graphique):
//la couleur peut être:
// - GFX_PIXEL_CLR => noir
// - GFX_PIXEL_SET => blanc
// - GFX_PIXEL_XOR => les points noirs deviennent blanc et inversement.
void OLEDDrawLine(struct point point1, struct point point2, enum gfx_mono_color color);

//****************************************************
//logo IUT
extern struct gfx_mono_bitmap logoIUT;

//****************************************************
// fonctions graphiques de bas niveau
// La suite du fichier correspond aux fonctions de bas niveau
// Elles sont reprises des fichiers fournis par Atmel
// dans leurs solution 'ASF'
//
//****************************************************
//fron ASF file ssd1306.h
//! \name Fundamental Command defines
//@{
#define SSD1306_CMD_COL_ADD_SET_LSB(column)         (0x00 | (column))
#define SSD1306_CMD_COL_ADD_SET_MSB(column)         (0x10 | (column))
#define SSD1306_CMD_SET_MEMORY_ADDRESSING_MODE      0x20
#define SSD1306_CMD_SET_COLUMN_ADDRESS              0x21
#define SSD1306_CMD_SET_PAGE_ADDRESS                0x22
#define SSD1306_CMD_SET_DISPLAY_START_LINE(line)    (0x40 | (line))
#define SSD1306_CMD_SET_CONTRAST_CONTROL_FOR_BANK0  0x81
#define SSD1306_CMD_SET_CHARGE_PUMP_SETTING         0x8D
#define SSD1306_CMD_SET_SEGMENT_RE_MAP_COL0_SEG0    0xA0
#define SSD1306_CMD_SET_SEGMENT_RE_MAP_COL127_SEG0  0xA1
#define SSD1306_CMD_ENTIRE_DISPLAY_AND_GDDRAM_ON    0xA4
#define SSD1306_CMD_ENTIRE_DISPLAY_ON               0xA5
#define SSD1306_CMD_SET_NORMAL_DISPLAY              0xA6
#define SSD1306_CMD_SET_INVERSE_DISPLAY             0xA7
#define SSD1306_CMD_SET_MULTIPLEX_RATIO             0xA8
#define SSD1306_CMD_SET_DISPLAY_ON                  0xAF
#define SSD1306_CMD_SET_DISPLAY_OFF                 0xAE
#define SSD1306_CMD_SET_PAGE_START_ADDRESS(page)    (0xB0 | (page))
#define SSD1306_CMD_SET_COM_OUTPUT_SCAN_UP          0xC0
#define SSD1306_CMD_SET_COM_OUTPUT_SCAN_DOWN        0xC8
#define SSD1306_CMD_SET_DISPLAY_OFFSET              0xD3
#define SSD1306_CMD_SET_DISPLAY_CLOCK_DIVIDE_RATIO  0xD5
#define SSD1306_CMD_SET_PRE_CHARGE_PERIOD           0xD9
#define SSD1306_CMD_SET_COM_PINS                    0xDA
#define SSD1306_CMD_SET_VCOMH_DESELECT_LEVEL        0xDB
#define SSD1306_CMD_NOP                             0xE3
//@}
//! \name Graphic Acceleration Command defines
//@{
#define SSD1306_CMD_SCROLL_H_RIGHT                  0x26
#define SSD1306_CMD_SCROLL_H_LEFT                   0x27
#define SSD1306_CMD_CONTINUOUS_SCROLL_V_AND_H_RIGHT 0x29
#define SSD1306_CMD_CONTINUOUS_SCROLL_V_AND_H_LEFT  0x2A
#define SSD1306_CMD_DEACTIVATE_SCROLL               0x2E
#define SSD1306_CMD_ACTIVATE_SCROLL                 0x2F
#define SSD1306_CMD_SET_VERTICAL_SCROLL_AREA        0xA3
//@}

//! \name OLED controller write and read functions
//@{
void ssd1306_write_command(uint8_t command);

void ssd1306_write_data(uint8_t data);

/**
 * \brief Read data from the controller
 *
 * \note The controller does not support read in serial mode.
 *
 * \retval 8 bit data read from the controller
 */
static inline uint8_t ssd1306_read_data(void)
{
	return 0;
}

/**
 * \brief Read status from the controller
 *
 * \note The controller does not support read in serial mode.
 *
 * \retval 8 bit status read from the controller
 */
static inline uint8_t ssd1306_get_status(void)
{
	return 0;
}
//@}

//! \name OLED Controller reset
//@{

//! \name Sleep control
//@{
/**
 * \brief Enable the OLED sleep mode
 */
static inline void ssd1306_sleep_enable(void)
{
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_OFF);
}

/**
 * \brief Disable the OLED sleep mode
 */
static inline void ssd1306_sleep_disable(void)
{
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_ON);
}
//@}

//! \name Address setup for the OLED
//@{
/**
 * \brief Set current page in display RAM
 *
 * This command is usually followed by the configuration of the column address
 * because this scheme will provide access to all locations in the display
 * RAM.
 *
 * \param address the page address
 */
static inline void ssd1306_set_page_address(uint8_t address)
{
	// Make sure that the address is 4 bits (only 8 pages)
	address &= 0x0F;
	ssd1306_write_command(SSD1306_CMD_SET_PAGE_START_ADDRESS(address));
}

/**
 * \brief Set current column in display RAM
 *
 * \param address the column address
 */
static inline void ssd1306_set_column_address(uint8_t address)
{
	// Make sure the address is 7 bits
	address &= 0x7F;
	ssd1306_write_command(SSD1306_CMD_COL_ADD_SET_MSB(address >> 4));
	ssd1306_write_command(SSD1306_CMD_COL_ADD_SET_LSB(address & 0x0F));
}

/**
 * \brief Set the display start draw line address
 *
 * This function will set which line should be the start draw line for the OLED.
 */
static inline void ssd1306_set_display_start_line_address(uint8_t address)
{
	// Make sure address is 6 bits
	address &= 0x3F;
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_START_LINE(address));
}
//@}

//! \name Display hardware control
//@{
/**
 * \brief Turn the OLED display on
 *
 * This function will turn on the OLED.
 */
static inline void ssd1306_display_on(void)
{
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_ON);
}

/**
 * \brief Turn the OLED display off
 *
 * This function will turn off the OLED.
 */
static inline void ssd1306_display_off(void)
{
	ssd1306_write_command(SSD1306_CMD_SET_DISPLAY_OFF);
}

/**
 * \brief Set the OLED contrast level
 *
 * \param contrast a number between 0 and 0xFF
 *
 * \retval contrast the contrast value written to the OLED controller
 */
static inline uint8_t ssd1306_set_contrast(uint8_t contrast)
{
	ssd1306_write_command(SSD1306_CMD_SET_CONTRAST_CONTROL_FOR_BANK0);
	ssd1306_write_command(contrast);
	return contrast;
}

/**
 * \brief Invert all pixels on the device
 *
 * This function will invert all pixels on the OLED
 *
 */
static inline void ssd1306_display_invert_enable(void)
{
	ssd1306_write_command(SSD1306_CMD_SET_INVERSE_DISPLAY);
}

/**
 * \brief Disable invert of all pixels on the device
 *
 * This function will disable invert on all pixels on the OLED
 *
 */
static inline void ssd1306_display_invert_disable(void)
{
	ssd1306_write_command(SSD1306_CMD_SET_NORMAL_DISPLAY);
}

//init
void ssd1306_init(void);

//from ASF file gfx_mono.h
#ifndef PROGMEM_DECLARE
#  define PROGMEM_DECLARE(type, name) const type name
#  define PROGMEM_T const
#  define PROGMEM_PTR_T const *
#  define PROGMEM_READ_BYTE(x) *(x)
#  define PROGMEM_STRING_T const char*
#endif

typedef uint8_t gfx_mono_color_t;
typedef uint8_t gfx_coord_t;


/** Bitmap types */
enum gfx_mono_bitmap_type {
	/** Bitmap stored in SRAM */
	GFX_MONO_BITMAP_RAM,
	/** Bitmap stored in progmem */
	GFX_MONO_BITMAP_PROGMEM
};

#define GFX_OCTANT0     (1 << 0)
#define GFX_OCTANT1     (1 << 1)
#define GFX_OCTANT2  (1 << 2)
#define GFX_OCTANT3     (1 << 3)
#define GFX_OCTANT4     (1 << 4)
#define GFX_OCTANT5     (1 << 5)
#define GFX_OCTANT6     (1 << 6)
#define GFX_OCTANT7     (1 << 7)

#define GFX_QUADRANT0   (GFX_OCTANT0 | GFX_OCTANT1)
#define GFX_QUADRANT1   (GFX_OCTANT2 | GFX_OCTANT3)
#define GFX_QUADRANT2   (GFX_OCTANT4 | GFX_OCTANT5)
#define GFX_QUADRANT3   (GFX_OCTANT6 | GFX_OCTANT7)

#define GFX_LEFTHALF    (GFX_QUADRANT3 | GFX_QUADRANT0)
#define GFX_TOPHALF     (GFX_QUADRANT0 | GFX_QUADRANT1)
#define GFX_RIGHTHALF   (GFX_QUADRANT1 | GFX_QUADRANT2)
#define GFX_BOTTOMHALF  (GFX_QUADRANT2 | GFX_QUADRANT3)

#define GFX_WHOLE       0xFF

//from ASF file gfx_mono_text.h
/**
 * \brief Valid storage locations for font data
 *
 * Add support for fonts in regular ram
 */
enum font_data_type {
	/** Font data stored in program/flash memory. */
	FONT_LOC_PROGMEM,
};

/** Storage structure for font meta data. */
struct font {
	/** Type of storage used for binary font data. See \ref font_data_type. */
	enum font_data_type type;
	union {
		/**
		 * Pointer to where the binary font data is stored. This
		 * variable is accessed either through hugemem or progmem
		 * depending on the value of \a type.
		 */
#ifdef CONFIG_HAVE_HUGEMEM
		hugemem_ptr_t hugemem;
#endif
		uint8_t PROGMEM_PTR_T progmem;
	} data;
	/** Width of one font character, in pixels. */
	uint8_t width;
	/** Height of one font character, in pixels. */
	uint8_t height;
	/** ASCII value of first character in font set. */
	uint8_t first_char;
	/** ASCII value of last character in the set. */
	uint8_t last_char;
};

/** \name Strings and characters located in RAM */
/** @{ */
void gfx_mono_draw_char(const char c, const gfx_coord_t x, const gfx_coord_t y,
		const struct font *font);

void gfx_mono_draw_string(const char *str, const gfx_coord_t x,
		const gfx_coord_t y, const struct font *font);

void gfx_mono_get_string_bounding_box(char const *str, const struct font *font,
		gfx_coord_t *width, gfx_coord_t *height);

/** @} */

/** \name Strings located in flash */
/** @{ */
void gfx_mono_draw_progmem_string(char PROGMEM_PTR_T str, gfx_coord_t x,
		gfx_coord_t y, const struct font *font);

void gfx_mono_get_progmem_string_bounding_box(char PROGMEM_PTR_T str,
		const struct font *font, gfx_coord_t *width,
		gfx_coord_t *height);


//from ASF file sysfont.h
extern struct font sysfont;

//from ASF file gfx_mono_2832hsweg04.h
#define GFX_MONO_LCD_WIDTH              128
#ifndef GFX_MONO_LCD_HEIGHT
#       define GFX_MONO_LCD_HEIGHT             32
#endif
#define GFX_MONO_LCD_PIXELS_PER_BYTE    8
#define GFX_MONO_LCD_PAGES              (GFX_MONO_LCD_HEIGHT / \
	GFX_MONO_LCD_PIXELS_PER_BYTE)
#define GFX_MONO_LCD_FRAMEBUFFER_SIZE   ((GFX_MONO_LCD_WIDTH * \
	GFX_MONO_LCD_HEIGHT) / GFX_MONO_LCD_PIXELS_PER_BYTE)

#define gfx_mono_draw_horizontal_line(x, y, length, color) \
	gfx_mono_generic_draw_horizontal_line(x, y, length, color)

#define gfx_mono_draw_vertical_line(x, y, length, color) \
	gfx_mono_generic_draw_vertical_line(x, y, length, color)

#define gfx_mono_draw_line(x1, y1, x2, y2, color) \
	gfx_mono_generic_draw_line(x1, y1, x2, y2, color)

#define gfx_mono_draw_rect(x, y, width, height, color) \
	gfx_mono_generic_draw_rect(x, y, width, height, color)

#define gfx_mono_draw_filled_rect(x, y, width, height, color) \
	gfx_mono_generic_draw_filled_rect(x, y, width, height, \
		color)

#define gfx_mono_draw_circle(x, y, radius, color, octant_mask) \
	gfx_mono_generic_draw_circle(x, y, radius, color, \
		octant_mask)

#define gfx_mono_draw_filled_circle(x, y, radius, color, quadrant_mask)	\
	gfx_mono_generic_draw_filled_circle(x, y, radius, \
		color, quadrant_mask)

#define gfx_mono_put_bitmap(bitmap, x, y) \
	gfx_mono_generic_put_bitmap(bitmap, x, y)

#define gfx_mono_draw_pixel(x, y, color) \
	gfx_mono_ssd1306_draw_pixel(x, y, color)

#define gfx_mono_get_pixel(x, y) \
	gfx_mono_ssd1306_get_pixel(x, y)

#define gfx_mono_init()	\
	gfx_mono_ssd1306_init()

#define gfx_mono_put_page(data, page, column, width) \
	gfx_mono_ssd1306_put_page(data, page, column, width)

#define gfx_mono_get_page(data, page, column, width) \
	gfx_mono_ssd1306_get_page(data, page, column, width)

#define gfx_mono_put_byte(page, column, data) \
	gfx_mono_ssd1306_put_byte(page, column, data, 0)

#define gfx_mono_get_byte(page, column)	\
	gfx_mono_ssd1306_get_byte(page, column)

#define gfx_mono_mask_byte(page, column, pixel_mask, color) \
	gfx_mono_ssd1306_mask_byte(page, column, pixel_mask, color)

#define gfx_mono_put_framebuffer() \
	gfx_mono_ssd1306_put_framebuffer()

void gfx_mono_ssd1306_put_framebuffer(void);

void gfx_mono_ssd1306_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_ssd1306_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_ssd1306_init(void);

void gfx_mono_ssd1306_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color);

uint8_t gfx_mono_ssd1306_get_pixel(gfx_coord_t x, gfx_coord_t y);

void gfx_mono_ssd1306_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data, unsigned char force);

uint8_t gfx_mono_ssd1306_get_byte(gfx_coord_t page, gfx_coord_t column);

void gfx_mono_ssd1306_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color);

//from ASF file gfx_mono_frame_buffer.h

void gfx_mono_set_framebuffer(uint8_t *framebuffer);

void gfx_mono_framebuffer_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_framebuffer_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_framebuffer_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color);

uint8_t gfx_mono_framebuffer_get_pixel(gfx_coord_t x, gfx_coord_t y);

void gfx_mono_framebuffer_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data);

uint8_t gfx_mono_framebuffer_get_byte(gfx_coord_t page, gfx_coord_t column);

void gfx_mono_framebuffer_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color);

//from ASF file gfx_mono_generic.h

struct gfx_mono_bitmap {
	/** Width of bitmap */
	gfx_coord_t width;
	/** Height of bitmap */
	gfx_coord_t height;
	/** Bitmap type */
	enum gfx_mono_bitmap_type type;
	union {
		/** Pointer to pixels for bitmap stored in RAM */
		gfx_mono_color_t *pixmap;
		/** Pointer to pixels for bitmap stored in progmem */
		gfx_mono_color_t PROGMEM_T *progmem;
	}
	data;
};

void gfx_mono_generic_draw_horizontal_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color);

void gfx_mono_generic_draw_vertical_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color);

void gfx_mono_generic_draw_line(gfx_coord_t x1, gfx_coord_t y1,
		gfx_coord_t x2, gfx_coord_t y2,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_filled_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t octant_mask);

void gfx_mono_generic_draw_filled_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t quadrant_mask);

void gfx_mono_generic_put_bitmap(struct gfx_mono_bitmap *bitmap, gfx_coord_t x,
		gfx_coord_t y);


//from ASF file conf_sysfont.h
/** Width of each glyph, including spacer column. */
#  define SYSFONT_WIDTH           6
/** Height of each glyph, excluding spacer line. */
#  define SYSFONT_HEIGHT          7
/** Line height. */
#  define SYSFONT_LINESPACING     8
/** First character defined. */
#  define SYSFONT_FIRSTCHAR       ((uint8_t)' ')
/** Last character defined. */
#  define SYSFONT_LASTCHAR        ((uint8_t)'}')

/** Define variable containing the font */
#  define SYSFONT_DEFINE_GLYPHS \
        /* Glyph data, row by row, MSB is leftmost pixel, one byte per row. */ \
	static PROGMEM_DECLARE(uint8_t, sysfont_glyphs[]) = { \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,          /* " " */ \
		0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20,          /* "!" */ \
		0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00,          /* """ */ \
		0x50, 0x50, 0xf8, 0x50, 0xf8, 0x50, 0x50,          /* "#" */ \
		0x20, 0x78, 0xa0, 0x70, 0x28, 0xf0, 0x20,          /* "$" */ \
		0xc0, 0xc8, 0x10, 0x20, 0x40, 0x98, 0x18,          /* "%" */ \
		0x60, 0x90, 0xa0, 0x40, 0xa8, 0x90, 0x68,          /* "&" */ \
		0x60, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00,          /* "'" */ \
		0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10,          /* "(" */ \
		0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40,          /* ")" */ \
		0x00, 0x50, 0x20, 0xf8, 0x20, 0x50, 0x00,          /* "*" */ \
		0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00,          /* "+" */ \
		0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0x40,          /* "," */ \
		0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00,          /* "-" */ \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60,          /* "." */ \
		0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00,          /* "/" */ \
		0x70, 0x88, 0x98, 0xa8, 0xc8, 0x88, 0x70,          /* "0" */ \
		0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70,          /* "1" */ \
		0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xf8,          /* "2" */ \
		0xf8, 0x10, 0x20, 0x10, 0x08, 0x88, 0x70,          /* "3" */ \
		0x10, 0x30, 0x50, 0x90, 0xf8, 0x10, 0x10,          /* "4" */ \
		0xf8, 0x80, 0xf0, 0x08, 0x08, 0x88, 0x70,          /* "5" */ \
		0x30, 0x40, 0x80, 0xf0, 0x88, 0x88, 0x70,          /* "6" */ \
		0xf8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40,          /* "7" */ \
		0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70,          /* "8" */ \
		0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60,          /* "9" */ \
		0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00,          /* ":" */ \
		0x00, 0x60, 0x60, 0x00, 0x60, 0x20, 0x40,          /* ";" */ \
		0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08,          /* "<" */ \
		0x00, 0x00, 0xf8, 0x00, 0xf8, 0x00, 0x00,          /* "=" */ \
		0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80,          /* ">" */ \
		0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20,          /* "?" */ \
		0x70, 0x88, 0x08, 0x68, 0xa8, 0xa8, 0x70,          /* "@" */ \
		0x70, 0x88, 0x88, 0x88, 0xf8, 0x88, 0x88,          /* "A" */ \
		0xf0, 0x88, 0x88, 0xf0, 0x88, 0x88, 0xf0,          /* "B" */ \
		0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70,          /* "C" */ \
		0xe0, 0x90, 0x88, 0x88, 0x88, 0x90, 0xe0,          /* "D" */ \
		0xf8, 0x80, 0x80, 0xf0, 0x80, 0x80, 0xf8,          /* "E" */ \
		0xf8, 0x80, 0x80, 0xe0, 0x80, 0x80, 0x80,          /* "F" */ \
		0x70, 0x88, 0x80, 0x80, 0x98, 0x88, 0x70,          /* "G" */ \
		0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88,          /* "H" */ \
		0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,          /* "I" */ \
		0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60,          /* "J" */ \
		0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x88,          /* "K" */ \
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf8,          /* "L" */ \
		0x88, 0xd8, 0xa8, 0x88, 0x88, 0x88, 0x88,          /* "M" */ \
		0x88, 0x88, 0xc8, 0xa8, 0x98, 0x88, 0x88,          /* "N" */ \
		0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,          /* "O" */ \
		0xf0, 0x88, 0x88, 0xf0, 0x80, 0x80, 0x80,          /* "P" */ \
		0x70, 0x88, 0x88, 0x88, 0xa8, 0x90, 0x68,          /* "Q" */ \
		0xf0, 0x88, 0x88, 0xf0, 0xa0, 0x90, 0x88,          /* "R" */ \
		0x78, 0x80, 0x80, 0x70, 0x08, 0x08, 0xf0,          /* "S" */ \
		0xf8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,          /* "T" */ \
		0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,          /* "U" */ \
		0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20,          /* "V" */ \
		0x88, 0x88, 0x88, 0xa8, 0xa8, 0xd8, 0x88,          /* "W" */ \
		0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88,          /* "X" */ \
		0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20,          /* "Y" */ \
		0xf8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xf8,          /* "Z" */ \
		0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38,          /* "[" */ \
		0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00,          /* "\" */ \
		0xe0, 0x20, 0x20, 0x20, 0x20, 0x20, 0xe0,          /* "]" */ \
		0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00,          /* "^" */ \
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,          /* "_" */ \
		0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00,          /* "`" */ \
		0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78,          /* "a" */ \
		0x80, 0x80, 0xb0, 0xc8, 0x88, 0x88, 0xf0,          /* "b" */ \
		0x00, 0x00, 0x70, 0x80, 0x80, 0x88, 0x70,          /* "c" */ \
		0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x78,          /* "d" */ \
		0x00, 0x00, 0x70, 0x88, 0xf8, 0x80, 0x70,          /* "e" */ \
		0x30, 0x48, 0x40, 0xe0, 0x40, 0x40, 0x40,          /* "f" */ \
		0x00, 0x00, 0x78, 0x88, 0x78, 0x08, 0x30,          /* "g" */ \
		0x80, 0x80, 0xb0, 0xc8, 0x88, 0x88, 0x88,          /* "h" */ \
		0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70,          /* "i" */ \
		0x10, 0x00, 0x30, 0x10, 0x10, 0x90, 0x60,          /* "j" */ \
		0x40, 0x40, 0x48, 0x50, 0x60, 0x50, 0x48,          /* "k" */ \
		0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,          /* "l" */ \
		0x00, 0x00, 0xd0, 0xa8, 0xa8, 0x88, 0x88,          /* "m" */ \
		0x00, 0x00, 0xb0, 0xc8, 0x88, 0x88, 0x88,          /* "n" */ \
		0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70,          /* "o" */ \
		0x00, 0x00, 0xf0, 0x88, 0xf0, 0x80, 0x80,          /* "p" */ \
		0x00, 0x00, 0x68, 0x98, 0x78, 0x08, 0x08,          /* "q" */ \
		0x00, 0x00, 0xb0, 0xc8, 0x80, 0x80, 0x80,          /* "r" */ \
		0x00, 0x00, 0x70, 0x80, 0x70, 0x08, 0xf0,          /* "s" */ \
		0x40, 0x40, 0xe0, 0x40, 0x40, 0x48, 0x30,          /* "t" */ \
		0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68,          /* "u" */ \
		0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20,          /* "v" */ \
		0x00, 0x00, 0x88, 0x88, 0xa8, 0xa8, 0x50,          /* "w" */ \
		0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88,          /* "x" */ \
		0x00, 0x00, 0x88, 0x88, 0x78, 0x08, 0x70,          /* "y" */ \
		0x00, 0x00, 0xf8, 0x10, 0x20, 0x40, 0xf8,          /* "z" */ \
		0x10, 0x20, 0x20, 0x40, 0x20, 0x20, 0x10,          /* "{" */ \
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,          /* "|" */ \
		0x40, 0x20, 0x20, 0x10, 0x20, 0x20, 0x40,          /* "}" */ \
	};

#endif
