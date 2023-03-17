#ifndef GPIO_CONTROLLER_H
#define GPIO_CONTROLLER_H


#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct GPIOController GPIOController_t;

struct GPIOController {
    bool (*getMSP_STAT) (void);


    void (*setLED1) (bool state);
    void (*setLED2) (bool state);
    void (*setLED3) (bool state);
    void (*setLED4) (bool state);
    void (*setEN2)  (bool state);
    void (*setPROG) (bool state);
    void (*addBTN1Interrupt) (void (* callback));
    void (*addBTN2Interrupt) (void (* callback));

};

void initGPIOController(GPIOController_t *self);
#endif /* GPIO_CONTROLLER_H */