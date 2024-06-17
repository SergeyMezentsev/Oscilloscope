#include "stm32f4xx_hal.h"
#include "ui.h"
#include "st7735.h"
#include "gfx.h"
#include "markers.h"
#include "menu.h"
#include "sideMarkers.h"
#include "ADC.h"
#include "graphic.h"

void initDisplay(SPI_HandleTypeDef* hspi) {

    ST7735_initR(INITR_BLACKTAB, hspi); // Initialize the LCD
    setRotation(1);                     // set the orientation (rotation) 
    clearDisplay();

}

void createBottomMarkers() {
	createBottomMarkerArray();
	setDefaultBottomMarkers();
}

static void drawGrid() {

    // Grid for graphics
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
}

void createDefaultScreen() {
	drawGrid();
	drawBottomMarkers();
	drawSideMarkers();
}

void handleRunningMarker() {
	updateRunningMarker();
}

void handleBottomMarkers() {
	updateBottomMarkers();
}

void createMenu() {
	drawMenu();
}

void handleMenu() {
	udpateMenu();
}

void cleanMenu() {
	cleanMenuScreen();
}

void createSideMarkers() {
	createSideMarkerArray();
	setDefaultSideMarkers();
}

void handleSideMarkers() {
	updateSideMarkers();
}

void createADC() {
	createADCArray();
}

void handleADC() {
	getNewADCMeasures();
}

void createGraphic() {
	createPointArrays();
}

void handleGraphic() {
	updateGraphic();
}








