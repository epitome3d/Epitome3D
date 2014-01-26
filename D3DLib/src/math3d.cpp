#include "math3d.h"

namespace D3DLIB { namespace Math {

	void DrawCircle_Vertex(int num_verts)
	{
		float angle;
		for( int i = 0; i < num_verts; i++ )
		{
			angle = 3.14159 * 2 / (float)num_verts * i;

			D3DXVECTOR3 pos( sin( angle ), cos( angle ), 0 );
			// Now you fill this position into a vertexbuffer. If you don't know how to do this, the directx sdk got alot of tutorials and there are also alot available in the internet.
		}
	}

}}