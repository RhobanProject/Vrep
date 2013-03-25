#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

#include <VREPClient.hpp>
#include "spline.h"

void primitive_init(VREPClient &vrep);
void primitive_step(VREPClient &vrep, Spline *splines);

#endif
