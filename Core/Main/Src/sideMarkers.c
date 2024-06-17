#include <stdlib.h>
#include "st7735.h"
#include "gfx.h"
#include "markers.h"
#include "ADC.h"
#include "graphic.h"
#include "sideMarkers.h"


static uint8_t lastOwnedPos = 0U;
sideMarker_t* sideMarkers = NULL;

void createSideMarkerArray() {
    sideMarkers = (sideMarker_t*)malloc(4 * sizeof(sideMarker_t));
}

void setDefaultSideMarkers() {

    // set defaults for max marker
    (sideMarkers + MAX_SIDE_MARKER)->title[0] = 'm';
    (sideMarkers + MAX_SIDE_MARKER)->title[1] = 'a';
    (sideMarkers + MAX_SIDE_MARKER)->title[2] = 'x';
    (sideMarkers + MAX_SIDE_MARKER)->title[3] = '\0';

    (sideMarkers + MAX_SIDE_MARKER)->measure[0] = 'm';
    (sideMarkers + MAX_SIDE_MARKER)->measure[1] = 'V';
    (sideMarkers + MAX_SIDE_MARKER)->measure[2] = '\0';

    (sideMarkers + MAX_SIDE_MARKER)->meaning[0] = '0';
    (sideMarkers + MAX_SIDE_MARKER)->meaning[1] = '0';
    (sideMarkers + MAX_SIDE_MARKER)->meaning[2] = '0';
    (sideMarkers + MAX_SIDE_MARKER)->meaning[3] = '0';
    (sideMarkers + MAX_SIDE_MARKER)->meaning[4] = '\0';

    (sideMarkers + MAX_SIDE_MARKER)->state = UNCHOSEN;

    // ser defaults for min marker
    (sideMarkers + MIN_SIDE_MARKER)->title[0] = 'm';
    (sideMarkers + MIN_SIDE_MARKER)->title[1] = 'i';
    (sideMarkers + MIN_SIDE_MARKER)->title[2] = 'n';
    (sideMarkers + MIN_SIDE_MARKER)->title[3] = '\0';

    (sideMarkers + MIN_SIDE_MARKER)->measure[0] = 'm';
    (sideMarkers + MIN_SIDE_MARKER)->measure[1] = 'V';
    (sideMarkers + MIN_SIDE_MARKER)->measure[2] = '\0';

    (sideMarkers + MIN_SIDE_MARKER)->meaning[0] = '0';
    (sideMarkers + MIN_SIDE_MARKER)->meaning[1] = '0';
    (sideMarkers + MIN_SIDE_MARKER)->meaning[2] = '0';
    (sideMarkers + MIN_SIDE_MARKER)->meaning[3] = '0';
    (sideMarkers + MIN_SIDE_MARKER)->meaning[4] = '\0';

    (sideMarkers + MIN_SIDE_MARKER)->state = UNCHOSEN;

    // ser defaults for Ppk marker
    (sideMarkers + PPK_SIDE_MARKER)->title[0] = 'P';
    (sideMarkers + PPK_SIDE_MARKER)->title[1] = 'p';
    (sideMarkers + PPK_SIDE_MARKER)->title[2] = 'k';
    (sideMarkers + PPK_SIDE_MARKER)->title[3] = '\0';

    (sideMarkers + PPK_SIDE_MARKER)->measure[0] = 'm';
    (sideMarkers + PPK_SIDE_MARKER)->measure[1] = 'V';
    (sideMarkers + PPK_SIDE_MARKER)->measure[2] = '\0';

    (sideMarkers + PPK_SIDE_MARKER)->meaning[0] = '0';
    (sideMarkers + PPK_SIDE_MARKER)->meaning[1] = '0';
    (sideMarkers + PPK_SIDE_MARKER)->meaning[2] = '0';
    (sideMarkers + PPK_SIDE_MARKER)->meaning[3] = '0';
    (sideMarkers + PPK_SIDE_MARKER)->meaning[4] = '\0';
    
    (sideMarkers + PPK_SIDE_MARKER)->state = UNCHOSEN;

    // ser defaults for trig marker
    (sideMarkers + TRIG_SIDE_MARKER)->title[0] = 'T';
    (sideMarkers + TRIG_SIDE_MARKER)->title[1] = 'r';
    (sideMarkers + TRIG_SIDE_MARKER)->title[2] = 'i';
    (sideMarkers + TRIG_SIDE_MARKER)->title[3] = 'g';
    (sideMarkers + TRIG_SIDE_MARKER)->title[4] = '\0';

    (sideMarkers + TRIG_SIDE_MARKER)->measure[0] = 'm';
    (sideMarkers + TRIG_SIDE_MARKER)->measure[1] = 'V';
    (sideMarkers + TRIG_SIDE_MARKER)->measure[2] = '\0';

    (sideMarkers + TRIG_SIDE_MARKER)->meaning[0] = '0';
    (sideMarkers + TRIG_SIDE_MARKER)->meaning[1] = '0';
    (sideMarkers + TRIG_SIDE_MARKER)->meaning[2] = '0';
    (sideMarkers + TRIG_SIDE_MARKER)->meaning[3] = '0';
    (sideMarkers + TRIG_SIDE_MARKER)->meaning[4] = '\0';

    (sideMarkers + TRIG_SIDE_MARKER)->state = UNCHOSEN;
}

void setMeasure (uint8_t marker, uint8_t measure) {

    switch (measure) {
        case MV_MEASURE_SIDE_MARKER:
            (sideMarkers + marker)->measure[0] = 'm';
            (sideMarkers + marker)->measure[1] = 'V';
            break;
        case V_MEASURE_SIDE_MARKER:
            (sideMarkers + marker)->measure[0] = 'V';
            (sideMarkers + marker)->measure[1] = ' ';
            break;
    }
}

void setMeaningMV (uint8_t marker, int16_t meaning) {

    // from -999 to 999 mV

    if (meaning > 0) {
        (sideMarkers + marker)->meaning[0] = ' ';
    } else {
        (sideMarkers + marker)->meaning[0] = '-';
        meaning = -meaning;
    }

    if (meaning < 10) {
        (sideMarkers + marker)->meaning[1] = '0' + (char)meaning;
        (sideMarkers + marker)->meaning[2] = ' ';
        (sideMarkers + marker)->meaning[3] = ' ';
    } else if (meaning < 100) {
        (sideMarkers + marker)->meaning[1] = '0' + (char)(meaning / 10);
        (sideMarkers + marker)->meaning[2] = '0' + (char)(meaning - 10 * (meaning / 10));
        (sideMarkers + marker)->meaning[3] = ' ';
    } else {
        uint16_t hundreds = meaning / 100;
        uint16_t dozens = (meaning - 100 * hundreds) / 10;
        uint16_t units = meaning - 100 * hundreds - 10 * dozens;
        (sideMarkers + marker)->meaning[1] = '0' + (char)hundreds;
        (sideMarkers + marker)->meaning[2] = '0' + (char)dozens;
        (sideMarkers + marker)->meaning[3] = '0' + (char)units;
    }

}

static void setMeaningV (uint8_t marker, int16_t meaning) {

    // The functin gets from 11 to 999 (or from -999 to -11)
    // The last digit is a tenth of a Volt
    // First one/two digits(s) is(are) whole Volts

    if (meaning > 0) {
        (sideMarkers + marker)->meaning[0] = ' ';
    } else {
        (sideMarkers + marker)->meaning[0] = '-';
        meaning = -meaning;
    }

    if (meaning < 100) {
        (sideMarkers + marker)->meaning[1] = '0' + (char)(meaning / 10);
        (sideMarkers + marker)->meaning[2] = '.';
        (sideMarkers + marker)->meaning[3] = '0' + (char)(meaning - 10 * (meaning / 10));
    } else {
        meaning /= 10;
        (sideMarkers + marker)->meaning[1] = '0' + (char)(meaning / 10);
        (sideMarkers + marker)->meaning[2] = '0' + (char)(meaning - 10 * (meaning / 10));
        (sideMarkers + marker)->meaning[3] = ' ';
    }
}

static void showMarker(uint8_t marker, uint8_t pos) {

    setTextColor(ST7735_WHITE, ST7735_BLACK);
    setCursor(105, 5 + 32U * pos);
    printString((sideMarkers + marker)->title);
	setCursor(105, 16 + 32U * pos);
    printString((sideMarkers + marker)->meaning);
	setCursor(105, 27 + 32U * pos);
    printString((sideMarkers + marker)->measure);
	drawFastHLine(105, 35 + 32U * pos, 26, ST7735_WHITE);

}

static void cleanPosition (uint8_t pos) {

    fillRect(105, 5 + 32U * pos, 26, 31, ST7735_BLACK);

}

void drawSideMarkers() {

    uint8_t pos = 0U;
    for (uint8_t i = 0; i < 4U; ++i) {
        if ((sideMarkers + i)->state == CHOSEN) {
            cleanPosition(pos);
            showMarker(i, pos);
            pos++;
        }
    }

    for (; pos < 3U; ++pos) {
        cleanPosition(pos);
    }
}

static void updateMaxMinPpk() {

    int32_t max = (int32_t) measures[start];
    int32_t min = (int32_t) measures[start];
    int32_t ppk;

    for (uint16_t i = start; i <= stop; ++i) {
        if ( ( (int32_t) measures[i] ) < min)
            min = (int32_t) measures[i];
        
        if (( (int32_t) measures[i] ) > max)
            max = (int32_t) measures[i];
    }
    ppk = max - min;

    max *= 3300;
    max *= (int32_t) ( (bottomMarkers + ATT_MARKER)->scaleBuf[(bottomMarkers + ATT_MARKER)->scalePos] );
    max /= 4095;
    if (max > -1000 && max < 1000) {
        setMeasure(MAX_SIDE_MARKER, MV_MEASURE_SIDE_MARKER);
        setMeaningMV(MAX_SIDE_MARKER, max);
    } else {
        setMeasure(MAX_SIDE_MARKER, V_MEASURE_SIDE_MARKER);
        max /= 100;
        setMeaningV(MAX_SIDE_MARKER, max);
    }

    min *= 3300;
    min *= (int32_t) ( (bottomMarkers + ATT_MARKER)->scaleBuf[(bottomMarkers + ATT_MARKER)->scalePos] );
    min /= 4095;
    if (min > -1000 && min < 1000) {
        setMeasure(MIN_SIDE_MARKER, MV_MEASURE_SIDE_MARKER);
        setMeaningMV(MIN_SIDE_MARKER, min);
    } else {
        setMeasure(MIN_SIDE_MARKER, V_MEASURE_SIDE_MARKER);
        min /= 100;
        setMeaningV(MIN_SIDE_MARKER, min);
    }

    ppk *= 3300;
    ppk *= (int32_t) ( (bottomMarkers + ATT_MARKER)->scaleBuf[(bottomMarkers + ATT_MARKER)->scalePos] );
    ppk /= 4095;
    if (ppk > -1000 && ppk < 1000) {
        setMeasure(PPK_SIDE_MARKER, MV_MEASURE_SIDE_MARKER);
        setMeaningMV(PPK_SIDE_MARKER, ppk);
    } else {
        setMeasure(PPK_SIDE_MARKER, V_MEASURE_SIDE_MARKER);
        ppk /= 100;
        setMeaningV(PPK_SIDE_MARKER, ppk);
    }
}

static void updateTrig() {

    if (trigLevelMV > -1000 && trigLevelMV < 1000) {
        setMeasure(TRIG_SIDE_MARKER, MV_MEASURE_SIDE_MARKER);
        setMeaningMV(TRIG_SIDE_MARKER, trigLevelMV);
    } else {
        setMeasure(TRIG_SIDE_MARKER, V_MEASURE_SIDE_MARKER);
        setMeaningV(TRIG_SIDE_MARKER, trigLevelMV / 100);
    }    
}

void updateSideMarkers() {

    updateMaxMinPpk();
    updateTrig();

    setTextColor(ST7735_WHITE, ST7735_BLACK);
    for (uint8_t i = 0U, pos = 0U; i < 4U; ++i) {
        if ((sideMarkers + i)->state == CHOSEN) {
            setCursor(105, 16 + 32U * pos);
            printString((sideMarkers + i)->meaning);
            setCursor(105, 27 + 32U * pos);
            printString((sideMarkers + i)->measure);
            pos++;
        }
    }
}



