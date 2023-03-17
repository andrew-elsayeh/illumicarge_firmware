#ifndef EMPTY_CLASS_H
#define EMPTY_CLASS_H


#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

typedef struct GPIOReader EmptyClass_t;

struct GPIOReader {
    uint8_t (*emptyPublicMethod) (uint32_t argument);

};


void initEmptyClass(EmptyClass_t *self);
#endif /* EMPTY_CLASS_H */