#pragma once

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

#include <GL/freeglut.h>

int main(int argc, char** argv);
static void RenderSceneCB();
static void InitializeGlutCallbacks();