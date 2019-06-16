/*
 * wrapper.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: watashi
 */




#include "wrapper.hpp"
#include "LedBlink.hpp"

void cpploop(void) {
    LedBlink instance;

    instance.toggle();
}
