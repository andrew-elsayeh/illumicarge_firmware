#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include "../pwm_controller/pwm_controller.h"
#include "../gpio_controller/gpio_controller.h"

typedef struct UserInterface UserInterface_t;

struct UserInterface {

    void (*setStatusLEDs) (uint32_t percentage);
    uint32_t (*getUserInputLEDBrightnessPercent) (void);

};

void initUserInterface(UserInterface_t *self, PWMController_t *PWMController, GPIOController_t *GPIOController);
#endif /* USER_INTERFACE_H */