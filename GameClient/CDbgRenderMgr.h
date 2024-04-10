#pragma once
class CDbgRenderMgr
{
	SINGLE(CDbgRenderMgr)

private:
	list<DbgRenderInfo>	  m_RenderList;
	list<DbgLog>		  m_LogList;
	list<DbgObjInfo>	  m_InfoList;
	float				  m_LogLife;
	int					  m_LogSpace;
	Vec2D				  m_LogStartPos;

	bool				  m_bRender;

public:
	void AddDbgRenderInfo(const DbgRenderInfo& _info)
	{
		m_RenderList.push_back(_info);
	}

	void AddDbgLog(const DbgLog& _info) 
	{
		m_LogList.push_back(_info);
	}

	void AddDbgObjInfo(const DbgObjInfo& _info)
	{
		m_InfoList.push_back(_info);
	}

	bool IsDbgRender() { return m_bRender; }

public:
	void tick();
	void render();
};

