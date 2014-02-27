#ifndef D3DLIB_MODEL_FBX
#define D3DLIB_MODEL_FBX

//includes
#pragma comment (lib,"libfbxsdk.lib")
#include <fbxsdk.h>
#include "../model.h"

namespace D3DLIB
{
	class Model_FBX : public Model
	{

	public:
		Model_FBX();
		
		Orientation GetOrientation() { return Orientation(Zpositive, Left); }

	protected:
		bool LoadModel(char* filename);

	private:
		bool LoadPolygonData(FbxMesh*);
		FbxManager* g_pFbxSdkManager;
	};

}
#endif