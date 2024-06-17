#ifndef GRAPHIC_H
#define GRAPHIC_H


void createPointArrays();
void updateGraphic();

extern uint16_t start;     // Borders in the "measures" array for screen window
extern uint16_t stop;

extern int32_t pixelScaleMV;   // scale of one pixel in millivolts
extern int32_t trigLevelMV;    // trigger level in millivolts

#endif // GRAPHIC_H