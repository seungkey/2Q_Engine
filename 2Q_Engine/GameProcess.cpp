#include "pch.h"
#include "D2DRenderer.h"
#include "GameProcess.h"
#include "Time.h"
#include "Input.h"
#include "World.h"
#include "Player.h"
#include "Ground.h"
#include "Ground2.h"
#include "CollisionManager.h"


HRESULT GameProcess::Initialize(HINSTANCE hInstance)
{
#pragma region _WINDOWINIT_
	/// Win32 관련
	// 윈도 클래스
	WCHAR szAppName[] = L"Direct2D Demo";
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = GameProcess::WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// 윈도 클래스 등록
	RegisterClass(&wndclass);

	// 윈도 생성
	m_hwnd = CreateWindow(
		szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 100, m_screenWidth, m_screenHeight,
		NULL, NULL, hInstance, NULL);

	if (!m_hwnd) return S_FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);

	m_D2DRenderer = new D2DRenderer;
	D2DRenderer::m_instance = m_D2DRenderer;
	HRESULT hr = m_D2DRenderer->Initialize(m_hwnd);

	
	time = new Time;
	time->Initialize();
	collisionManger = new CollisionManager;
	

	m_pInput = new Input(m_hwnd);
	m_pWorld = new World();
	m_pInput->m_pInputInstance = m_pInput;
	m_pInput->m_pInputInstance = m_pInput;

	m_pInput->Initialize();
	m_pWorld->Initialize();

	m_player =  m_pWorld->CreateGameObject<Player>();
	m_player->Initialize();
	collisionManger->SetPlayerCollider(m_player->m_boxCollider);

	for (int i = 0; i < 20; i++)
	{
		m_ground.push_back(m_pWorld->CreateGameObject<Ground>());
		m_ground[i]->SetCollider(Vector2D(32+(64*i), 700-(64*(i/2))), Vector2D(32, 32));
		collisionManger->AddCollider(m_ground[i]->GetCollider());
	}


	return S_OK;
}



void GameProcess::Loop()
{
	while (true)
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT) break;

			DispatchMessage(&m_msg);
		}
		else
		{	
			time->Update();
			
			time->m_elapsedTime += time->GetDeltaTime();
			Update(time->GetDeltaTime());
			Render();
		}

	}
}

void GameProcess::GameLoop()
{

}

void GameProcess::Update(float dt)
{
	m_pInput->Update();
	while (time->m_elapsedTime >= 0.015)
	{
		time->m_elapsedTime -= 0.015;
		collisionManger->Update();
		m_pWorld->Update(0.015);
		CalculateFps(0.015);

		
	}
	
}

void GameProcess::Render()
{
	m_D2DRenderer->m_pRenderTarget->BeginDraw();
	m_D2DRenderer->m_pRenderTarget->Clear();
	m_pWorld->Render(m_D2DRenderer->m_pRenderTarget);
	m_D2DRenderer->m_pRenderTarget->EndDraw();
}

void GameProcess::CalculateFps(float dt)
{
	static int frameCnt = -1;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if (frameCnt == 0)
		return;

	timeElapsed += dt;

	//1초동안의 프레임 시간의 평균을 계산합니다.
	if (timeElapsed >= 1.0f)
	{
		float fps = (float)frameCnt;  //Frame Per Second
		float spf = 1000.0f / fps;   // MilliSecond Per Frame

		std::wstring windowText;
		windowText.append(m_szTitle);
		windowText.append(L"  FPS: ");
		windowText.append(std::to_wstring(fps));
		windowText.append(L"  SPF: ");
		windowText.append(std::to_wstring(spf));
		windowText.append(L" Used VRAM: ");


		SetWindowText(m_hwnd, windowText.c_str());

		//다음 계산을위해 리셋
		frameCnt = 0;
		timeElapsed -= 1.0f;
	}
}

void GameProcess::Finalize()
{
	delete m_D2DRenderer;
	delete m_pInput;
	delete m_pWorld;
	delete time;
	delete collisionManger;
}

LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}