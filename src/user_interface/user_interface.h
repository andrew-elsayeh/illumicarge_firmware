#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

typedef struct UserInterface UserInterface_t;

struct UserInterface {

int32_t (*getLEDBrightness) (UserInterface_t *self);

};



uint8_t initUserInterface(UserInterface_t *UserInterface);