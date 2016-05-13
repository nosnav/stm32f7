#ifndef __STM32F7_LCD_H
#define __STM32F7_LCD_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx.h"
#include "stm32f7_sdram.h"
#include "stm32f7_gpio.h"
#include "stm32f7_fonts.h"
#include "stm32f7_dma2d_graphic.h"

/**
 * @defgroup LCD_Macros
 * @brief    Library defines
 * @{
 */

	/* Set pixel settings */
	#define LCD_PIXEL_WIDTH        480
	#define LCD_PIXEL_HEIGHT       272
	#define LCD_PIXEL_SIZE         2
	
	/* LCD configuration */
	#define LCD_HSYNC              41
	#define LCD_HBP                13
	#define LCD_HFP                32
	#define LCD_VSYNC              10
	#define LCD_VBP                2
	#define LCD_VFP                2
	
	/* Frequency division for LTDC */
	#define LCD_FREQUENCY_DIV      5


/* Frame settings */
#define LCD_FRAME_BUFFER           ((uint32_t)SDRAM_START_ADR)
#define LCD_BUFFER_OFFSET          ((uint32_t)(LCD_PIXEL_WIDTH * LCD_PIXEL_HEIGHT * LCD_PIXEL_SIZE))

/**
 * @defgroup LCD_Color
 * @brief    LCD Colors
 * @{
 */

#define LCD_COLOR_WHITE            0xFFFF
#define LCD_COLOR_BLACK            0x0000
#define LCD_COLOR_RED              0xF800
#define LCD_COLOR_GREEN            0x07E0
#define LCD_COLOR_GREEN2           0xB723
#define LCD_COLOR_BLUE             0x001F
#define LCD_COLOR_BLUE2            0x051D
#define LCD_COLOR_YELLOW           0xFFE0
#define LCD_COLOR_ORANGE           0xFBE4
#define LCD_COLOR_CYAN             0x07FF
#define LCD_COLOR_MAGENTA          0xA254
#define LCD_COLOR_GRAY             0x7BEF
#define LCD_COLOR_BROWN            0xBBCA

/**
 * @}
 */

/**
 * @}
 */
 
/**
 * @defgroup LCD_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  LCD result enumeration
 */
typedef enum _LCD_Result_t {
	LCD_Result_Ok = 0x00,  /*!< Everything OK */
	LCD_Result_Error,      /*!< An error occurred */
	LCD_Result_SDRAM_Error /*!< SDRAM initialization has failed */
} LCD_Result_t;

/**
 * @}
 */

/**
 * @defgroup LCD_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes LCD
 * @note   This function must be called at the beginning of LCD operations
 * @param  None
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_Init(void);

/**
 * @brief  Fills currently active layer with desired color
 * @note   To select active layer, use @ref LCD_SetLayer1() or @ref LCD_SetLayer2() functions
 * @param  color: Color index in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_Fill(uint32_t color);

/**
 * @brief  Sets display ON
 * @note   This function is already called inside @ref LCD_Init() function
 * @param  None
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DisplayOn(void);

/**
 * @brief  Sets display OFF
 * @param  None
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DisplayOff(void);

/**
 * @brief  Gets LCD width in unit of pixels
 * @param  None
 * @retval LCD width in unit of pixels 
 */
uint16_t LCD_GetWidth(void);

/**
 * @brief  Gets LCD height in unit of pixels
 * @param  None
 * @retval LCD width in unit of pixels 
 */
uint16_t LCD_GetHeight(void);

/**
 * @brief  Gets location where LCD buffer is located
 * @param  None
 * @retval Location in memory where LCD buffer is located
 */
uint32_t LCD_GetFrameBuffer(void);

/**
 * @brief  Sets LCD orientation
 * @param  orientation: LCD orientation you wanna use, values 0 to 3 are available
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_SetOrientation(uint8_t orientation);

/**
 * @brief  Gets LCD orientation
 * @retval LCD orientation
 */
uint8_t LCD_GetOrientation(void);

/**
 * @defgroup LCD_String_Functions
 * @brief    String functions
 * @{
 */

/**
 * @brief  Sets X and Y location for character drawings
 * @param  X: X coordinate for character drawings
 * @param  Y: Y coordinate for character drawings
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_SetXY(uint16_t X, uint16_t Y);

/**
 * @brief  Gets current X location for LCD strings
 * @param  None
 * @retval Current X location for string operations
 */
uint16_t LCD_GetCurrentX(void);

/**
 * @brief  Gets current Y location for LCD strings
 * @param  None
 * @retval Current Y location for string operations
 */
uint16_t LCD_GetCurrentY(void);

/**
 * @brief  Sets active font for character drawings
 * @param  *Font: Pointer to @ref FONT_t structure with font
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_SetFont(FONT_t* Font);

/**
 * @brief  Gets active font for character drawings
 * @param  None
 * @retval Pointer to @ref FONT_t structure with font
 */
FONT_t* LCD_GetFont(void);

/**
 * @brief  Sets foreground and background colors for character drawings
 * @param  Foreground: Foreground color for characters
 * @param  Background: Background color for characters
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_SetColors(uint32_t Foreground, uint32_t Background);

/**
 * @brief  Puts single character to LCD
 * @note   To set X and Y coordinate, use @ref LCD_SetXY function
 * @param  c: Character to be written on LCD
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_Putc(char c);

/**
 * @brief  Puts string to LCD
 * @note   To set X and Y coordinate, use @ref LCD_SetXY function
 * @param  *str: String to be written on LCD
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_Puts(char* str);

/**
 * @}
 */

/**
 * @defgroup LCD_GRAPHIC_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Draws single pixel to LCD
 * @param  X: X coordinate for pixel
 * @param  Y: Y coordinate for pixel
 * @param  color: Color index in RGB565 mode
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawPixel(uint16_t X, uint16_t Y, uint32_t color);

/**
 * @brief  Gets pixel index at specific coordinate
 * @param  X: X coordinate for pixel
 * @param  Y: Y coordinate for pixel
 * @retval Pixel index in RGB565 format 
 */
uint32_t LCD_GetPixel(uint16_t X, uint16_t Y);

/**
 * @brief  Draws line between 2 coordinates
 * @param  x0: First point X location
 * @param  y0: First point Y location
 * @param  x1: Second point X location
 * @param  y1: Second point Y location
 * @param  color: Color index for line in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color);

/**
 * @brief  Draws rectangle on LCD
 * @param  x0: Top left X location
 * @param  y0: Top left Y location
 * @param  Width: Rectangle width in unit of pixels
 * @param  Height: Rectangle height in unit of pixels
 * @param  color: Color index in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint32_t color);

/**
 * @brief  Draws filled rectangle on LCD
 * @param  x0: Top left X location
 * @param  y0: Top left Y location
 * @param  Width: Rectangle width in unit of pixels
 * @param  Height: Rectangle height in unit of pixels
 * @param  color: Color index in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawFilledRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint32_t color);

/**
 * @brief  Draws rounded rectangle on LCD
 * @param  x0: Top left X location
 * @param  y0: Top left Y location
 * @param  Width: Rectangle width in unit of pixels
 * @param  Height: Rectangle height in unit of pixels
 * @param  r: Radius in unit of pixels in each corner
 * @param  color: Color index in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawRoundedRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint16_t r, uint32_t color);

/**
 * @brief  Draws filled rounded rectangle on LCD
 * @param  x0: Top left X location
 * @param  y0: Top left Y location
 * @param  Width: Rectangle width in unit of pixels
 * @param  Height: Rectangle height in unit of pixels
 * @param  r: Radius in unit of pixels in each corner
 * @param  color: Color index in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawFilledRoundedRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint16_t r, uint32_t color);

/**
 * @brief  Draws circle on LCD
 * @param  x0: X coordinate of circle's center location
 * @param  y0: Y coordinate of circle's center location
 * @param  r: Radius in unit of pixels
 * @param  color: Color index in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);

/**
 * @brief  Draws filled circle on LCD
 * @param  x0: X coordinate of circle's center location
 * @param  y0: Y coordinate of circle's center location
 * @param  r: Radius in unit of pixels
 * @param  color: Color index in RGB565 format
 * @retval Member of @ref LCD_Result_t enumeration
 */
LCD_Result_t LCD_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);

/**
 * @}
 */

/**
 * @defgroup LCD_LAYER_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Sets layer 1 as active layer for drawing on LCD 
 * @param  None
 * @retval None 
 */
LCD_Result_t LCD_SetLayer1(void);

/**
 * @brief  Sets layer 2 as active layer for drawing on LCD 
 * @param  None
 * @retval None 
 */
LCD_Result_t LCD_SetLayer2(void);

/**
 * @brief  Sets layer 1 alpha value
 * @param  opacity: Alpha value as 8-bit parameter
 * @retval None
 */
LCD_Result_t LCD_SetLayer1Opacity(uint8_t opacity);

/**
 * @brief  Sets layer 2 alpha value
 * @param  opacity: Alpha value as 8-bit parameter
 * @retval None
 */
LCD_Result_t LCD_SetLayer2Opacity(uint8_t opacity);

/**
 * @brief  Changes currently visible layer on LCD
 * @param  None
 * @retval None
 */
LCD_Result_t LCD_ChangeLayers(void);

/**
 * @brief  Copies content from layer 2 to layer 1
 * @param  None
 * @retval None
 */
LCD_Result_t LCD_Layer2To1(void);

/**
 * @brief  Copies content from layer 1 to layer 2
 * @param  None
 * @retval None
 */
LCD_Result_t LCD_Layer1To2(void);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
