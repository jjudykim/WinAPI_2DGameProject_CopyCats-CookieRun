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
