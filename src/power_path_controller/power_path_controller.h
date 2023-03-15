#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

typedef struct PowerPathController PowerPathController_t;

struct PowerPathController {

    void (*setLoad)(bool status);
    bool (*getLoadStatus)(void);

    void (*setBatteryCharger)(bool status);
    bool (*getBatteryChargerStatus)(void);

};


void initPowerPathController(PowerPathController_t *self);

