#ifndef EPITOME_TEXT
#define EPITOME_TEXT

#pragma warning (disable:4005)
#include <FW1FontWrapper.h>
#pragma comment (lib, "FW1FontWrapper.lib")

namespace EPITOME
{
	class Text
	{
	public:
		Text();
		Text(const Text&);
		~Text();

		bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		void Render(ID3D11DeviceContext* deviceContext, const WCHAR* string, const WCHAR* fontfamily, float positionX, float positionY, float fontsize,
						   UINT32 colorABGR, UINT FW1_TEXT_FLAGs);
		void Shutdown();
	private:
		IFW1FontWrapper *m_fontwrapper;
		D3D11_VIEWPORT *m_viewport;
	};
}

#endif