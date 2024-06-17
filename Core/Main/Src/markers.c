#include <stdlib.h>
#include "st7735.h"
#include "gfx.h"
#include "markers.h"
#include "trigger.h"
#include "IRQ_Handlers.h"


bottomMarker_t* bottomMarkers = NULL;
static int8_t highlightedBottomMarker = 0;      // Number of the currnet gighlighted bottom marker

static uint16_t* voltScales = NULL;
static uint16_t* secondScales = NULL;
static uint16_t* attScales = NULL;


void createBottomMarkerArray() {
    bottomMarkers = (bottomMarker_t*)malloc(3 * sizeof(bottomMarker_t));
    voltScales = (uint16_t*)malloc(VOLT_SCALE_NUM * sizeof(uint16_t));
    secondScales = (uint16_t*)malloc(SEC_SCALE_NUM * sizeof(uint16_t));
    attScales = (uint16_t*)malloc(ATT_SCALE_NUM * sizeof(uint16_t));

    // create trigger
    createTrigger();
}

void setDefaultBottomMarkers() {

    // set the voltage scales
    voltScales[0] = (uint16_t) 20;      voltScales[5] = (uint16_t) 1;
    voltScales[1] = (uint16_t) 50;      voltScales[6] = (uint16_t) 2;
    voltScales[2] = (uint16_t) 100;     voltScales[7] = (uint16_t) 5;
    voltScales[3] = (uint16_t) 200;     voltScales[8] = (uint16_t) 10;
    voltScales[4] = (uint16_t) 500;

    // set the seconds scales
    secondScales[0] = (uint16_t) 200;      secondScales[5] = (uint16_t) 50;
    secondScales[1] = (uint16_t) 500;      secondScales[6] = (uint16_t) 200;
    secondScales[2] = (uint16_t) 1;        secondScales[7] = (uint16_t) 500;
    secondScales[3] = (uint16_t) 5;        secondScales[8] = (uint16_t) 1;
    secondScales[4] = (uint16_t) 10;       secondScales[9] = (uint16_t) 2;

    // set attenuation scales
    attScales[0] = (uint16_t) 1;      attScales[1] = (uint16_t) 10;

    // set v/div marker
    (bottomMarkers + VOLT_MARKER)->title[0] = 'm';
    (bottomMarkers + VOLT_MARKER)->title[1] = 'V';
    (bottomMarkers + VOLT_MARKER)->title[2] = ' ';
    (bottomMarkers + VOLT_MARKER)->title[3] = '\0';

    (bottomMarkers + VOLT_MARKER)->scale[0] = '5';
    (bottomMarkers + VOLT_MARKER)->scale[1] = '0';
    (bottomMarkers + VOLT_MARKER)->scale[2] = '0';
    (bottomMarkers + VOLT_MARKER)->scale[3] = ' ';
    (bottomMarkers + VOLT_MARKER)->scale[4] = '\0';

    (bottomMarkers + VOLT_MARKER)->scaleBuf = voltScales;
    (bottomMarkers + VOLT_MARKER)->scalePos = 4U;
    (bottomMarkers + VOLT_MARKER)->measure = MV_MEASURE;


    // set sec/div marker
    (bottomMarkers + SEC_MARKER)->title[0] = 'm';
    (bottomMarkers + SEC_MARKER)->title[1] = 's';
    (bottomMarkers + SEC_MARKER)->title[2] = ' ';
    (bottomMarkers + SEC_MARKER)->title[3] = '\0';

    (bottomMarkers + SEC_MARKER)->scale[0] = '1';
    (bottomMarkers + SEC_MARKER)->scale[1] = '0';
    (bottomMarkers + SEC_MARKER)->scale[2] = ' ';
    (bottomMarkers + SEC_MARKER)->scale[3] = ' ';
    (bottomMarkers + SEC_MARKER)->scale[4] = '\0';

    (bottomMarkers + SEC_MARKER)->scaleBuf = secondScales;
    (bottomMarkers + SEC_MARKER)->scalePos = 4U;
    (bottomMarkers + SEC_MARKER)->measure = MILLISEC_MEASURE;


    // set Att marker
    (bottomMarkers + ATT_MARKER)->title[0] = 'A';
    (bottomMarkers + ATT_MARKER)->title[1] = 't';
    (bottomMarkers + ATT_MARKER)->title[2] = 't';
    (bottomMarkers + ATT_MARKER)->title[3] = '\0';

    (bottomMarkers + ATT_MARKER)->scale[0] = '1';
    (bottomMarkers + ATT_MARKER)->scale[1] = ' ';
    (bottomMarkers + ATT_MARKER)->scale[2] = ' ';
    (bottomMarkers + ATT_MARKER)->scale[3] = ' ';
    (bottomMarkers + ATT_MARKER)->scale[4] = '\0';

    (bottomMarkers + ATT_MARKER)->scaleBuf = attScales;
    (bottomMarkers + ATT_MARKER)->scalePos = 0U;
    (bottomMarkers + ATT_MARKER)->measure = ATT_MEASURE;

    // set default to trigger
    setDefaultTrigger();
}

static void highlightCertainBottomMarker(uint8_t index) {

    if (index == 3U) {  // If we have index of the trigger
        highlightTrigger();
    } else {
        setCursor(3 + index * 33, 101);
        fillRect(3 + index * 33, 101, 21, 9, ST7735_BLUE);
        setTextColor(ST7735_WHITE, ST7735_BLUE);
        setCursor(5 + index * 33, 103);
        printString((bottomMarkers + index)->title);
    }
}

static void DeHighlightCertainBottomMarker(uint8_t index) {

    if (index == 3U) {  // If we have index of the trigger
        dehighlightTrigger();
    } else {
        setCursor(3 + index * 33, 101);
        fillRect(3 + index * 33, 101, 21, 9, ST7735_BLACK);
        setTextColor(ST7735_WHITE, ST7735_BLACK);
        setCursor(5 + index * 33, 103);
        printString((bottomMarkers + index)->title);
    }
}

void updateRunningMarker() {

    static uint8_t prevState = 0U;

    if (prevState != stopButtonPushed) {    // We need to update the marker only if it's needed

        if (stopButtonPushed == 0U) {   // RUN mode

            // Clear some red space after "STOP" mode
            fillRect(121, 106, 8, 10, ST7735_BLACK);

            fillRect(100, 106, 21, 10, ST7735_GREEN);
            setTextColor(ST7735_BLACK, ST7735_GREEN);
            setCursor(102, 108);
            printString("RUN");

        } else {    // STOP mode

            fillRect(100, 106, 28, 10, ST7735_RED);
            setTextColor(ST7735_BLACK, ST7735_RED);
            setCursor(102, 108);
            printString("STOP");

        }

        prevState = stopButtonPushed;

    }
}

static void highlightCertainScale(uint8_t index) {
    DeHighlightCertainBottomMarker(index);

    setTextColor(ST7735_WHITE, ST7735_BLUE);
    setCursor(5 + index * 33, 114);
    printString((bottomMarkers + index)->scale);
}

static void DeHighlightCertainScale (uint8_t index) {
    highlightCertainBottomMarker(index);

    setTextColor(ST7735_WHITE, ST7735_BLACK);
    setCursor(5 + index * 33, 114);
    printString((bottomMarkers + index)->scale);
}

static void increaseScalePos (uint8_t marker){

    (bottomMarkers + marker)->scalePos++;

    switch (marker) {
        case VOLT_MARKER:
            if ((bottomMarkers + marker)->scalePos >= VOLT_SCALE_NUM)
                (bottomMarkers + marker)->scalePos = VOLT_SCALE_NUM - 1U;
            break;
        case SEC_MARKER:
            if ((bottomMarkers + marker)->scalePos >= SEC_SCALE_NUM)
                (bottomMarkers + marker)->scalePos = SEC_SCALE_NUM - 1U;
            break;
        case ATT_MARKER:
            if ((bottomMarkers + marker)->scalePos >= ATT_SCALE_NUM)
                (bottomMarkers + marker)->scalePos = ATT_SCALE_NUM - 1U;
            break;
    }
}

static void decreaseScalePos (uint8_t marker){

    if ((bottomMarkers + marker)->scalePos > 0U) {
        (bottomMarkers + marker)->scalePos--;
    }
}

static void updateMeasure(uint8_t marker) {

    switch (marker) {
        case VOLT_MARKER:
            if ((bottomMarkers + marker)->scalePos < 5U) {
                (bottomMarkers + marker)->measure = MV_MEASURE;
            } else {
                (bottomMarkers + marker)->measure = V_MEASURE;
            }
            break;
        case SEC_MARKER:
            if ((bottomMarkers + marker)->scalePos < 2U) {
                (bottomMarkers + marker)->measure = MICROSEC_MEASURE;
            } else if ((bottomMarkers + marker)->scalePos < 8U) {
                (bottomMarkers + marker)->measure = MILLISEC_MEASURE;
            } else {
                (bottomMarkers + marker)->measure = SEC_MEASURE;
            }
            break;    
    }
}

static void updateScale(uint8_t marker) {

    uint16_t curScale = ((bottomMarkers + marker)->scaleBuf)[(bottomMarkers + marker)->scalePos];

    if (curScale < 10U) {
        (bottomMarkers + marker)->scale[0] = '0' + (char)curScale;
        (bottomMarkers + marker)->scale[1] = ' ';
        (bottomMarkers + marker)->scale[2] = ' ';
    } else if (curScale < 100U) {
        (bottomMarkers + marker)->scale[0] = '0' + (char)(curScale / 10U);
        (bottomMarkers + marker)->scale[1] = '0' + (char)(curScale - 10U * (curScale / 10U));
        (bottomMarkers + marker)->scale[2] = ' ';
    } else {
        uint16_t hundreds = curScale / 100U;
        uint16_t dozens = (curScale - 100U * hundreds) / 10U;
        uint16_t units = curScale - 100U * hundreds - 10U * dozens;
        (bottomMarkers + marker)->scale[0] = '0' + (char)hundreds;
        (bottomMarkers + marker)->scale[1] = '0' + (char)dozens;
        (bottomMarkers + marker)->scale[2] = '0' + (char)units;
    }
}

static void updateTitle(uint8_t marker) {

    switch (marker) {
        case VOLT_MARKER:
            if ((bottomMarkers + marker)->measure == MV_MEASURE) {
                (bottomMarkers + marker)->title[0] = 'm';
                (bottomMarkers + marker)->title[1] = 'V';
            } else if ((bottomMarkers + marker)->measure == V_MEASURE) {
                (bottomMarkers + marker)->title[0] = 'V';
                (bottomMarkers + marker)->title[1] = ' ';
            }
            break;
        case SEC_MARKER:
            if ((bottomMarkers + marker)->measure == MICROSEC_MEASURE) {
                (bottomMarkers + marker)->title[0] = 'u';
                (bottomMarkers + marker)->title[1] = 's';
            } else if ((bottomMarkers + marker)->measure == MILLISEC_MEASURE) {
                (bottomMarkers + marker)->title[0] = 'm';
                (bottomMarkers + marker)->title[1] = 's';
            } else if ((bottomMarkers + marker)->measure == SEC_MEASURE) {
                (bottomMarkers + marker)->title[0] = 's';
                (bottomMarkers + marker)->title[1] = ' ';
            }
            break;    
    }

}

void updateBottomMarkers() {

    static uint8_t scaleIsHighlighted = 0U;     // This variable shows if some scale is highlighted

    if (encoderButtonPushed == 0) {     // We are not choosing the scale

        if (scaleIsHighlighted == 1U) { // If scale fo some marker was highlighted --> dehighlight it

            if (highlightedBottomMarker == 3) {
                unchooseTrigger();
            } else {
                DeHighlightCertainScale(highlightedBottomMarker);
            }
            scaleIsHighlighted = 0U;
            encoderChangedPosition = 0U;    // In order to prevent changing highlighted marker
                                            // right after setting the scale
        }

        if (encoderChangedPosition != 0U) {   // If the encoder has been rotated

            if (encoderDir > 0) {     // If encoder has worked and dir > 0

                ++highlightedBottomMarker;
                if (highlightedBottomMarker > 3) {
                    highlightedBottomMarker = 0;
                    DeHighlightCertainBottomMarker(3);
                } else {
                    DeHighlightCertainBottomMarker(highlightedBottomMarker - 1);
                }
                highlightCertainBottomMarker(highlightedBottomMarker);

            } else if (encoderDir < 0) {     // If encoder has worked and dir < 0

                --highlightedBottomMarker;
                if (highlightedBottomMarker < 0) {
                    highlightedBottomMarker = 3;
                    DeHighlightCertainBottomMarker(0U);
                } else {
                    DeHighlightCertainBottomMarker(highlightedBottomMarker + 1);
                }
                highlightCertainBottomMarker(highlightedBottomMarker);
            }

            encoderChangedPosition = 0U;
        }

    } else {        // If we are choosing the scale
        
        if (scaleIsHighlighted == 0U) { // If scale fo some marker was highlighted --> dehighlight it

            if (highlightedBottomMarker == 3) {
                chooseTrigger();
            } else {
                highlightCertainScale(highlightedBottomMarker);
            }
            scaleIsHighlighted = 1U;
        }

        if  (encoderChangedPosition != 0U) {   // If the encoder has been rotated
        
            if (encoderDir > 0) {     // If encoder has worked and dir > 0

                if (highlightedBottomMarker == 3) {
                    moveUpTrigger();
                } else {
                    increaseScalePos(highlightedBottomMarker);
                    updateMeasure(highlightedBottomMarker);
                    updateScale(highlightedBottomMarker);
                    updateTitle(highlightedBottomMarker);
                    highlightCertainScale(highlightedBottomMarker);
                }

            } else if (encoderDir < 0) {     // If encoder has worked and dir < 0

                if (highlightedBottomMarker == 3) {
                    moveDownTrigger();
                } else {
                    decreaseScalePos(highlightedBottomMarker);
                    updateMeasure(highlightedBottomMarker);
                    updateScale(highlightedBottomMarker);
                    updateTitle(highlightedBottomMarker);
                    highlightCertainScale(highlightedBottomMarker);
                }
                
            }
            
            encoderChangedPosition = 0U;
        }
    }
}

void drawBottomMarkers() {

    setTextColor(ST7735_WHITE, ST7735_BLACK);
	setTextSize(1);

    // draw first 3 bottom markers
    for (uint8_t i = 0; i < 3; ++i) {
        setCursor(5 + i * 33, 103);
        printString((bottomMarkers + i)->title);
	    setCursor(5 + i * 33, 114);
        printString((bottomMarkers + i)->scale);
    }

    // Clear some red space after "STOP" mode
    fillRect(121, 106, 8, 10, ST7735_BLACK);

    fillRect(100, 106, 21, 10, ST7735_GREEN);
	setTextColor(ST7735_BLACK, ST7735_GREEN);
	setCursor(102, 108);
    printString("RUN");

    // draw the trigger
    drawTrigger();
}



