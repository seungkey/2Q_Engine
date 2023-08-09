#include "pch.h"

#include "D2DRenderer.h"

#include "AnimationAsset.h"
#include "GameProcess.h"

#include <istream>
#include <fstream>
#include <filesystem>

namespace FS = std::filesystem;

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")	// writefactory

ID2D1HwndRenderTarget* D2DRenderer::m_pRenderTarget = nullptr;
D2DRenderer* D2DRenderer::m_instance = nullptr;

D2DRenderer::D2DRenderer()
	: m_pD2DFactory(nullptr)
	, m_pDWriteFactory(nullptr)
	, m_pDWriteTextFormat(nullptr)
	, m_pWICFactory(nullptr)
	, m_pBrush(nullptr)
	, m_hwnd(NULL)
{
}

D2DRenderer::~D2DRenderer()
{
	if (m_pD2DFactory != nullptr)
	{
		m_pD2DFactory->Release();
		m_pD2DFactory = nullptr;
	}
		
	if (m_pDWriteFactory != nullptr)
	{
		m_pDWriteFactory->Release();
		m_pDWriteFactory = nullptr;
	}
	
	if (m_pDWriteTextFormat != nullptr)
	{
		m_pDWriteTextFormat->Release();
		m_pDWriteTextFormat = nullptr;
	}

	if (m_pWICFactory != nullptr)
	{
		m_pWICFactory->Release();
		m_pWICFactory = nullptr;
	}

	if (m_pBrush != nullptr)
	{
		m_pBrush->Release();
		m_pBrush = nullptr;
	}
}

HRESULT D2DRenderer::Initialize(HWND hwnd)
{
	HRESULT hr = S_OK;
	// COM ��� ����
	hr = CoInitialize(NULL);
	m_hwnd = hwnd;
	if (SUCCEEDED(hr))
	{
		/*	��ġ�� ���ε����� ���� ���ҽ��� ����ϴ�.������ ���� ���ӵǴ� ���� ȿ�������� ����˴ϴ�.
			�̷��� ���ҽ����� Direct2D �� DirectWrite ���͸���
			DirectWrite �ؽ�Ʈ ���� ��ü(Ư�� �۲� Ư���� �ĺ��ϴ� �� ����)�� ���Ե˴ϴ�.
		*/
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	}
	if (SUCCEEDED(hr))
	{
		/*
		Direct3D ��ġ�� ���ε��� ���ҽ��� ����ϴ�.
		Direct3D ��ġ�� �սǵ� ���(��: ���÷��� ����, ����, ���� ī�� ���� ��)
		���ҽ��� �ٽ� �����ؾ� �ϴ� ��츦 ����Ͽ� ��� ���⿡ �߾� ����ȭ�Ǿ� �ֽ��ϴ�.
		*/

		RECT rc;
		::GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U ScreenSize = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);


		// Create a Direct2D render target.
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, ScreenSize),
			&m_pRenderTarget);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	}

	if (SUCCEEDED(hr))
	{
		// Create WIC factory
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pWICFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite ���͸��� ����ϴ�.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		// DirectWrite �ؽ�Ʈ ���� ��ü�� ����ϴ�.
		hr = m_pDWriteFactory->CreateTextFormat(
			L"", // FontName    ������-���������-�׸�-�۲�-Ŭ�� ���� �۲��̸� Ȯ�ΰ���
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,   // Font Size
			L"", //locale
			&m_pDWriteTextFormat
		);
	}

	// �귯��, DXGI ���丮�� �ʿ� ���� �� ���� �������� �ʾ���. ���� �ʿ������� ������ ����

	return hr;
}

ID2D1Bitmap* D2DRenderer::CreateBitmapFromFile(wstring strFilePath)
{
	ID2D1Bitmap* ppID2D1Bitmap = nullptr;
	// ���ڿ��� ������ �ֿ��� ���ڿ��� ������ �ش� ���Ҹ� ã�´�.
	auto it = m_sharingBitmaps.find(strFilePath);
	if (it != m_sharingBitmaps.end())
	{
		ID2D1Bitmap* pBitmap = it->second;
		ppID2D1Bitmap = pBitmap;
		pBitmap->AddRef();
		return ppID2D1Bitmap;
	}

	// �����̳ʿ� �̹� ���� ��ΰ� ������ �ٽ� ������ �ʴ´�. 
	// �� ���� ��Ʈ���� ���۷��� ������Ű�� ������ ������ ���� �ִ´�.
	HRESULT hr;
	

	// Create a decoder
	IWICBitmapDecoder* pDecoder = NULL;
	IWICFormatConverter* pConverter = NULL;

	hr = m_pWICFactory->CreateDecoderFromFilename(
		strFilePath.c_str(),                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	IWICBitmapFrameDecode* pFrame = NULL;
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = m_pWICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &ppID2D1Bitmap);
	}

	// ������ ����Ҷ����� �ٽ� �����.
	if (pConverter)
		pConverter->Release();

	if (pDecoder)
		pDecoder->Release();

	if (pFrame)
		pFrame->Release();

	

	m_sharingBitmaps.insert(make_pair(strFilePath, ppID2D1Bitmap));
	return ppID2D1Bitmap;
}

AnimationAsset* D2DRenderer::CreateAnimationAsset(wstring strFilePath)
{
	AnimationAsset* pAsset;
	auto it = m_sharingAnimationAssets.find(strFilePath);
	if (it != m_sharingAnimationAssets.end())
	{
		pAsset = it->second;
		pAsset->AddRef();
		return pAsset;
	}

	pAsset = new AnimationAsset;
	pAsset->SetBitmap(CreateBitmapFromFile(strFilePath));
	m_sharingAnimationAssets.insert(make_pair(strFilePath, pAsset));
	pAsset->AddRef();
	return pAsset;
}

void D2DRenderer::DrawRectangle(ID2D1RenderTarget* pRenderTarget, D2D1_RECT_F rect, D2D1_COLOR_F color)
{
	m_pBrush->SetColor(color);
	pRenderTarget->DrawRectangle(rect, m_pBrush);
}

// �ؽ�Ʈ ���Ϸ� �ִϸ��̼� ��� �߰� (Ű�� �״�� �̹��� ���� �����)
// testLoadMotion.txt ���Ĵ�� �����ؾ� ��� ����
AnimationAsset* D2DRenderer::CreateAnimationAssetFromFile(wstring strFilePath)
{
	std::ifstream file(strFilePath);
	assert(file.is_open());

	AnimationAsset* pAsset = nullptr;
	AnimationInfo pInfo{ "" };

	string line;

	bool isFirtLine = true;
	bool isNameLine = false;

	// ���پ� ���� �б�
	while (getline(file, line))
	{
		// ù�ٿ� ���� �̹��� ���� ��η� ��� �߰�
		if (isFirtLine)
		{
			isFirtLine = false;
			wstring wstr;
			wstr.assign(line.begin(), line.end());
			pAsset = CreateAnimationAsset(wstr);
			continue;
		}

		if (line.empty())
		{
			isNameLine = true;
			if(pInfo.m_name != "")
				pAsset->m_animations.push_back(pInfo);
			pInfo = AnimationInfo{};
			continue;
		}

		const string delimiter = ",";
		size_t pos = 0, index = 0;

		// �ִϸ��̼� ������ �̸��� �ӵ�
		if (isNameLine)
		{
			if (line.empty()) break;

			isNameLine = false;

			while (pos != std::string::npos)
			{
				pos = line.find(delimiter);
				string token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());

				switch (index)
				{
					case 0:
						pInfo.m_name = token;
						break;
					case 1:
						pInfo.progressTime = stof(token);
						break;
				}
				index++;
			}

			continue;
		}


		float top, left, bottom, right;

		// �� ���� ��� frame info �߰�
		while (pos != std::string::npos)
		{
			pos = line.find(delimiter);
			string token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());

			switch (index)
			{
				case 0:
					top = stof(token);
					break;
				case 1:
					left = stof(token);
					break;
				case 2:
					bottom = stof(token);
					break;
				case 3:
					right = stof(token);
					break;
			}
			index++;
		}
		// �� �� �� ������ ���� �߰�
		pInfo.m_frames.push_back(FrameInfo(top, left, bottom, right));
	}

	if(pAsset!=nullptr && pInfo.m_name != "") pAsset->m_animations.push_back(pInfo);

	file.close();
	return pAsset;

}

void D2DRenderer::ReleaseBitmap(wstring strFilePath)
{
	auto it = m_sharingBitmaps.find(strFilePath);

	int count = it->second->Release();

	if (count > 0)
		return;

	if (it != m_sharingBitmaps.end())
		m_sharingBitmaps.erase(it);
}

void D2DRenderer::ReleaseBitmap(ID2D1Bitmap* pBitmap)
{
	auto it = std::find_if(m_sharingBitmaps.begin(), m_sharingBitmaps.end(), [&](const auto& pair) {
		return pair.second == pBitmap;
		});

	int count = it->second->Release();

	if (count > 0)
		return;

	if (it != m_sharingBitmaps.end())
		m_sharingBitmaps.erase(it);
}



void D2DRenderer::ReleaseAnimationAsset(wstring strFilePath) // �ִϸ��̼� Release���� �� Bitmap�� ���� Release ����� �ϴ°�?
{
	auto it = m_sharingAnimationAssets.find(strFilePath);

	int count = it->second->Release();

	if (count > 0)
		return;
	if (it != m_sharingAnimationAssets.end())
		m_sharingAnimationAssets.erase(it);
}

void D2DRenderer::ReleaseAnimationAsset(AnimationAsset* pAsset)
{
	auto it = std::find_if(m_sharingAnimationAssets.begin(), m_sharingAnimationAssets.end(), [&](const auto& pair) {
		return pair.second == pAsset;
		});

	int count = it->second->Release();

	if (count > 0)
		return;

	if(it !=m_sharingAnimationAssets.end())
		m_sharingAnimationAssets.erase(it);
}


void D2DRenderer::EndDraw() // �׷���ī�忡 ������ ���� ��� EndDraw�� ���� ���� ��찡 �ֱ� ������ ���� ó������
{
	HRESULT hr = m_pRenderTarget->EndDraw();
	assert(hr == S_OK, "EndDraw Error");
}

// ���� ��θ� �޾Ƽ� �ѹ��� ��Ʈ��, �ִϸ��̼� ��� �����ϴ� �Լ�
void D2DRenderer::LoadResource(wstring _folderPath)
{
	FS::path folderPath(_folderPath);

	assert(FS::exists(folderPath) && FS::is_directory(folderPath));

	for (const auto& entry : FS::directory_iterator(folderPath))
	{
		const FS::path& filePath = entry.path();

		if (!FS::is_regular_file(filePath) || !filePath.has_extension()) continue;

		// ���� Ȯ���ڸ� �޾Ƽ� �ҹ��ڷ� ��ȯ�Ѵ�
		std::wstring fileExtension = filePath.extension().c_str();
		std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);

		std::wstring wFilePath = filePath.wstring();

		// �̹��� �����̸� ��Ʈ�� �߰�
		if (fileExtension == L".jpg" || fileExtension == L".jpeg" || fileExtension == L".png"
			|| fileExtension == L".bmp" || fileExtension == L".webp")
		{
			CreateBitmapFromFile(wFilePath);
		}
		// �ؽ�Ʈ �����̸� ��� �߰�
		else if (fileExtension == L"txt")
		{
			//CreateAnimationAssetFromFile(wFilePath); 
		}
	}
}



