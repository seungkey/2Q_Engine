#include "pch.h"
#include "World.h"

#include "GameObject.h"
#include "Resource.h"
#include "D2DRenderer.h"
#include "AnimationComponent.h"
#include "BitmapComponent.h"
#include "TileComponent.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;



World::World()
{
    // 비트맵 출력 이렇게
    //GameObject* bitObj = CreateGameObject<GameObject>();
    //TileComponent* bit = bitObj->AddComponent<TileComponent>("bit");
    ////bit->SetTilePos(POINT{ 0,0 });
    //bit->SetRelativeScale({ 0.25,0.25 });
    //bit->SetBitmap(L"../Resource/tile.jpg");


    //GameObject* bitObj2 = CreateGameObject<GameObject>();
    //TileComponent* bit2 = bitObj->AddComponent<TileComponent>("bit");
    ////bit2->SetTilePos(POINT { 1,1 });
    //bit2->SetRelativeScale({ 0.25,0.25 });
    //bit2->SetBitmap(L"../Resource/tile.jpg");

}

World::~World()
{
    for (size_t i = 0; i < m_gameObjects.size(); i++)
    {
        delete m_gameObjects[i];
    }
}

void World::Enter()
{
}

void World::Initialize()
{
}

void World::Update(float dt)
{
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update(dt);
	}
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Render(pRenderTarget);
	}
}


void World::Exit()
{
}

void World::LoadWorld(string _path)
{
    std::ifstream file(_path);
    assert(file.is_open());

    json world_data;
    file >> world_data;

    for (const auto& obj_data : world_data)
    {
        GameObject* obj = CreateGameObject<GameObject>();

        obj->SetTag(obj_data["name"]);

        if (obj_data.contains("anim"))
        {
            int index = 0;
            AnimationComponent* anim = obj->AddComponent<AnimationComponent>();
            //tc->SetParentTransform(obj_data["TransformComponent"][index++]);
            anim->SetRelativeTranslation({ obj_data["anim"][index++] ,obj_data["anim"][index++] });
            anim->SetRelativeRotation(obj_data["anim"][index++]);
            anim->SetRelativeScale({ obj_data["anim"][index++], obj_data["anim"][index++] });
            anim->SetAnimation(obj_data["anim"][index++], obj_data["anim"][index++], obj_data["anim"][index++]);
            anim->SetAnimationAsset(obj_data["anim"][index++]);
        }
    }
    file.close();

}

void World::SaveWorld(string _path)
{
    json world_data;
    for (const auto& obj : m_gameObjects)
    {
        json obj_data;
        obj_data["name"] = obj->GetTag();

        AnimationComponent* anim = obj->GetComponent<AnimationComponent>("AnimationComponent");
        if (anim != NULL)
        {
            obj_data["AnimationComponent"] =
            {
                //anim->GetParentTransform(),
                anim->GetRelativeRotation(),
                anim->GetRelativeScale().x, anim->GetRelativeScale().y,
                anim->GetRelativeTranslation().x, anim->GetRelativeTranslation().y
                //anim->GetAnimationData1(), anim->GetAnimationData2(),anim->GetAnimationData3(),
                //anim->GetAnimationAsset()
            };
        }

        world_data.push_back(obj_data);
    }

    std::ofstream file{ _path };
    assert(file.is_open());

    file << world_data.dump(2);
    file.close();
}
