#ifndef D3DLIB_MODEL_OBJ
#define D3DLIB_MODEL_OBJ

//includes
#include "../model.h"

namespace D3DLIB
{
	class Model_OBJ : public Model
	{

	public:
		Model_OBJ();
		
		Orientation GetOrientation() { return Orientation(Ypositive, Left); }

	protected:
		bool LoadModel(char* filename);

	private:
		bool LoadDataStructures(char* filename);

	};

}
#endif