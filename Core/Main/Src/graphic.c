#include <stdlib.h>
#include <stdint.h>
#include "st7735.h"
#include "gfx.h"
#include "markers.h"
#include "trigger.h"
#include "ADC.h"
#include "graphic.h"



#define POINT_ARR_LENGTH 95U

 int16_t* newPoints = NULL;
 int16_t* oldPoints = NULL;

 uint16_t start;     // Borders in the "measures" array for screen window
 uint16_t stop;

 int32_t pixelScaleMV;   // scale of one pixel in millivolts
 int32_t trigLevelMV;    // trigger level in millivolts




void createPointArrays() {
    newPoints = (int16_t*)malloc(POINT_ARR_LENGTH * sizeof(int16_t));
    oldPoints = (int16_t*)malloc(POINT_ARR_LENGTH * sizeof(int16_t));
}

void swapPointArrays() {
    int16_t* tmp = newPoints;
    newPoints = oldPoints;
    oldPoints = tmp;
}

void updateScales() {

    pixelScaleMV = 1;

    switch ( (bottomMarkers + VOLT_MARKER)->measure ) {
        case MV_MEASURE:
            pixelScaleMV *= (int32_t)( (bottomMarkers + VOLT_MARKER)->scaleBuf[(bottomMarkers + VOLT_MARKER)->scalePos] ) / 16;
            break;
        case V_MEASURE:
            pixelScaleMV *= (int32_t)( (bottomMarkers + VOLT_MARKER)->scaleBuf[(bottomMarkers + VOLT_MARKER)->scalePos] ) * 1000 / 16;
            break;
    }

    trigLevelMV = pixelScaleMV * ( (int32_t)trigger->meaning - 48 );
}

int32_t getMeasureMV(int16_t* measures, uint16_t pos) {

    return ( (int32_t) measures[pos] ) * 1650 / 2048 * (int32_t)( (bottomMarkers + ATT_MARKER)->scaleBuf[(bottomMarkers + ATT_MARKER)->scalePos] );

}

void triggerSynchronize(int16_t* measures) {

    for (uint16_t i = 1U; i + 1 < LENGTH; ++i) {
        if ( getMeasureMV(measures, i - 1U) < trigLevelMV  &&  trigLevelMV < getMeasureMV(measures, i + 1U) ) {
            start = i;
            stop = i + 94U;
            return;
        }
    }

    start = 0U;
    stop = 94U;
}

void convertMeasures(int16_t* measures) {

    int16_t y = 0;

    for (uint8_t i = 0U; i + start <= stop; ++i) {

        y = 50 - (int16_t) ( getMeasureMV(measures, i + start) / pixelScaleMV );

        if (y < 3U) {
            newPoints[i] = 1000;
        } else if(y > 97U) {
            newPoints[i] = -1000;
        } else {
            newPoints[i] = y;
        }
    }
}

void eraseOldGraphic() {

    uint16_t color = ST7735_BLACK;

    for (uint16_t i = 0U; i + 1 < POINT_ARR_LENGTH; ++i) {

        if ( i - 16U * (i / 16U) == 15U || i == 94U)
            color = ST7735_WHITE;
        else
            color = ST7735_BLACK;

        if (oldPoints[i] != 1000 && oldPoints[i] != -1000 && oldPoints[i + 1U] != 1000 && oldPoints[i + 1U] != -1000) {
            int16_t y = oldPoints[i];
            if (y <= oldPoints[i + 1U]) {
                for ( ; y < oldPoints[i + 1U]; ++y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
                }
            } else if (y >= oldPoints[i + 1U]) {
                for ( ; y > oldPoints[i + 1U]; --y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
                }
            }
        } else if (oldPoints[i] != 1000 && oldPoints[i] != -1000 && oldPoints[i + 1U] == 1000) {    // If the next pixel is outside the cell area and HIGHER
            int16_t y = oldPoints[i];           
            for ( ; y >= 3; --y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
            }
        } else if (oldPoints[i] != 1000 && oldPoints[i] != -1000 && oldPoints[i + 1U] == -1000) {    // If the next pixel is outside the cell area and LOWER
            int16_t y = oldPoints[i];           
            for ( ; y <= 97; ++y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
            }
        } else if (oldPoints[i] == 1000 && oldPoints[i + 1U] != 1000 && oldPoints[i + 1U] != -1000) {
            int16_t y = 3;           
            for ( ; y < oldPoints[i + 1U]; ++y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
            }
        } else if (oldPoints[i] == -1000 && oldPoints[i + 1U] != 1000 && oldPoints[i + 1U] != -1000) {
            int16_t y = 97;         
            for ( ; y > oldPoints[i + 1U]; --y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
            }
        } else if (oldPoints[i] == -1000 && oldPoints[i + 1U] == 1000) {
            int16_t y = 97;         
            for ( ; y >= 3; --y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
            }
        } else if (oldPoints[i] == 1000 && oldPoints[i + 1U] == -1000) {
            int16_t y = 3;         
            for ( ; y <= 97; ++y) {
                    if (y == 50)
                        drawPixel(i + 4U, y, ST7735_YELLOW);
                    else if ( y - 16U * (y / 16U) == 2U || y == 97)
                        drawPixel(i + 4U, y, ST7735_WHITE);
                    else
                        drawPixel(i + 4U, y, color);
            }
        }
    }

    if (oldPoints[POINT_ARR_LENGTH - 1U] != -1000 && oldPoints[POINT_ARR_LENGTH - 1U] != 1000) {
        drawPixel(98U, oldPoints[POINT_ARR_LENGTH - 1U], ST7735_WHITE);
    }
}

void drawNewGraphic() {
    for (uint16_t i = 0U; i + 1 < POINT_ARR_LENGTH; ++i) {

        if (newPoints[i] != 1000 && newPoints[i] != -1000 && newPoints[i + 1U] != 1000 && newPoints[i + 1U] != -1000) {
            int16_t y = newPoints[i];
            if (y <= newPoints[i + 1U]) {
                for ( ; y < newPoints[i + 1U]; ++y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
                }
            } else if (y >= newPoints[i + 1U]) {
                for ( ; y > newPoints[i + 1U]; --y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
                }
            }
        } else if (newPoints[i] != 1000 && newPoints[i] != -1000 && newPoints[i + 1U] == 1000) {    // If the next pixel is outside the cell area and HIGHER
            int16_t y = newPoints[i];           
            for ( ; y >= 3; --y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
            }
        } else if (newPoints[i] != 1000 && newPoints[i] != -1000 && newPoints[i + 1U] == -1000) {    // If the next pixel is outside the cell area and LOWER
            int16_t y = newPoints[i];           
            for ( ; y <= 97; ++y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
            }
        } else if (newPoints[i] == 1000 && newPoints[i + 1U] != 1000 && newPoints[i + 1U] != -1000) {
            int16_t y = 3;           
            for ( ; y < newPoints[i + 1U]; ++y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
            }
        } else if (newPoints[i] == -1000 && newPoints[i + 1U] != 1000 && newPoints[i + 1U] != -1000) {
            int16_t y = 97;         
            for ( ; y > newPoints[i + 1U]; --y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
            }
        } else if (newPoints[i] == -1000 && newPoints[i + 1U] == 1000) {
            int16_t y = 97;         
            for ( ; y >= 3; --y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
            }
        } else if (newPoints[i] == 1000 && newPoints[i + 1U] == -1000) {
            int16_t y = 3;         
            for ( ; y <= 97; ++y) {
                    drawPixel(i + 4U, y, ST7735_YELLOW);
            }
        }
    }

    if (newPoints[POINT_ARR_LENGTH - 1U] != -1000 && newPoints[POINT_ARR_LENGTH - 1U] != 1000) {
        drawPixel(98U, newPoints[POINT_ARR_LENGTH - 1U], ST7735_YELLOW);
    }
}

void updateGraphic() {

    static uint8_t startFlag = 1U;

    updateScales();
    triggerSynchronize(measures);

    if (startFlag == 1U) {
        convertMeasures(measures);
        drawNewGraphic();
        startFlag = 0U;
    } else {

        swapPointArrays();
        convertMeasures(measures);
        eraseOldGraphic();
        drawNewGraphic();
    }
}










