#pragma once

class CObject;

class CTaskMgr
{
	SINGLE(CTaskMgr)

private:
	vector<Task> m_vecTask;
	vector<CObject*> m_GC;

public:
	void tick();
	void AddTask(const Task& _Task) { m_vecTask.push_back(_Task); }

private:
	void ClearGC();
	void ExectueTask();
};

