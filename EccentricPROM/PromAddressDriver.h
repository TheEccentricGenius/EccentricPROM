#ifndef INCLUDE_PROM_ADDRESS_DRIVER_H
#define INCLUDE_PROM_ADDRESS_DRIVER_H

#include "Arduino.h"

class PromAddressDriver {
  public:
    static void begin();
    static void setAddress(uint32_t address, bool outputEnable);
};


#endif // #define INCLUDE_PROM_ADDRESS_DRIVER_H
