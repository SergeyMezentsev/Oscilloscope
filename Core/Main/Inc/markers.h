#ifndef MARKERS_H
#define MARKERS_H

// Certain marker's position in the common array
// This is the offset for the markerArray in the heap
#define VOLT_MARKER 0
#define SEC_MARKER 1
#define ATT_MARKER 2

// Main measures for voltages
#define MV_MEASURE 3U
#define V_MEASURE 4U

// Main measures for seconds
#define SEC_MEASURE 5U
#define MILLISEC_MEASURE 6U
#define MICROSEC_MEASURE 7U

// Main measures for attenuation
#define ATT_MEASURE 8U

// number of voltage scales
#define VOLT_SCALE_NUM 9
// number of seconds scales
#define SEC_SCALE_NUM 10
// number of attenuation scales
#define ATT_SCALE_NUM 2


typedef struct {

    char title[4];
    char scale[5];

    uint16_t* scaleBuf;
    uint8_t scalePos;
    uint8_t measure;

} bottomMarker_t;

extern bottomMarker_t* bottomMarkers;

void createBottomMarkerArray();
void setDefaultBottomMarkers();
void drawBottomMarkers();
void updateRunningMarker();
void updateBottomMarkers();

#endif  // MARKERS_H