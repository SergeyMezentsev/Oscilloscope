#ifndef UI_H
#define UI_H


void initDisplay(SPI_HandleTypeDef* hspi);

void createDefaultScreen();
void cleanDefaultScreen();

void createBottomMarkers();
void handleRunningMarker();
void handleBottomMarkers();

void createMenu();
void cleanMenu();
void handleMenu();

void createSideMarkers();
void handleSideMarkers();

void createADC();
void handleADC();

void createGraphic();
void handleGraphic();


    

#endif  // UI_H