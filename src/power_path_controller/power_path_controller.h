#ifndef POWER_PATH_CONTROLLER_H
#define POWER_PATH_CONTROLLER_H
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "../gpio_controller/gpio_controller.h"

typedef struct PowerPathController PowerPathController_t;

struct PowerPathController {

    void (*setLoad)(bool status);

    //This turns charging on or off
    void (*setBatteryCharger)(bool status);

};


void initPowerPathController(PowerPathController_t *self, GPIOController_t *GPIOController);

#endif /* POWER_PATH_CONTROLLER_H */