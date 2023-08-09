#pragma once
#include "RenderComponent.h"
class World;
class TileComponent;
class TileMapManager
{
public:
	TileMapManager(World* _world);
	virtual ~TileMapManager() { }

	void SetTileMapSize(POINT _tileMapSize);

protected:
	POINT m_tileMapSize;
	World* m_pWorld;
	TileComponent* m_curSelectedTile;
};

#include "BitmapComponent.h"
class TileComponent : public BitmapComponent
{
public:
	TileComponent(GameObject* pOwner, const string name, TransformComponent* pRoot)
		:BitmapComponent(pOwner, name, pRoot), m_tilePos()
	{
	}

	virtual ~TileComponent() { }

	void SetTilePos(POINT _tilePos);

protected:
	POINT m_tilePos;
};

