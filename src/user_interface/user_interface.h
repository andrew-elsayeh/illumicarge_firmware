#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

typedef struct UserInterface UserInterface_t;

struct UserInterface {

int32_t (*getLEDBrightnessPercentage) (UserInterface_t *self);
void (*setLEDPWM) (UserInterface_t *self, uint32_t percentage);

};



uint8_t initUserInterface(UserInterface_t *UserInterface);