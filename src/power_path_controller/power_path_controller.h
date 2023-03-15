#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

typedef struct PowerPathController PowerPathController_t;

struct PowerPathController {

    void (*setLoad)(bool status);

    //This sets the PROG pin that should be connected to PC12. When High, the battery charger turns off
    void (*setBatteryCharger)(bool status);

};


void initPowerPathController(PowerPathController_t *self);

