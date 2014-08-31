#ifndef GLUTBACKEND_H
#define GLUTBACKEND_H

#include "Callbacks.h"

void glutBackendInit(int argc, char** argv);

bool glutBackendWindow(unsigned int Width, unsigned int Height, const char* pTitle);

void glutBackendRun(Callbacks *calls);

#endif