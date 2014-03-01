#ifndef D3DLIBTEST_MAIN
#define D3DLIBTEST_MAIN

#include "window.h"
#include "sounds/sound_WAVEPCM.h"
#include "shaders/shader_TEXTURE.h"
#include "shaders/shader_LIGHT.h"
#include "models/model_FBX.h"
#include "models/model_OBJ.h"
#pragma comment (lib, "D3DLib.lib")

using namespace D3DLIB;

bool Initialize();
void Run();
void Shutdown();
void DrawStartupText(const WCHAR* string);

void DrawInfo();
void DrawView();
void Movement();
void ScrollMove(unsigned char DIK, float &directionSpeedVar, float &outputVar,
				float frameTime, bool positive, bool allowNegatives);

/*** DRAWING ***/

Window win;

Model_FBX m_sphere;
Bitmap cursor;
Bitmap stars;

Shader_TEXTURE s_tex;
Shader_LIGHT s_light;

Texture t_stars;
Texture t_earth;
Texture t_mouseoff;
Texture t_mouseon;

/*** MOVEMENT CONTROL ***/

float frameTime = 0.0f;
float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;
float movementX = 0.0f;
float movementZ = 0.0f;

float rotUSpeed = 0.0f;
float rotDSpeed = 0.0f;
float moveL = 0.0f;
float moveR = 0.0f;
float moveUP = 0.0f;
float moveD = 0.0f;

bool mousePressed = false;
bool mouseEnabled = false;
int originalX = 0;
int originalY = 0;
float rotXo = 0.0f;
float rotYo = 0.0f;
int mouseX = 0;
int mouseY = 0;

#endif