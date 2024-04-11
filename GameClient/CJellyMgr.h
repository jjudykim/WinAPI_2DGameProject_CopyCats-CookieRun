#pragma once

class CJelly;

class CJellyMgr
{
	SINGLE(CJellyMgr)
private:
	vector<CJelly*> m_arrJelly[(UINT)DYNAMIC_OBJ_TYPE::END];

public:
	void init();
	void LoadJellyInfo();
	const vector<CJelly*>& GetVecJelly(UINT _Type) { return m_arrJelly[_Type]; }
};

