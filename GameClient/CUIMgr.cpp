#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CLevel.h"
#include "CUI.h"

CUIMgr::CUIMgr()
	: m_FocusedUI(nullptr)
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::tick()
{
	bool LBtnTap = KEY_TAP(KEY::LBTN);
	bool LBtnReleased = KEY_RELEASED(KEY::LBTN);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (pCurLevel == nullptr) return;

	vector<CObject*>& vecUI = pCurLevel->m_arrObj[(UINT)LAYER_TYPE::UI];

	CUI* pFocusedUI = nullptr;

	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		CUI* pParent = (CUI*)(*iter);
		if (pParent->IsMouseOn())
		{
			pFocusedUI = pParent;
		}
	}

	if (nullptr == pFocusedUI) return;

	CUI* pPriorityUI = GetPriorityUI(pFocusedUI);
	assert(pPriorityUI);

	if (LBtnTap)
	{
		// ���ʹ�ư ���� ȣ��
		pPriorityUI->LButtonDown();

		// ������ �߻��ϸ� �ش� UI �� ��Ŀ�̵� UI �� ����ó�� �Ѵ�.
		ChangeFocusedUI(pFocusedUI);
	}
	// ���� ��ư�� ������, �װ� �ش� UI �ȿ�����
	else if (LBtnReleased)
	{
		// ���ʹ�ƴ �� ȣ��
		pPriorityUI->LButtonUp();
		// ������ ���ʹ�ư�� �������� ������
		if (pPriorityUI->IsLbtnDowned())
		{
			// ���ʹ�ư Ŭ�� ȣ��
			pPriorityUI->LButtonClicked();
		}
	}
}

CUI* CUIMgr::GetPriorityUI(CUI* _UI)
{
	static list<CUI*> queue;
	queue.clear();

	CUI* pPriorityUI = nullptr;


	queue.push_back(_UI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			pPriorityUI = pUI;

			const vector<CUI*>& vecChildUI = pUI->GetChildUI();
			for (size_t i = 0; i < vecChildUI.size(); ++i)
			{
				queue.push_back(vecChildUI[i]);
			}
		}
	}

	return pPriorityUI;
}

void CUIMgr::ChangeFocusedUI(CUI* _UI)
{
	if (m_FocusedUI == _UI)
		return;

	m_FocusedUI = _UI;

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	vector<CObject*>& vecUI = pCurLevel->m_arrObj[(UINT)LAYER_TYPE::UI];
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if ((*iter) == _UI)
		{
			vecUI.erase(iter);
			vecUI.push_back(_UI);
			break;
		}
	}
}
