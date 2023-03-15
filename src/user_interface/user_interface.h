#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#include "../pwm_controller/pwm_controller.h"

typedef struct UserInterface UserInterface_t;

struct UserInterface {

    PWMController_t* PWMController;
    uint32_t user_input_led_brightness_percent;
    void (*setStatusLEDs) (uint32_t percentage);
    uint32_t (*getUserInputLEDBrightnessPercent) (void);

};

void initUserInterface(UserInterface_t *self, PWMController_t *PWMController);
#endif /* USER_INTERFACE_H */