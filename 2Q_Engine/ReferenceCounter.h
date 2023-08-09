#pragma once
class ReferenceCounter // Animation Asset���� ��Ʈ�ʰ� ���� ���� ī��Ʈ Ȯ���� ���� ���� Ŭ����
{
private:
	unsigned int m_refCount;
public:
	ReferenceCounter():m_refCount(0) {}
	virtual ~ReferenceCounter() {}

	unsigned int AddRef()
	{
		m_refCount++;
		return m_refCount;
	}

	unsigned int Release()
	{
		assert(m_refCount != 0, "Release Error");
		m_refCount--;
		if (m_refCount == 0)
		{
			delete this;
			return 0;
		}
		return m_refCount;
	}

	unsigned int GetRefCount()
	{
		return m_refCount;
	}
};

