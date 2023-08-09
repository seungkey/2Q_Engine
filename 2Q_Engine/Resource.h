#pragma once

#include <filesystem>

class D2DRenderer;
class World;

class Resource
{
public:
	Resource();
	~Resource();

	void Initialize();
	void Finalize() {}

	void LoadAnimation(wstring _animPath, D2DRenderer* _pRenderer);

protected:
	void LoadAnimInfoFromTextFile(filesystem::path _filePath, D2DRenderer* _pRenderer);

};

