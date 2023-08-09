#pragma once
#include <list>
#include <map>
class AnimationAsset;
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	static ID2D1HwndRenderTarget* m_pRenderTarget;
	static D2DRenderer* m_instance;
private:
	HWND m_hwnd;
	ID2D1Factory* m_pD2DFactory; //D2D ��ü �������̽� ������ ����
	IWICImagingFactory* m_pWICFactory; // ��Ʈ�� ���� �ϴµ� �ʿ��� ���丮
	IDWriteFactory* m_pDWriteFactory;	// TextFormat������ ���� ���丮
	IDWriteTextFormat* m_pDWriteTextFormat; // �⺻ �ؽ�Ʈ ����� ���� Format

	ID2D1SolidColorBrush* m_pBrush;	// ����Ÿ���� �����ϴ� ���ҽ� ���� ��ġ����

	map<wstring, AnimationAsset*> m_sharingAnimationAssets;
	map<wstring, ID2D1Bitmap*> m_sharingBitmaps;
public:
	HRESULT Initialize(HWND hwnd);

	ID2D1Bitmap* CreateBitmapFromFile(wstring strFilePath);
	AnimationAsset* CreateAnimationAsset(wstring strFilePath);

	void DrawRectangle(ID2D1RenderTarget* pRenderTarget, D2D1_RECT_F rect, D2D1_COLOR_F color);
	AnimationAsset* CreateAnimationAssetFromFile(wstring strFilePath);
	void ReleaseBitmap(wstring strFilePath);
	void ReleaseBitmap(ID2D1Bitmap* pBitmap);
	void ReleaseAnimationAsset(wstring strFilePath);
	void ReleaseAnimationAsset(AnimationAsset* pAsset);
	void EndDraw();

	ID2D1SolidColorBrush* GetBrush() const { return m_pBrush; }

	void LoadResource(wstring _folderPath);

};

