#include "empty_class.h"

/**
 * Private Methods
 */
void _private_method(void)
{
    return;
}

/**
 * Private Members
 */
uint8_t _private_variable;


/**
 * Public Methods
 */
uint8_t emptyPublicMethod(uint32_t argument)
{
    return 0;
}

void initEmptyClass(EmptyClass_t *self)
{
    self->emptyPublicMethod = emptyPublicMethod;


}