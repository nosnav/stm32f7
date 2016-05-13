#include "stm32f7_lcd.h"

/* Private structures, variables and functions */
static void LCD_INT_InitLTDC(void);
static void LCD_INT_InitLayers(void);
static void LCD_INT_InitPins(void);

/* Private variables */
static LTDC_HandleTypeDef LTDCHandle;

/* Private structure */
typedef struct _LCD_INT_t {
	uint16_t Width;
	uint16_t Height;
	uint16_t CurrentWidth;
	uint16_t CurrentHeight;
	uint8_t Orientation;
	uint32_t CurrentFrameBuffer;
	uint32_t FrameStart;
	uint32_t FrameOffset;
	uint8_t CurrentLayer;
	
	/* Strings */
	uint32_t ForegroundColor;
	uint32_t BackgroundColor;
	FONT_t* CurrentFont;
	uint16_t CurrentX;
	uint16_t StartX;
	uint16_t CurrentY;
} LCD_INT_t;
static LCD_INT_t LCD;

LCD_Result_t LCD_Init(void) {
	DMA2DGRAPHIC_INT_Conf_t DMA2DConf;
	
	/* Init SDRAM */
	if (!SDRAM_Init()) {
		/* Return error */
		return LCD_Result_SDRAM_Error;
	}
	
	/* Fill default structure */
	LCD.Width = LCD_PIXEL_WIDTH;
	LCD.Height = LCD_PIXEL_HEIGHT;
	LCD.CurrentFrameBuffer = LCD_FRAME_BUFFER;
	LCD.FrameStart = LCD_FRAME_BUFFER;
	LCD.FrameOffset = LCD_BUFFER_OFFSET;
	LCD.CurrentFont = &Font_11x18;
	LCD.ForegroundColor = 0x0000;
	LCD.BackgroundColor = 0xFFFF;
	LCD.Orientation = 1;
	
	/* Set orientation */
	LCD_SetOrientation(LCD.Orientation);
	
	/* Set configrations for DMA2D */
	DMA2DConf.BufferStart = LCD_FRAME_BUFFER;
	DMA2DConf.BufferOffset = LCD_BUFFER_OFFSET;
	DMA2DConf.BytesPerPixel = LCD_PIXEL_SIZE;
	DMA2DConf.Width = LCD_PIXEL_WIDTH;
	DMA2DConf.Height = LCD_PIXEL_HEIGHT;
	DMA2DConf.Orientation = 1;
	
	/* Init LCD pins */
	LCD_INT_InitPins();
	
	/* Init LTDC peripheral */
	LCD_INT_InitLTDC();
	
	/* Init LTDC layers */
	LCD_INT_InitLayers();
	
	/* Init DMA2D GRAPHICS */
	DMA2DGRAPHIC_Init();
	
	/* Set settings */
	INT_DMA2DGRAPHIC_SetConf(&DMA2DConf);
	
	/* Enable LCD */
	LCD_DisplayOn();
	
	/* Set layer 1 as active layer */
	LCD_SetLayer1();
	LCD_Fill(LCD_COLOR_WHITE);
	LCD_SetLayer2();
	LCD_Fill(LCD_COLOR_WHITE);
	LCD_SetLayer1();
	
	/* Set layer 1 as active layer */
	LCD_SetLayer1Opacity(255);
	LCD_SetLayer2Opacity(0);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_Fill(uint32_t color) {
	/* Erase memory */
	DMA2DGRAPHIC_Fill(color);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_SetOrientation(uint8_t orientation) {
	/* Check input */
	if (orientation > 3) {
		return LCD_Result_Error;
	}
	
	/* Save rotation */
	LCD.Orientation = orientation;
	
	/* Check X and Y values */
	if (
		orientation == 0 ||
		orientation == 1
	) {
		LCD.CurrentHeight = LCD.Height;
		LCD.CurrentWidth = LCD.Width;
	} else {
		LCD.CurrentHeight = LCD.Width;
		LCD.CurrentWidth = LCD.Height;
	}
	
	/* Rotate DMA2D graphic library */
	DMA2DGRAPHIC_SetOrientation(orientation);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DisplayOn(void) {
	/* Enable LTDC */
	LTDC->GCR |= LTDC_GCR_LTDCEN;
	
	/* Set PIN high */
	GPIO_SetPinHigh(GPIOI, GPIO_PIN_12);	
    GPIO_SetPinHigh(GPIOK, GPIO_PIN_3);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DisplayOff(void) {
	/* Disable LTDC */
	LTDC->GCR &= ~LTDC_GCR_LTDCEN;
	
	/* Set PIN low */
	GPIO_SetPinLow(GPIOI, GPIO_PIN_12);	
    GPIO_SetPinLow(GPIOK, GPIO_PIN_3);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_SetXY(uint16_t X, uint16_t Y) {
	/* Check if we are inside LCD */
	if (X >= LCD.CurrentWidth || Y >= LCD.CurrentHeight) {
		return LCD_Result_Error;
	}
	
	/* Set new values */
	LCD.CurrentX = X;
	LCD.CurrentY = Y;
	LCD.StartX = X;
	
	/* Return OK */
	return LCD_Result_Ok;
}

uint16_t LCD_GetCurrentX(void) {
	/* Return current X location for strings */
	return LCD.CurrentX;
}

uint16_t LCD_GetCurrentY(void) {
	/* Return current Y location for strings */
	return LCD.CurrentY;
}

LCD_Result_t LCD_SetFont(FONT_t* Font) {
	/* Set new font used for drawing */
	LCD.CurrentFont = Font;
	
	/* Return OK */
	return LCD_Result_Ok;
}

FONT_t* LCD_GetFont(void) {
	/* Return pointer to font */
	return LCD.CurrentFont;
}

LCD_Result_t LCD_SetColors(uint32_t Foreground, uint32_t Background) {
	/* Set new colors */
	LCD.ForegroundColor = Foreground;
	LCD.BackgroundColor = Background;
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_Putc(char c) {
	uint32_t i, b, j;
	
	/* Check current coordinates */
	if ((LCD.CurrentX + LCD.CurrentFont->FontWidth) >= LCD.CurrentWidth || c == '\n') {
		/* If at the end of a line of display, go to new line and set x to 0 position */
		LCD.CurrentY += LCD.CurrentFont->FontHeight;
		LCD.CurrentX = LCD.StartX;
		
		/* Check X */
		if ((LCD.CurrentX + LCD.CurrentFont->FontWidth) >= LCD.CurrentWidth) {
			LCD.CurrentX = 0;
		}
		
		/* Check for Y position */
		if (LCD.CurrentY >= LCD.CurrentHeight) {
			/* Return error */
			return LCD_Result_Error;
		}
	}
	
	/* Draw character */
	if (c != '\n') {
		/* Draw all pixels */
		for (i = 0; i < LCD.CurrentFont->FontHeight; i++) {
			b = LCD.CurrentFont->data[(c - 32) * LCD.CurrentFont->FontHeight + i];
			for (j = 0; j < LCD.CurrentFont->FontWidth; j++) {
				if ((b << j) & 0x8000) {
					DMA2DGRAPHIC_DrawPixel(LCD.CurrentX + j, (LCD.CurrentY + i), LCD.ForegroundColor);
				} else {
					DMA2DGRAPHIC_DrawPixel(LCD.CurrentX + j, (LCD.CurrentY + i), LCD.BackgroundColor);
				}
			}
		}
	
		/* Set new current X location */
		LCD.CurrentX += LCD.CurrentFont->FontWidth;
	}
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DrawPixel(uint16_t X, uint16_t Y, uint32_t color) {
	/* Draw pixel at desired location */
	DMA2DGRAPHIC_DrawPixel(X, Y, color);
	
	/* Return OK */
	return LCD_Result_Ok;
}

uint32_t LCD_GetPixel(uint16_t X, uint16_t Y) {
	/* Get pixel at desired location */
	return DMA2DGRAPHIC_GetPixel(X, Y);
}

LCD_Result_t LCD_Puts(char* str) {
	/* Send till string ends or error returned */
	while (*str) {
		/* Check if string OK */
		if (LCD_Putc(*str) != LCD_Result_Ok) {
			/* Return error */
			return LCD_Result_Error;
		}
		
		/* Increase pointer */
		str++;
	}
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_SetLayer1(void) {
	/* Fill settings */
	LCD.CurrentFrameBuffer = LCD.FrameStart;
	LCD.CurrentLayer = 0;
	
	/* Set layer for DMA2D */
	DMA2DGRAPHIC_SetLayer(LCD.CurrentLayer);
	
	/* Return OK */
	return LCD_Result_Ok;

}

LCD_Result_t LCD_SetLayer2(void) {
	/* Fill settings */
	LCD.CurrentFrameBuffer = LCD.FrameStart + LCD.FrameOffset;
	LCD.CurrentLayer = 1;
	
	/* Set layer for DMA2D also */
	DMA2DGRAPHIC_SetLayer(LCD.CurrentLayer);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_SetLayer1Opacity(uint8_t opacity) {
	/* Set opacity */
	HAL_LTDC_SetAlpha(&LTDCHandle, opacity, 0);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_SetLayer2Opacity(uint8_t opacity) {
	/* Set opacity */
	HAL_LTDC_SetAlpha(&LTDCHandle, opacity, 1);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_ChangeLayers(void) {
	/* Change layers */
	if (LCD.CurrentLayer == 0) {
		LCD_SetLayer2();
		LCD_SetLayer1Opacity(0);
		LCD_SetLayer2Opacity(255);
	} else {
		LCD_SetLayer1();
		LCD_SetLayer1Opacity(255);
		LCD_SetLayer2Opacity(0);
	}
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_Layer2To1(void) {
	/* Copy buffer using DMA2D */
	DMA2DGRAPHIC_CopyBuffer(
		(void *)(LCD.FrameStart),
		(void *)(LCD.FrameStart + LCD.FrameOffset),
		LCD.Height,
		LCD.Width,
		0,
		0
	);

	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_Layer1To2(void) {
	/* Copy buffer using DMA2D */
	DMA2DGRAPHIC_CopyBuffer(
		(void *)(LCD.FrameStart),
		(void *)(LCD.FrameStart + LCD.FrameOffset),
		LCD.Width,
		LCD.Height,
		0,
		0
	);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color) {
	/* Draw line with DMA2D */
	DMA2DGRAPHIC_DrawLine(x0, y0, x1, y1, color);
	
	/* Return OK */
	return LCD_Result_Ok;
}


LCD_Result_t LCD_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint32_t color) {
	/* Use DMA2D for drawing */
	DMA2DGRAPHIC_DrawRectangle(x0, y0, Width, Height, color);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DrawRoundedRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint16_t r, uint32_t color) {
	/* Check input parameters */
	if ((x0 + Width) > LCD.Width || (y0 + Height) > LCD.Height) {
		/* Return error */
		return LCD_Result_Error;
	}
	
	/* Draw rectangle with DMA2D */
	DMA2DGRAPHIC_DrawRoundedRectangle(x0, y0, Width, Height, r, color);

	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DrawFilledRoundedRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint16_t r, uint32_t color) {
	/* Check input parameters */
	DMA2DGRAPHIC_DrawFilledRoundedRectangle(x0, y0, Width, Height, r, color);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DrawFilledRectangle(uint16_t x0, uint16_t y0, uint16_t Width, uint16_t Height, uint32_t color) {
	/* Draw with DMA2D */
	DMA2DGRAPHIC_DrawFilledRectangle(x0, y0, Width, Height, color);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) {
	/* Use DMA2D */
	DMA2DGRAPHIC_DrawCircle(x0, y0, r, color);
	
	/* Return OK */
	return LCD_Result_Ok;
}

LCD_Result_t LCD_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) {
	/* Use DMA2D */
	DMA2DGRAPHIC_DrawFilledCircle(x0, y0, r, color);
	
	/* Return OK */
	return LCD_Result_Ok;
}


uint16_t LCD_GetWidth(void) {
	return LCD.CurrentWidth;
}

uint16_t LCD_GetHeight(void) {
	return LCD.CurrentHeight;
}

uint32_t LCD_GetFrameBuffer(void) {
	return LCD.FrameStart;
}

uint8_t LCD_GetOrientation(void) {
	return LCD.Orientation;
}

/* Private functions */
static void LCD_INT_InitLTDC(void) {
	RCC_PeriphCLKInitTypeDef  periph_clk_init_struct;
	
	/* Enable LTDC and DMA2D clocks */
	__HAL_RCC_DMA2D_CLK_ENABLE();
	__HAL_RCC_LTDC_CLK_ENABLE();
	
	/* Disable LTDC */
	LTDC->GCR &= ~LTDC_GCR_LTDCEN;

    /* Timing configuration */     
    LTDCHandle.Init.HorizontalSync = LCD_HSYNC - 1;
    LTDCHandle.Init.VerticalSync = LCD_VSYNC - 1;
    LTDCHandle.Init.AccumulatedHBP = LCD_HSYNC + LCD_HBP - 1;
    LTDCHandle.Init.AccumulatedVBP = LCD_VSYNC + LCD_VBP - 1;  
    LTDCHandle.Init.AccumulatedActiveH = LCD_PIXEL_HEIGHT + LCD_VSYNC + LCD_VBP - 1;
    LTDCHandle.Init.AccumulatedActiveW = LCD_PIXEL_WIDTH + LCD_HSYNC + LCD_HBP - 1;
    LTDCHandle.Init.TotalWidth = LCD_PIXEL_WIDTH + LCD_HSYNC + LCD_HBP + LCD_HFP - 1; 
    LTDCHandle.Init.TotalHeigh = LCD_PIXEL_HEIGHT + LCD_VSYNC + LCD_VBP + LCD_VFP - 1;

    /* Configure PLLSAI prescalers for LCD */
    /* Enable Pixel Clock */
    /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
    /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAI_N = 192 Mhz */
    /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAI_R = 192/2 = 96 Mhz */
    /* LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDivR = 96/4 = 24 Mhz */
	periph_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	periph_clk_init_struct.PLLSAI.PLLSAIN = 192;
	periph_clk_init_struct.PLLSAI.PLLSAIR = LCD_FREQUENCY_DIV;
	periph_clk_init_struct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
	HAL_RCCEx_PeriphCLKConfig(&periph_clk_init_struct);

	/* Initialize the LCD pixel width and pixel height */
	LTDCHandle.LayerCfg->ImageWidth  = LCD_PIXEL_WIDTH;
	LTDCHandle.LayerCfg->ImageHeight = LCD_PIXEL_HEIGHT;

	/* Background value */
	LTDCHandle.Init.Backcolor.Blue = 0;
	LTDCHandle.Init.Backcolor.Green = 0;
	LTDCHandle.Init.Backcolor.Red = 0;

	/* Polarity */
	LTDCHandle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	LTDCHandle.Init.VSPolarity = LTDC_VSPOLARITY_AL; 
	LTDCHandle.Init.DEPolarity = LTDC_DEPOLARITY_AL;  
	LTDCHandle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	LTDCHandle.Instance = LTDC;

	/* Init LTDC */
	HAL_LTDC_Init(&LTDCHandle);
}

static void LCD_INT_InitLayers(void) {
	LTDC_LayerCfgTypeDef layer_cfg;
	
	/* Layer Init */
	layer_cfg.WindowX0 = 0;
	layer_cfg.WindowX1 = LCD_PIXEL_WIDTH;
	layer_cfg.WindowY0 = 0;
	layer_cfg.WindowY1 = LCD_PIXEL_HEIGHT; 
	layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
	layer_cfg.FBStartAdress = SDRAM_START_ADR;
	layer_cfg.Alpha = 255;
	layer_cfg.Alpha0 = 0;
	layer_cfg.Backcolor.Blue = 0;
	layer_cfg.Backcolor.Green = 0;
	layer_cfg.Backcolor.Red = 0;
	layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	layer_cfg.ImageWidth = LCD_PIXEL_WIDTH;
	layer_cfg.ImageHeight = LCD_PIXEL_HEIGHT;

	/* Init layer 1 */
	HAL_LTDC_ConfigLayer(&LTDCHandle, &layer_cfg, 0);
	
	/* Config layer 2 */
	layer_cfg.Alpha = 255;
	layer_cfg.FBStartAdress = SDRAM_START_ADR + LCD_PIXEL_SIZE * LCD_PIXEL_HEIGHT * LCD_PIXEL_WIDTH;

	/* Init layer 2 */
	HAL_LTDC_ConfigLayer(&LTDCHandle, &layer_cfg, 1);
}

static void LCD_INT_InitPins(void) {
    
	/* Init GPIO pins for LTDC */
	GPIO_InitAlternate(GPIOE, GPIO_PIN_4, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast, GPIO_AF14_LTDC);
	GPIO_InitAlternate(GPIOG, GPIO_PIN_12, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast, GPIO_AF14_LTDC);
	GPIO_InitAlternate(GPIOI, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast, GPIO_AF14_LTDC);
	GPIO_InitAlternate(GPIOJ, GPIO_PIN_All & ~(GPIO_PIN_12), GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast, GPIO_AF14_LTDC);
	GPIO_InitAlternate(GPIOK, 0x00FF & ~(GPIO_PIN_3), GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_Fast, GPIO_AF14_LTDC);
	
	/* Init pins for LCD control */
	/* Display enable */
	GPIO_Init(GPIOI, GPIO_PIN_12, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_Low);
	/* Backlight control */
	GPIO_Init(GPIOK, GPIO_PIN_3, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_PuPd_DOWN, GPIO_Speed_Low);

}
