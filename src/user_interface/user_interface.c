#include "user_interface.h"



int32_t getLEDBrightness(UserInterface_t *self)
{
    
    return -2;
}

uint8_t initUserInterface(UserInterface_t *UserInterface)
{
    UserInterface->getLEDBrightness = getLEDBrightness;

    return 0;

}