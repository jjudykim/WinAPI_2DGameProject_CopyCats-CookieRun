#pragma once
class CDbgRenderMgr
{
	SINGLE(CDbgRenderMgr)

private:
	list<tDbgRenderInfo>  m_RenderList;
	list<tDbgLog>		  m_LogList;

	float				  m_LogLife;
	int					  m_LogSpace;
	Vec2D				  m_LogStartPos;

public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info)
	{
		m_RenderList.push_back(_info);
	}

public:
	void tick();
	void render();
};

