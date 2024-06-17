#include <stdlib.h>
#include <stdint.h>
#include "ADC.h"

int16_t* measures = NULL;

void createADCArray() {
    measures = (int16_t*)malloc(LENGTH * sizeof(int16_t));
}

void getNewADCMeasures() {
    // Here we need to get/fill array with positive and negative meanings

    int16_t m = 0;


    for (uint16_t i = 0U; i < LENGTH; ++i, m += 100) {
        if (m >= 2047)
            m = -2047;
        measures[i] = m;
    }

}