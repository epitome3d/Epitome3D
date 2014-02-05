#pragma once

//globals
static bool FULL_SCREEN = false;
static bool VSYNC_ENABLED = true;
static float SCREEN_DEPTH = 1000.0f;
static float SCREEN_NEAR = 0.1f;
static unsigned long WINDOWED_WIDTH = 800;
static unsigned long WINDOWED_HEIGTH = 600;
static bool SHOW_CURSOR = true;

#pragma warning(disable:4005)
#include <d3d11.h>
#include <d3dx10math.h>

enum UpAxis
{
	Ypositive = 2,
	Zpositive = 4
};

namespace D3DLIB
{
	struct Transform
	{
	public:
		Transform();
		Transform(D3DXVECTOR3 rotation, D3DXVECTOR3 scale,
			D3DXVECTOR3 translation);

		D3DXVECTOR3 rotation;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 translation;
	};

	struct ModelData
	{
	public:
		ModelData()
		{

		}

		void Reset() 
		{ 
			data = false;
			radius = 0;
			xSize = 0;
			ySize = 0;
			zSize = 0;
			xCenter = 0;
			yCenter = 0;
			zCenter = 0;
		}

		float xCenter, yCenter, zCenter;
		float xSize, ySize, zSize, radius;
		bool data;
	};
}