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

namespace D3DLIB
{
	enum UpAxis
	{
		Ypositive = 2,
		Zpositive = 4
	};

	enum Handedness
	{
		Left = 0,
		Right = 1
	};

	enum UVOrigin
	{
		TopLeft = 0,
		BottomLeft = 1
	};

	enum RotMode
	{
		Deg = 0,
		Rad = 1
	};

	///<summary>Transformations applied to a set points.  If mode (for rotation) is unset, defaults to radians.</summary>
	struct Transform
	{
	public:
		Transform();
		Transform(RotMode mode);
		Transform(D3DXVECTOR3 rotation, D3DXVECTOR3 scale,
			D3DXVECTOR3 translation, RotMode mode);

		D3DXVECTOR3 rotation;
		D3DXVECTOR3 scale;
		D3DXVECTOR3 translation;
		RotMode mode;
	};

	struct Orientation
	{
		Orientation();
		Orientation(UpAxis upaxis, Handedness hand, UVOrigin uvorigin);

		UpAxis upaxis;
		Handedness hand;
		UVOrigin uvorigin;
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