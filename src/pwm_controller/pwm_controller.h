#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H
// Your library header content goes here


#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

typedef struct PWMController PWMController_t;

struct PWMController {
    uint32_t (*getLEDBrightnessPercentage) (void);
    void (*setLEDBrightness) (uint32_t percentage);

};


void initPWMController(PWMController_t *self);
#endif /* PWM_CONTROLLER_H */