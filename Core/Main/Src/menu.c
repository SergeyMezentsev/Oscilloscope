#include <stdlib.h>
#include "st7735.h"
#include "gfx.h"
#include "IRQ_Handlers.h"
#include "menu.h"
#include "sideMarkers.h"

static uint8_t curMarker = 0U;
static uint8_t activatedMarkers = 0U;


static void setMenuCursor(uint8_t marker) {
    uint8_t arrow_menu_pos_y = 38u + marker * 15U;
    drawPixel(16, arrow_menu_pos_y, ST7735_YELLOW);
    drawFastVLine(15, arrow_menu_pos_y - 1u, 2, ST7735_YELLOW);
    drawFastVLine(14, arrow_menu_pos_y - 2u, 4, ST7735_YELLOW);
    drawFastVLine(13, arrow_menu_pos_y - 3u, 6, ST7735_YELLOW);
}

static void unsetMenuCursor(uint8_t marker) {
    uint8_t arrow_menu_pos_y = 38u + marker * 15U;
    drawPixel(16, arrow_menu_pos_y, ST7735_BLACK);
    drawFastVLine(15, arrow_menu_pos_y - 1u, 2, ST7735_BLACK);
    drawFastVLine(14, arrow_menu_pos_y - 2u, 4, ST7735_BLACK);
    drawFastVLine(13, arrow_menu_pos_y - 3u, 6, ST7735_BLACK);
}

static void chooseMarker(uint8_t marker) {

    if (activatedMarkers < 3U) {
        fillRect(83, 33 + marker * 15U, 45, 10, ST7735_GREEN);
        setTextColor(ST7735_BLACK, ST7735_GREEN);
        setCursor(85, 35 + marker * 15U);
        printString("ACTIVE");

        (sideMarkers + marker)->state = CHOSEN;
        activatedMarkers++;
    }

}

static void unchooseMarker(uint8_t marker) {

    fillRect(83, 33 + marker * 15U, 45, 10, ST7735_RED);
    setTextColor(ST7735_BLACK, ST7735_RED);
    setCursor(85, 35 + marker * 15U);
    printString("DISABLE");

    (sideMarkers + marker)->state = UNCHOSEN;
    activatedMarkers--;

}

void drawMenu() {

    clearDisplay();
    encoderButtonPushed = 0U;   // Otherwise some marker can be already chosen right after menu opened

    // Menu
    setTextColor(ST7735_WHITE, ST7735_BLACK);
    setTextSize(1);
    setCursor(20, 10);
    printString("MEASURE:");
    setCursor(85, 10);
    printString("STATE:");
    
    // Menu settings (chosen markers)
    setCursor(20, 35);
    printString("MAXIMUM");
    setCursor(20, 50);
    printString("MINIMUM");
    setCursor(20, 65);
    printString("PEAK-PEAK");
    setCursor(20, 80);
    printString("TRIGGER");
    
    // choices' states
    if ((sideMarkers + MAX_SIDE_MARKER)->state == CHOSEN) {
        fillRect(83, 33, 45, 10, ST7735_GREEN);
        setTextColor(ST7735_BLACK, ST7735_GREEN);
        setCursor(85, 35);
        printString("ACTIVE");
    } else {
        fillRect(83, 33, 45, 10, ST7735_RED);
        setTextColor(ST7735_BLACK, ST7735_RED);
        setCursor(85, 35);
        printString("DISABLE");
    }
    
    if ((sideMarkers + MIN_SIDE_MARKER)->state == CHOSEN) {
        fillRect(83, 48, 45, 10, ST7735_GREEN);
        setTextColor(ST7735_BLACK, ST7735_GREEN);
        setCursor(85, 50);
        printString("ACTIVE");
    } else {
        fillRect(83, 48, 45, 10, ST7735_RED);
        setTextColor(ST7735_BLACK, ST7735_RED);
        setCursor(85, 50);
        printString("DISABLE");
    }
    
    if ((sideMarkers + PPK_SIDE_MARKER)->state == CHOSEN) {
        fillRect(83, 63, 45, 10, ST7735_GREEN);
        setTextColor(ST7735_BLACK, ST7735_GREEN);
        setCursor(85, 65);
        printString("ACTIVE");
    } else {
        fillRect(83, 63, 45, 10, ST7735_RED);
        setTextColor(ST7735_BLACK, ST7735_RED);
        setCursor(85, 65);
        printString("DISABLE");
    }
    
    if ((sideMarkers + TRIG_SIDE_MARKER)->state == CHOSEN) {
        fillRect(83, 78, 45, 10, ST7735_GREEN);
        setTextColor(ST7735_BLACK, ST7735_GREEN);
        setCursor(85, 80);
        printString("ACTIVE");
    } else {
        fillRect(83, 78, 45, 10, ST7735_RED);
        setTextColor(ST7735_BLACK, ST7735_RED);
        setCursor(85, 80);
        printString("DISABLE");
    }
    
    
    // cursor for menu
    setMenuCursor(curMarker);
}

void udpateMenu () {

    if (encoderChangedPosition != 0U) {   // If the encoder has been rotated

        if (encoderDir > 0) {     // If encoder has worked and dir > 0

            if (curMarker < 3U) {
                unsetMenuCursor(curMarker);
                curMarker++;
                setMenuCursor(curMarker);
            }

        } else if (encoderDir < 0) {
            
            if (curMarker > 0U) {
                unsetMenuCursor(curMarker);
                curMarker--;
                setMenuCursor(curMarker);
            }

        }
        
        encoderChangedPosition = 0U;
    }

    if (encoderButtonPushed != 0U) {

        if ((sideMarkers + curMarker)->state == UNCHOSEN) {
            chooseMarker(curMarker);
        } else if ((sideMarkers + curMarker)->state == CHOSEN) {
            unchooseMarker(curMarker);
        }

        encoderButtonPushed = 0U;
    }
}

void cleanMenuScreen() {

    fillRect(20, 10, 100, 10, ST7735_BLACK);    // CLean the hadline

    fillRect(20, 35, 60, 10, ST7735_BLACK);     // Clean markers
    fillRect(20, 50, 60, 10, ST7735_BLACK);
    fillRect(20, 65, 75, 10, ST7735_BLACK);
    fillRect(20, 80, 55, 10, ST7735_BLACK);
    
    fillRect(83, 33, 45, 10, ST7735_BLACK);    // Clean states
    fillRect(83, 48, 45, 10, ST7735_BLACK);    
    fillRect(83, 63, 45, 10, ST7735_BLACK);    
    fillRect(83, 78, 45, 10, ST7735_BLACK);
    
    unsetMenuCursor(curMarker);               // CLean the cursor
    
}








