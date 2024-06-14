#include <stdlib.h>
#include "st7735.h"
#include "gfx.h"
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

void setMeaning (uint8_t marker, uint16_t meaning) {

    if (meaning < 10U) {
        (sideMarkers + marker)->meaning[0] = '0' + (char)meaning;
        (sideMarkers + marker)->meaning[1] = ' ';
        (sideMarkers + marker)->meaning[2] = ' ';
        (sideMarkers + marker)->meaning[3] = ' ';
    } else if (meaning < 100U) {
        (sideMarkers + marker)->meaning[0] = '0' + (char)(meaning / 10U);
        (sideMarkers + marker)->meaning[1] = '0' + (char)(meaning - 10U * (meaning / 10U));
        (sideMarkers + marker)->meaning[2] = ' ';
        (sideMarkers + marker)->meaning[3] = ' ';
    } else {
        uint16_t hundreds = meaning / 100U;
        uint16_t dozens = (meaning - 100U * hundreds) / 10U;
        uint16_t units = meaning - 100U * hundreds - 10U * dozens;
        (sideMarkers + marker)->meaning[0] = '0' + (char)hundreds;
        (sideMarkers + marker)->meaning[1] = '0' + (char)dozens;
        (sideMarkers + marker)->meaning[2] = '0' + (char)units;
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

void updateSideMarkers() {
    setTextColor(ST7735_WHITE, ST7735_BLACK);
    for (uint8_t i = 0U, pos = 0U; i < 4U; ++i) {
        if ((sideMarkers + i)->state == CHOSEN) {
            setCursor(105, 16 + 32U * pos);
            printString((sideMarkers + i)->meaning);
            pos++;
        }
    }
}



