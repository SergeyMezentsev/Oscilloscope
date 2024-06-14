#ifndef SIDE_MARKERS_H
#define SIDE_MARKERS_H

#define UNCHOSEN 0U
#define CHOSEN 1U

#define MAX_SIDE_MARKER 0U
#define MIN_SIDE_MARKER 1U
#define PPK_SIDE_MARKER 2U
#define TRIG_SIDE_MARKER 3U

#define MV_MEASURE_SIDE_MARKER 4U
#define V_MEASURE_SIDE_MARKER 5U

typedef struct {

    char title[5];
    char meaning[5];
    char measure[3];
    unsigned char state;

} sideMarker_t;

extern sideMarker_t* sideMarkers;

void createSideMarkerArray();
void setDefaultSideMarkers();
void drawSideMarkers();

void setMeasure (uint8_t marker, uint8_t measure);
void setMeaning (uint8_t marker, uint16_t meaning);
void updateSideMarkers();


#endif  // SIDE_MARKERS_H