#include "pch.h"
#include "func.h"

#include "CDbgRenderMgr.h"

void DebugLog(LOG_TYPE _Type, const wchar_t* _LogMgs)
{
	DbgLog log = {};
	log.Type = _Type;
	log.strLog = _LogMgs;

	CDbgRenderMgr::GetInst()->AddDbgLog(log);
}

void DebugLog(LOG_TYPE _Type, wstring _LogMgs)
{
	DbgLog log = {};
	log.Type = _Type;
	log.strLog = _LogMgs;

	CDbgRenderMgr::GetInst()->AddDbgLog(log);
}

void DrawDebugRect(PEN_TYPE _Type, Vec2D _Pos, Vec2D _Scale, float _Time)
{
	DbgRenderInfo info{};
	info.Shape = DBG_SHAPE::RECT;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	CDbgRenderMgr::GetInst()->AddDbgRenderInfo(info);
}

void DrawDebugCircle(PEN_TYPE _Type, Vec2D _Pos, Vec2D _Scale, float _Time)
{
	DbgRenderInfo info{};
	info.Shape = DBG_SHAPE::CIRCLE;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	CDbgRenderMgr::GetInst()->AddDbgRenderInfo(info);
}

void DrawDebugLine(PEN_TYPE _Type, Vec2D _Start, Vec2D _End, float _Time)
{
	DbgRenderInfo info{};
	info.Shape = DBG_SHAPE::LINE;
	info.Color = _Type;
	info.Position = _Start;
	info.Scale = _End;
	info.Duration = _Time;
	info.Age = 0.f;

	CDbgRenderMgr::GetInst()->AddDbgRenderInfo(info);
}