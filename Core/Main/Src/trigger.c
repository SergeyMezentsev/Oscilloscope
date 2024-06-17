#include <stdlib.h>
#include "st7735.h"
#include "gfx.h"
#include "trigger.h"

trigger_t* trigger = NULL;

void createTrigger() {

    trigger = (trigger_t*)malloc(sizeof(trigger_t));

}

void setDefaultTrigger() {
    trigger->pos = 50U;
    //trigger->meaning = (uint16_t)( (1.0f - ((float)(trigger->pos) - 3.0f) / 95.0f) * 4095.0f );
    //trigger->meaning = (uint16_t)( 4095U - (trigger->pos - 3U) * 43U );
    trigger->meaning = (uint16_t)(98U - trigger->pos);
}

void drawTrigger() {
    drawPixel(99, trigger->pos, ST7735_WHITE);
    drawFastVLine(100, trigger->pos - 1u, 2, ST7735_WHITE);
    drawFastVLine(101, trigger->pos - 2u, 4, ST7735_WHITE);
}

static void hideTrigger() {
    drawPixel(99, trigger->pos, ST7735_BLACK);
    drawFastVLine(100, trigger->pos - 1u, 2, ST7735_BLACK);
    drawFastVLine(101, trigger->pos - 2u, 4, ST7735_BLACK);
}

void highlightTrigger() {
    drawPixel(99, trigger->pos, ST7735_BLUE);
    drawFastVLine(100, trigger->pos - 1u, 2, ST7735_BLUE);
    drawFastVLine(101, trigger->pos - 2u, 4, ST7735_BLUE);
}

void dehighlightTrigger() {
    drawTrigger();
}

void chooseTrigger() {
    drawPixel(99, trigger->pos, ST7735_YELLOW);
    drawFastVLine(100, trigger->pos - 1u, 2, ST7735_YELLOW);
    drawFastVLine(101, trigger->pos - 2u, 4, ST7735_YELLOW);
}

void unchooseTrigger() {
    highlightTrigger();
}


void moveUpTrigger() {

    if (trigger->pos > 3U) {
        hideTrigger();
        trigger->pos--;
        //trigger->meaning = (uint16_t)( (1.0f - ((float)(trigger->pos) - 3.0f) / 95.0f) * 4095.0f );
        //trigger->meaning = (uint16_t)( 4095U - (trigger->pos - 3U) * 43U );
        trigger->meaning = (uint16_t)(98U - trigger->pos);
        chooseTrigger();
    }
}

void moveDownTrigger() {

    if (trigger->pos < 97U) {
        hideTrigger();
        trigger->pos++;
        //trigger->meaning = (uint16_t)( (1.0f - ((float)(trigger->pos) - 3.0f) / 95.0f) * 4095.0f );
        //trigger->meaning = (uint16_t)( 4095U - (trigger->pos - 3U) * 43U );
        trigger->meaning = (uint16_t)(98U - trigger->pos);
        chooseTrigger();
    }
}






