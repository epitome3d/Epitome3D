#ifndef D3DLIB_MODEL_OBJ
#define D3DLIB_MODEL_OBJ

//includes
#include "../model.h"

namespace D3DLIB
{
	class Model_OBJ : public Model
	{
	private:
		typedef struct FaceType
		{
			int vIndex1, vIndex2, vIndex3;
			int tIndex1, tIndex2, tIndex3;
			int nIndex1, nIndex2, nIndex3;
		};

	public:
		Model_OBJ();
		
		Orientation GetOrientation() { return Orientation(Ypositive, Left, TopLeft); }

	protected:
		bool LoadModel(char* filename);

	private:
		bool LoadDataStructures(char* filename);

	};

}
#endif