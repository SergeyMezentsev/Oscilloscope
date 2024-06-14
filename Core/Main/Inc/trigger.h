#ifndef TRIGGER_H
#define TRIGGER_H

typedef struct {
    uint8_t pos;
    uint16_t meaning;   // trigger level converted to [0; 4095] for ADC array
} trigger_t;

extern trigger_t* trigger;

void createTrigger();
void setDefaultTrigger();
void drawTrigger();
void highlightTrigger();
void dehighlightTrigger();
void chooseTrigger();
void unchooseTrigger();
void moveUpTrigger();
void moveDownTrigger();

#endif  // TRIGGER_H