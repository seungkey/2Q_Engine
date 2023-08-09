#include "pch.h"

#include "AnimationComponent.h"

#include "D2DRenderer.h"
#include "RenderComponent.h"
#include "AnimationAsset.h"

AnimationComponent::AnimationComponent(GameObject* pOwner, string name, TransformComponent* pRoot)
	: RenderComponent(pOwner, name, pRoot)
	, m_animationIndex(0)
	, m_curFrameIndex(0)
	, m_prevFrameIndex(0)
	, m_bLoop(true)
	, m_bReverse(false)
	, m_pAnimationAsset(nullptr)
	, m_pAnimationInfo(nullptr)
	, m_speed(1.f)
	, m_cumulativeTime(0.f)
{
	m_destRect = { 0.f,0.f,0.f,0.f };
	m_srcRect = { 0.f,0.f,0.f,0.f };
}

AnimationComponent::~AnimationComponent()
{
	D2DRenderer::m_instance->ReleaseAnimationAsset(m_pAnimationAsset);
}

void AnimationComponent::Update(float dt)
{
	__super::Update(dt);

	assert(m_pAnimationAsset != nullptr);

	if (m_pAnimationInfo == nullptr)
		return;

	float progressTime = m_pAnimationInfo->progressTime;

	m_prevFrameIndex = m_curFrameIndex;
	m_cumulativeTime += dt * m_speed;
	if (m_cumulativeTime >= progressTime)
	{
		m_cumulativeTime = 0;
		m_curFrameIndex++;
		if (m_bLoop)
		{
			m_curFrameIndex = m_curFrameIndex % m_pAnimationInfo->m_frames.size();
		}
		else
		{
			m_curFrameIndex = min(m_curFrameIndex,m_pAnimationInfo->m_frames.size() - 1);
		}
	}

	m_srcRect = m_pAnimationInfo->m_frames[m_curFrameIndex].rect;
	m_destRect = { -(m_srcRect.right - m_srcRect.left) / 2
				 , -(m_srcRect.bottom - m_srcRect.top) / 2
				 , (m_srcRect.right - m_srcRect.left) / 2
				 , (m_srcRect.bottom - m_srcRect.top) / 2 };


}

void AnimationComponent::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	D2D1_MATRIX_3X2_F transform;
		
	transform = m_relativeTransform;

	if (m_bReverse == true)
	{
		transform = transform * D2D1::Matrix3x2F::Scale(-1.f, 1.f);
	}

	transform = transform * m_pParentComponent->GetWorldTransform();
	if (m_pAnimationInfo == nullptr)
		return;

	pRenderTarget->SetTransform(transform);
	pRenderTarget->DrawBitmap(m_pAnimationAsset->GetBitmap(), m_destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_srcRect);
}

bool AnimationComponent::Initialize()
{
	return false;
}

void AnimationComponent::SetAnimationAsset(const wstring strAssetKey)
{
	m_pAnimationAsset = D2DRenderer::m_instance->CreateAnimationAssetFromFile(strAssetKey);
}

void AnimationComponent::SetAnimation(const string name, bool mirror, bool loop)
{
	m_bLoop = loop;
	m_bReverse = mirror;
	m_pAnimationInfo = m_pAnimationAsset->GetAnimationInfo(name);
	assert(m_pAnimationInfo != nullptr, "Animation Info is nullptr");
}
