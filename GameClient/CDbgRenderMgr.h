#pragma once
class CDbgRenderMgr
{
	SINGLE(CDbgRenderMgr)

private:
	list<DbgRenderInfo>  m_RenderList;
	list<DbgLog>		  m_LogList;

	float				  m_LogLife;
	int					  m_LogSpace;
	Vec2D				  m_LogStartPos;

public:
	void AddDbgRenderInfo(const DbgRenderInfo& _info)
	{
		m_RenderList.push_back(_info);
	}

	void AddDbgLog(const DbgLog& _info) 
	{
		m_LogList.push_back(_info);
	}

public:
	void tick();
	void render();
};

