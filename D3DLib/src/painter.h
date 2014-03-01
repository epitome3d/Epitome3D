#ifndef D3DLIB_PAINTER
#define D3DLIB_PAINTER

#pragma warning(disable:4005)
#include "shader.h"
#include "model.h"
#include "globals.h"
#include "text.h"
#include "bitmap.h"
#include "D3D.h"
#include "frustumcull.h"
#include "viewport.h"

#include <vector>
#include <algorithm>
using namespace std;

namespace D3DLIB
{
	struct PaintData
	{
		PaintData(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* projection,
			D3DXMATRIX* ortho, D3D11_VIEWPORT *viewport, D3DDesc::Rasterizer* rasterizer);
		PaintData* Clone();

		D3DXMATRIX *world, *view, *projection, *ortho;
		D3D11_VIEWPORT *viewport;
		D3DDesc::Rasterizer* rasterizer;
	};

	struct BaseType abstract
	{
	public:
		BaseType();
		BaseType(const BaseType&);
		~BaseType();

		BaseType& operator= (const BaseType &other);
		int operator== (const BaseType &other) const;
		int operator< (const BaseType &other) const;

		virtual BaseType* Clone() = 0;
		virtual int GetType() = 0;
		//virtual void Clean() = 0;

		float ZOrder;
	};

	struct ModelType : public BaseType
	{
	public:
		ModelType();
		ModelType(Model* model,
			Shader* shader, Transform* transform, CullType* cull, PaintData* data);
		ModelType(const ModelType&);
		~ModelType();

		void Render(ID3D11DeviceContext* deviceContext, Frustum* frustum, Viewport* viewport); //called from Painter

		BaseType* Clone();
		int GetType() { return 1; }

		Model* model;
		CullType* cull;
		Shader* shader;
		Transform* transform;
		PaintData* data;
	};

	struct TextType : public BaseType
	{
	public:
		TextType();
		TextType(Text* text, const WCHAR* string, const WCHAR* fontfamily,
			float positionX, float positionY, float fontsize,
			UINT32 colorABGR, UINT FW1_TEXT_FLAGs, PaintData* data);
		TextType(const TextType&);
		~TextType();

		void Render(ID3D11DeviceContext* deviceContext, Viewport* viewport);

		BaseType* Clone();
		int GetType() { return 2; }

		PaintData* data;
		Text* m_text;
		const WCHAR* m_string;
		const WCHAR* m_fontfamily;
		float m_positionX, m_positionY, m_fontsize;
		UINT32 m_colorABGR;
		UINT m_FW1_TEXT_FLAGs;
	};

	struct BitmapType : public BaseType
	{
		BitmapType();
		BitmapType(Bitmap* bitmap, Shader* shader, Transform* transform, 
			int positionX, int positionY, int bitmapWidth, int bitmapHeight,
			float depth, bool draw2D, PaintData* data);
		BitmapType(const BitmapType&);
		~BitmapType();

		void Render(D3D* d3d, Viewport* viewport);

		BaseType* Clone();
		int GetType() { return 3; }

		int m_positionX, m_positionY, m_bitmapWidth, m_bitmapHeight;
		float depth;
		bool draw2D;

		Bitmap* bitmap;
		Shader* shader;
		Transform* transform;
		PaintData* data;
	};

	/*struct TransformType : public BaseType
	{
		TransformType();
		TransformType(Transform* world, Transform* view, Transform* projection,
			Transform* ortho, bool force);
		TransformType(const TransformType&);
		~TransformType();

		void Render(D3D* d3d, 
		D3DXMATRIX &world, D3DXMATRIX &view, D3DXMATRIX &projection, D3DXMATRIX &ortho);

		BaseType* Clone();
		int GetType() { return 4; }

		Transform *world, *view, *projection, *ortho;
		bool force;
	};*/
	
	//TODO: Add Clean() to each Type class, call from Painter
	//TODO: Add std::list<ModelType*> clean for use during Clean() operation, add AddToClean() function
	//TODO: Privatize and protect 'Type' classes
	//TODO: Allow for both static and dynamic BitmapTypes

	class Painter
	{
	public:
		Painter();
		Painter(const Painter&);
		~Painter();

		void ClearList(); //clear model list
		void Render(D3D* d3d, Frustum* frustum, Viewport* viewport, 
			D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection, D3DXMATRIX ortho); //called in MAIN
		
		static bool Compare(const BaseType * const & a,
			const BaseType * const & b)
		{
		   return b->ZOrder < a->ZOrder;
		}

		void AddToFront(BaseType& item);

		//TODO: Add functions below!

		//void BringToFront(BaseType item);
		//void SendToBack(BaseType item);
		//void BringInFrontOf(BaseType item, BaseType other);
		//void SendBehind(BaseType item, BaseType other);
		//bool SetZValue(BaseType item);

		std::vector<BaseType*> z;
	};
}

#endif