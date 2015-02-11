#include "painter.h"

namespace D3DLIB
{
	PaintData::PaintData(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* projection,
		D3DXMATRIX* ortho, D3D11_VIEWPORT *viewport, D3DDesc::Rasterizer* rasterizer)
	{
		this->world = new D3DXMATRIX(*world);
		this->view = new D3DXMATRIX(*view);
		this->projection = new D3DXMATRIX(*projection);
		this->ortho = new D3DXMATRIX(*ortho);
		this->viewport = new D3D11_VIEWPORT(*viewport);
		this->rasterizer = new D3DDesc::Rasterizer(*rasterizer);
	}
	PaintData* PaintData::Clone()
	{
		PaintData* i = new PaintData(*this);
		i->ortho = this->ortho;
		i->projection = this->projection;
		i->view = this->view;
		i->world = this->world;
		i->viewport = this->viewport;
		return i;
	}

	BaseType::BaseType()
	{
		//ZOrder = 0;
	}
	BaseType::BaseType(const BaseType& other)
	{
	}
	BaseType::~BaseType()
	{
	}

	BaseType& BaseType::operator= (const BaseType &other)
	{
		ZOrder = other.ZOrder;
		return *this;
	}
	int BaseType::operator== (const BaseType &other) const
	{
		if (ZOrder != other.ZOrder) { return 0; }
		return 1;
	}

	//REQUIRED FOR SORTING
	int BaseType::operator< (const BaseType &other) const
	{
		if (ZOrder < other.ZOrder) { return 1; }
		return 0;
	}

	//DO NOT CALL THIS
	ModelType::ModelType()
	{
		model = 0;
		shader = 0;
		transform = 0;
		ZOrder = 0;
		data = 0;
	}

	ModelType::ModelType(const ModelType& other)
	{
		model = other.model;
		shader = other.shader;
		transform = other.transform;
		ZOrder = other.ZOrder;
		data = other.data;
		//*this = other;
	}
	
	ModelType::ModelType(Model* model,
			Shader* shader, Transform* transform, CullType* cull, PaintData* data)
	{
		this->model = model;
		this->shader = shader->Clone();
		this->transform = transform;
		this->cull = cull;
		this->ZOrder = 0;
		this->data = data->Clone();
	}

	ModelType::~ModelType()
	{
	}

	void ModelType::Render(ID3D11DeviceContext* deviceContext, Frustum* frustum, Viewport* viewport)
	{
		if (this->cull->IsInside(frustum, this->model->GetData()))
		{
			viewport->SetViewport(deviceContext, *this->data->viewport);
			viewport->RenderViewport(deviceContext);
			this->model->Render(deviceContext);
			this->shader->Render(deviceContext, model->GetIndexCount(),
				*(this->data->world), *(this->data->view), *(this->data->projection), *this->transform, this->model->GetOrientation());			
		}
		return;
	}
	BaseType* ModelType::Clone()
    {
		ModelType* i = new ModelType(*this);
		i->model = this->model;
		i->shader = this->shader;
		i->transform = this->transform;
		i->ZOrder = this->ZOrder;
		i->cull = this->cull;
        return i;
    }


	TextType::TextType()
	{
		this->m_text = 0;
		this->m_colorABGR = 0;
		this->m_fontfamily = 0;
		this->m_fontsize = 0;
		this->m_FW1_TEXT_FLAGs = 0;
		this->m_positionX = 0;
		this->m_positionY = 0;
		this->m_string = 0;
		this->ZOrder = 0;
	}
	TextType::TextType(const TextType& other)
	{
	}
	TextType::~TextType()
	{
	}

	TextType::TextType(Text* text, const WCHAR* string, const WCHAR* fontfamily,
			float positionX, float positionY, float fontsize,
			UINT32 colorABGR, UINT FW1_TEXT_FLAGs, PaintData* data)
	{
		this->m_text = text;
		this->m_colorABGR = colorABGR;
		this->m_fontfamily = fontfamily;
		this->m_fontsize = fontsize;
		this->m_FW1_TEXT_FLAGs = FW1_TEXT_FLAGs;
		this->m_positionX = positionX;
		this->m_positionY = positionY;
		this->m_string = string;
		this->ZOrder = 0;
		this->data = data;
	}
	void TextType::Render(ID3D11DeviceContext* deviceContext, Viewport* viewport)
	{
		viewport->SetViewport(deviceContext, *this->data->viewport);
		viewport->RenderViewport(deviceContext);
		m_text->Render(deviceContext, m_string, m_fontfamily,
			m_positionX, m_positionY, m_fontsize, m_colorABGR, 
			m_FW1_TEXT_FLAGs);
	}
	BaseType* TextType::Clone()
	{
		TextType* i = new TextType(*this);
		i->m_text = this->m_text;
		i->m_colorABGR = this->m_colorABGR;
		i->m_fontfamily = this->m_fontfamily;
		i->m_fontsize = this->m_fontsize;
		i->m_FW1_TEXT_FLAGs = this->m_FW1_TEXT_FLAGs;
		i->m_positionX = this->m_positionX;
		i->m_positionY = this->m_positionY;
		i->m_string = this->m_string;
		i->ZOrder = this->ZOrder;
		i->data = this->data;
        return i;
	}

	BitmapType::BitmapType()
	{
		bitmap = 0;
		shader = 0;
		transform = 0;
		ZOrder = 0;
		depth = 0;
		draw2D = false;
		data = 0;
	}
	
	BitmapType::BitmapType(const BitmapType& other)
	{
		shader = other.shader;
		bitmap = other.bitmap;
		transform = other.transform;
		m_bitmapHeight = other.m_bitmapHeight;
		m_bitmapWidth = other.m_bitmapWidth;
		m_positionX = other.m_positionX;
		m_positionY = other.m_positionY;
		depth = other.depth;
		draw2D = other.draw2D;
		this->ZOrder = other.ZOrder;
		ZOrder = this->ZOrder;
		data = other.data;
	}
	
	BitmapType::~BitmapType()
	{
	}

	BitmapType::BitmapType(Bitmap* bitmap, Shader* shader,
		Transform* transform, int positionX, int positionY,
		int bitmapWidth, int bitmapHeight, float depth,
		bool draw2D, PaintData* data)
	{
		this->bitmap = bitmap;
		this->shader = shader->Clone();
		this->transform = transform;
		this->m_bitmapHeight = bitmapHeight;
		this->m_bitmapWidth = bitmapWidth;
		this->m_positionX = positionX;
		this->m_positionY = positionY;
		this->depth = depth;
		this->ZOrder = 0;
		this->draw2D = draw2D;
		this->data = data->Clone();
	}

	BaseType* BitmapType::Clone()
	{
		BitmapType* i = new BitmapType(*this);
		i->bitmap = this->bitmap;
		i->shader = this->shader;
		i->transform = this->transform;
		i->ZOrder = this->ZOrder;
		i->m_bitmapHeight = this->m_bitmapHeight;
		i->m_bitmapWidth = this->m_bitmapWidth;
		i->m_positionX = this->m_positionX;
		i->m_positionY = this->m_positionY;
		i->depth = this->depth;
		i->draw2D = this->draw2D;
        return i;
	}

	void BitmapType::Render(D3D* d3d, Viewport* viewport)
	{
		viewport->SetViewport(d3d->GetDeviceContext(), *this->data->viewport);
		viewport->RenderViewport(d3d->GetDeviceContext());
		bitmap->Render(d3d->GetDeviceContext(), this->m_positionX, this->m_positionY, this->m_bitmapWidth,
			this->m_bitmapHeight, this->depth);
		if (draw2D)
		{
			d3d->TurnZBufferOff();
			shader->Render(d3d->GetDeviceContext(), bitmap->GetIndexCount(),
				*(this->data->world), *(this->data->view), *(this->data->ortho), *transform, this->bitmap->GetOrientation());
			d3d->TurnZBufferOn();
		}
		else
		{
			shader->Render(d3d->GetDeviceContext(), bitmap->GetIndexCount(),
				*(this->data->world), *(this->data->view), *(this->data->projection), *transform, this->bitmap->GetOrientation());
		}
		return;
	}

	/*TransformType::TransformType()
	{
		world = 0;
		projection = 0;
		ortho = 0;
		view = 0;
		force = false;
	}
	TransformType::TransformType(const TransformType& other)
	{
		world = other.world;
		view = other.view;
		projection = other.projection;
		ortho = other.ortho;
		force = other.force;
	}
	TransformType::TransformType(Transform* world, Transform* view,
		Transform* projection, Transform* ortho, bool force)
	{
		this->world = world;
		this->projection = projection;
		this->view = view;
		this->ortho = ortho;
		this->force = force;
	}
	TransformType::~TransformType()
	{
	}
	void TransformType::Render(D3D* d3d, 
		D3DXMATRIX &world, D3DXMATRIX &view, D3DXMATRIX &projection, D3DXMATRIX &ortho)
	{
		D3DXQUATERNION quad = D3DXQUATERNION();
		D3DXQuaternionRotationYawPitchRoll(&quad, this->world->rotation.x, this->world->rotation.y, this->world->rotation.z);
		D3DXMatrixTransformation(&world, NULL, NULL, &D3DXVECTOR3(this->world->scale.x, this->world->scale.y, this->world->scale.z),
			NULL, &quad, &D3DXVECTOR3(this->world->translation.x, this->world->translation.y, this->world->translation.z));

		quad = D3DXQUATERNION();
		D3DXQuaternionRotationYawPitchRoll(&quad, this->view->rotation.x, this->view->rotation.y, this->view->rotation.z);
		D3DXMatrixTransformation(&view, NULL, NULL, &D3DXVECTOR3(this->view->scale.x, this->view->scale.y, this->view->scale.z),
			NULL, &quad, &D3DXVECTOR3(this->view->translation.x, this->view->translation.y, this->view->translation.z));

		quad = D3DXQUATERNION();
		D3DXQuaternionRotationYawPitchRoll(&quad, this->projection->rotation.x, this->projection->rotation.y, this->projection->rotation.z);
		D3DXMatrixTransformation(&projection, NULL, NULL, &D3DXVECTOR3(this->projection->scale.x, this->projection->scale.y, this->projection->scale.z),
			NULL, &quad, &D3DXVECTOR3(this->projection->translation.x, this->projection->translation.y, this->projection->translation.z));

		quad = D3DXQUATERNION();
		D3DXQuaternionRotationYawPitchRoll(&quad, this->ortho->rotation.x, this->ortho->rotation.y, this->ortho->rotation.z);
		D3DXMatrixTransformation(&ortho, NULL, NULL, &D3DXVECTOR3(this->ortho->scale.x, this->ortho->scale.y, this->ortho->scale.z),
			NULL, &quad, &D3DXVECTOR3(this->ortho->translation.x, this->ortho->translation.y, this->ortho->translation.z));
		
	}

	BaseType* TransformType::Clone()
	{
		TransformType* i = new TransformType(*this);
		i->force = this->force;
		i->ortho = this->ortho;
		i->projection = this->projection;
		i->view = this->view;
		i->world = this->world;
		return i;
	}*/

	Painter::Painter()
	{
		z = std::vector<BaseType*>();
	}
	Painter::Painter(const Painter &other)
	{
	}
	Painter::~Painter()
	{
	}

	void Painter::AddToFront(BaseType& item)
	{
		item.ZOrder = 0;
		if (!z.empty())
		{
			BaseType* front;
			std::sort(z.begin(), z.end(), Compare);

			//z.BACK = FRONT

			front = z.back(); //z.front or z.back?
			float loc = front->ZOrder - 1;
			item.ZOrder = loc;
		}
		BaseType* base = item.Clone();
		//BaseType* base = dynamic_cast<BaseType*>((BaseType*)&model);
		z.push_back(base);
		return;
	}
	void Painter::ClearList()
	{
		z.clear();
	}
	void Painter::Render(D3D* d3d, Frustum* frustum, Viewport* viewport, 
		D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX projection, D3DXMATRIX ortho)
	{
		std::sort(z.begin(), z.end(), Compare);
		for( vector<BaseType*>::iterator p=z.begin(); p!=z.end(); ++p)
		{
			//process(*p); RENDER BACK TO FRONT

			//FRONT = negatives
			//BACK = positives
			//sort list greatest to least so back renders first

			BaseType* base = *p;
			int type = base->GetType();
			if (type == 1)
			{
				ModelType* model = (ModelType*)base;
				model->transform = &xforce(*model->transform, Rad);
				model->Render(d3d->GetDeviceContext(), frustum, viewport);
			}
			if (type == 2)
			{
				TextType* text = (TextType*)base;
				text->Render(d3d->GetDeviceContext(), viewport);
			}
			if (type == 3)
			{
				BitmapType* bitmap = (BitmapType*)base;
				bitmap->transform = &xforce(*bitmap->transform, Rad);
				bitmap->Render(d3d, viewport);
			}
			/*if (type == 4)
			{
				TransformType* transform = (TransformType*)base;
				transform->Render(d3d, world, view, projection, ortho);
			}*/
		}
		return;
	}
}