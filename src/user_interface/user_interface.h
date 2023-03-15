#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

typedef struct UserInterface UserInterface_t;

struct UserInterface {

    uint32_t user_input_led_brightness_percent;
    void (*setStatusLEDs) (uint32_t percentage);
    uint32_t (*getUserInputLEDBrightnessPercent) (void);

};

/**
 * Public Methods
 */

void initUserInterface(UserInterface_t *UserInterface);
void setStatusLEDs( uint32_t percentage);
uint32_t getUserInputLEDBrightnessPercent(void);