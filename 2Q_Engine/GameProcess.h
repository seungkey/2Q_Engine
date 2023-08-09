#include "../2Q_Engine/pch.h"

class D2DRenderer;
class Time;
class Input;
class World;

class CollisionManager;
class Player;
class Ground;
class Ground2;

class GameProcess
{
private:
	HWND m_hwnd;
	MSG m_msg;
	D2DRenderer* m_D2DRenderer;
	Time* time;
	Input* m_pInput;
	World* m_pWorld;
	CollisionManager* collisionManger;
	Player* m_player;
	vector<Ground*> m_ground;
	
	

	const int m_screenWidth = 1024;
	const int m_screenHeight = 768;

	
	WCHAR m_szTitle[100];
public:
	HRESULT Initialize(HINSTANCE hInstance);


	void Loop();
	void GameLoop();
	void Update(float dt);
	void Render();

	void CalculateFps(float dt);

	void Finalize();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};