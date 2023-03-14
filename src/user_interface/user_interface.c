#include "user_interface.h"


uint32_t led_brightness_percentage = -5;


int32_t getLEDBrightnessPercentage(UserInterface_t *self)
{
    
    return led_brightness_percentage;
}

uint8_t initUserInterface(UserInterface_t *UserInterface)
{
    UserInterface->getLEDBrightnessPercentage = getLEDBrightnessPercentage;

    return 0;

}