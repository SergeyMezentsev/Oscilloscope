#include "stm32f4xx_hal.h"
#include "spi.h"
#include "ui.h"
#include "IRQ_Handlers.h"




void scopeInit() {

	// Init TIM1 (set it in default position)
	TIM1->CNT = (uint16_t)50U;

	initDisplay(&hspi1);
	createBottomMarkers();
	createSideMarkers();
	

	

	
	



    // ST7735_initR(INITR_BLACKTAB, &hspi1); // Initialize the LCD
    // setRotation(1);                       // set the orientation (rotation)  
    // //createFramebuf();                     // Create the framebuffer for the LCD
    // clearDisplay();
    //splash(); // Splash screen
	
		//drawBitmap(0, 0, 160, 128, (uint16_t*)logo);
	
	
	
		/*
		// Main area for graphics
		drawRect(3, 2, 96, 96, ST7735_WHITE);

		drawFastVLine(19, 2, 96, ST7735_WHITE);
    drawFastVLine(35, 2, 96, ST7735_WHITE);
    drawFastVLine(51, 2, 96, ST7735_WHITE);
		drawFastVLine(67, 2, 96, ST7735_WHITE);
		drawFastVLine(83, 2, 96, ST7735_WHITE);
		drawFastVLine(98, 2, 96, ST7735_WHITE);
	
		drawFastHLine(3, 18, 96, ST7735_WHITE);
		drawFastHLine(3, 34, 96, ST7735_WHITE);
		drawFastHLine(3, 50, 96, ST7735_YELLOW);
		drawFastHLine(3, 66, 96, ST7735_WHITE);
		drawFastHLine(3, 82, 96, ST7735_WHITE);
	
		drawFastHLine(3, 98, 96, ST7735_BLACK);
		drawFastVLine(99, 2, 96, ST7735_BLACK);
		
		
		// Fields for markers
    setTextColor(ST7735_WHITE, ST7735_BLACK);
		setTextSize(1);
		
		setCursor(5, 103);
    printString("mV");
		setCursor(5, 114);
    printString("000");
		
		setCursor(38, 103);
    printString("ms");
		setCursor(38, 114);
    printString("000");
		
		setCursor(71, 103);
    printString("Att");
		setCursor(71, 114);
    printString("00");
		
		setCursor(105, 103);
    printString("kHz");
		setCursor(105, 114);
    printString("0000");
		
		
		// Arrow for the trigger
		uint8_t arrow_trigger_pos_y = 10u;
		drawPixel(99, arrow_trigger_pos_y, ST7735_YELLOW);
		drawFastVLine(100, arrow_trigger_pos_y - 1u, 2, ST7735_YELLOW);
		drawFastVLine(101, arrow_trigger_pos_y - 2u, 4, ST7735_YELLOW);
		*/
		
		
		
		
		
		
		/*
		//Additional menu settings
		// Additional markers
		
		// max
		setCursor(105, 5);
    printString("max");
		setCursor(105, 16);
    printString("0000");
		setCursor(105, 27);
    printString("mV");
		drawFastHLine(105, 35, 26, ST7735_WHITE);
		
		//min
		setCursor(105, 37);
    printString("min");
		setCursor(105, 48);
    printString("0000");
		setCursor(105, 59);
    printString("mV");
		drawFastHLine(105, 67, 26, ST7735_WHITE);
		
		//Ppk
		setCursor(105, 69);
    printString("Ppk");
		setCursor(105, 80);
    printString("0000");
		setCursor(105, 91);
    printString("mV");
		drawFastHLine(105, 101, 26, ST7735_WHITE);
		
		//Trig
		setCursor(105, 69);
    printString("Trig");
		setCursor(105, 80);
    printString("0000");
		setCursor(105, 91);
    printString("mV");
		drawFastHLine(105, 101, 26, ST7735_WHITE);
		
		//RUN	(pos 3 in the additional menu settings)
		//fillRect(108, 78, 21, 10, ST7735_GREEN);
		//setTextColor(ST7735_BLACK, ST7735_GREEN);
		//setCursor(110, 80);
    //printString("RUN");
		
		//STOP	(pos 3 in the additional menu settings)
		//fillRect(105, 78, 28, 10, ST7735_RED);
		//setTextColor(ST7735_BLACK, ST7735_RED);
		//setCursor(107, 80);
    //printString("STOP");
		
		
		//setTextColor(ST7735_WHITE, ST7735_BLACK);
		*/
		
		
		
		
		
		
		/*
		// Menu
		setTextColor(ST7735_WHITE, ST7735_BLACK);
		setTextSize(1);
		setCursor(20, 10);
    printString("MEASURE:");
		setCursor(85, 10);
    printString("STATE:");
		
		// Menu settings
		setCursor(20, 35);
    printString("MAXIMUM");
		setCursor(20, 50);
    printString("MINIMUM");
		setCursor(20, 65);
    printString("PEAK-PEAK");
		setCursor(20, 80);
    printString("TRIGGER");
		
		// 
		fillRect(83, 33, 40, 10, ST7735_GREEN);
		setTextColor(ST7735_BLACK, ST7735_GREEN);
		setCursor(85, 35);
    printString("ACTIVE");
		
		fillRect(83, 48, 45, 10, ST7735_RED);
		setTextColor(ST7735_BLACK, ST7735_RED);
		setCursor(85, 50);
    printString("DISABLE");
		
		fillRect(83, 63, 40, 10, ST7735_GREEN);
		setTextColor(ST7735_BLACK, ST7735_GREEN);
		setCursor(85, 65);
    printString("ACTIVE");
		
		fillRect(83, 78, 45, 10, ST7735_RED);
		setTextColor(ST7735_BLACK, ST7735_RED);
		setCursor(85, 80);
    printString("DISABLE");
		
		
		// cursor for menu
		uint8_t arrow_menu_pos_y = 38u;
		//arrow_menu_pos_y is neede to be moved for 15px
		drawPixel(16, arrow_menu_pos_y, ST7735_YELLOW);
		drawFastVLine(15, arrow_menu_pos_y - 1u, 2, ST7735_YELLOW);
		drawFastVLine(14, arrow_menu_pos_y - 2u, 4, ST7735_YELLOW);
		drawFastVLine(13, arrow_menu_pos_y - 3u, 6, ST7735_YELLOW);
		
		*/
		
		
		
    //flushDisplay();
		

}




void scopeLoop() {

	static uint8_t defaultScreen = 1U;

	if (menuButtonPushed == 0U) {   // We are not in menu

		if (defaultScreen == 1U) {	// draw default screen once
			cleanMenu();
			createDefaultScreen();
			defaultScreen = 0U;
		}


		if (stopButtonPushed == 0U) {	// Scope is running

			handleBottomMarkers();
			
		}

		// Scope isn't running
		handleRunningMarker();

	} else if (menuButtonPushed == 1U){	// We are in menu

		if (defaultScreen == 0U) {	// draw menu screen once
			createMenu();
			defaultScreen = 1U;
		}

		handleMenu();

	}
}