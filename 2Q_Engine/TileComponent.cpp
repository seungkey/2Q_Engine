#include "pch.h"
#include "TileComponent.h"

#include "World.h"
#include "GameObject.h"

#define TileSize 185 // 가로 세로 동일

TileMapManager::TileMapManager(World* _world)
	:m_pWorld(_world)
{
}

void TileMapManager::SetTileMapSize(POINT _tileMapSize)
{
	for (int i = 0; i < _tileMapSize.y; i++)
	{
		for (int j = 0; j < _tileMapSize.x; j++)
		{
			GameObject* newObj = m_pWorld->CreateGameObject<GameObject>();
			TileComponent* tile = newObj->AddComponent<TileComponent>("tile");
			tile->SetTilePos({ j, i });
		}
	}
}

void TileComponent::SetTilePos(POINT _tilePos)
{
	m_tilePos = _tilePos;
	m_relativeTranslation.x = _tilePos.x * TileSize + TileSize/2;
	m_relativeTranslation.y = _tilePos.y * TileSize + TileSize / 2;
}
