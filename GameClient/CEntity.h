#pragma once

class CEntity
{
private:
	static UINT g_NextID;

private:
	const UINT m_ID;
	wstring m_strName;

public:
	UINT GetID() { return m_ID; }
	const wstring& GetName() { return m_strName; }

	void SetName(const wstring& _Name) { m_strName = _Name; }

public:
	virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _Other);
	virtual ~CEntity();
};

