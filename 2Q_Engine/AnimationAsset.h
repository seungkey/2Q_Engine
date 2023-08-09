#pragma once
#include "ReferenceCounter.h"

struct FrameInfo // �ִϸ��̼ǿ� ����� ������ ����
{
	D2D1_RECT_F rect;

	FrameInfo()
		:rect{ 0.f,0.f,0.f,0.f }
	{}

	FrameInfo(float top, float left, float bottom, float right)
		: rect{ top,left,bottom,right }
	{}

};

struct AnimationInfo
{
	string m_name;
	float progressTime;
	vector<FrameInfo> m_frames;
};

class AnimationAsset :
	public ReferenceCounter
{
public:
	AnimationAsset();
	virtual ~AnimationAsset();

public: // �ϴ� �ۺ����� �غ�(private�� �ٲ� �� ������ �ٲ� ����)
	ID2D1Bitmap* m_pBitmap;
	vector<AnimationInfo> m_animations;
public:
	void SetBitmap(ID2D1Bitmap* pBitmap);
	ID2D1Bitmap* GetBitmap() { return m_pBitmap; }
	AnimationInfo* GetAnimationInfo(const string animationName);


};

